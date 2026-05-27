#include <bits/stdc++.h>
using namespace std;

int64_t mx(int64_t a, int64_t b){
    if(a > b) return a;
    return b;
}

int main(){
    int n; cin >> n;
    vector<int> e(n);
    vector<vector<int>> v(n,vector<int>(3));

    for(int i=0;i<n;i++){
        int si,ei,pi; cin >> si >> ei >> pi;
        v[i][0] = si, v[i][1] = ei,v[i][2] = pi;
        e[i] = ei;
    }

    sort(e.begin(),e.end());
    sort(v.begin(),v.end(),[](const vector<int> &v1, const vector<int> &v2){
        return v1[1] < v2[1];
    });

    vector<int64_t> dp(n,0);
    dp[0] = v[0][2];
    for(int i=1;i<n;i++){
        int si = v[i][0], pi = v[i][2];

        dp[i] = dp[i-1];
        int j = lower_bound(e.begin(),e.end(),si) - e.begin() - 1;
       
        if(j != -1) dp[i] = mx(dp[i], pi + dp[j]);
        else dp[i] = mx(dp[i], pi);

        // debugging ::
        // cout << "si = "<< si <<" ei = "<< v[i][1] <<" pi = " << pi << " ji = " <<j <<endl;
    }

    cout << dp[n-1] << endl;

    return 0;
}