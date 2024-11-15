#include <iostream>
#include <vector>

using namespace std;

vector<int> bellmanFord(vector<vector<int>> &edges, int V, int src){
    //all distances from src is inf
    vector<int> dist(V,1e8);
    dist[src] = 0 ; //dist of src to src is 0

    for(int i=1; i<V+1; i++){
        for(vector<int> edge : edges){
            int u = edge[0];
            int v = edge[1];
            int wt = edge[2];
            //relaxation possible or not
            if(dist[u] != 1e8 && dist[u]+wt < dist[v]){
                //Vth relaxation
                if(i == V){
                    return {-1};
                }
                //update dist
                dist[v] = dist[u]+wt;
            }
        }
    }

    return dist;
}

int main(){
    vector<vector<int>> edges = {{1, 3, 2}, {4, 3, -1}, {2, 4, 1}, 
                                 {1, 2, 1}, {0, 1, 5}};

    int src = 0;
    int V = 5;
    vector <int> ans = bellmanFord(edges,V,src);

    for (int dist : ans) 
        cout << dist << " ";
    return 0;
}