import paho.mqtt.client as mqtt
import time
import threading
import piplates.DAQCplate as DAQC

#----------INPUTS

p0_max_pressure = 10000
p0_volt_range_low = 1
p0_volt_range_high = 5

p1_max_pressure = 5800
p1_volt_range_low = 1
p1_volt_range_high = 5

p2_max_pressure = 300
p2_volt_range_low = 1
p2_volt_range_high = 5

p3_max_pressure = 'none'
p3_volt_range_low = 'none'
p3_volt_range_high = 'none'

#----------------

DAQC.enableDINint(1,4,'b')
DAQC.enableDINint(1,5,'b')
DAQC.enableDINint(1,6,'b')

HOST = "192.168.0.10"
TOPIC_1 = "RELAY"
TOPIC_2 = "DATA"
TOPIC_3 = "STATE"

print("\nDAQC Server Ready.")
print("\nWaiting to establish connection....\n")

def on_connect(client, userdata, flags, rc):
	print("Connected with result code "+str(rc))
	client.subscribe(TOPIC_1)
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

def lox_mpv_open():
	x = 0
	while x<5:
		DAQC.setDOUTbit(1,4)
		x += 1
#	print("lox_open")
	return

def lox_mpv_close():
	x = 0
	while x<5:
		DAQC.clrDOUTbit(1,4)
		x += 1
#	print("lox_close")
	return

def ch4_mpv_open():
	x = 0
	while x<5:
		DAQC.setDOUTbit(1,5)
		x += 1
#	print("ch4_open")
	return

def ch4_mpv_close():
	x = 0
	while x<5:
		DAQC.clrDOUTbit(1,5)
		x += 1
#	print("ch4_close")
	return

def ignitor_on():
	x = 0
	while x<5:
		DAQC.setDOUTbit(1,6)
		x += 1
#	print("ignitor on")
	return

def ignitor_off():
	x = 0
	while x<5:
		DAQC.clrDOUTbit(1,6)
		x+=1
#	print("ignitor off")
	return

def launch():
	ignitor_on()
	time.sleep(2)
	ch4_mpv_open()
	time.sleep(0.25)
	lox_mpv_open()
	print("launch")
	return

def abort():
	ignitor_off()
	ch4_mpv_close()
	lox_mpv_close()
	print("abort")

def calldata(data):


	if 'LOX_MPV_OPEN' in data:
		lox_mpv_open()

	elif 'LOX_MPV_CLOSE' in data:
		lox_mpv_close()

	elif 'CH4_MPV_OPEN' in data:
		ch4_mpv_open()

	elif 'CH4_MPV_CLOSE' in data:
		ch4_mpv_close()

	elif 'IGNITOR_ON' in data:
		ignitor_on()

	elif 'IGNITOR_OFF' in data:
		ignitor_off()

	elif 'LAUNCH' in data:
		launch()

	elif 'ABORT' in data:
		abort()

def formula(data, max_pressure, low_volt, high_volt):
	volt_range = high_volt - low_volt
	result = str((max_pressure/volt_range)*(data-low_volt))
	return result

def compare(type_,data):
	#if type 0, nothing connected
	#if type 1, goes to 0
	#if type 2, goes to 2
	if type_ == 0:
		return '0'
	if type_ == 1:
		if data < 1:
			return '1'
		else:
			return '0'
	if type_ == 2:
		if data > 1:
			return '1'
		else:
			return '0'

f = open("DAQC1.txt", "w+")
f2 = open("DAQC2.txt", "w+")

i0 = DAQC.getADC(1,0)
i1 = DAQC.getADC(1,1)
i2 = DAQC.getADC(1,2)
i3 = DAQC.getADC(1,3)
i4 = DAQC.getADC(1,4)
i5 = DAQC.getADC(1,5)
i6 = DAQC.getADC(1,6)

while(1):
	try:

		#Ignitor Safety (2.5->0)
		#Pressure Safety (0->2)
		#Empty
		#MPV Safety (0->2)
		#MPV Switch (0->2)
		#Empty
		#Ignitor Switch (3->0)

		r0 = compare(1, DAQC.getADC(1,0) - i0)
		r1 = compare(2, DAQC.getADC(1,1) - i1)
		r2 = compare(0, DAQC.getADC(1,2) - i2)
		r3 = compare(2, DAQC.getADC(1,3) - i3)
		r4 = compare(2, DAQC.getADC(1,4) - i4)
		r5 = compare(0, DAQC.getADC(1,5) - i5)
		r6 = compare(1, DAQC.getADC(1,6) - i6)

		f.write('{}, {}, {}, {}, {}, {}, {}, {}, {}\n'.format(time.strftime("%H:%M:%S"),time.strftime("%d:%m:%Y"),r0,r1,r2,r3,r4,r5,r6))
		x = client.publish(TOPIC_3,b'{},{},{},{},{},{},{}'.format(r0,r1,r2,r3,r4,r5,r6), qos = 2)
		print('{}, {}, {}, {}, {}, {}, {}\r'.format(r0,r1,r2,r3,r4,r5,r6))
		x.wait_for_publish()

		#Pressure 0 Formula
		v0 = DAQC.getADC(0,0)
		if type(p0_max_pressure) == type('str'):
			pressure_0 = '0'
		else:
			pressure_0 = formula(v0, p0_max_pressure, p0_volt_range_low, p0_volt_range_high)

		#Pressure 1 Formula
		v1 = DAQC.getADC(0,1)
		if type(p1_max_pressure) == type('str'):
			pressure_1 = '0'
		else:
			pressure_1 = formula(v1, p1_max_pressure, p1_volt_range_low, p1_volt_range_high)

		#Pressure 2 Formula
		v2 = DAQC.getADC(0,2)
		if type(p2_max_pressure) == type('str'):
			pressure_2 = '0'
		else:
			pressure_2 = formula(v2, p2_max_pressure, p2_volt_range_low, p2_volt_range_high)

		#Pressure 3 Formula
		v3 = DAQC.getADC(0,3)
		if type(p3_max_pressure) == type('str'):
			pressure_3 = '0'
		else:
			pressure_3 = formula(v3, p3_max_pressure, p3_volt_range_low, p3_volt_range_high)


		f2.write('{}, {}, {}, {}, {}, {}\n'.format(time.strftime("%H:%M:%S"),time.strftime("%d:%m:%Y"),pressure_0,pressure_1,pressure_2,pressure_3))
		y = client.publish(TOPIC_2,b'{},{},{},{}'.format(pressure_0,pressure_1,pressure_2,pressure_3), qos=2)
		print('{}, {}, {}, {}\r'.format(pressure_0,pressure_1,pressure_2,pressure_3))
		y.wait_for_publish()

		time.sleep(0.2)

	except:
		print('error')
		pass

f.close()
f2.close()