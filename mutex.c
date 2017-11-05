#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
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
    *m = false;
    return m;
}

void mutex_delete(mutex* m) {
    free(m);
}

bool mutex_islocked(mutex* m) {
    return __atomic_load_n(m, __ATOMIC_ACQUIRE);
}

void mutex_lock(mutex* m) {
    while (!_lock(m)) {
        // FIXME: switch to clock_nanosleep() using monotonic clock
        if (nanosleep(&_t, NULL)) {
            fprintf(stderr, "problem with nanosleep, note FIXME\n");
            assert(false);
        }
    }
}

void mutex_unlock(mutex* m) {
    __atomic_store_n(m, false, __ATOMIC_RELEASE);
}
