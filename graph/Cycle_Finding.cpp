#include <bits/stdc++.h>
using namespace std;

void solve(){
    int n,m; cin >> n >> m;
    vector<vector<int>> edges(m,vector<int>(3,0));
    for(int i=0;i<m;i++){
        int a,b,c; cin >> a >> b >> c;
        edges[i] = {a, b, c};
    }

    vector<int64_t> dist(n+1,0); 
    vector<int> par(n+1,-1);
    for(int i=1;i<n;i++){
        for(auto it : edges){
            int u = it[0], v = it[1], edgeWt = it[2];
            if(dist[u] + edgeWt < dist[v]){
                dist[v] = dist[u] + edgeWt;
                par[v] = u;
            }
        }
    }

    int x = -1;  /* x :- one of the affected vertices */
    for(auto it : edges){
        int u = it[0], v = it[1], edgeWt = it[2];
        if(dist[u] + edgeWt < dist[v]){
            par[v] = u;
            dist[v] = dist[u] + edgeWt;
            x = v;
            break;
        }
    }

    if(x == -1) cout << "NO" << '\n';
    else{
        cout << "YES" << '\n';
        // move to cycle
        for(int i=0;i<n;i++) x = par[x];

        // print the cycle
        int start = x; x = par[x];
        vector<int> cycle; 
        while(x != start){
            cycle.push_back(x);
            x = par[x];
        }

        reverse(cycle.begin(),cycle.end());
        cout << start << " ";
        for(int elem : cycle) cout << elem << " ";
        cout << start << '\n';
    }

}

int main(){
    solve();
    return 0;
}