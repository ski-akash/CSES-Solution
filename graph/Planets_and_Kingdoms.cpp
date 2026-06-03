#include <bits/stdc++.h>
using namespace std;

stack<int> st;
void dfs(int i, vector<int> adj[], vector<int> &vis){
    vis[i] = 1;
    for(auto neib : adj[i]) if(!vis[neib]) dfs(neib,adj,vis);
    st.push(i);
}

void visit(int node, vector<int> adjT[], vector<int> &comp, int k){
    comp[node] = k;
    for(auto neib : adjT[node]) if(comp[neib] == 0) visit(neib,adjT,comp,k);
}

void solve(){
    int n,m; cin >> n >> m;
    vector<int> adj[n+1];
    for(int i=0;i<m;i++){
        int u,v; cin >> u >> v;
        adj[u].push_back(v);
    }

    vector<int> vis(n+1,0);
    /* Using Kosaraju's SCC */

    /* 1. DFS : Push onto STACK */
    for(int i=1;i<=n;i++){
        if(!vis[i]){
            dfs(i,adj,vis);
        }
    }

    /* 2. Reverse edges : Transpose Graph */
    vector<int> adjT[n+1];
    for(int i=1;i<=n;i++){
        for(auto neib : adj[i]){
            adjT[neib].push_back(i);
        }
    }

    /*3. DFS : Pop out the element in DFS traversal */
    vector<int> comp(n+1,0);
    int k = 1;

    while(!st.empty()){
        if(comp[st.top()] == 0){
            visit(st.top(),adjT,comp,k); 
            k ++;
        }
        st.pop();
    }

    cout << k-1 << '\n';
    for(int i=1;i<=n;i++) cout << comp[i] << " ";
}

int main(){
    solve();
    return 0;
}