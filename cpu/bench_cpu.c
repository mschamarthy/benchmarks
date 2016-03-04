/*
============================================================================
 Name        : bench_cpu.c
 Author      : Mohan Shashanka Chamarthy
 CWID		 : A20365258
 Version     : 1.0
 Description : Main benchmarking code for CPU
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include "cpu.h"

int main(int argc, char *argv[]){
	int noOfThreads = 1;

	if(argc == 1) {	// No arguments - Use 1 Thread
		noOfThreads = 1;
	} else if(argc == 2) {	// Read the number of parameters
		noOfThreads = atoi(argv[1]);
	} else {
		fprintf(stderr, "Enter atmost 1 Command Line argument\n");
		exit(1);
	}

	iOPsBenchmark(noOfThreads);
	flOPsBenchmark(noOfThreads);
	
	return 0;
}