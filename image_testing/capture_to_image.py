import sys  
import os
import struct
import numpy as np
import pandas as pd

if len(sys.argv) != 3:
    print("Usage: {} /input.csv /output.ppm".format(sys.argv[0]))
    sys.exit(1)

inpath = sys.argv[1]
outpath = sys.argv[2]

if not os.path.isfile(inpath):
    print("File path {} does not exist. Exiting...".format(inpath))
    sys.exit()

# Open Output File 
out = open(outpath,'wb')

# Open CSV and Read MOSI Column
df = pd.read_csv(inpath)
data = df.MOSI
num_bytes = len(data)


for i in range (0, num_bytes):
    out.write(bytes([int(data[i][4:8] + data[i][10:14],2)]))
