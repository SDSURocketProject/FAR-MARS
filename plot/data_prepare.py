import sys

filename = sys.argv[1]

with open(filename, 'r') as original: data = original.read()
with open(filename, 'w') as modified: modified.write("TIME,BRD,CH4,LOX,HEL,CBR,REG,UAF,HALLCH4,HALLLOX,BAT\n" + data)
