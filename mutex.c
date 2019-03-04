#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "mutex.h"

static struct timespec _t = {0, 100};
static bool _e;

STATIC bool _lock(mutex* m) {
    _e = false;
    /*
        bool __atomic_compare_exchange_n (type *ptr, type *expected, type desired, bool weak, int success_memorder, int failure_memorder)
        https://gcc.gnu.org/onlinedocs/gcc/_005f_005fatomic-Builtins.html
    */
    return __atomic_compare_exchange_n(m, &_e, true, true, __ATOMIC_ACQ_REL, __ATOMIC_RELAXED);
}

mutex* mutex_create() {
    mutex* m = malloc(sizeof(bool));
    if (m == NULL) assert(true);
    *m = false;
    return m;
}

void mutex_delete(mutex* m) {
    free(m);
}

bool mutex_islocked(mutex* m) {
    return __atomic_load_n(m, __ATOMIC_ACQUIRE);
}

bool mutex_lock(mutex* m) {
    return _lock(m);
}

bool mutex_lock2(mutex* m0, mutex* m1) {
    if (mutex_lock(m0)) {
        if (mutex_lock(m1)) {
            return true;
        }
        mutex_unlock(m0);
    }
    return false;
}

void mutex_spinlock(mutex* m) {
    int e;
    while (!_lock(m)) {
        e = clock_nanosleep(CLOCK_MONOTONIC, 0, &_t, NULL);
        if (e) {
            fprintf(stderr, "problem with nanosleep, error was: %s\n", strerror(e));
            assert(false);
        }
    }
}

void mutex_unlock(mutex* m) {
    __atomic_store_n(m, false, __ATOMIC_RELEASE);
}
