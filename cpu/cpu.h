/*
============================================================================
 Name        : cpu.h
 Author      : Mohan Shashanka Chamarthy
 CWID		 : A20365258
 Version     : 1.0
 Description : Header file for cpu benchmarking
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <pthread.h>
#include "../lib/timer.h"

#define MAX_THREADS 5
#define REPEAT_EXPT 1000
#define LOOP_COUNT 1000000

double cpu_benchmark(char, int);
void iOPsBenchmark(int);
void flOPsBenchmark(int);
void multiThreadJobI(int);
void multiThreadJobF(int);
void *jobI(void *t);
void *jobF(void *t);