#!/bin/bash

python3 ../gen_stream.py ./data.csv ./data_stream.txt
python3 ../gen_stream.py ./decoded.csv ./decoded_stream.txt
python3 ../error_rate.py ./data_stream.txt ./decoded_stream.txt
