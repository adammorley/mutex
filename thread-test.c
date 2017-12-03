#include <assert.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "mutex.h"

struct t_args {
    int* x;
    mutex* m;
};

void* update(void* args) {
    struct t_args* arg = (struct t_args*) args;
    mutex_spinlock(arg->m);
    *arg->x += 1;
    usleep(100);
    mutex_unlock(arg->m);
    return NULL;
}

int main(void) {
    struct t_args args;
    args.m = mutex_create();
    args.x = malloc(sizeof(int));
    *args.x = 0;

    pthread_t tid0;
    pthread_t tid1;
    pthread_create(&tid0, NULL, update, (void*) &args);
    usleep(50);
    assert(mutex_islocked(args.m));
    assert(*args.x == 1);
    pthread_create(&tid1, NULL, update, (void*) &args);
    assert(*args.x == 1);
    assert(mutex_islocked(args.m));
    usleep(50);
    assert(*args.x == 2);
    usleep(150);
    assert(!mutex_islocked(args.m));
    pthread_join(tid0, NULL);
    pthread_join(tid1, NULL);
    mutex_delete(args.m);
    free(args.x);
    return 0;
}
