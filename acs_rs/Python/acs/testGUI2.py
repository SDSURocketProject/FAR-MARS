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
from PyQt5.QtCore import QThread, pyqtSignal, QPropertyAnimation

qtCreatorFile = "RocketGUI1.ui"
Ui_MainWindow, QtBaseClass = uic.loadUiType(qtCreatorFile)

HOST = "192.168.0.10"
port = 1883
TOPIC_1 = "RELAY"
TOPIC_2 = "DATA"
TOPIC_3 = "STATE"

class mainthread(QThread):
    STATEsignal = pyqtSignal('PyQt_PyObject')
    DATAsignal = pyqtSignal('PyQt_PyObject')

    def __init__(self):
        QThread.__init__(self)
        self.connect1()

    def connect1(self):
        self.mqtt_client = mqtt.Client()
        self.mqtt_client.on_message = self.subscrib1
        self.mqtt_client.connect(HOST, port=port, keepalive=60)
        self.mqtt_client.subscribe(TOPIC_2)
        self.mqtt_client.subscribe(TOPIC_3)
        self.mqtt_client.loop_start()
        print("connected")

    def subscrib1(self, mqtt_client, userdata, msg):
        try:
            if msg.topic == "DATA":
                D = str(msg.payload)[2:-1]
                C = (D.split(',')[0], D.split(',')[1], D.split(',')[2], D.split(',')[3])
                C = ('%4s' % C[0], '%4s' % C[1], '%4s' % C[2], '%4s' % C[3])
                self.DATAsignal.emit(C)
                print(C)
            if msg.topic == "STATE":
                B = str(msg.payload)[2:-1]
                A = (B.split(',')[0], B.split(',')[1], B.split(',')[2], B.split(',')[3], B.split(',')[4], B.split(',')[5], B.split(',')[6])
                A = ('%4s' % A[0], '%4s' % A[1], '%4s' % A[2], '%4s' % A[3], '%4s' % A[4], '%4s' % A[5], '%4s' % A[6],)
                self.STATEsignal.emit(A)
        except:
            print('Missed Data')

class MainApp(QtWidgets.QMainWindow, Ui_MainWindow):
    def __init__(self, parent=None):
        super(MainApp, self).__init__(parent)
        QMainWindow.__init__(self)
        self.setupUi(self)
        self.mythread1 = mainthread()
        self.init_ui()
        self.Alert1.hide()
        self.label_6.hide()
        self.mythread1.STATEsignal.connect(self.progress1)
        self.mythread1.DATAsignal.connect(self.progress2)        
        #self.radioButton1.toggled.connect(self.radio1)
        #self.radioButton2.toggled.connect(self.radio2)
        #self.radioButton3.toggled.connect(self.radio3)
        self.radioButton1.hide()
        self.radioButton2.hide()
        self.radioButton3.hide()
        self.checkBox.toggled.connect(self.radio4)

    def init_ui(self):
        self.mythread1.start()
#------State color set-----------
    def progress1(self, A):
        self.Pressure_Key.setAutoFillBackground(True)
        self.Ign_Safety.setAutoFillBackground(True)
        self.MPV_Safety.setAutoFillBackground(True)
        self.MPV_Key.setAutoFillBackground(True)
        self.Ign_Key.setAutoFillBackground(True)
        try:
            if int(A[1]) == 1:
                p1 = self.Pressure_Key.palette()
                p1.setColor(self.Pressure_Key.backgroundRole(), Qt.red)
                self.Pressure_Key.setPalette(p1)
            if int(A[1]) == 0:
                p2 = self.Pressure_Key.palette()
                p2.setColor(self.Pressure_Key.backgroundRole(), Qt.white)
                self.Pressure_Key.setPalette(p2)
            if int(A[6]) == 1:
                p1 = self.Ign_Safety.palette()
                p1.setColor(self.Ign_Safety.backgroundRole(), Qt.red)
                self.Ign_Safety.setPalette(p1)
            if int(A[6]) == 0:
                p2 = self.Ign_Safety.palette()
                p2.setColor(self.Ign_Safety.backgroundRole(), Qt.white)
                self.Ign_Safety.setPalette(p2)
            if int(A[4]) == 1:
                p1 = self.MPV_Safety.palette()
                p1.setColor(self.MPV_Safety.backgroundRole(), Qt.red)
                self.MPV_Safety.setPalette(p1)
            if int(A[4]) == 0:
                p2 = self.MPV_Safety.palette()
                p2.setColor(self.MPV_Safety.backgroundRole(), Qt.white)
                self.MPV_Safety.setPalette(p2)
            if int(A[3]) == 1:
                p1 = self.MPV_Key.palette()
                p1.setColor(self.MPV_Key.backgroundRole(), Qt.red)
                self.MPV_Key.setPalette(p1)
            if int(A[3]) == 0:
                p2 = self.MPV_Key.palette()
                p2.setColor(self.MPV_Key.backgroundRole(), Qt.white)
                self.MPV_Key.setPalette(p2)
            if int(A[0]) == 1:
                p1 = self.Ign_Key.palette()
                p1.setColor(self.Ign_Key.backgroundRole(), Qt.red)
                self.Ign_Key.setPalette(p1)
            if int(A[0]) == 0:
                p2 = self.Ign_Key.palette()
                p2.setColor(self.Ign_Key.backgroundRole(), Qt.white)
                self.Ign_Key.setPalette(p2)
        except:
            pass
#------Set Progress bar values and Readout values/colors----------
    def progress2(self, C):
        try:
            self.Readout0.display(C[1])
            self.Readout1.display(C[0])
            self.Readout2.display(C[2])
            self.Readout3.display(C[3])
#------HE_BOTTLE-------
            if float(C[1]) >= 4500:
                self.Readout0.setAutoFillBackground(True)
                p = self.Readout0.palette()
                p.setColor(self.Readout0.backgroundRole(), Qt.red)
                self.Readout0.setPalette(p)
                self.progressBar0.setValue(4500)
            if 3500 <= float(C[1]) < 4500:
                self.Readout0.setAutoFillBackground(True)
                p = self.Readout0.palette()
                p.setColor(self.Readout0.backgroundRole(), Qt.green)
                self.Readout0.setPalette(p)
                self.progressBar0.setValue(float(C[1]))
            if float(C[1]) < 3500:
                self.Readout0.setAutoFillBackground(True)
                p = self.Readout0.palette()
                p.setColor(self.Readout0.backgroundRole(), Qt.white)
                self.Readout0.setPalette(p)
                self.progressBar0.setValue(float(C[1]))
#------HE_REG--------
            if float(C[0]) >= 4500:
                self.Readout1.setAutoFillBackground(True)
                c = self.Readout1.palette()
                c.setColor(self.Readout1.backgroundRole(), Qt.red)
                self.Readout1.setPalette(c)
                self.progressBar1.setValue(4500)
            if 3500 <= float(C[0]) < 4500:
                self.Readout1.setAutoFillBackground(True)
                c = self.Readout1.palette()
                c.setColor(self.Readout1.backgroundRole(), Qt.green)
                self.Readout1.setPalette(c)
                self.progressBar1.setValue(float(C[0]))
            if float(C[0]) < 3500:
                self.Readout1.setAutoFillBackground(True)
                c = self.Readout1.palette()
                c.setColor(self.Readout1.backgroundRole(), Qt.white)
                self.Readout1.setPalette(c)
                self.progressBar1.setValue(float(C[0]))
#------PNU-------
            if float(C[2]) > 150:
                self.Readout2.setAutoFillBackground(True)
                h = self.Readout2.palette()
                h.setColor(self.Readout2.backgroundRole(), Qt.red)
                self.Readout2.setPalette(h)
                self.progressBar2.setValue(150)
            if 135 <= float(C[2]) <= 150:
                self.Readout2.setAutoFillBackground(True)
                h = self.Readout2.palette()
                h.setColor(self.Readout2.backgroundRole(), Qt.green)
                self.Readout2.setPalette(h)
                self.progressBar2.setValue(float(C[2]))
            if float(C[2]) < 135:
                self.Readout2.setAutoFillBackground(True)
                h = self.Readout2.palette()
                h.setColor(self.Readout2.backgroundRole(), Qt.white)
                self.Readout2.setPalette(h)
                self.progressBar2.setValue(float(C[2]))
#------Extra-------                
            if float(C[3]) >= 4500:
                self.Readout3.setAutoFillBackground(True)
                k = self.Readout3.palette()
                k.setColor(self.Readout3.backgroundRole(), Qt.red)
                self.Readout3.setPalette(k)
                self.progressBar3.setValue(4500)
            if float(C[3]) < 4500:
                self.Readout3.setAutoFillBackground(True)
                k = self.Readout3.palette()
                k.setColor(self.Readout3.backgroundRole(), Qt.white)
                self.Readout3.setPalette(k)
                self.progressBar3.setValue(float(C[3]))
        except:
            pass

#------Radio button functions (no need for SHF)----------
    def radio1(self):
        self.progressBar0.setMaximum(300)
        self.label_2.setText('300 PSI')

    def radio2(self):
        self.progressBar0.setMaximum(4500)
        self.label_2.setText('4500 PSI')

    def radio3(self):
        self.progressBar0.setMaximum(500)
        self.label_2.setText('500 PSI')
#------Check Box Functions--------
    def radio4(self):
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

    def radio5(self):
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
#------Disconnected alert -------
    def alert(self):
        self.Alert1.show()
        self.label_6.show()

def main():
    app = QApplication(sys.argv)
    window = MainApp()
    window.show()
    t1 = threading.Thread(target=switch_loop, args=(1, ))
    t1.start()
    app.exec_()

if __name__ == '__main__':
    main()