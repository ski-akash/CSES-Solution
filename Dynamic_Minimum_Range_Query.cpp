/* Problem: 
            for each query qi -
            1 k u => update a[k] = u
            2 a b => Find minimum in Range [a,b]
*/

/* Implementation using Segment Trees */

#include <bits/stdc++.h>
using namespace std;

vector<int> st;

void build(int node, int l, int r, vector<int> &a){
    // base case :: leaf node
    if(l == r) {
        st[node] = a[l];
        return;
    }

    // rec rln ::
    int mid = l + (r-l)/2;
    build(2*node+1,l,mid,a); /* Build Left Subtree */
    build(2*node+2,mid+1,r,a); /* Build Right Subtree */
    
    st[node] = min(st[2*node+1], st[2*node+2]); /* update the parent node */
}

int query(int node, int L, int R, int l, int r){
    // base cases : 2 
    /* 1. Complete Overlap */  /*    L  [l,r] R    */
    if(L <= l && r <= R) return st[node];

    /* 2. No Overlap */ /* [l,r] L R [l,r] */
    if(r < L || R < l) return INT_MAX;

    // rec rln ::
    /* Partial Overlap */
    int mid = l + (r-l)/2;
    int left_query = query(2*node+1,L,R,l,mid);
    int right_query = query(2*node+2,L,R,mid+1,r);
    return min(left_query, right_query);
}

void update(int node, int l, int r, int indx, int val){
    // base case :: {l = r} 
    if(l == r){
        st[node] = val;
        return;
    }

    // rec rln ::
    int mid = l + (r-l)/2;
    /*key idea? Update only takes place for one side */
    if(indx <= mid) update(2*node+1,l,mid,indx,val); /* update the left part only */
    else update(2*node+2,mid+1,r,indx,val); /* update the right part only */

    st[node] = min(st[2*node+1], st[2*node+2]);
}

int main(){
    int n,q; cin >> n >> q;
    vector<int> a(n);
    for(int i=0;i<n;i++) cin >> a[i];

    /* build segment tree */
    st.resize(4*n,INT_MAX);
    build(0,0,n-1,a);

    while(q--){
        int t; cin >> t;
        if(t == 1){
            int k, u; cin >> k >> u;
            update(0,0,n-1,k-1,u);
        }
        else{
            int L, R; cin >> L >> R;
            L = L-1; R = R-1; /* convert to 0-based indexing */
            cout << query(0,L,R,0,n-1) << endl;
        }
    }
    return 0;
}