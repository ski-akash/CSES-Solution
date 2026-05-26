/* Implementation using Segment Trees */

#include <bits/stdc++.h>
using namespace std;

const int64_t MINIMUM = -1e15;
struct Node{
    int64_t start, end, max, sum;
};

vector<Node> st;

int64_t mx(const int64_t &a, const int64_t &b, const int64_t &c){
    if(a > b && a > c) return a;
    if(b > a && b > c) return b;
    return c;
}

Node merge(const Node &left, const Node &right){
    Node node;

    node.sum = left.sum + right.sum;
    node.max = mx(left.max, right.max, left.end + right.start);
    node.start = max(left.start, left.sum + right.start);
    node.end = max(right.end, right.sum + left.end);

    return node;
}

void build(int node, int l, int r, vector<int> &a){
    // base case :: leaf node
    if(l == r) {
        st[node] = { max(0,a[l]), max(0,a[l]), max(0,a[l]), a[l] }; /* as max_prefix is 0 for negative element */
        return;
    }

    // rec rln ::
    int mid = l + (r-l)/2;
    build(2*node+1,l,mid,a); /* Build Left Subtree */
    build(2*node+2,mid+1,r,a); /* Build Right Subtree */
    
    st[node] = merge(st[2*node+1],st[2*node+2]);
}


void update(int node, int l, int r, int indx, int val){
    // base case :: {l = r} 
    if(l == r){
        st[node] = { max(0,val), max(0,val), max(0,val), val };
        return;
    }

    // rec rln ::
    int mid = l + (r-l)/2;
   
    if(indx <= mid) update(2*node+1,l,mid,indx,val); /* update the left part only */
    else update(2*node+2,mid+1,r,indx,val); /* update the right part only */

    st[node] = merge(st[2*node+1], st[2*node+2]);
}

Node query(int node, int L, int R, int l, int r){
    // No overlap :: [l,r] L R [l,r]
    if(r < L || R < l) return { MINIMUM, MINIMUM, MINIMUM, 0 };

    // Complete Overlap :: L [l,r] R
    if(L <= l && r <= R) return st[node];

    // Parital Overlap ::
    int mid = l + (r-l)/2;

    Node left_q = query(2*node+1,L,R,l,mid);
    Node right_q = query(2*node+2,L,R,mid+1,r);

    return merge(left_q, right_q);
}

int main(){
    int n,q; cin >> n >> q;
    vector<int> a(n);
    for(int i=0;i<n;i++) cin >> a[i];

    /* build segment tree */
    st.resize(4*n);
    build(0,0,n-1,a);

    while(q--){
        int k, x; cin >> k >> x;
        update(0,0,n-1,k-1,x);
    
        cout << query(0,0,n-1,0,n-1).max << endl;
    }

    return 0;
}