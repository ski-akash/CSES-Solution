#include <bits/stdc++.h>
using namespace std;

vector<int> Rank, par;
int comp;
int64_t mst_sum;

int find(int node){
    if(node == par[node]) return node;
    return par[node] = find(par[node]);
}

void merge(int u, int v, int edgeWt){
    int U = find(u), V = find(v);
    if(U == V) return;
    comp --;
    mst_sum += edgeWt;
    if(Rank[U] < Rank[V]){
        par[U] = V; 
    } 
    else if(Rank[U] > Rank[V]){
        par[V] = U; 
    } 
    else{
        par[U] = V; 
        Rank[V] ++;
    }
}

void solve(){
    int n,m; cin >> n >> m;

    comp = n, mst_sum = 0;
    Rank.resize(n+1,0);
    par.resize(n+1);
    for(int i=1;i<=n;i++) par[i] = i;

    vector<vector<int>> edges(m,vector<int>(3));
    for(int i=0;i<m;i++){
        int u,v,wt; cin >> u >> v >> wt;
        edges[i] = {u,v,wt};
    }

    sort(edges.begin(),edges.end(),[](const vector<int>& a, const vector<int>& b){
        return a[2] < b[2];
    });

    for(auto it : edges){
        int u = it[0], v = it[1], edgeWt = it[2];
        merge(u,v,edgeWt);
    }

    if(comp == 1) cout << mst_sum << '\n';
    else cout << "IMPOSSIBLE";
}

int main(){
    solve();
    return 0;
}