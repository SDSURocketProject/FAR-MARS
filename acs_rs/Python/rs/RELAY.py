import paho.mqtt.client as mqtt
import time
import piplates.DAQCplate as RELAY

RELAY.enableDINint(1,4,'b')
RELAY.enableDINint(1,5,'b')
RELAY.enableDINint(1,6,'b')
HOST = "192.168.0.10"
TOPIC_1 = "RELAY"
TOPIC_3 = "STATE"

print("\nRelay Server Ready.")
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

print("Connection Established")

def lox_mpv_open():
	x = 0
	while x<5:
		RELAY.setDOUTbit(1,4)
		x += 1
#	print("lox_open")
	return

def lox_mpv_close():
	x = 0
	while x<5:
		RELAY.clrDOUTbit(1,4)
		x += 1
#	print("lox_close")
	return

def ch4_mpv_open():
	x = 0
	while x<5:
		RELAY.setDOUTbit(1,5)
		x += 1
#	print("ch4_open")
	return

def ch4_mpv_close():
	x = 0
	while x<5:
		RELAY.clrDOUTbit(1,5)
		x += 1
#	print("ch4_close")
	return

def ignitor_on():
	x = 0
	while x<5:
		RELAY.setDOUTbit(1,6)
		x += 1
#	print("ignitor on")
	return

def ignitor_off():
	x = 0
	while x<5:
		RELAY.clrDOUTbit(1,6)
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

client.loop_forever()
