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
    ax1.plot(data['TIME'], data['CH4'], label='CH4')
    ax1.plot(data['TIME'], data['LOX'], label='LOX')
    ax1.plot(data['TIME'], data['HEL'], label='HEL')
    ax1.plot(data['TIME'], data['CBR'], label='CBR')
except ValueError:
    print('CSV headers not prepended. Run the data_preparation.py script to fix this.')
    quit()
plt.xlabel('Time (ms)')
plt.ylabel('Pressure (psi)')
plt.legend(loc='best')
plt.grid(True)
plt.show()
