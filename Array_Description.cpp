#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;
int64_t dp[100005][101];

int64_t dfs(int i, int d, int m, vector<int> &a){
    // base case ::
    if(d < 1 || d > m) return 0; /* invalid a_i */
    //if(i == a.size()) return 1;

    // memo ::
    if(dp[i][d] != -1) return dp[i][d];

    // rec rln ::
    int64_t cnt = 0;
    if(a[i] != 0){
        if(a[i] == d){
           if(i == (int)a.size()-1) cnt = 1; 
           else cnt = ( dfs(i+1,d-1,m,a) % MOD + dfs(i+1,d+1,m,a) % MOD + dfs(i+1,d,m,a) % MOD) % MOD;
        }
    }
    else{
        if(i == (int)a.size()-1) cnt = 1;
        else cnt = ( dfs(i+1,d-1,m,a) % MOD + dfs(i+1,d+1,m,a) % MOD + dfs(i+1,d,m,a) % MOD ) % MOD;
    }

    return dp[i][d] = cnt;
}

int main(){
    int n,m; cin >> n >> m;
    vector<int> a(n); 
    for(int i=0;i<n;i++) cin >> a[i];

    memset(dp,-1,sizeof(dp));

    int64_t ans = 0;
    for(int j=1;j<=m;j++){
        int64_t cur = dfs(0,j,m,a) % MOD;
        ans = (ans % MOD + cur % MOD) % MOD;
    }

    cout << ans << endl;
    return 0;
}