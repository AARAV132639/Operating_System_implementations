#define _POSIX_C_SOURCE 200809L //enables clock_gettime() and CLOCK_MONOTONIC

#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<time.h>

//Shared variables
#define THREADS 4
#define ITERATIONS 1000000

long long counter = 0;

pthread_mutex_t mutex;
sem_t semaphore;


//Race condition: Answer changes everytime because multiple threads update counter simulatneously
void* race(void *arg)
{
    for(int i=0; i<ITERATIONS;i++) counter++;
    return NULL;
}

//Mutex version
void* mutex_inc(void*arg)
{
    for(int i=0; i<ITERATIONS; i++)
    {
        pthread_mutex_lock(&mutex);
        counter++;
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

//Semphore version
void *semaphore_inc(void*arg)
{
    for(int i=0;i<ITERATIONS;i++)
    {
        sem_wait(&semaphore);
        counter++;
        sem_post(&semaphore);
    }
    return NULL;
}

void benchmark(void* (*func)(void*), const char*name)
{
    pthread_t threads[THREADS];

    counter = 0;

    struct timespec start, end;

    clock_gettime(CLOCK_MONOTONIC, &start);

    for(int i=0; i<THREADS;i++)  pthread_create(&threads[i],NULL,func,NULL);
   
    for(int i=0;i<THREADS; i++) pthread_join(threads[i], NULL);

    clock_gettime(CLOCK_MONOTONIC, &end);

    double time = (end.tv_sec-start.tv_sec) + (end.tv_nsec-start.tv_nsec)/1e9; //Elapsed time

    printf("%s\n", name);
    printf("Counter: %lld\n", counter);
    printf("Time  : %.6f sec\n\n", time);

}

int main()
{
    pthread_mutex_init(&mutex, NULL);
    sem_init(&semaphore, 0,1);

    benchmark(race, "Race Condition");

    benchmark(mutex_inc, "Mutex");

    benchmark(semaphore_inc, "Semaphore");

    pthread_mutex_destroy(&mutex);
    sem_destroy(&semaphore);

    return 0;
}

/*

## Insights:

[Q] Why is the Race Condition faster?

- Because it performs only: counter++

- There is no lock acquistion

- No waiting an no syncronization overhead.

- The downside is that the result is incorrect

[Q] Why is Mutex slower?

- Every increment requires: acquire mutex, increment, release mutex

- These operations add overhead but ensure correctnes

[Q] Why is semaphore slightly slower?

- Semaphore maintains a count and may involve additional book keeping compated to a mutex used solely for mutual exclusion

- For protecting a single critical section, a mutex is generally the preferred synchronization primitive

*/