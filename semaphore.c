#include "semaphore.h"

int pthread_semaphore_init(pthread_semaphore_t* sem, const pthread_mutexattr_t* m_attr,
						   const pthread_condattr_t * c_attr)
{
	int r;

	r = pthread_mutex_init(&sem->mutex, m_attr);
	if(r != 0)
		return r;
	r = pthread_cond_init(&sem->cond, c_attr);
	sem->triggered = 0;
	return r;
}

void pthread_semaphore_post(pthread_semaphore_t* sem)
{
	pthread_mutex_lock(&sem->mutex);
	sem->triggered = 1;
	pthread_cond_signal(&sem->cond);
	pthread_mutex_unlock(&sem->mutex);
}

void pthread_semaphore_wait(pthread_semaphore_t* sem)
{
	pthread_mutex_lock(&sem->mutex);
	while (!sem->triggered)
		pthread_cond_wait(&sem->cond, &sem->mutex);
	sem->triggered = 0;
	pthread_mutex_unlock(&sem->mutex);
}

void pthread_semaphore_destroy(pthread_semaphore_t* sem)
{
	pthread_cond_destroy(&sem->cond);
	pthread_mutex_destroy(&sem->mutex);
}
