/*  Intuition :-
                assigning 0 to a remove element and 1 to a present element
                and use Segment Sum Tree.
                query_i = pi = find x such that sum of Range[1,x] = pi;
*/

#include <bits/stdc++.h>
using namespace std;

vector<int> st;
int sz;

void build(int node, int l, int r, vector<int> &a){
    // base case :: leaf node
    if(l == r) {
        st[node] = 1;
        return;
    }

    // rec rln ::
    int mid = l + (r-l)/2;
    build(2*node+1,l,mid,a); /* Build Left Subtree */
    build(2*node+2,mid+1,r,a); /* Build Right Subtree */
    
    st[node] = st[2*node+1] + st[2*node+2] ; /* update the parent node */
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

    st[node] = st[2*node+1] + st[2*node+2];
}

int query(int node, int l, int r, int p){
    // base case :: {leaf Node}
    if(l == r) return l;

    // rec rln ::
    int mid = l + (r-l)/2;
    int left_cnt = st[2*node+1];
    if(left_cnt >= p) return query(2*node+1,l,mid,p);
    return query(2*node+2,mid+1,r,p-left_cnt);
}

int main(){
    int n; cin >> n; 
    vector<int> a(n), p(n);
    for(int i=0;i<n;i++) cin >> a[i];
    for(int i=0;i<n;i++) cin >> p[i];

    st.resize(4*n,0); sz = n;
    build(0,0,n-1,a);

    for(int pi : p){
        int indx = query(0,0,n-1,pi);
        cout << a[indx] << " ";
        update(0,0,n-1,indx,0);
    }

    return 0;
}