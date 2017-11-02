#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "mutex.h"

int main(void) {
    mutex* m = mutex_create();
    assert(_lock(m));
    assert(mutex_islocked(m));
    assert(!_lock(m));
    assert(mutex_islocked(m));
    mutex_unlock(m);
    assert(!mutex_islocked(m));
    mutex_delete(m);
    return 0;
}
