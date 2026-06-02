#include <bits/stdc++.h>
using namespace std;

void dfs(int node, vector<int> adj[], vector<int> &vis){
    vis[node] = 1;
    for(auto nb : adj[node]){
        if(!vis[nb]) dfs(nb,adj,vis);
    }
}

void solve(){
    int n,m; cin >> n >> m;
    vector<int> adj[n+1]; /* adj[i] : neighbours of node-i (1 based index) */
    for(int i=0;i<m;i++){
        int a,b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    vector<int> vis(n+1,0);
    vector<int> comp;
    for(int i=1;i<=n;i++){
        if(!vis[i]){
            dfs(i,adj,vis);
            comp.push_back(i); /* i - representative of cur component */
        }
    }

    cout << comp.size() - 1 << endl;
    for(int i = 0; i+1 < (int)comp.size(); i++){
        cout << comp[i] << " " << comp[i+1] << endl;
    }
}

int main(){
    solve();
    return 0;
}