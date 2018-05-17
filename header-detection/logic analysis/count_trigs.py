import sys  
import os
import numpy as np

if len(sys.argv) != 2:
    print("Usage: {} /input_stream.txt".format(sys.argv[0]))
    sys.exit(1)

inpath = sys.argv[1]

if not os.path.isfile(inpath):
    print("File path {} does not exist. Exiting...".format(inpath))
    sys.exit()
      
 
count = 0
 
with open(inpath) as f:
  while True:
    c = f.read(1)
    if not c:
      break
    if(c=='1'):
        count += 1
        
print(count, 'Trigger Events Detected')
