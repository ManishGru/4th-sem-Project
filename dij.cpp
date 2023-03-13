#include <iostream>
#include <limits.h>

using namespace std;

#define vertices 9
int minDist(int dist[], bool sptSet[])
{
    int min = INT_MAX, min_index;

    for (int i = 0; i < vertices; i++)
    {

        if (sptSet[i] == false && min >= dist[i])

        {

            min = dist[i], min_index = i;
        }
    }
    cout << "choosing min vertices" << endl;
    return min_index;
}

void printsln(int dist[])
{
    cout << "Vertex \t\t\t Distance from Source" << endl;
    for (int i = 0; i < vertices; i++)
    {
        cout << i << " \t\t\t\t" << dist[i] << endl;
    }
}

void dij(int graph[vertices][vertices], int src)
{
    /*----------------------*/
    int dist[vertices];
    bool sptSet[vertices];

    for (int i = 0; i < vertices; i++)
    {
        dist[i] = INT_MAX;
        sptSet[i] = false;
    }
    dist[src] = 0;
    /*----------------------*/
    for (int i = 0; i < vertices - 1; i++)
    {
        cout << "Traversed i = " << i << " th verteces" << endl;
        int u = minDist(dist, sptSet);
        cout << "u   " << u << endl;
        sptSet[u] = true;

        for (int j = 0; j < vertices; j++)
        {
            cout << "Traversed j = " << j << " th verteces" << endl;

            if (!sptSet[j] && graph[u][j] && dist[u] != INT_MAX && dist[u] + graph[u][j] < dist[j])
            {
                // cout << "c vf  " << u << endl;

                dist[j] = dist[u] + graph[u][j];
                cout << "c vf  " << j << endl;
            }
        }
    }
    printsln(dist);
}
int main()
{

    int graph[vertices][vertices] = {{0, 4, 0, 0, 0, 0, 0, 8, 0},
                                     {4, 0, 8, 0, 0, 0, 0, 11, 0},
                                     {0, 8, 0, 7, 0, 4, 0, 0, 2},
                                     {0, 0, 7, 0, 9, 14, 0, 0, 0},
                                     {0, 0, 0, 9, 0, 10, 0, 0, 0},
                                     {0, 0, 4, 14, 10, 0, 2, 0, 0},
                                     {0, 0, 0, 0, 0, 2, 0, 1, 6},
                                     {8, 11, 0, 0, 0, 0, 1, 0, 7},
                                     {0, 0, 2, 0, 0, 0, 6, 7, 0}};

    dij(graph, 0);
    return 0;
}
