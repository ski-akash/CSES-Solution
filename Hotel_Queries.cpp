/* Implementation using Segment Trees  as MAX Range Query */

#include <bits/stdc++.h>
using namespace std;

vector<int> st;
int sz;

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
    
    st[node] = max(st[2*node+1], st[2*node+2]); /* update the parent node */
}

int query(int node, int L, int R, int l, int r){
    // base cases : 2 
    /* 1. Complete Overlap */  /*    L  [l,r] R    */
    if(L <= l && r <= R) return st[node];

    /* 2. No Overlap */ /* [l,r] L R [l,r] */
    if(r < L || R < l) return INT_MIN;

    // rec rln ::
    /* Partial Overlap */
    int mid = l + (r-l)/2;
    int left_query = query(2*node+1,L,R,l,mid);
    int right_query = query(2*node+2,L,R,mid+1,r);
    return max(left_query, right_query);
}

int query_2(int node, int l, int r, int req_rooms ){
    // base case ::
    if(l == r) return l;

    // rec rln ::
    int mid = l + (r-l)/2;
    int left_max = query(0,l,mid,0,sz-1); 
    if(left_max >= req_rooms)
        return query_2(2*node+1,l,mid,req_rooms);
    
    return query_2(2*node+2,mid+1,r,req_rooms);
    
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

    st[node] = max(st[2*node+1], st[2*node+2]);
}

int main(){
    int n,m; cin >> n >> m;
    sz = n;
    vector<int> h(n), r(m);
    for(int i=0;i<n;i++) cin >> h[i];
    for(int i=0;i<m;i++) cin >> r[i];

    /* build segment tree */
    st.resize(4*n,INT_MIN);
    build(0,0,n-1,h);

    for(int i=0;i<m;i++){
        int indx = -1;
        if(query(0,0,n-1,0,n-1) < r[i]) cout << "0" << " ";
        else{
            // Now I know indx exists 
            indx = query_2(0,0,n-1,r[i]);
            cout << indx + 1 << " ";
        }

        if(indx != -1){
            update(0,0,n-1,indx,h[indx]-r[i]);
            h[indx] = h[indx] - r[i];
        }
    }

    return 0;
}