#include <bits/stdc++.h>
using namespace std;

bool hasCycle = false;
void dfs(int node, vector<int> adj[], vector<int> &state, vector<int> &topo){
    state[node] = 1;
    for(auto neib : adj[node]){
        if(state[neib] == 0) dfs(neib,adj,state,topo);
        else if(state[neib] == 1){
            hasCycle = true;
            return;
        }
    }
    topo.push_back(node);
    state[node] = 2;
}

void solve(){
    int n,m; cin >> n >> m;
    vector<int> adj[n+1];
    for(int i=0;i<m;i++){
        int u,v; cin >> u >> v;
        adj[u].push_back(v);
    }

    /* Using Kahn's Algorithm */
    /* vector<int> inDeg(n+1,0);
    for(int i=1;i<=n;i++){
        for(auto neib : adj[i]) inDeg[neib] += 1;
    }

    queue<int> q;
    for(int i=1;i<=n;i++) if(inDeg[i] == 0) q.push(i);

    vector<int> topo;
    while(!q.empty()){
        int node = q.front(); q.pop();
        topo.push_back(node);

        for(auto neib : adj[node]){
            inDeg[neib] -= 1;
            if(inDeg[neib] == 0) q.push(neib);
        } 
    }
    */

    /* 3- State Approach for cycle detection in directed graph */
    // 0 => unexplored
    // 1 => currently in DFS stack(exploring)
    // 2 => fully explored
    
    vector<int> topo, state(n+1,0);
    for(int i=1;i<=n;i++){
        if(state[i] == 0){
            dfs(i,adj,state,topo);
        }
    }

    reverse(topo.begin(),topo.end());

    if(hasCycle) cout << "IMPOSSIBLE" << '\n';
    else for(int elem : topo) cout << elem << " ";
}

int main(){
    solve();
    return 0;
}