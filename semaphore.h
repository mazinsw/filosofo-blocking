//      This program is free software; you can redistribute it and/or modify
//      it under the terms of the GNU General Public License as published by
//      the Free Software Foundation; either version 2 of the License, or
//      any later version.
//      
//      This program is distributed in the hope that it will be useful,
//      but WITHOUT ANY WARRANTY; without even the implied warranty of
//      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//      GNU General Public License for more details.
//      
//      You should have received a copy of the GNU General Public License
//      along with this program; if not, write to the Free Software
//      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
//      MA 02110-1301, USA.
#ifndef _SEMAPHORE_H_
#define _SEMAPHORE_H_
#include <pthread.h>

typedef struct pthread_semaphore_
{
	pthread_mutex_t mutex;
	pthread_cond_t cond;
	unsigned char triggered;
} pthread_semaphore_t;

int pthread_semaphore_init(pthread_semaphore_t* sem, 
	const pthread_mutexattr_t * m_attr, const pthread_condattr_t * c_attr);
void pthread_semaphore_post(pthread_semaphore_t* sem);
void pthread_semaphore_wait(pthread_semaphore_t* sem);
void pthread_semaphore_destroy(pthread_semaphore_t* sem);

#endif /* _SEMAPHORE_H_ */
