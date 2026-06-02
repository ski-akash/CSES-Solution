#include <bits/stdc++.h>
using namespace std;

int _node = -1;
bool isCycle(int node, int par, vector<int> adj[], vector<int> &vis, vector<int> &path){
    vis[node] = 1;
    path.push_back(node);

    for(auto neib : adj[node]){
        if(!vis[neib]){
            if(isCycle(neib,node,adj,vis,path) == true) return true;
        }
        else if(neib != par){
            /* Found a Cycle: par --- node --- neib(!= par) len of cycle >= 3*/
            _node = neib;
            return true;
        }
    }

    path.pop_back();
    return false;
}

void solve(){
    int n,m; cin >> n >> m;
    vector<int> adj[n+1]; /* adj[i] : neighbours of node-i (1 based index) */
    for(int i=0;i<m;i++){
        int a,b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    vector<int> vis(n+1,0), path;
    for(int i=1;i<=n;i++){
        if(!vis[i]){
            if(isCycle(i,-1,adj,vis,path) == true){
                vector<int> ans; ans.push_back(_node);
                for(int j=path.size()-1;j>=0;j--){
                    ans.push_back(path[j]);
                    if(path[j] == _node) break;
                }

                cout << ans.size() << endl;
                for(int j=ans.size()-1;j>=0;j--) cout << ans[j] << " ";
                return;
            }
        }
    }

    cout << "IMPOSSIBLE" << endl;
}

int main(){
    solve();
    return 0;
}
