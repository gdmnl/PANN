#!/bin/bash

make clean
make
# ./knng "letter.scale.txt" 15000
# ./knng "combined_scale.txt" 78823
# ./knng "protein.txt" 17766
# ./knng "mnist.scale.txt" 60000
# ./knng "sift.txt" 25000
./knng "cifar10.txt" 50000