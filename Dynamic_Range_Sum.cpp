#include <bits/stdc++.h>
using namespace std;

/* Implementation of Fenwick Trees - Easiest to Build */
vector<int64_t> fn;
int N;

/* Build Fenwick Tree */
void build(vector<int> &arr){
    /* Obvious Approach := n * lg(n) */
    /* Optimized Approach := n */

    for(int i=1;i<=N;i++){
        fn[i] += arr[i];   
        int par = i + (i&-i);
        if(par <= N) fn[par] += fn[i]; /* Just check for the parent only!! */
    }
}

/* Sum Query */
int64_t sum(int R){
    int64_t S = 0;
    while(R > 0){
        S += fn[R];
        R = R - (R & -R);
    }
    return S;
}

/* Add */
void add(int indx, int u){
    while(indx <= N){
        fn[indx] += u;
        indx = indx + (indx & -indx);
    }
} 

int main(){
    int n,q; cin >> n >> q;
    vector<int> a(n);
    for(int i=0;i<n;i++) cin >> a[i];

    a.insert(a.begin(),0);
    fn.resize(n+1,0);
    N = n;
    build(a);

    while(q--){
        int t, u, v ; cin >> t >> u >> v;
        if(t == 1){
            add(u, v - a[u]);
            a[u] = v;
        }
        else{
            cout << sum(v) - sum(u-1) << endl;
        }
    }

    return 0;
}