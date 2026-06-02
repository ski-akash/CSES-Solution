#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;
int dfs(int node, vector<int> adj[], vector<int> &dp){
    // base case ::
    if(node == (dp.size()-1)) return 1;
    
    // memo ::
    if(dp[node] != -1) return dp[node];

    // rec rln ::
    dp[node] = 0;
    for(auto neib : adj[node]){
        dp[node] = (dp[node] + dfs(neib,adj,dp)) % MOD; 
    }

    return dp[node];
}

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
    for(int i = n-1; i >= 0; i--){
        int u = topo[i]; /* # of ways from u ---> n */
        for(auto neib : adj[u]){
            dp[u] = (dp[u] + dp[neib]) % MOD;
        }
    }

    cout << dp[1] << endl;
}

int main(){
    solve();
    return 0;
}