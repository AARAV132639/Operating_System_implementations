#include <stdio.h>
#include<stdlib.h>
#include<pthread.h>


#define NUM_THREADS 5

//function exectued by each thread

void *printMessage(void *arg)
{
    int thread_id = *(int*)arg;

    printf("Hello from Thread %d\n", thread_id);

    pthread_exit(NULL);
}

int main()
{
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];

    //Create threads
    for(int i=0; i<NUM_THREADS;i++)
    {
        thread_ids[i]=i+1;

        if(pthread_create(&threads[i], NULL, printMessage, &thread_ids[i])!=0)
        {
            printf("Error creating thread %d\n",i+1);
            return 1;
        }
    }

    //Wait for all threads to finish
    for(int i=0; i< NUM_THREADS;i++)
    {
        pthread_join(threads[i], NULL);
    }

    printf("All threads have finished execution.\n");
    return 0;
}
