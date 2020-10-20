#include <iostream>
#include <vector>

using namespace std;



class BellmanFord {
    int N;
    vector<vector<int>> edges;
    int source;
    
    vector<int> shortestDistance() {
        vector<int> dist(N+1, INT_MAX);
        dist[source] = 0;
        
        for (int i = 0; i < N; i++) {
            for (auto edge : edges) {
                int u = edge[0];
                int v = edge[1];
                int w = edge[2];
                if (dist[u] != INT_MAX and dist[v] > dist[u] + w) {
                    dist[v] = dist[u] + w;
                }
            }
        }
        
        dist.erase(dist.begin());
        return dist;
    }
}

