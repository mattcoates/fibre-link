import sys  
import os
import numpy as np

if len(sys.argv) != 3:
    print("Usage: {} /input.txt /output.txt".format(sys.argv[0]))
    sys.exit(1)

inpath = sys.argv[1]
outpath = sys.argv[2]

if not os.path.isfile(inpath):
    print("File path {} does not exist. Exiting...".format(inpath))
    sys.exit()

out = open(outpath,'w')

with open(inpath) as fp:

    for line in fp:
        print(line[4:8] + line[10:14])
        out.write(line[4:8] + line[10:14])
