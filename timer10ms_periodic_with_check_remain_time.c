#include <time.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

#define M 1000000               // Million
#define MS_TO_NS(x) (x * M)     

void check_remaining_time();
void timer_callback (union sigval value);

void main()
{
	timer_t timer_id;
	
   struct timespec interval;
   struct timespec remaining;
   struct sigevent sev;
   interval.tv_sec = 0;
   interval.tv_nsec = MS_TO_NS(10);

   sev.sigev_notify = SIGEV_THREAD;
   sev.sigev_notify_function = timer_callback;
   sev.sigev_notify_attributes = NULL;
   sev.sigev_value.sival_ptr = NULL;			//&timer_id;
   timer_create(CLOCK_MONOTONIC, &sev, &timer_handler);
   struct itimerspec its;
   its.it_interval = interval;
   its.it_value = interval;
  
   timer_settime(timer_id, 0, &its, NULL);
 while (1)											
  {
      
       check_remaining_time();
   }

   return 0;
}

void timer_callback(union sigval value) {

	 printf("Timer expired:\n");
}

void check_remaining_time() {
   struct itimerspec remaining_time;
   long int ns_to_ms =  ((remaining_time.it_value.tv_nsec)/1000000);
   timer_gettime(timerid, &remaining_time);
   printf("Remaining time: %ld sec %ld ns\n", remaining_time.it_value.tv_sec,ns_to_ms );
}
