#include <bits/stdc++.h>
using namespace std;

void solve(){
    int n,m; cin >> n >> m;
    vector<int> adj[n+1];
    for(int i=0;i<m;i++){
        int u,v; cin >> u >> v;
        adj[u].push_back(v);
    } 
    
    /* Using Kahn's Algorithm */
    vector<int> inDeg(n+1,0);
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

    vector<int> dp(n+1,0); dp[n] = 1;
    vector<int> mx(n+1,-1);
    for(int i = n-2; i >= 0; i--){
        int u = topo[i]; /* # of ways from u ---> n */
        int max_cost = 0, max_node = 
        for(auto neib : adj[u]){
            if(dp[neib] > max_cost){
                max_cost = dp[neib];
                max_node = neib;
            }
        }

    }

    cout << dp[1] << endl;
}

int main(){
    solve();
    return 0;
}