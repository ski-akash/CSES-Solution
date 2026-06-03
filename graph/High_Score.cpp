#include <bits/stdc++.h>
using namespace std;

/* Inspired by Bellman Ford Algo. */

bool canReach(int node, int n, vector<int> adj[], vector<int> &vis){
    if(node == n) return true;
    vis[node] = 1;
    for(auto neib : adj[node]){
        if(!vis[neib]){
            if(canReach(neib,n,adj,vis) == true) return true;
        }
    }
    return false;
}

void solve(){
    int n,m; cin >> n >> m;
    vector<vector<int>> edges(m,vector<int>(3));
    vector<int> adj[n+1];
    for(int i=0;i<m;i++){
        int u, v, c; cin >> u >> v >> c;
        edges[i] = {u, v, c};
        adj[u].push_back(v);
    }

    vector<int64_t> dist(n+1,LLONG_MIN); dist[1] = 0;
    for(int i=1;i<n;i++){
        /* V-1 Iterations */
        for(auto it : edges){
            int u = it[0], v = it[1], edgeWt = it[2];
            if(dist[u] != LLONG_MIN) dist[v] = max(dist[v], dist[u] + edgeWt);
        }
    }

    // check for positive cycle:
    /* V-th Iterations */
    vector<int> affected;
    for(auto it : edges){
        int u = it[0], v = it[1], edgeWt = it[2];
        if(dist[u] != LLONG_MIN){
            if(dist[u] + edgeWt > dist[v]) affected.push_back(v);
        } 
    }

    vector<int> vis(n+1,0);
    for(int node : affected){
        if(!vis[node] && canReach(node,n,adj,vis) == true){
            cout << "-1";
            return;
        }
    }

    cout << dist[n];

}

int main(){
    solve();
    return 0;
}