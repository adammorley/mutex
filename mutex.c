#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mutex.h"

static struct timespec _t = {0, 100};

mutex* mutex_create() {
    mutex* m = malloc(sizeof(mutex));
    m->m = malloc(sizeof(bool));
    return m;
}

void mutex_delete(mutex* m) {
    free(m->m);
    free(m);
}

void mutex_lock(mutex* m) {
    bool* e = malloc(sizeof(bool));
    *e = false;
    /*
        bool __atomic_compare_exchange_n (type *ptr, type *expected, type desired, bool weak, int success_memorder, int failure_memorder)
        https://gcc.gnu.org/onlinedocs/gcc-7.2.0/gcc/_005f_005fatomic-Builtins.html#g_t_005f_005fatomic-Builtins
    */
    if (! __atomic_compare_exchange_n(m->m, e, true, false, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST) ) {
        __atomic_exchange_n(e, false, __ATOMIC_SEQ_CST);
        // FIXME: update to clock_nanosleep
        int r = nanosleep(&_t, NULL);
        if (r) {
            fprintf(stderr, "problem with nanosleep, note FIXME\n");
            assert(false);
        }
    }
}

void mutex_unlock(mutex* m) {
    __atomic_store_n(m->m, false, __ATOMIC_SEQ_CST);
}
