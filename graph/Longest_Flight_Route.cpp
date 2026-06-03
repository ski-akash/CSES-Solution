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

    vector<int> dp(n+1,INT_MIN); dp[n] = 1;
    vector<int> mx(n+1,-1);
    for(int i=n-1;i>=0;i--){
        int u = topo[i], v = -1;
        if(u == n) continue;
        for(auto neib : adj[u]){
            if(dp[neib] > dp[u]){
                dp[u] = dp[neib];
                v = neib;
            }
        }
        if(dp[u] != INT_MIN) dp[u] += 1;
        if(v != -1) mx[u] = v;
    }

    if(dp[1] == INT_MIN){
        cout << "IMPOSSIBLE" << '\n';
        return;
    }

    cout << dp[1] << endl; /* Max no of cities */

    int node = 1;
    while(true){
        cout << node << " ";
        if(node == n) break;
        node = mx[node];
    }
}

int main(){
    solve();
    return 0;
}