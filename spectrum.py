import sys  
import os
import numpy as np
import matplotlib.pyplot as plt    

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
    
    # Remove DC of Bitstream
    bit_stream[bit_stream == 0] = -1
    print(bit_stream)
    
    # Find Spectrum of Bit Stream
    spectrum = np.fft.fft(bit_stream)   
    fig, ax = plt.subplots()
    t = np.arange(n)
    freq = np.fft.fftfreq(t.shape[-1])
    ax.plot(freq, spectrum)
    plt.xlabel('Normalised Frequency')
    plt.title('FFT of Pseudo-Random Bit Stream')
    plt.show()
