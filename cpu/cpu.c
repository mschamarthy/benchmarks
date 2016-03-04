/*
============================================================================
 Name        : cpu.c
 Author      : Mohan Shashanka Chamarthy
 CWID		 : A20365258
 Version     : 1.0
 Description : Code containing the function for CPU benchmarking
============================================================================
*/
#include "cpu.h"

// Function to run IOPS benchmarking for different no. of threads
void iOPsBenchmark(int noOfThreads){
	double flops = 0.0L;
	long double a_flops = 0.0L;
	int i = 0;
	for(i = 0; i < REPEAT_EXPT ; i++){
		flops = cpu_benchmark('i', noOfThreads);
		a_flops += (long double) (flops/REPEAT_EXPT);
	}
	printf("IOPS : %0.2Lf GIOPS\n", a_flops);
}

// Function to run FLOPS benchmarking for different no. of threads
void flOPsBenchmark(int noOfThreads){
	double flops = 0.0L;
	long double a_flops = 0.0L;
	int i = 0;
	for(i = 0; i < REPEAT_EXPT ; i++){
		flops = cpu_benchmark('f', noOfThreads);
		a_flops += (long double) (flops/REPEAT_EXPT);
	}
	printf("FLOPS : %0.2Lf GFLOPS\n", a_flops);
}

// Function to run IOPS & FLOPS benchmarking
double cpu_benchmark(char mode, int noOfThreads){
	my_timer_t timerA;
	long int time_spent;
	long double ops;
	
	int inst_per_loop = 8;
	
	if(mode == 'i' || mode == 'I'){
		startTimer(&timerA);
		multiThreadJobI(noOfThreads);
		stopTimer(&timerA);
	} else if(mode == 'f' || mode == 'F'){
		startTimer(&timerA);
		multiThreadJobF(noOfThreads);
		stopTimer(&timerA);
	}

	time_spent = getTotalTimeLapsed(&timerA)*1000;

	// Giga Ops per second
	ops = (double)(inst_per_loop * LOOP_COUNT * noOfThreads) / time_spent;
	return ops;
}

// Funtion to run multi thread IOPS function
void multiThreadJobI(int noOfThreads){
	pthread_t threads[MAX_THREADS];
	long tArgs[MAX_THREADS];
	int rc, t;

	// Create Threads
	for(t = 0; t < noOfThreads; t++){
		// printf("In main: creating thread %d\n", t);
		tArgs[t] = LOOP_COUNT;
		rc = pthread_create(&threads[t], NULL, jobI, (void *)tArgs[t]);
		// printf("In multiThreadJobI: creating thread %d\n", t);
		if (rc){
			printf("ERROR; return code from pthread_create() is %d\n", rc);
			exit(-1);
		}
	}

	// Wait for threads to join
	for(t = 0; t < noOfThreads; t++){
		rc = pthread_join(threads[t], NULL);
		// printf("In multiThreadJobI: joined thread %d\n", t);
		if (rc) {
			printf("ERROR; return code from pthread_join() is %d\n", rc);
			exit(-1);
		}
	}

	return;
}

// Funtion to run multi thread FLOPS function
void multiThreadJobF(int noOfThreads){
	pthread_t threads[MAX_THREADS];
	long tArgs[MAX_THREADS];
	int rc, t;

	// Create Threads
	for(t = 0; t < noOfThreads; t++){
		// printf("In main: creating thread %d\n", t);
		tArgs[t] = LOOP_COUNT;
		rc = pthread_create(&threads[t], NULL, jobF, (void *)tArgs[t]);
		// printf("In multiThreadJobI: creating thread %d\n", t);
		if (rc){
			printf("ERROR; return code from pthread_create() is %d\n", rc);
			exit(-1);
		}
	}

	// Wait for threads to join
	for(t = 0; t < noOfThreads; t++){
		rc = pthread_join(threads[t], NULL);
		// printf("In multiThreadJobI: joined thread %d\n", t);
		if (rc) {
			printf("ERROR; return code from pthread_join() is %d\n", rc);
			exit(-1);
		}
	}
	return;
}

// Function called by threads to run the FLOPS operations
void *jobF(void *t){
	int i;
	long int N = (long int) t;
	float c = 2312.1232, d = 456.45646;
	float res;
	for(i = 0; i < N ; i++){
		res = ((c/d)+c)*(d - c/d - (c*c));
	}
	pthread_exit(NULL);
}

// Function called by threads to run the IOPS operations
void *jobI(void *t){
	int i;
	long int N = (long int) t;
	int a = 23423, b = 75676;
	float res;
	for(i = 0; i < N ; i++){
		res = ((a/b)+a)*(b - a/b - (a*a));
	}
	pthread_exit(NULL);
}