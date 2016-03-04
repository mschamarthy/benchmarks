/*
============================================================================
 Name        : timer.c
 Author      : Mohan Shashanka Chamarthy
 CWID		 : A20365258
 Version     : 1.0
 Description : Code containing the library of simplified functions for 
 			   timer structure used in timing different code sections of 
 			   the programs.
============================================================================
*/
#include "timer.h"

/*
	Function to start the timer. Function records the user and 
	system cpu timing.
*/
void startTimer(my_timer_t* timer) {
	struct rusage r_begin;
	getrusage(RUSAGE_SELF, &r_begin);
	timer->u_begin = r_begin.ru_utime;
	timer->s_begin = r_begin.ru_stime;
}

/*
	Function to stop the timer. Function records the user and 
	system cpu timing.
*/
void stopTimer(my_timer_t* timer) {
	struct rusage r_end;
	getrusage(RUSAGE_SELF, &r_end);
	timer->u_end = r_end.ru_utime;
	timer->s_end = r_end.ru_stime;
}

/*
	Function to calculate the user time lapsed.
*/
long double getUserTimeLapsed(my_timer_t* timer) {
	long double time_spent = 0.0L;
	time_spent = (long double)((((timer->u_end).tv_sec - (timer->u_begin).tv_sec)*1000000)+((timer->u_end).tv_usec - (timer->u_begin).tv_usec));
	return time_spent;
}

/*
	Function to calculate the system time lapsed.
*/
long double getSystemTimeLapsed(my_timer_t* timer) {
	long double time_spent = 0.0L;
	time_spent = (long double)((((timer->s_end).tv_sec - (timer->s_begin).tv_sec)*1000000)+((timer->s_end).tv_usec - (timer->s_begin).tv_usec));
	return time_spent;
}

/*
	Function to calculate the user + system time lapsed.
*/
long double getTotalTimeLapsed(my_timer_t* timer) {
	long double time_spent = 0.0L;
	time_spent = getUserTimeLapsed(timer) + getSystemTimeLapsed(timer);
	return time_spent;
}