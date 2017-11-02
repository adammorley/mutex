#include <assert.h>
#include <pthread.h>
#include <unistd.h>
#include "mutex.h"

int x = 0;
mutex* m;
void *update(void *arg) {
    mutex_lock(m);
    x++;
    sleep(5);
    mutex_unlock(m);
}

int main(void) {
    m = mutex_create();
    pthread_t tid0;
    pthread_t tid1;
    pthread_create(&tid0, NULL, update, NULL);
    sleep(1);
    assert(x == 1);
    pthread_create(&tid1, NULL, update, NULL);
    sleep(1);
    assert(x == 1);
    sleep(5);
    assert(x == 2);
    pthread_join(tid0, NULL);
    pthread_join(tid1, NULL);
    mutex_delete(m);
    return 0;
}
