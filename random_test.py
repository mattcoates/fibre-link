import sys  
import os
import numpy as np
from scipy.special import comb
np.set_printoptions(precision=5)

# Percentage Difference
def percent_diff(est, act):
    try:
       return (np.divide(abs(est - act), act))*100.0
    except ZeroDivisionError:
        return 0

# File Path
if len(sys.argv) != 2:
    print("Usage: {} /file.txt".format(sys.argv[0]))
    sys.exit(1)

filepath = sys.argv[1]

if not os.path.isfile(filepath):
    print("File path {} does not exist. Exiting...".format(filepath))
    sys.exit()

# Open File
print("Opening {}".format(filepath))
print("")
    
# Analyse Bitstream
with open(filepath) as fp:
    bit_stream = np.asarray(tuple(map(int, fp.read())))
    n = bit_stream.size
    print(bit_stream)
    print("")
    print( n, " Bits Loaded")
    print("")
    
    for k in range(1,9):
    
        # Test Sequences of Length k
        freq = np.zeros(k+1)
        for i in range(0, n):            
            
            # Read Sequence of Length k
            tmp = bit_stream[i:i+k]
            
            # Handle Remainder at EOF
            if (tmp.size<k):            
                continue
                
            # Update Frequency
            freq[np.count_nonzero(tmp)] +=1
            
        
        # Generate Actual p Dist
        p = np.zeros(k+1)
        for j in range(0, k+1):
            p[j] = comb(k,j)*np.power(0.5,k)
        
        # Generate Measured Dist
        prob = freq/np.sum(freq)
        
        # Output Results of Test
        print("Length", k, "Sequences:")
        print("Freq -", freq)
        print("Prob -", prob)
        print("Actual - ", p)
        print("% Diff - ", percent_diff(prob, p))
        print("")
