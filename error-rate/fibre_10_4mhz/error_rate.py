import sys  
import os
import numpy as np

if len(sys.argv) != 3:
    print("Usage: {} /tx_stream.txt /rx_stream.txt".format(sys.argv[0]))
    sys.exit(1)

txpath = sys.argv[1]
rxpath = sys.argv[2]

if not os.path.isfile(txpath):
    print("File path {} does not exist. Exiting...".format(txpath))
    sys.exit()
    
if not os.path.isfile(rxpath):
    print("File path {} does not exist. Exiting...".format(rxpath))
    sys.exit()
      
 
bits = 0
correct = 0
error = 0
 
# Inspect Streams
with open(rxpath) as rx:
    with open(txpath) as tx:

        gbg = rx.read(2)

        # Loop Over Stream
        while True:
            tx_bit = tx.read(1)
            rx_bit = rx.read(1)
            if not tx_bit:
              break
            if(tx_bit==rx_bit):
                correct += 1
                bits += 1
            else:
                error += 1
                bits += 1
        
print(bits, 'bits transmitted:')
print('Reciever detected', correct, 'bits correctly, giving', error, 'bit errors.')
print('Bit Error Percentage of %.4f' %((error/bits)*100))





