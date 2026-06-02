#include <bits/stdc++.h>
using namespace std;

bool hasCycle = false;
vector<int> path;
int s = -1;

void dfs(int node, vector<int> adj[], vector<int> &state){
    state[node] = 1;
    path.push_back(node);

    for(auto neib : adj[node]){
        if(state[neib] == 0){
            dfs(neib,adj,state);
            if(hasCycle) return;
        }
        else if(state[neib] == 1){
            s = neib;
            hasCycle = true;
            return;
        }
    }

    state[node] = 2;
    path.pop_back();
}

void solve(){
    int n,m; cin >> n >> m;
    vector<int> adj[n+1]; /* adj[i] : neighbours of node-i (1 based index) */
    for(int i=0;i<m;i++){
        int a,b; cin >> a >> b;
        adj[a].push_back(b);
    }

    /* using 3-state approach */
    vector<int> state(n+1,0);
    for(int i=1;i<=n;i++){
        if(state[i] == 0){
            dfs(i,adj,state);
            if(hasCycle){
                vector<int> ans;
                ans.push_back(s);
                for(int j=path.size()-1;j>=0;j--){
                    ans.push_back(path[j]);
                    if(path[j] == s) break;
                }
                
                reverse(ans.begin(),ans.end());
                cout << ans.size() << endl;
                for(int elem : ans) cout << elem << " ";
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
