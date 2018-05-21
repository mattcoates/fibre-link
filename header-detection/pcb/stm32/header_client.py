#!/usr/bin/env python3

import sys
import struct
import serial
import numpy as np

# Useage
if len(sys.argv) != 2:
    print("Usage: {} /dev/ttyACMx".format(sys.argv[0]))
    sys.exit(1)

# Message Type Definitions
MESSAGE_COUNTS = 1 


# Open Serial Port
ser = serial.Serial(sys.argv[1])
print("Listening on", ser.name)

# Fetch & Decode
while True:

    # Read in a Log
    data = ser.read(128)
      
    # Get Message Metadata
    meta_data = struct.unpack('<BI', data[0:5])
    log_type = meta_data[0]
    systick = meta_data[1]
    systick /= 10000.0
    
    
    
    if(log_type == MESSAGE_COUNTS):
    
        # Extract Timestamp
        payload = data[5:9]
        counts = struct.unpack('<I', payload)
        print("Time = ", systick, "Counts = ", counts[0])

