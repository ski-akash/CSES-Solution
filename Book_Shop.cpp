#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 100005;

int main(){
    int n,amt; cin >> n >> amt;
    vector<int> price(n), pages(n);
    for(int i=0;i<n;i++) cin >> price[i];
    for(int i=0;i<n;i++) cin >> pages[i];

    vector<int64_t> prev(amt+1,0);
    for(int i=0;i<n;i++){
        vector<int64_t> cur(amt+1,0);
        for(int j=0;j<=amt;j++){
            cur[j] = prev[j];
            if( (j-price[i]) >=0 ) cur[j] = max(cur[j], pages[i] + prev[j-price[i]]);
        }
        prev = cur;
    }

    cout << prev[amt] << endl;
    return 0;
}