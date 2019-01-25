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
ax1.plot(data['time'], data['tc1'], label='tc1')
ax1.plot(data['time'], data['tc2'], label='tc2')
ax1.plot(data['time'], data['tc3'], label='tc3')
ax1.plot(data['time'], data['tc4'], label='tc4')
ax1.plot(data['time'], data['tc5'], label='tc5')
ax1.plot(data['time'], data['tc6'], label='tc6')
ax1.plot(data['time'], data['tc7'], label='tc7')
ax1.plot(data['time'], data['tc8'], label='tc8')
ax1.plot(data['time'], data['pt1'], label='pt1')
ax1.plot(data['time'], data['pt2'], label='pt2')
plt.xlabel('Time (ms)')
plt.ylabel('Value')
plt.legend(loc='best')
plt.grid(True)
plt.show()
