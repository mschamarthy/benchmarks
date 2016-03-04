/*
============================================================================
 Name        : memory.c
 Author      : Mohan Shashanka Chamarthy
 CWID		 : A20365258
 Version     : 1.0
 Description : Code containing the function for memory benchmarking
============================================================================
*/
#include "memory.h"

void runExptWith(int no_of_threads, char* type, int mode){
	int i, j;
	my_mem_result_t result[MAX_THREADS], avg;
	pthread_t threads[MAX_THREADS];
	avg.speed = 0;
	avg.latency = 0;

	for(i = 0; i < REPEAT_EXPT ; i++){
		for(j = 0; j < no_of_threads; j++){
			result[j].type = type;
			result[j].mode = mode;
			pthread_create(&threads[j], NULL, ReadWrite, (void *)&result[j]);
		}
		for(j = 0; j < no_of_threads; j++){
			pthread_join(threads[j], NULL);
			avg.speed += (result[j].speed / (no_of_threads * REPEAT_EXPT));
			avg.latency += (result[j].latency / (no_of_threads * REPEAT_EXPT));
			avg.type = result[j].type;
		}
	}
	printf("\tBlock Size - 1%s\n", avg.type);
	printf("\t\tThroughput : %.2Lf MB/s\n", avg.speed);
	printf("\t\tLatency : %Le ms\n", avg.latency/1000.0);
	printf("\n");

	return;
}

// Function to run the Read Write experiement for different cases
void* ReadWrite(void* param)
{
	my_timer_t timerA;
	my_mem_result_t *result = (my_mem_result_t *)param;

	int fileSize = 100; // file size in MB
	long long block_size = 1;	// BLock Size in Bytes

	long long i, k, loopSize = (1048576 / block_size);
    char *sourceString, *destinationString, *temp;
    sourceString = (char *)malloc(fileSize * 1048576);
    destinationString = (char *)malloc(fileSize * 1048576);

    temp = sourceString;
    for(i = 0; i < (fileSize * 1048576); i++) {
        *temp = (rand() % 256);
        temp++;
    }

    // Find the correct block size for the case
    if(strcmp("B", result->type) == 0){
    	block_size = 1;
    } else if (strcmp("KB", result->type) == 0){
    	block_size = 1024;
    } else if (strcmp("MB", result->type) == 0){
    	block_size = 1024 * 1024;
    }

    // Calculate the no of blocks the loop has to run to read & write a 100 MB file
    loopSize = ((1048576 * fileSize) / block_size);

    // Run appropriate loop for sequence / random read+write case
    if(result->mode == 0){
    	startTimer(&timerA);
		for(i = 0; i < loopSize; i++) {
			memcpy(destinationString+(i * block_size), sourceString+(i * block_size), block_size);
		}
		stopTimer(&timerA);
    } else {
    	startTimer(&timerA);
	    for(i = 0; i < loopSize; i++) {
        	k = rand()%loopSize;
        	memcpy(destinationString+(i * block_size), sourceString+(k * block_size), block_size);
        }
		stopTimer(&timerA);
    }

	result->latency = getTotalTimeLapsed(&timerA) / loopSize;
	// Throughput = (2 * no. of bytes) / time taken
	// 2 times because, we perform a read & write of a block in memcpy method.
	result->speed = (2*fileSize * 1048576) / getTotalTimeLapsed(&timerA);
	// printf("Transfer speed Thread (total) : %Lf\n", *speed);

	free(sourceString);free(destinationString);

	pthread_exit(NULL);
}