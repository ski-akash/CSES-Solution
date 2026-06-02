#include <bits/stdc++.h>
using namespace std;

void solve(){
    int n,m,q; cin >> n >> m >> q;
    vector<vector<int64_t>> dist(n+1,vector<int64_t>(n+1,LLONG_MAX));
    for(int i=1;i<=n;i++) dist[i][i] = 0;

    for(int i=0;i<m;i++){
        int a,b,c; cin >> a >> b >> c;
        if( c < dist[a][b] ){
            dist[a][b] = c;
            dist[b][a] = c;
        }
    }

    for(int k=1;k<=n;k++){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                /*
                   At kth iteration : 
                    dist[i][j] : shortest distance between Node-i and Node-j using {1,2,..k} as intermediate nodes.
                */
               if(dist[i][k] == LLONG_MAX || dist[k][j] == LLONG_MAX) continue;
               dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }

    while(q--){
        int a,b; cin >> a >> b;
        if(dist[a][b] == LLONG_MAX) cout << "-1" << endl;
        else cout << dist[a][b] << endl;
    }
}

int main(){
    solve();
    return 0;
}