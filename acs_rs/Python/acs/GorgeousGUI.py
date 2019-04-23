from PyQt5 import QtCore, QtWidgets, QtGui, Qt, uic
import sys
import time
from os import path
import paho.mqtt.client as mqtt
import paho.mqtt.publish as publish
import paho.mqtt.subscribe as subscribe
from PyQt5.QtGui import *
from PyQt5.QtCore import *
from PyQt5.QtWidgets import *
from PyQt5.uic import loadUiType
from PyQt5.QtCore import QThread, pyqtSignal
import RPi.GPIO as GPIO
import threading

qtCreatorFile = "RocketGUIv2.ui" # Import .UI file
Ui_MainWindow, QtBaseClass = uic.loadUiType(qtCreatorFile) # Load .UI file

HOST = "192.168.0.10" # Declare connection and topic information
port = 1883
TOPIC_1 = "RELAY"
TOPIC_2 = "DATA"
TOPIC_3 = "STATE"

GPIO.setmode(GPIO.BCM) # Setup Pins for Buzzer
GPIO.setup(21, GPIO.OUT)
GPIO.output(21, 1)

class mainthread(QThread): # Data and state communications class
    STATEsignal = pyqtSignal('PyQt_PyObject') # Declare signals to be emmitted from Mainthread to MainApp
    DATAsignal = pyqtSignal('PyQt_PyObject')
    disconnectSignal = pyqtSignal('PyQt_PyObject')

    def __init__(self): # PyQT initialization function
        QThread.__init__(self)
        self.connect1()

    def connect1(self): # Connect to RS Pi
        self.mqtt_client = mqtt.Client()
        self.mqtt_client.on_connect = self.on_connect # Does This when connected
        self.mqtt_client.on_disconnect = self.on_disconnect # Does this when disconnected
        self.mqtt_client.connect(HOST, port=port, keepalive=4) # Connect to Pi
        self.mqtt_client.loop_start() # Start Reciving data

    def on_disconnect(self, mqtt_client, userdata, flags, rc=0): # What to do when disconnected
        connectionFlag = 0
        self.disconnectSignal.emit(connectionFlag) # When disconnected send connection flag to alert function
        print("disconnected") 

    def on_connect(self, mqtt_client, userdata, flags, rc): # What to do when reconnected
        self.mqtt_client.on_message = self.subscrib1 # Call subscrib1 to start reading data when a message is recieved
        self.mqtt_client.subscribe(TOPIC_2) 
        self.mqtt_client.subscribe(TOPIC_3)
        connectionFlag = 1
        self.disconnectSignal.emit(connectionFlag)
        print("connected")

    def subscrib1(self, mqtt_client, userdata, msg): # What to do when message is recieved
        try:
            if msg.topic == "DATA": 
                D = str(msg.payload)[2:-1] # Get rid of excess delimiters
                C = (D.split(',')[0], D.split(',')[1], D.split(',')[2], D.split(',')[3], D.split(',')[4], D.split(',')[5]) # Tokenizing into array
                C = ('%4s' % C[0], '%4s' % C[1], '%4s' % C[2], '%4s' % C[3], '%4s' % C[4], '%4s' % C[5]) # Truncating
                self.DATAsignal.emit(C)
                print(C)
            if msg.topic == "STATE":
                B = str(msg.payload)[2:-1]
                A = (B.split(',')[0], B.split(',')[1], B.split(',')[2], B.split(',')[3], B.split(',')[4], B.split(',')[5], B.split(',')[6], B.split(',')[7])
                A = ('%4s' % A[0], '%4s' % A[1], '%4s' % A[2], '%4s' % A[3], '%4s' % A[4], '%4s' % A[5], '%4s' % A[6], '%4s' % A[7],)
                self.STATEsignal.emit(A)
        except:
            print('Missed Data')

class MainApp(QtWidgets.QMainWindow, Ui_MainWindow): # PyQT class
    def __init__(self, parent=None): # Initialization function
        super(MainApp, self).__init__(parent) # Set Mainapp as parent
        QMainWindow.__init__(self) 
        self.setupUi(self) 
        self.mythread1 = mainthread() # Threading to Mainthread
        self.init_ui()
        self.Alert1.hide() 
        self.label_6.hide()
        self.mythread1.STATEsignal.connect(self.progress1) # Connect signals from Mainthread to coresponding functions
        self.mythread1.DATAsignal.connect(self.progress2)
        self.mythread1.disconnectSignal.connect(self.alert)
        self.checkBox.toggled.connect(self.radio4) # When checkbox is clicked call radio 4
        self.checkBox_2.toggled.connect(self.record) # Start recoding

    def init_ui(self): # Start Mainthread
        self.mythread1.start()
#------State color set----------
    def progress1(self, A): # Set state colors
        self.Pressure_Key.setAutoFillBackground(True) # Used for PyQt to set backround colors
        self.Ign_Safety.setAutoFillBackground(True)
        self.MPV_Safety.setAutoFillBackground(True)
        self.MPV_Key.setAutoFillBackground(True)
        self.Ign_Key.setAutoFillBackground(True)
        self.ign_state.setAutoFillBackground(True)
        self.ch4_state.setAutoFillBackground(True)
        self.lox_state.setAutoFillBackground(True)
        try:
#-----------------IGN KEY------------------------------------
            if int(A[0]): # Set colors of state displays
                p1 = self.Ign_Key.palette()
                p1.setColor(self.Ign_Key.backgroundRole(), Qt.red)
                self.Ign_Key.setPalette(p1)
            else:
                p2 = self.Ign_Key.palette()
                p2.setColor(self.Ign_Key.backgroundRole(), Qt.white)
                self.Ign_Key.setPalette(p2)
#-----------------Pressure KEY--------------------------------
            if int(A[1]):
                p1 = self.Pressure_Key.palette()
                p1.setColor(self.Pressure_Key.backgroundRole(), Qt.red)
                self.Pressure_Key.setPalette(p1)
            else:
                p2 = self.Pressure_Key.palette()
                p2.setColor(self.Pressure_Key.backgroundRole(), Qt.white)
                self.Pressure_Key.setPalette(p2)
#-----------------IGN STATE------------------------------------
            if int(A[2]):
                p1 = self.ign_state.palette()
                p1.setColor(self.ign_state.backgroundRole(), Qt.white)
                self.ign_state.setPalette(p1)
            else:
                p2 = self.ign_state.palette()
                p2.setColor(self.ign_state.backgroundRole(), Qt.red)
                self.ign_state.setPalette(p2)
#-----------------MPV KEY------------------------------------
            if int(A[3]):
                p1 = self.MPV_Key.palette()
                p1.setColor(self.MPV_Key.backgroundRole(), Qt.red)
                self.MPV_Key.setPalette(p1)
            else:
                p2 = self.MPV_Key.palette()
                p2.setColor(self.MPV_Key.backgroundRole(), Qt.white)
                self.MPV_Key.setPalette(p2)
#-----------------MPV SAFETY---------------------------------
            if int(A[4]):
                p1 = self.MPV_Safety.palette()
                p1.setColor(self.MPV_Safety.backgroundRole(), Qt.red)
                self.MPV_Safety.setPalette(p1)
            else:
                p2 = self.MPV_Safety.palette()
                p2.setColor(self.MPV_Safety.backgroundRole(), Qt.white)
                self.MPV_Safety.setPalette(p2)
#-----------------CH4 STATE------------------------------------
            if int(A[5]):
                p1 = self.ch4_state.palette()
                p1.setColor(self.ch4_state.backgroundRole(), Qt.white)
                self.ch4_state.setPalette(p1)
            else:
                p2 = self.ch4_state.palette()
                p2.setColor(self.ch4_state.backgroundRole(), Qt.red)
                self.ch4_state.setPalette(p2)
#-----------------IGN SAFTEY----------------------------------
            if int(A[6]):
                p1 = self.Ign_Safety.palette()
                p1.setColor(self.Ign_Safety.backgroundRole(), Qt.red)
                self.Ign_Safety.setPalette(p1)
            else:
                p2 = self.Ign_Safety.palette()
                p2.setColor(self.Ign_Safety.backgroundRole(), Qt.white)
                self.Ign_Safety.setPalette(p2)
#-----------------LOX STATE----------------------------------
            if int(A[7]):
                p1 = self.lox_state.palette()
                p1.setColor(self.lox_state.backgroundRole(), Qt.white)
                self.lox_state.setPalette(p1)
            else:
                p2 = self.lox_state.palette()
                p2.setColor(self.lox_state.backgroundRole(), Qt.red)
                self.lox_state.setPalette(p2)
        except:
            pass
#------Set Progress bar values and Readout values/colors----------
    def progress2(self, C): # Set progress bars and readouts for pressure data
        try:
            self.Readout0.display(C[1]) # Display Pessure data in readouts
            self.Readout1.display(C[0])
            self.Readout2.display(C[2])
            self.Readout3.display(C[3])
            self.TReadout_2.display(C[4])
            self.TReadout.display(C[5])
            self.Readout0.setAutoFillBackground(True)
            self.Readout1.setAutoFillBackground(True)
            self.Readout2.setAutoFillBackground(True)
            self.Readout3.setAutoFillBackground(True)
            p = self.Readout0.palette()
            c = self.Readout1.palette()
            h = self.Readout2.palette()
            k = self.Readout3.palette()
#------HE_BOTTLE-------
            if float(C[1]) >= 4500: # Set Progress bar values for pressure data and change readout color based on value
                p.setColor(self.Readout0.backgroundRole(), Qt.red)
                self.Readout0.setPalette(p)
                self.progressBar0.setValue(4500)
            if 3500 <= float(C[1]) < 4500:
                p.setColor(self.Readout0.backgroundRole(), Qt.green)
                self.Readout0.setPalette(p)
                self.progressBar0.setValue(float(C[1]))
            else:
                p.setColor(self.Readout0.backgroundRole(), Qt.white)
                self.Readout0.setPalette(p)
                self.progressBar0.setValue(float(C[1]))
#------HE_REG--------
            if float(C[0]) >= 4500:
                c.setColor(self.Readout1.backgroundRole(), Qt.red)
                self.Readout1.setPalette(c)
                self.progressBar1.setValue(4500)
            if 3500 <= float(C[0]) < 4500:
                c.setColor(self.Readout1.backgroundRole(), Qt.green)
                self.Readout1.setPalette(c)
                self.progressBar1.setValue(float(C[0]))
            else:
                c.setColor(self.Readout1.backgroundRole(), Qt.white)
                self.Readout1.setPalette(c)
                self.progressBar1.setValue(float(C[0]))
#------PNU-------
            if float(C[2]) > 160:
                h.setColor(self.Readout2.backgroundRole(), Qt.red)
                self.Readout2.setPalette(h)
                self.progressBar2.setValue(150)
            if 135 <= float(C[2]) <= 150:
                h.setColor(self.Readout2.backgroundRole(), Qt.green)
                self.Readout2.setPalette(h)
                self.progressBar2.setValue(float(C[2]))
            if 150 < float(C[2]) <= 160:
                h.setColor(self.Readout2.backgroundRole(), Qt.green)
                self.Readout2.setPalette(h)
                self.progressBar2.setValue(150)
            else:
                h.setColor(self.Readout2.backgroundRole(), Qt.white)
                self.Readout2.setPalette(h)
                self.progressBar2.setValue(float(C[2]))
#------Extra-------                
            if float(C[3]) >= 4500:
                k.setColor(self.Readout3.backgroundRole(), Qt.red)
                self.Readout3.setPalette(k)
                self.progressBar3.setValue(4500)
            else:
                k.setColor(self.Readout3.backgroundRole(), Qt.white)
                self.Readout3.setPalette(k)
                self.progressBar3.setValue(float(C[3]))
        except:
            pass

#------Check Box Functions--------
    def radio4(self): # When checkbox cliked hide uneccesary readouts and reshape display
        self.pstate_label_7.hide()
        self.pstate_label_6.hide()
        self.TReadout.hide()
        self.TReadout_2.hide()
        self.beepCall(1)
        self.progressBar3.hide()
        self.pstate_label_5.hide()
        self.Readout3.hide()
        self.label_5.hide()
        self.progressBar2.move(130, 365)
        self.Readout2.move(20, 350)
        self.label_4.move(130, 345)
        self.pstate_label_4.move(350, 330)
        self.pstate_label_3.move(350, 225)
        self.progressBar1.move(130, 265)
        self.label_3.move(130, 245)
        self.Readout1.move(20, 250)
        self.label_7.move(707, 245)
        self.label_8.move(707, 325)
        if self.checkBox.isChecked() == False:
            self.radio5()

    def radio5(self): # When Checkbox unclicked show extra readouts and move all to original spots
        self.pstate_label_7.show()
        self.pstate_label_6.show()
        self.TReadout.show()
        self.TReadout_2.show()
        self.progressBar3.show()
        self.pstate_label_5.show()
        self.Readout3.show()
        self.label_5.show()
        self.progressBar2.move(130, 325)
        self.Readout2.move(20, 310)
        self.label_4.move(130, 305)
        self.pstate_label_4.move(350, 290)
        self.pstate_label_3.move(350, 205)
        self.progressBar1.move(130, 245)
        self.label_3.move(130, 225)
        self.Readout1.move(20, 230)
        self.label_7.move(707, 225)
        self.label_8.move(707, 305)

    def beepCall(self, x): # Thread to beep function
        t1 = threading.Thread(target = self.beep(x))
        t1.start()

    def beep(self, x): # beep for .5 seconds
        if x == 1:
             GPIO.output(21, 0)
             time.sleep(0.5)
             GPIO.output(21,1)

#------Disconnected alert -------
    def alert(self, connectionFlag): # Called when disconnected show alerts
        if connectionFlag == 1:
            self.Alert1.hide()
            self.label_6.hide()
        if connectionFlag == 0:
            self.Alert1.show()
            self.label_6.show()
            self.beepCall(1)

    def record(self):
        filename = self.lineEdit.text()
        f = open(filename, "w+")
        f.write('{},{},{},{}\n'.format(time.strftime("%H:%M:%S"),time.strftime("%d:%m:%Y"),C,A))
        if self.checkBox_2.isChecked() == False:
            self.stopRecording()

    def stopRecording():
        f.close()

def main():
    app = QApplication(sys.argv) # start PyQT
    window = MainApp()
    window.show()
    app.exec_()

if __name__ == '__main__': # run PyQT
    main()