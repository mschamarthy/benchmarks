#!/bin/bash

: '
============================================================================
 Name        : lib.sh
 Author      : Mohan Shashanka Chamarthy
 CWID		 : A20365258
 Version     : 1.0
 Description : Bash script to build the custom library files.
============================================================================
'

# compile and run Lib

# Compile timer.c
gcc -pthread -c timer.c -o timer.o