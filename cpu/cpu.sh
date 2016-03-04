#!/bin/bash

: '
============================================================================
 Name        : cpu.sh
 Author      : Mohan Shashanka Chamarthy
 CWID		 : A20365258
 Version     : 1.0
 Description : Bash script to build the cpu benchmarking code with 
 			   dependencies. Automatically running CPU benchmarking for 
 			   different cases.
============================================================================
'

# build the Library first
cd ../lib
sh lib.sh 2>/dev/null
cd ../cpu

# compile and run CPU benchmarking
# Compile bench_cpu.c
gcc -c cpu.c -o cpu.o
gcc -c bench_cpu.c -o bench_cpu.o
gcc -pthread bench_cpu.o cpu.o ../lib/timer.o -o cpu

# Make the report folder for cpu if not Exists
[ -d ../report ] || mkdir ../report

# Target for CPU report
# cpuOut="../report/cpu/cpu.txt"
cpuOut="../report/cpu.txt"

# Remove previous report
if [ -e $cpuOut ] ; then
	rm $cpuOut
fi

: '
Run CPU benchmarking for 1, 2, 4 threads and store the result to 
above target location
'
echo "CPU benchmarking running.."
echo "CPU benchmarking report generate on - `date`" >> $cpuOut
echo "=========================" >> $cpuOut

for i in 1 2 4;
do
	echo "CPU - no. of Threads : $i" >> $cpuOut
    ./cpu $i >> $cpuOut
	echo "-------------------------" >> $cpuOut    
done
echo "CPU benchmarking Completed.."
echo "CPU report at $cpuOut"
echo "-------------------------"