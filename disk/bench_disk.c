/*
============================================================================
 Name        : bench_disk.c
 Author      : Mohan Shashanka Chamarthy
 CWID		 : A20365258
 Version     : 1.0
 Description : Main benchmarking code for Disk
============================================================================
*/
#include "disk.h"

/*
Usage : disk <read_write: 0 = read, 1 = write> <no_of_threads: Max 4> <block_size: 0 = 1B, 1 = 1KB, 2 = 1MB> <seq_or_random: 0 = Seqencial, 1 = Random>
*/
int main(int argc, char *argv[]){

	int read_write = atoi(argv[1]);
	int no_of_threads = atoi(argv[2]);
	int block_size = atoi(argv[3]);
	int seq_or_random = atoi(argv[4]);

	if(block_size == 0){
		runExptWith(read_write, no_of_threads, "B", 0);
	} else if(block_size == 1){
		runExptWith(read_write, no_of_threads, "KB", 0);
	} else if(block_size == 2){
		runExptWith(read_write, no_of_threads, "MB", 0);
	} 
	return 0;
}