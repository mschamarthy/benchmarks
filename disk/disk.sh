#!/bin/bash

: '
============================================================================
 Name        : disk.sh
 Author      : Mohan Shashanka Chamarthy
 CWID		 : A20365258
 Version     : 1.0
 Description : Bash script to build the disk benchmarking code with 
 			   dependencies. Automatically running Disk benchmarking for 
 			   different cases.
============================================================================
'

# build the Library first
cd ../lib
sh lib.sh 2>/dev/null
cd ../disk

# compile and run DISK benchmarking
# Compile disk.c
gcc -c disk.c -o disk.o
gcc -c bench_disk.c -o bench_disk.o
gcc -pthread bench_disk.o disk.o ../lib/timer.o -o disk

# Make the report folder if not Exists
[ -d ../report ] || mkdir ../report

# Target for Memory report
diskOut="../report/disk.txt"

# Remove previous report
if [ -e $diskOut ] ; then
	rm $diskOut
fi

: '
Run Disk benchmarking for 1, 2 threads and store the result to 
above target location
'
echo "Disk benchmarking running.."
echo "Disk Benchmarking report generate on - `date`" >> $diskOut
echo "=========================" >> $diskOut

echo "Sequential Read Benchmarking" >> $diskOut
for i in 1 2;
do
	echo "Using Threads = $i" >> $diskOut
	for j in 0 1 2;
	do
    	./disk 0 $i $j 0 >> $diskOut
	done
done
echo "-------------------------" >> $diskOut  

echo "Random Read Benchmarking" >> $diskOut
for i in 1 2;
do
	echo "Using Threads = $i" >> $diskOut
	for j in 0 1 2;
	do
    	./disk 0 $i $j 1 >> $diskOut
	done 
done
echo "-------------------------" >> $diskOut

echo "Sequential Write Benchmarking" >> $diskOut
for i in 1 2;
do
	echo "Using Threads = $i" >> $diskOut
	for j in 0 1 2;
	do
    	./disk 1 $i $j 0 >> $diskOut
	done
done
echo "-------------------------" >> $diskOut  

echo "Random Write Benchmarking" >> $diskOut
for i in 1 2;
do
	echo "Using Threads = $i" >> $diskOut
	for j in 0 1 2;
	do
    	./disk 1 $i $j 1 >> $diskOut
	done 
done

echo "Disk benchmarking Completed.."
echo "Disk report at $diskOut"
echo "-------------------------"