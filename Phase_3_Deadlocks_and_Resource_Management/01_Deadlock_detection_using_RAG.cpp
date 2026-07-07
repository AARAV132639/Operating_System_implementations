#include <iostream>
#include <vector>

using namespace std;

const int NODES = 5;

vector<int>graph[NODES];
bool visited[NODES];
bool recStack[NODES];

bool dfs(int node)
{
    visited[node] = true;
    recStack[node] = true;

    for(int next: graph[node])
    {
        if(!visited[next])
        {
            if(dfs(next)) return true;

        }

        else if(recStack[next]) return true;
    }
    recStack[node] = false;
    return false;
}

bool detectDeadlock()
{
    for(int i=0;i<NODES; i++)
    {
        visited[i] = false;
        recStack[i] = false;
    }

    for(int i =0; i<NODES; i++)
    {
        if(!visited[i]) if(dfs(i)) return true;
    }
    return false;
}


int main()
{
    /*Nodes
    
    0 = P0
    1= p1
    2= p2
    3 =p0
    4= r1
    */

    graph[0].push_back(3);
    graph[3].push_back(1);
    graph[1].push_back(4);

    //graph[4].push_back(0); //deadlock condition

    if(detectDeadlock()) cout<< "Deadlock detected\n";
    else cout<<"No deadlock";

}