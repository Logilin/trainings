/****************************************************************************\
** Exemple de la formation "Temps-reel Linux et Xenomai"                    **
**                                                                          **
** Christophe Blaess 2010-2018                                              **
** http://christophe.blaess.fr                                              **
** Licence GPLv2                                                            **
\****************************************************************************/

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>


pthread_mutex_t _Mutex;

#define LOOPS 100000000

void * thread_function_2(void * unused)
{
	int i;

	sleep(3);
	while (1) {
		for (i = 0; i < LOOPS; i ++)
			;
		sleep(3);
	}
}



void * thread_function_1(void *unused)
{
	int i;
	struct timeval tv, previous = {0,0};
	long long delay, delay_max;

	sleep(1);

	for (;;) {
		delay_max = 0;
		previous.tv_sec = 0;

		pthread_mutex_lock(&_Mutex);

		for (i = 0; i < 10000000; i++) {
			gettimeofday(&tv, NULL);
			if (previous.tv_sec != 0) {
				delay  = tv.tv_sec - previous.tv_sec;
				delay *= 1000000;
				delay += tv.tv_usec - previous.tv_usec;
				if (delay > delay_max)
					delay_max = delay;
			}
			previous = tv;
		}
		pthread_mutex_unlock(&_Mutex);

		fprintf(stderr, "T1 preempted during %lld usec.\n", delay_max);
		sleep(1);
	}

	return NULL;
}



int main(int argc, char * argv [])
{
	pthread_t thread_1, thread_2;
	pthread_attr_t attr;
	struct sched_param param;
	pthread_mutexattr_t mtx_attr;
//	int unused;

	pthread_mutexattr_init(&mtx_attr);
//	pthread_mutexattr_setprotocol(&mtx_attr, PTHREAD_PRIO_PROTECT);

	pthread_mutex_init(&_Mutex, &mtx_attr);
//	pthread_mutex_setprioceiling (&_Mutex, 99, &unused);

	pthread_attr_init(&attr);
	pthread_attr_setschedpolicy(&attr, SCHED_FIFO);
	pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED);

	param.sched_priority = 10;
	pthread_attr_setschedparam(&attr, &param);

	if ((errno = pthread_create(&thread_1, &attr, thread_function_1, NULL)) != 0) {
		perror("pthread_create");
		exit(EXIT_FAILURE);
	}

	param.sched_priority = 20;
	pthread_attr_setschedparam(&attr, &param);

	if ((errno = pthread_create(&thread_2, &attr, thread_function_2, NULL)) != 0) {
		perror("pthread_create");
		exit(EXIT_FAILURE);
	}

	pthread_exit(NULL);
}
