#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define N 5

pthread_mutex_t forks[N];

void* philosopher(void* arg)
{
    int id = *(int*)arg;

    while(1) // Os examples use while(1) because philosophers represent long-running processes. A webserver never stops accepting requrest, A scheduler keeps scheduling etc
    {
        printf("Philosopher %d is thinking\n", id);
        sleep(1);

        int left = id;
        int right = (id + 1) % N;

        if(left > right)
        {
            int temp = left;
            left = right;
            right = temp;
        }

        pthread_mutex_lock(&forks[left]);
        pthread_mutex_lock(&forks[right]);

        printf("Philosopher %d is eating\n", id);
        sleep(2);

        pthread_mutex_unlock(&forks[right]);
        pthread_mutex_unlock(&forks[left]);
    }
}

int main()
{
    pthread_t phil[N];
    int id[N];

    for(int i = 0; i < N; i++)
        pthread_mutex_init(&forks[i], NULL);

    for(int i = 0; i < N; i++)
    {
        id[i] = i;
        pthread_create(&phil[i], NULL, philosopher, &id[i]);
    }

    for(int i = 0; i < N; i++)
        pthread_join(phil[i], NULL);

    return 0;
}