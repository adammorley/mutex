#include <stdbool.h>

#ifndef MUTEX_H
#define MUTEX_H

typedef struct mutex mutex;
struct mutex {
    bool* m;
};

/*
    create the mutex
*/
mutex* mutex_create();

/*
    frees the mutex
*/
void mutex_delete(mutex* mutex);

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
