import paho.mqtt.client as mqtt
import time
import threading
import piplates.DAQCplate as DAQC

#----------INPUTS

p0_max_pressure = 5000
p0_volt_range_low = 1
p0_volt_range_high = 5

p1_max_pressure = 10000
p1_volt_range_low = 1
p1_volt_range_high = 5

p2_max_pressure = 300
p2_volt_range_low = 1
p2_volt_range_high = 5

p3_max_pressure = 1500
p3_volt_range_low = .5
p3_volt_range_high = 4.5

#----------------

HOST = "192.168.0.10"
TOPIC_1 = "RELAY"
TOPIC_2 = "DATA"
TOPIC_3 = "STATE"

print("\nDAQC Server Ready.")
print("\nWaiting to establish connection....\n")

def on_connect(client, userdata, flags, rc):
	print("Connected with result code "+str(rc))
	error = rc
	return error

def on_disconnect(client, userdata,rc=0):
	print("Connection Lost.")
	client.loop_stop()

def on_message(client, userdata, msg):
	calldata(str(msg.payload))

client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message
client.on_disconnect = on_disconnect
client.connect(HOST, 1883, 60)
client.loop_start()

print("Connection Established")

def formula(data, max_pressure, low_volt, high_volt, tof):
	volt_range = high_volt - low_volt
	if tof:
		data = data*2
	result = str((max_pressure/volt_range)*(data-low_volt))
	return result

def compare(type_,data):
	#if type 0, nothing connected
	#if type 1, goes to 0
	#if type 2, goes to 2
	if type_ == 0:
		return '0'
	if type_ == 1:
		return data < 1
	if type_ == 2:
		return data >= 1
	if type_ == 3:
		return data <= 1

f = open("Cryo4_17.txt", "w+")
f2 = open("Cryo4_17_2.txt", "w+")

while(1):
		r0 = compare(3, DAQC.getADC(1,0))  # IGN key
		r1 = compare(2, DAQC.getADC(1,1))  # Press Key
		r2 = DAQC.getDINbit(1,0)           # IGN state
		r3 = compare(2, DAQC.getADC(1,3))  # Launch key
		r4 = compare(2, DAQC.getADC(1,4))  # MPV switch
		r5 = DAQC.getDINbit(1,1)           # CH4 state
		r6 = compare(3, DAQC.getADC(1,6))  # IGN switch
		r7 = DAQC.getDINbit(1,2)           # LOX state

		f.write('{}, {}, {}, {}, {}, {}, {}, {}, {}, {}\n'.format(time.strftime("%H:%M:%S"),time.strftime("%d:%m:%Y"),r0,r1,r2,r3,r4,r5,r6,r7))
		client.publish(TOPIC_3,b'{},{},{},{},{},{},{},{}'.format(r0,r1,r2,r3,r4,r5,r6,r7))
		print('{}, {}, {}, {}, {}, {}, {}, {}\r'.format(r0,r1,r2,r3,r4,r5,r6,r7))
		#Pressure 0 Formula
		v0 = DAQC.getADC(0,0)
		if type(p0_max_pressure) == type('str'):
			pressure_0 = '0'
		else:
			pressure_0 = formula(v0, p0_max_pressure, p0_volt_range_low, p0_volt_range_high, 1)

		#Pressure 1 Formula
		v1 = DAQC.getADC(0,1)
		if type(p1_max_pressure) == type('str'):
			pressure_1 = '0'
		else:
			pressure_1 = formula(v1, p1_max_pressure, p1_volt_range_low, p1_volt_range_high, 0)

		#Pressure 2 Formula
		v2 = DAQC.getADC(0,2)
		if type(p2_max_pressure) == type('str'):
			pressure_2 = '0'
		else:
			pressure_2 = formula(v2, p2_max_pressure, p2_volt_range_low, p2_volt_range_high, 0)

		#Pressure 3 Formula
		v3 = DAQC.getADC(0,3)
		if type(p3_max_pressure) == type('str'):
			pressure_3 = '0'
		else:
			pressure_3 = formula(v3, p3_max_pressure, p3_volt_range_low, p3_volt_range_high, 0)

		v4 = DAQC.getADC(0,4)
		ch4_hall = compare(2, v4)

		v5 = DAQC.getADC(0,5)
		lox_hall = compare(2, v5)

		f2.write('{}, {}, {}, {}, {}, {}, {}, {}\n'.format(time.strftime("%H:%M:%S"),time.strftime("%d:%m:%Y"),pressure_0,pressure_1,pressure_2,pressure_3,ch4_hall,lox_hall))
		client.publish(TOPIC_2,b'{},{},{},{},{},{}'.format(pressure_0,pressure_1,pressure_2,pressure_3,ch4_hall,lox_hall))
		print('{}, {}, {}, {}, {}, {}\r'.format(pressure_0,pressure_1,pressure_2,pressure_3,ch4_hall,lox_hall))

		time.sleep(0.1)

f.close()
f2.close()
