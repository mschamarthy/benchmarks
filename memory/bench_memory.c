/*
============================================================================
 Name        : bench_memory.c
 Author      : Mohan Shashanka Chamarthy
 CWID		 : A20365258
 Version     : 1.0
 Description : Main benchmarking code for Memory
============================================================================
*/
#include "memory.h"

/*
Usage : memory <no_of_threads: Max 4> <block_size: 0 = 1B, 1 = 1KB, 2 = 1MB> <seq_or_random: 0 = Seqencial, 1 = Random>
*/
int main(int argc, char *argv[]){

	int no_of_threads = atoi(argv[1]);
	int block_size = atoi(argv[2]);
	int seq_or_random = atoi(argv[3]);

	if(block_size == 0){
		runExptWith(no_of_threads, "B", 0);
	} else if(block_size == 1){
		runExptWith(no_of_threads, "KB", 0);
	} else if(block_size == 2){
		runExptWith(no_of_threads, "MB", 0);
	} 
	return 0;
}