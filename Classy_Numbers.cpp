#include <bits/stdc++.h>
using namespace std;

int64_t dp[20][2][4];

int64_t dfs(int pos, int tight, int nz, const string &digit){
    // base case ::
    if(nz > 3) return 0;
    if(pos == digit.size()) return nz <= 3;

    // memo ::
    if(dp[pos][tight][nz] != -1) return dp[pos][tight][nz];

    // rec rln ::
    int64_t cnt = 0;
    int limit = tight ? digit[pos] - 48 : 9;
    
    for(int d = 0; d <= limit; d++){
        int new_tight = tight & (d == limit);

        if(d == 0) cnt += dfs(pos+1,new_tight,nz,digit);
        else cnt += dfs(pos+1,new_tight,nz+1,digit);
    }

    return dp[pos][tight][nz] = cnt;
}

int main(){
    int tc; cin >> tc;
    while(tc--){
        int64_t L,R; cin >> L >> R;
        
        memset(dp,-1,sizeof(dp));
        int64_t B = dfs(0,1,0,to_string(R));

        memset(dp,-1,sizeof(dp));
        int64_t A = dfs(0,1,0,to_string(L-1));

        cout << B - A << endl;
    }

    return 0;
}