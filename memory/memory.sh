#!/bin/bash

: '
============================================================================
 Name        : memory.sh
 Author      : Mohan Shashanka Chamarthy
 CWID		 : A20365258
 Version     : 1.0
 Description : Bash script to build the memory benchmarking code with 
 			   dependencies. Automatically running memory benchmarking for 
 			   different cases.
============================================================================
'

# build the Library first
cd ../lib
sh lib.sh 2>/dev/null
cd ../memory

# compile and run MEMORY benchmarking
# Compile memory.c
gcc -c memory.c -o memory.o
gcc -c bench_memory.c -o bench_memory.o
gcc -pthread bench_memory.o memory.o ../lib/timer.o -o memory

# Make the report folder if not Exists
[ -d ../report ] || mkdir ../report

# Target for Memory report
memOut="../report/memory.txt"

# Remove previous report
if [ -e $memOut ] ; then
	rm $memOut
fi

: '
Run Memory benchmarking for 1, 2 threads and store the result to 
above target location
'
echo "Memory benchmarking running.."
echo "Memory Benchmarking report generate on - `date`" >> $memOut
echo "=========================" >> $memOut

echo "Sequential Read+Write Benchmarking" >> $memOut
for i in 1 2;
do
	echo "Using Threads = $i" >> $memOut
	for j in 0 1 2;
	do
    	./memory $i $j 0 >> $memOut
	done
done
echo "-------------------------" >> $memOut  

echo "Random Read+Write Benchmarking" >> $memOut
for i in 1 2;
do
	echo "Using Threads = $i" >> $memOut
	for j in 0 1 2;
	do
    	./memory $i $j 1 >> $memOut
	done 
done

echo "Memory benchmarking Completed.."
echo "Memory report at $memOut"
echo "-------------------------"