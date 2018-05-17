import sys  
import os
import numpy as np

# Set Saleae Logic to decode with 15-bits per transfer 

if len(sys.argv) != 2:
    print("Usage: {} /file.txt".format(sys.argv[0]))
    sys.exit(1)

filepath = sys.argv[1]

if not os.path.isfile(filepath):
    print("File path {} does not exist. Exiting...".format(filepath))
    sys.exit()

out = open('bitstream.txt','w')

with open(filepath) as fp:
    cnt = 0
    for line in fp:
        print(line)
        out.write(format(int(line, 16), '015b'))
        cnt = cnt + 1
       
print("PRBS contains", cnt*15, "bits.")
