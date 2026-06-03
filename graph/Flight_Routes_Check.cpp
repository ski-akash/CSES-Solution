#include <bits/stdc++.h>
using namespace std;

stack<int> st;
void dfs(int i, vector<int> adj[], vector<int> &vis){
    vis[i] = 1;
    for(auto neib : adj[i]) if(!vis[neib]) dfs(neib,adj,vis);
    st.push(i);
}

void visit(int node, vector<int> adjT[], vector<int> &vis){
    vis[node] = 1;
    for(auto neib : adjT[node]) if(!vis[neib]) visit(neib,adjT,vis);
}

bool canReach(int node, int dest, vector<int> adj[], vector<int> &vis){
    if(node == dest) return true;
    vis[node] = 1;
    for(auto neib : adj[node]){
        if(!vis[neib]){
            if(canReach(neib,dest,adj,vis)) return true;
        }
    }
    return false;
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
    fill(vis.begin(),vis.end(),0);
    vector<int> comp;
    while(!st.empty()){
        if(!vis[st.top()]){
            visit(st.top(),adjT,vis);
            comp.push_back(st.top());
            if(comp.size() == 2) break;
        }
        st.pop();
    }

    if(comp.size() == 1) cout << "YES" << '\n';
    else{
        cout << "NO" << '\n';
        fill(vis.begin(),vis.end(),0);
        if(canReach(comp[0],comp[1],adj,vis) == true) cout << comp[1] << " " << comp[0] ;
        else cout << comp[0] << " " << comp[1];
    }
}

int main(){
    solve();
    return 0;
}