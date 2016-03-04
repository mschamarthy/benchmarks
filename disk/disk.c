/*
============================================================================
 Name        : disk.c
 Author      : Mohan Shashanka Chamarthy
 CWID		 : A20365258
 Version     : 1.0
 Description : Code containing the function for Disk benchmarking
============================================================================
*/
#include "disk.h"

void runExptWith(int rw_mode, int no_of_threads, char* type, int mode){
	int i, j;
	my_disk_result_t result[MAX_THREADS], avg;
	pthread_t threads[MAX_THREADS];
	avg.speed = 0;
	avg.latency = 0;

	for(i = 0; i < REPEAT_EXPT ; i++){
		for(j = 0; j < no_of_threads; j++){
			result[j].type = type;
			result[j].mode = mode;
			if(rw_mode == 0){	// READ mode
				pthread_create(&threads[j], NULL, Read, (void *)&result[j]);
			} else if (rw_mode == 1){	//WRITE mode
				pthread_create(&threads[j], NULL, Write, (void *)&result[j]);
			}
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

// Function to run the Write experiement for different cases
void* Write(void* param)
{
	my_timer_t timerA;
	my_disk_result_t *result = (my_disk_result_t *)param;

	int fileSize = 100; // file size in MB
	long long block_size = 1;

	long long i, loopSize = (1048576 / block_size);
    int k;
    char *sourceString, *destinationString, *temp;
    sourceString = (char *)malloc(fileSize * 1048576);

    // Create a temp file to perform any read write operations
    FILE *fp;
    char filename[50];
    sprintf(filename, "FileName-%d.txt", rand()%256);
    fp = fopen(filename, "w");

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

    loopSize = ((1048576 * fileSize) / block_size);

    // Run appropriate loop for sequence / random write case
    if(result->mode == 0){
    	startTimer(&timerA);
		for(i = 0; i < loopSize; i++) {
			fwrite(sourceString+(i*block_size), 1, block_size, fp);
		}
		stopTimer(&timerA);
    } else {
    	startTimer(&timerA);
	    for(i = 0; i < loopSize; i++) {
        	k = rand()%loopSize;
        	fseek(fp, k*block_size, SEEK_SET);
        	fwrite(sourceString+(k*block_size), 1, block_size, fp);
        }
		stopTimer(&timerA);
    }

	result->latency = getTotalTimeLapsed(&timerA) / loopSize;
	result->speed = (fileSize * 1048576) / getTotalTimeLapsed(&timerA);
	// printf("Transfer speed Thread (total) : %Lf\n", *speed);

	free(sourceString);free(destinationString);
	
	// Close the file and Delete it before exiting
	fclose(fp);
	remove(filename);
	
	pthread_exit(NULL);
}

// Function to run the Write experiement for different cases
void* Read(void* param)
{
	my_timer_t timerA;
	my_disk_result_t *result = (my_disk_result_t *)param;

	int fileSize = 100; // file size in MB
	long long block_size = 1;

	long long i, loopSize = (1048576 / block_size);
    int k;
    char *sourceString, *destinationString, *temp;
    sourceString = (char *)malloc(fileSize * 1048576);
    destinationString = (char *)malloc(fileSize * 1048576);

    // Create a temp file to perform any read write operations
    FILE *fp;
    char filename[50];
    sprintf(filename, "FileName-%d.txt", rand()%256);
    fp = fopen(filename, "w");

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

    loopSize = ((1048576 * fileSize) / block_size);

    // Write the data into the test file
    fwrite(sourceString, 1, (1048576 * fileSize), fp);
    fclose(fp);
    fp = fopen(filename, "r");

    // Run appropriate loop for sequence / random read case
    if(result->mode == 0){
    	startTimer(&timerA);
		for(i = 0; i < loopSize; i++) {
			fread(destinationString+(i*block_size), 1, block_size, fp);
		}
		stopTimer(&timerA);
    } else {
    	startTimer(&timerA);
	    for(i = 0; i < loopSize; i++) {
        	k = rand()%loopSize;
        	fseek(fp, k*block_size, SEEK_SET);
        	fread(destinationString+(k*block_size), 1, block_size, fp);
        }
		stopTimer(&timerA);
    }

	result->latency = getTotalTimeLapsed(&timerA) / loopSize;
	result->speed = (fileSize * 1048576) / getTotalTimeLapsed(&timerA);
	// printf("Transfer speed Thread (total) : %Lf\n", *speed);

	free(sourceString);free(destinationString);
	
	// Close the file and Delete it before exiting
	fclose(fp);
	remove(filename);
	
	pthread_exit(NULL);
}