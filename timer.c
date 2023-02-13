#include <time.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

#define M 1000000               // Million
#define MS_TO_NS(x) (x * M)                     //covert ms to nano sec

void timer_callback (union sigval value);
void check_remaining_time();


timer_t timerid;                  //timer data structure

int main() {
   struct timespec interval;
   struct timespec remaining;
   interval.tv_sec = 0;
   interval.tv_nsec = MS_TO_NS(10);
   struct sigevent sev;
   sev.sigev_notify = SIGEV_THREAD;     //      The struct sigevent sev variable is used to specify the behavior of the timer. 
                                        //     In this case, it is set to use the SIGEV_THREAD notification  
                                        //      method, which means that the timer_callback() function will be called in a separate thread when the timer expires
   sev.sigev_notify_function = timer_callback;
   sev.sigev_notify_attributes = NULL;
   sev.sigev_value.sival_ptr = &timerid;
   timer_create(CLOCK_MONOTONIC, &sev, &timerid);
   struct itimerspec its;
   its.it_interval = interval;
   its.it_value = interval;
   timer_settime(timerid, 0, &its, NULL);
   while (1) {
      
   }
   return 0;
}
