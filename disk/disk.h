/*
============================================================================
 Name        : disk.h
 Author      : Mohan Shashanka Chamarthy
 CWID		 : A20365258
 Version     : 1.0
 Description : Header file for disk benchmarking
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

void runExptWith(int, int, char*, int);
void* Read(void*);
void* Write(void*);

struct disk_result {
	long double speed;
	long double latency;
	char* type;	// B / KB / MB
	int mode;
	int access_mode;	// Sequence = 0/ Random = 1
	int rw_mode;	// Read = 0/ Write = 1
};

typedef struct disk_result my_disk_result_t;