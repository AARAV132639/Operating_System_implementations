#include<iostream>
#include<vector>

using namespace std;

struct Resource
{
    bool allocated = false;
    int owner = -1;
};

struct Process
{
    int id; 
    vector<int>resources;
};

void release(Process &p, vector<Resource>&resources)
{
    for(int r: p.resources)
    {
        resources[r].allocated = false;
        resources[r].owner = -1;
    }

    p.resources.clear();
}

int chooseVictim(vector<Process>&processes)
{
    int victim = 0;

    int mx = processes[0].resources.size();

    for(int i=1; i<processes.size(); i++)
    {
        if(processes[i].resources.size()>mx)
        {
            mx = processes[i].resources.size();
            victim = i;
        }
    }

    return victim;
}

int main()
{
    vector<Resource>resources(4);

    vector<Process>processes = {
        {0,{1}},
        {1,{4,3,4}},
        {2,{1}}
    };

    for(auto&p: processes)
    {
        for(int r: p.resources)
        {
            resources[r].allocated = true;
            resources[r].owner = p.id;
        }
    }

    cout<<"Deadlock Detected\n";

    int victim = chooseVictim(processes);

    cout<<"Recovering...\n";

    release(processes[victim], resources);

    cout<<"Terminal Process P"<<victim<<endl;

    cout<<"Resources Released\n";
}
