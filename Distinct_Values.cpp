#include <bits/stdc++.h>
using namespace std;

/* Implementation of Fenwick Trees - Easiest to Build */
vector<int64_t> fn;
int N;

/* Build Fenwick Tree */
void build(){
    /* Obvious Approach := n * lg(n) */
    /* Optimized Approach := n */

    for(int i=1;i<=N;i++){   
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

    vector< vector<int> > Q(q);
    for(int i=0;i<q;i++){
        int a,b; cin >> a >> b;
        Q[i] = {a,b,i};
    }

    a.insert(a.begin(),0);
    fn.resize(n+1,0);
    N = n;

    build();

    sort(Q.begin(),Q.end(),[](const vector<int> &p1, const vector<int> &p2){
        return p1[1] < p2[1];
    });

    // for(auto it : Q) cout << it.first <<","<< it.second <<endl;

    map<int,int> m;
    for(int i=1;i<=n;i++) m[a[i]] = -1; /* -1 deontes a[i] is not added so far. */

    vector<int> ans(q);
    int j = 1; /* upto which index tree has been updated */
    for(int i=0;i<q;i++){
        int l = Q[i][0], r = Q[i][1], pos = Q[i][2];

        /* update the tree */
        for( ;j<=r;j++){
            int indx = m[a[j]];
            if(indx == -1) add(j,1);
            else{
                add(j,1); /* latest occurence */
                add(indx,-1); /* older occurence */
            }
            m[a[j]] = j;
        }
       
        ans[pos] = sum(r) - sum(l-1);
    }

    for(int i=0; i<q; i++) cout << ans[i] << endl;

    return 0;
}