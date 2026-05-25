#include <bits/stdc++.h>
using namespace std;

int64_t dp[20][2][10][2];

int64_t dfs(int pos, int tight, int prev, int lz, string digit){
    // base case ::
    if(pos == digit.size()) return 1;

    // memo ::
    if(dp[pos][tight][prev][lz] != -1) return dp[pos][tight][prev][lz];

    // rec rln ::
    int limit = tight ? digit[pos] - 48 : 9;
    int64_t cnt = 0;

    for(int d = 0; d <= limit; d++){
        int new_lz = lz & (d == 0);
        if( d == prev && new_lz == 0 ) continue;

        int new_tight = tight & (d == limit);
        
        cnt += dfs(pos+1,new_tight,d,new_lz,digit);
    }

    return dp[pos][tight][prev][lz] = cnt;
}

int main(){
    int64_t a,b; cin >> a >> b;

    memset(dp,-1,sizeof(dp));
    int64_t B = dfs(0,1,-1,1,to_string(b));

    if(a == 0){
        cout << B << endl;
        return 0;
    }

    memset(dp,-1,sizeof(dp));
    int64_t A = dfs(0,1,-1,1,to_string(a-1));

    cout << B - A << endl;
    return 0;
}