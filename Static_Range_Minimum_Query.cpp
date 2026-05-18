/* Problem :-
            process each query qi - {a, b}
            Find Minimum in range[a,b]?
*/

/*
    Implementation using Sparse Table
    allows query resolve in O(1)
*/

#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 2 * 100000 + 7;
const int LOG = 18;

int m[MAX_N][LOG];

int main(){
    int n,q; cin >> n >> q;
    vector<int> a(n);
    for(int i=0;i<n;i++) cin >> a[i];

    /* Fill sparse table m[][] */
    // m[i][j] = minimum in range [i,i+2^j-1]
    
    for(int i=0;i<n;i++) m[i][0] = a[i];
    for(int j=1;j<LOG;j++){
        for(int i=0;i+(1<<j)-1 < n;i++){
            m[i][j] = min( m[i][j-1], m[i + (1<<(j-1))][j-1] );
        }
    }

    while(q--){
        int L,R; cin >> L >> R;
        L = L-1; R = R-1; /* change to 0-based indexing */

        /* Find minimum in range [L,R] */
        int len = (R-L+1);
        int j = 31 - __builtin_clz(len); /* max power of 2 <= len*/

        // q[L,R] = min { m[L][j], m[?][j] }
        cout << min(m[L][j], m[R-(1<<j)+1][j]) << endl;
    }
    return 0;
}