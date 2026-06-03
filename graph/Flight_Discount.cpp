#include <bits/stdc++.h>
using namespace std;

void solve(){
    int n,m; cin >> n >> m;
    vector< pair<int,int> > adj[n+1];
    for(int i=0;i<m;i++){
        int a,b,c; cin >> a >> b >> c;
        adj[a].push_back({b,c});
    }

    vector<vector<int64_t>> dist(n+1,vector<int64_t>(2,LLONG_MAX)); 
    dist[1][0] = 0; 
    priority_queue< vector<int64_t>, vector<vector<int64_t>>, greater<vector<int64_t>> > pq;
    pq.push({0,0,1}); 

    while(!pq.empty()){
        vector<int64_t> x = pq.top(); pq.pop();
        int64_t d = x[0], coup = x[1], node = x[2];

        if(dist[node][coup] < d) continue;

        if(coup == 0){ /* coupon is not used so far. */
            for(auto neib : adj[node]){
                  int64_t adjNode = neib.first, edgeWt = neib.second;
                  /*1. Don't use coupon. */
                  if(d + edgeWt < dist[adjNode][0]){
                        dist[adjNode][0] = d + edgeWt;
                        pq.push({dist[adjNode][0], 0, adjNode});
                  }

                  /*2. Use the coupon. */
                  if(d + (edgeWt/2) < dist[adjNode][1]){
                        dist[adjNode][1] = d + (edgeWt/2);
                        pq.push({dist[adjNode][1], 1, adjNode});
                  }
            }
        }
        else{ /* coupon is used. */
            for(auto neib : adj[node]){
                  int64_t adjNode = neib.first, edgeWt = neib.second;
                  /*1. Don't use coupon. */
                  if(d + edgeWt < dist[adjNode][1]){
                        dist[adjNode][1] = d + edgeWt;
                        pq.push({dist[adjNode][1], 1, adjNode});
                  }
            }
        }
    }

    cout << dist[n][1] << '\n';
}

int main(){
    solve();
    return 0;
}