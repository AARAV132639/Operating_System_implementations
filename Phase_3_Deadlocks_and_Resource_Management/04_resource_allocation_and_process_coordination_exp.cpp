#include<algorithm>
#include <pthread.h>
#include<vector>
#include<iostream>
#include <unistd.h>

using namespace std;

//declaring resources

//Each resource has its own mutex and own variable condition
struct Resource
{
    bool allocated = false;
    int owner =-1;

    pthread_mutex_t mutex;
    pthread_cond_t cond;
};

//process structure
struct Process
{
    int id;
    vector<int> required;
};

vector<Resource> resources;

//Request Function
void acquire(Process &p, vector<Resource>&resources)
{
    vector<int>req = p.required;

    //global resource ordering
    sort(req.begin(), req.end());

    for(int id: p.required)
    {
        pthread_mutex_lock(&resources[id].mutex);

        while(resources[id].allocated)
        {
            pthread_cond_wait(&resources[id].cond, &resources[id].mutex);
        }

        resources[id].allocated = true;
        resources[id].owner = p.id;

        cout<<"P" <<p.id<<"acquired R"<<id<<endl;

        pthread_mutex_unlock(&resources[id].mutex);
    }
}

//Release function

void release ( Process &p, vector<Resource> & resources)
{
    vector<int>req = p.required;
    sort(req.begin(), req.end());

    for(int id: p.required)
    {
        pthread_mutex_lock(&resources[id].mutex);

        resources[id].allocated = false;
        resources[id].owner = -1;

        pthread_cond_signal(&resources[id].cond); //wakes up one waiting thread

        cout<<"P"<<p.id<< " released R"<<id<<endl;

        pthread_mutex_unlock(&resources[id].mutex);
    }
}

//thread function
void* worker(void* arg)
{
    Process *p = (Process*) arg;

    acquire(*p, resources);

    cout<<"P"<<p->id<<"executing\n";

    sleep(2);

    release(*p, resources);

    return NULL;
}

//main function

int main()
{
    resources.resize(3);
   

    for(int i=0;i<3;i++)
    {
        pthread_mutex_init(&resources[i].mutex, NULL);

        pthread_cond_init(&resources[i].cond, NULL);
    }

    vector<Process>processes=
    {
        {0,{0,1}},
        {1,{1,2}},
        {2,{0}}
    };

    pthread_t threads[3];

    for(int i=0; i<3; i++) pthread_create(&threads[i], NULL, worker, &processes[i]);
   
    for(int i=0;i<3;i++) pthread_join(threads[i], NULL);

    for(int i=0; i<3; i++) 
    {
        pthread_mutex_destroy(&resources[i].mutex);
        pthread_cond_destroy(&resources[i].cond);
    }

    return 0;
}