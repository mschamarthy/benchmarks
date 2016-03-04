/*
============================================================================
 Name        : memory.h
 Author      : Mohan Shashanka Chamarthy
 CWID		 : A20365258
 Version     : 1.0
 Description : Header file for memory benchmarking
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <pthread.h>
#include <string.h>
#include "../lib/timer.h"

#define MAX_THREADS 4
#define REPEAT_EXPT 3

void* ReadWrite(void*);
void runExptWith(int, char*, int);

struct mem_result {
	long double speed;
	long double latency;
	char* type;	// B / KB / MB
	int mode;	// Sequence = 0/ Random = 1
};

typedef struct mem_result my_mem_result_t;