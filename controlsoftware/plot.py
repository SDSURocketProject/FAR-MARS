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
ax1.plot(data['time'], data['CH4'], label='CH4')
ax1.plot(data['time'], data['LOX'], label='LOX')
ax1.plot(data['time'], data['HEL'], label='HEL')
plt.xlabel('Time (ms)')
plt.ylabel('Pressure (psi)')
plt.legend(loc='best')
plt.grid(True)
plt.show()
