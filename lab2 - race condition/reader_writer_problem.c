#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t resource_access;
sem_t read_count_access;
int read_count = 0;

void *reader(void *arg) {
    int id = *(int *)arg;

    sem_wait(&read_count_access);
    read_count++;
    if (read_count == 1) {
        sem_wait(&resource_access);
    }
    sem_post(&read_count_access);

    printf("Reader %d is reading...\n", id);
    sleep(1);

    sem_wait(&read_count_access);
    read_count--;
    if (read_count == 0) {
        sem_post(&resource_access);
    }
    sem_post(&read_count_access);

    printf("Reader %d finished reading.\n", id);
    return NULL;
}

void *writer(void *arg) {
    int id = *(int *)arg;

    printf("Writer %d is waiting to write...\n", id);
    sem_wait(&resource_access);

    printf("Writer %d is writing...\n", id);
    sleep(2);

    sem_post(&resource_access);
    printf("Writer %d finished writing.\n", id);
    return NULL;
}

int main() {
    pthread_t readers[5], writers[2];
    int ids[5] = {1, 2, 3, 4, 5};
    int i;

    sem_init(&resource_access, 0, 1);
    sem_init(&read_count_access, 0, 1);

    for (i = 0; i < 2; i++) {
        pthread_create(&writers[i], NULL, writer, &ids[i]);
    }
    for (i = 0; i < 5; i++) {
        pthread_create(&readers[i], NULL, reader, &ids[i]);
    }

    for (i = 0; i < 5; i++) {
        pthread_join(readers[i], NULL);
    }
    for (i = 0; i < 2; i++) {
        pthread_join(writers[i], NULL);
    }

    sem_destroy(&resource_access);
    sem_destroy(&read_count_access);

    return 0;
}
