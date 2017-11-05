#include <assert.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "mutex.h"

struct t_args {
    mutex* m;
    int* x;
};

void* update(void* args) {
    struct t_args* arg = (struct t_args*) args;
    mutex_lock(arg->m);
    *arg->x += 1;
    usleep(100);
    mutex_unlock(arg->m);
}

int main(void) {
    mutex* m = mutex_create();
    int* x = malloc(sizeof(int));
    *x = 0;

    struct t_args args;
    args.m = m;
    args.x = x;

    pthread_t tid0;
    pthread_t tid1;
    pthread_create(&tid0, NULL, update, (void*) &args);
    usleep(50);
    assert(mutex_islocked(m));
    assert(*x == 1);
    pthread_create(&tid1, NULL, update, (void*) &args);
    assert(*x == 1);
    assert(mutex_islocked(m));
    usleep(50);
    assert(*x == 2);
    usleep(100);
    assert(!mutex_islocked(m));
    pthread_join(tid0, NULL);
    pthread_join(tid1, NULL);
    mutex_delete(m);
    return 0;
}
