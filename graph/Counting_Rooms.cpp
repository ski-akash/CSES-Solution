#include <bits/stdc++.h>
using namespace std;

void dfs(int i, int j, vector<vector<int>> &vis, vector<vector<char>> &mat){
    vis[i][j] = 1;
    int delRow[] = {-1,0,1,0};
    int delCol[] = {0,1,0,-1};
    for(int k=0;k<4;k++){
        int r = i + delRow[k], c = j + delCol[k];
        if( r >= 0 && r < mat.size() && c >= 0 && c < mat[0].size() && mat[r][c]== '.' && !vis[r][c] ) dfs(r,c,vis,mat);
    }
}

void solve(){
    int n,m; cin >> n >> m;
    vector<vector<char>> mat(n,vector<char>(m));
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++) cin >> mat[i][j];
    }

    vector<vector<int>> vis(n,vector<int>(m,0));
    int rooms = 0;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(mat[i][j] == '.' && !vis[i][j]){
                rooms += 1;
                dfs(i,j,vis,mat);
            }
        }
    }

    cout << rooms << endl;
}

int main(){
    solve();
    return 0;
}