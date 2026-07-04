#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5
#define ITEMS 10

int buffer[BUFFER_SIZE];
int in = 0;
int out = 0;

pthread_mutex_t mutex;
sem_t empty;
sem_t full;

void *producer(void *args)
{
    for(int item =1; item <= ITEMS; item++)
    {
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);

        buffer[in] = item;

        printf("Produced %d at index %d\n", item, in);

        in = (in +1)%BUFFER_SIZE;

        pthread_mutex_unlock(&mutex);
        sem_post(&full);

        sleep(3); //for readibility, No connection to synchronization
    }
    return NULL;
}

void *consumer(void *arg)
{
    for(int i=0; i< ITEMS; i++)
    {
        sem_wait(&full);

        pthread_mutex_lock(&mutex);

        int item = buffer[out];

        printf("Consumed %d from index %d\n", item, out);

        out = (out+1)% BUFFER_SIZE;

        pthread_mutex_unlock(&mutex);

        sem_post(&empty);

       sleep(2);
    }
    return NULL;
}

int main()
{
    pthread_t prod, cons;

    pthread_mutex_init(&mutex, NULL);

    sem_init(&empty, 0, BUFFER_SIZE);

    sem_init(&full,0,0);

    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}