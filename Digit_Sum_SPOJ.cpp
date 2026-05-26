#include <bits/stdc++.h>
using namespace std;
using ll = unsigned long long;

ll dp[17][2];
ll power[17];

ll dfs(int pos, int tight, string digit){
    // base case ::
    if(pos == digit.size()) return 0;

    // memo ::
    if(dp[pos][tight] != -1) return dp[pos][tight];

    // rec rln ::
    int limit = tight ? digit[pos]-48 : 9;
    ll cnt = 0;

    for(int d = 0; d <= limit; d++){
        ll mul = 0;
        int new_tight = tight & (d == limit);

        if(pos == digit.size()-1) mul = 1;
        else if(new_tight) mul = 1 + stoll(digit.substr(pos+1,digit.size()-1-pos));
        else mul = power[digit.size()-1-pos];

        ll curWt = (1LL) * d * mul;

        cnt = cnt + dfs(pos+1,new_tight,digit) + curWt;
    }

    return dp[pos][tight] = cnt;
}

int main(){
    int tc; cin >> tc;

    power[0] = 1;
    for(int i = 1; i < 17; i++) power[i] = (1LL) * power[i-1] * 10;

    while(tc--){
        ll a,b; cin >> a >> b;

        memset(dp,-1,sizeof(dp));
        ll B = dfs(0,1,to_string(b));

        if(a == 0){
            cout << B << endl;
            continue;
        }

        memset(dp,-1,sizeof(dp));
        ll A = dfs(0,1,to_string(a-1));
        
        cout << B - A << endl;
    }

    return 0;
}