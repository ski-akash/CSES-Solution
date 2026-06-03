#include <bits/stdc++.h>
using namespace std;

vector<int> Rank, par, sz;
int comp, maxSize;

int find(int node){
    if(node == par[node]) return node;
    return par[node] = find(par[node]);
}

void merge(int u, int v){
    int U = find(u), V = find(v);
    if(U == V) return;
    comp --;
    if(Rank[U] < Rank[V]){
        par[U] = V; sz[V] += sz[U];
    } 
    else if(Rank[U] > Rank[V]){
        par[V] = U; sz[U] += sz[V];
    } 
    else{
        par[U] = V; sz[V] += sz[U];
        Rank[V] ++;
    }
    maxSize = max({maxSize,sz[U],sz[V]});
}

void solve(){
    int n,m; cin >> n >> m;

    comp = n, maxSize = 1;
    Rank.resize(n+1,0);
    sz.resize(n+1,1);
    par.resize(n+1);
    for(int i=1;i<=n;i++) par[i] = i;

    for(int i=0;i<m;i++){
        int u,v; cin >> u >> v; 
        /* u --- v */
        merge(u,v);
        cout << comp <<" "<< maxSize << '\n';
    }
}

int main(){
    solve();
    return 0;
}