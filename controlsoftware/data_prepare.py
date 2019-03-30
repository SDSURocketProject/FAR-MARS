import sys

filename = sys.argv[1]

with open(filename, 'r') as original: data = original.read()
with open(filename, 'w') as modified: modified.write("TIME,CH4,LOX,HEL,CBR,UAF\n" + data)
