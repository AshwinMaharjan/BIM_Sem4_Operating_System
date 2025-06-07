#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t sem;

void *worker_thread(void *arg) {
    printf("Worker thread waiting for signal...\n");
    sem_wait(&sem);
    printf("Worker thread received signal and woke up!\n");
    return NULL;
}

int main() {
    pthread_t thread;
    sem_init(&sem, 0, 0);

    pthread_create(&thread, NULL, worker_thread, NULL);

    printf("Main thread sleeping for 2 seconds...\n");
    sleep(2);

    printf("Main thread sending wakeup signal...\n");
    sem_post(&sem);

    pthread_join(thread, NULL);
    sem_destroy(&sem);
    return 0;
}
