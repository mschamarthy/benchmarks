#!/bin/bash

: '
============================================================================
 Name        : benchmark.sh
 Author      : Mohan Shashanka Chamarthy
 CWID		 : A20365258
 Version     : 1.0
 Description : Bash script to check and install pre-requisite software, make
 			   the `report` directory and automatically runs CPU, Memory & 
 			   Disk benchmarking for different cases.
============================================================================
'

# Check for pre-requisite software like gcc, etc.
perl scripts/prerequisites.pl

# Make the report directory if not present
[ -d report ] || mkdir report

# # build the Library first
# cd lib
# sh lib.sh 2>/dev/null
# cd ..

# Run CPU benchmarking
cd cpu
sh cpu.sh 2>/dev/null
cd ..

# Run MEMORY benchmarking
cd memory
sh memory.sh 2>/dev/null
cd ..

# Run DISK benchmarking
cd disk
sh disk.sh 2>/dev/null
cd ..

open report/