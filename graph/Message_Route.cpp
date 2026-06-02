#include <bits/stdc++.h>
using namespace std;

void solve(){
    int n,m; cin >> n >> m;
    vector<int> adj[n+1]; /* adj[i] : neighbours of node-i (1 based index) */
    for(int i=0;i<m;i++){
        int a,b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    vector<int> vis(n+1,0);
    vector<int> par(n+1,-1);
    queue<int> q; q.push(1); /* src = 1 */
    vis[1] = 1;
    int dist = 0;

    while(!q.empty()){
        int neib_cnt = q.size();
        while(neib_cnt--){
            int node = q.front(); q.pop();
            
            /* dest = n */
            if(node == n){
                cout << dist + 1 << endl;
                vector<int> path;
                while(true){
                    path.push_back(node);
                    if(node == 1) break;
                    node = par[node];
                }
                for(int j=path.size()-1;j>=0;j--) cout << path[j] << " ";

                return;
            }

            for(auto neib : adj[node]){
                if(!vis[neib]){
                    q.push(neib);
                    vis[neib] = 1;
                    /* Parent -> Child :: node -> neib */
                    par[neib] = node;
                }
            }
        }
        dist += 1;
    }

    cout << "IMPOSSIBLE" << endl;
}

int main(){
    solve();
    return 0;
}