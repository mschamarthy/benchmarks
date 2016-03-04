/*
============================================================================
 Name        : timer.h
 Author      : Mohan Shashanka Chamarthy
 CWID		 : A20365258
 Version     : 1.0
 Description : Header file for timer library
============================================================================
*/
#include <stdio.h>
#include <sys/time.h>
#include <sys/resource.h>

struct timer {
	// Timing for user process code
	struct timeval u_begin, u_end;
	long double u_time_spent;

	// Timing for system process code
	struct timeval s_begin, s_end;
	long double s_time_spent;
};

typedef struct timer my_timer_t;

void startTimer(my_timer_t*);
void stopTimer(my_timer_t*);
long double getUserTimeLapsed(my_timer_t*);
long double getSystemTimeLapsed(my_timer_t*);
long double getTotalTimeLapsed(my_timer_t*);