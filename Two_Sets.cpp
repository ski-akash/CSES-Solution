#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;
const int INV2 = 500000004;
int dp[501][70000];

int f(int n, int sum){
    // base case ::
    if(sum < 0) return 0;
    if(n == 0) return sum == 0;

    // memo ::
    if(dp[n][sum] != -1) return dp[n][sum];

    // rec rln ::
    return dp[n][sum] = (f(n-1,sum)%MOD + f(n-1,sum-n)%MOD) % MOD;
}

int main(){
    int n; cin >> n;
    memset(dp,-1,sizeof(dp));

    int64_t sum = (n*(n+1))/2;

    if(sum&1) cout << 0 << endl;

    else cout << ((1LL) * f(n,sum/2) * INV2) % MOD << endl;

    return 0;
}