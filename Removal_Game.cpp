#include <bits/stdc++.h>
using namespace std;

/* Think it as like storing score diff. */
int64_t dp[5001][5001];

int64_t dfs(int i, int j, vector<int> &a){
    // base case ::
    if(i > j) return 0;

    // memo ::
    if(dp[i][j] != -1) return dp[i][j];

    // rec rln ::
    int64_t score = max(a[i] - dfs(i+1,j,a), a[j] - dfs(i,j-1,a));
    return dp[i][j] = score;
}

int main(){
    int n; cin >> n;
    vector<int> a(n);
    for(int i=0;i<n;i++) cin >> a[i];

    memset(dp,-1,sizeof(dp));
    int64_t D = dfs(0,n-1,a);
    int64_t S = 0;
    for(int elem : a) S += elem;

    cout << (S+D)/2 << endl;

    return 0;
}