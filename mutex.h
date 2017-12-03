#include <stdbool.h>

#ifndef MUTEX_H
#define MUTEX_H

typedef bool mutex;

#ifdef _UNIT_TEST
#define STATIC 
#else
#define STATIC static
#endif

#ifdef _UNIT_TEST
bool _lock(mutex* mutex);
#endif

/*
    create the mutex
*/
mutex* mutex_create();

/*
    frees the mutex
*/
void mutex_delete(mutex* mutex);

/*
    returns whether the mutex is locked
*/
bool mutex_islocked(mutex* mutex);

/*
    lock the mutex
*/
bool mutex_lock(mutex* mutex);

/*
    lock two mutexes, doing backoff
*/
bool mutex_lock2(mutex* mutex0, mutex* mutex1);

/*
    spinlock the mutex
*/
void mutex_spinlock(mutex* mutex);

/*
    unlock the mutex
*/
void mutex_unlock(mutex* mutex);

#endif //MUTEX_H
