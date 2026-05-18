/* Implementation using Segment Trees */

#include <bits/stdc++.h>
using namespace std;

vector<int> st1, st2;

void build1(int node, int l, int r, vector<int> &a){
    // base case :: leaf node
    if(l == r) {
        st1[node] = a[l] + (l+1);
        return;
    }

    // rec rln ::
    int mid = l + (r-l)/2;
    build1(2*node+1,l,mid,a); /* Build Left Subtree */
    build1(2*node+2,mid+1,r,a); /* Build Right Subtree */
    
    st1[node] = min(st1[2*node+1], st1[2*node+2]); /* update the parent node */
}

void build2(int node, int l, int r, vector<int> &a){
    // base case :: leaf node
    if(l == r) {
        st2[node] = a[l] - (l+1);
        return;
    }

    // rec rln ::
    int mid = l + (r-l)/2;
    build2(2*node+1,l,mid,a); /* Build Left Subtree */
    build2(2*node+2,mid+1,r,a); /* Build Right Subtree */
    
    st2[node] = min(st2[2*node+1], st2[2*node+2]); /* update the parent node */
}

int query1(int node, int L, int R, int l, int r){
    // base cases : 2 
    /* 1. Complete Overlap */  /*    L  [l,r] R    */
    if(L <= l && r <= R) return st1[node];

    /* 2. No Overlap */ /* [l,r] L R [l,r] */
    if(r < L || R < l) return INT_MAX;

    // rec rln ::
    /* Partial Overlap */
    int mid = l + (r-l)/2;
    int left_query = query1(2*node+1,L,R,l,mid);
    int right_query = query1(2*node+2,L,R,mid+1,r);
    return min(left_query, right_query);
}

int query2(int node, int L, int R, int l, int r){
    // base cases : 2 
    /* 1. Complete Overlap */  /*    L  [l,r] R    */
    if(L <= l && r <= R) return st2[node];

    /* 2. No Overlap */ /* [l,r] L R [l,r] */
    if(r < L || R < l) return INT_MAX;

    // rec rln ::
    /* Partial Overlap */
    int mid = l + (r-l)/2;
    int left_query = query2(2*node+1,L,R,l,mid);
    int right_query = query2(2*node+2,L,R,mid+1,r);
    return min(left_query, right_query);
}

void update1(int node, int l, int r, int indx, int val){
    // base case :: {l = r} 
    if(l == r){
        st1[node] = val + (indx + 1);
        return;
    }

    // rec rln ::
    int mid = l + (r-l)/2;
    /*key idea? Update only takes place for one side */
    if(indx <= mid) update1(2*node+1,l,mid,indx,val); /* update the left part only */
    else update1(2*node+2,mid+1,r,indx,val); /* update the right part only */

    st1[node] = min(st1[2*node+1], st1[2*node+2]);
}

void update2(int node, int l, int r, int indx, int val){
    // base case :: {l = r} 
    if(l == r){
        st2[node] = val - (indx + 1);
        return;
    }

    // rec rln ::
    int mid = l + (r-l)/2;
    /*key idea? Update only takes place for one side */
    if(indx <= mid) update2(2*node+1,l,mid,indx,val); /* update the left part only */
    else update2(2*node+2,mid+1,r,indx,val); /* update the right part only */

    st2[node] = min(st2[2*node+1], st2[2*node+2]);
}

int main(){
    int n,q; cin >> n >> q;
    vector<int> a(n);
    for(int i=0;i<n;i++) cin >> a[i];

    /* build segment tree */
    st1.resize(4*n,INT_MAX);
    st2.resize(4*n,INT_MAX);
    build1(0,0,n-1,a);
    build2(0,0,n-1,a);

    while(q--){
        int t; cin >> t;
        if(t == 1){
            int k, x; cin >> k >> x;
            update1(0,0,n-1,k-1,x);
            update2(0,0,n-1,k-1,x);
        }
        else{
            int k; cin >> k;
            int R = query1(0,k,n-1,0,n-1) - k;
            int L = query2(0,0,k-1,0,n-1) + k;
            cout << min(L, R) << endl;
        }
    }
    return 0;
}