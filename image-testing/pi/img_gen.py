import sys  
import os
import struct
import numpy as np
import pandas as pd

# Open Output File 
out = open('grey.ppm','wb')

out.write(bytes([80, 54, 10, 51, 53, 48, 32, 50, 51, 52, 10, 50, 53, 53, 10]))

for i in range (0, 245700):
    out.write(bytes([170]))
