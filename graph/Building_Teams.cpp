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

    vector<int> col(n+1,0);
    for(int i=1;i<=n;i++){
        if(col[i] == 0){
            queue<int> q; q.push(i); /* src = 1 */
            col[i] = 1;

            while(!q.empty()){
                int neib_cnt = q.size();
                while(neib_cnt--){
                    int node = q.front(); q.pop();

                    for(auto neib : adj[node]){
                        if(col[neib] == 0){
                            q.push(neib);
                            col[neib] = (col[node] == 1) ? 2 : 1;
                        }
                        else if(col[neib] == col[node]){
                            cout << "IMPOSSIBLE" << endl;
                            return;
                        }
                    }
                }
            }
        }
    }

    for(int i=1;i<=n;i++) cout << col[i] << " ";
    cout << endl;
}

int main(){
    solve();
    return 0;
}