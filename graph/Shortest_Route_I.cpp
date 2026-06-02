#include <bits/stdc++.h>
using namespace std;

void solve(){
    int n,m; cin >> n >> m;
    vector< pair<int,int> > adj[n+1];
    for(int i=0;i<m;i++){
        int a,b,c; cin >> a >> b >> c;
        adj[a].push_back({b,c});
    }

    vector<int64_t> dist(n+1,LLONG_MAX); dist[1] = 0;
    priority_queue< pair<int64_t,int64_t> , vector< pair<int64_t,int64_t> >, greater< pair<int64_t,int64_t> > > pq; pq.push({0,1});
    
    while(!pq.empty()){
        int64_t d = pq.top().first, node = pq.top().second; pq.pop();
        if(d > dist[node]) continue;
        for(auto neib : adj[node]){
            int adjNode = neib.first, edgeWt = neib.second;
            if(d + edgeWt < dist[adjNode]){
                dist[adjNode] = d + edgeWt;
                pq.push({dist[adjNode], adjNode});
            }
        }
    }

    for(int i=1;i<=n;i++) cout << dist[i] << " ";
}

int main(){
    solve();
    return 0;
}