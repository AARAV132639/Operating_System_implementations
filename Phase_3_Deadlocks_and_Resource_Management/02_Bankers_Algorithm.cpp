#include<iostream>
#include<vector>

using namespace std;

int main()
{
    int processes = 5;
    int resources = 3;

    vector<vector<int>> allocation = {
        {0,1,0},
        {2,0,0},
        {3,0,2},
        {2,1,1},
        {0,0,2}
    };

    vector<vector<int>> maximum ={
        {7,5,3},
        {3,2,2},
        {9,0,2},
        {2,2,2},
        {4,3,3}
    };

    vector<int> available = {3,3,2};

    vector<vector<int>> need(processes, vector<int>(resources));

    for(int i=0;i<processes;i++) for(int j=0;j<resources;j++) need[i][j]= maximum[i][j]- allocation[i][j];

    vector<bool> finish(processes, false);

    vector<int> work = available;

    vector<int> safeSequence;

    while(true)
    {
        bool found = false;

        for(int i=0; i<processes; i++)
        {
            if(finish[i]) continue;

            bool possible = true;

            for(int j=0; j<resources; j++)
            {
                if(need[i][j]>work[j])
                {
                    possible = false;
                    break;
                }
            }

            if(possible)
            {
                for(int j=0; j<resources;j++) work[j]+= allocation[i][j];

                finish[i] = true;

                safeSequence.push_back(i);

                found = true;
            }
        }

        if(!found) break;
    }

    if(safeSequence.size()==processes)
    {
        cout<<"Safe State\n";
        cout<<"Safe Sequence: ";

        for(int p: safeSequence) cout<<"P"<<p<<" ";
        cout<<endl;
    }

    else cout<<"Unsafe State \n";

    return 0;

}