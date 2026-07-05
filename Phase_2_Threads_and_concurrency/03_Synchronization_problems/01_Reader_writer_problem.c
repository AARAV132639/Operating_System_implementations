# include <stdio.h>
# include <pthread.h>
#include <semaphore.h>
# include <unistd.h>

int sharedData = 0;
int readCount = 0;

pthread_mutex_t mutex;
sem_t wrt;

void* reader(void*arg)
{
    int id = *(int*) arg;

    pthread_mutex_lock(&mutex);

    readCount++;

    if(readCount==1) sem_wait(&wrt);

    pthread_mutex_unlock(&mutex);

    printf("Reader %d reads value %d\n",id, sharedData);

    //sleep(1);

    pthread_mutex_lock(&mutex);

    readCount--;

    if(readCount==0) sem_post(&wrt);

    pthread_mutex_unlock(&mutex);

    return NULL;
}

void* writer(void *arg)
{
    int id = *(int*) arg;

    sem_wait(&wrt);

    sharedData++;

    printf("Writer %d writes value %d\n", id, sharedData);

   // sleep(2);

    sem_post(&wrt);

    return NULL;
}

int main()
{
    pthread_t readers[5], writers[2];

    int rid[5] = {1,2,3,4,5};

    int wid[2] = {1,2}; // writer id and reader id

    pthread_mutex_init(&mutex, NULL);
    sem_init(&wrt,0,1);

    for(int i=0; i<5; i++) pthread_create(&readers[i], NULL, reader, &rid[i]);

    for(int i=0;i<2;i++) pthread_create(&writers[i],NULL, writer,&wid[i]);

    for(int i=0; i<5;i++) pthread_join(readers[i], NULL);

    for(int i=0; i<2;i++) pthread_join(writers[i], NULL);

    pthread_mutex_destroy(&mutex);
    sem_destroy(&wrt);

    return 0;
}