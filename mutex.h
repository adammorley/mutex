#include <stdbool.h>

#ifndef MUTEX_H
#define MUTEX_H

typedef struct mutex mutex;
struct mutex {
    bool* m;
};

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
    busy-waits with sleep
*/
void mutex_lock(mutex* mutex);

/*
    unlock the mutex
*/
void mutex_unlock(mutex* mutex);

#endif //MUTEX_H
