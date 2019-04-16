import sys
import matplotlib as mpl
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.cbook as cbook

try:
    data = np.genfromtxt(sys.argv[1], delimiter=',', names = True)
except IndexError:
    print('usage: python plot.py <path/to/csv>')
    quit()

fig = plt.figure()
ax1 = fig.add_subplot(111)
try:
    ax1.plot(data['TIME'], data['CH4'], label='CH4 Tank')
    ax1.plot(data['TIME'], data['LOX'], label='LOX Tank')
    ax1.plot(data['TIME'], data['HEL'], label='HEL Tank')
    ax1.plot(data['TIME'], data['CBR'], label='Chamber Pressure')
    ax1.plot(data['TIME'], data['REG'], label='Helium Regulator')
    ax1.plot(data['TIME'], data['UAF'], label='Upper Airframe')
    ax1.plot(data['TIME'], data['BAT'], label='Battery Voltage')
except ValueError:
    print('CSV headers not prepended. Run the data_preparation.py script to fix this.')
    quit()

hallarr = [0,0]

with open(sys.argv[1]) as f:
    for line in f:
        arr = line.split(',')
        if hallarr[0] != arr[7]:
            hallarr[0] = arr[7]
            plt.axvline(x=arr[0])
        if hallarr[1] != arr[8]:
            hallarr[1] = arr[8]
            plt.axvline(x=arr[0])

plt.xlabel('Time (ms)')
plt.ylabel('Pressure (psi) \ Temperature (C) \ Voltage (V)')
plt.legend(loc='best')
plt.grid(True)
plt.show()
