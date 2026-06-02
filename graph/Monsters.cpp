#include <bits/stdc++.h>
using namespace std;

int X = -1, Y = -1;
vector< pair<int,int> > path;

bool dfs(int i, int j, vector<vector<char>> &mat, vector<vector<int>> &vis){
    path.push_back({i,j});

    /* Found - A */
    if(i == X && j == Y) return true;

    vis[i][j] = 1;
    int delRow[] = {-1,0,1,0};
    int delCol[] = {0,1,0,-1};
    for(int k=0;k<4;k++){
        int r = i + delRow[k], c = j + delCol[k];
        if( r >= 0 && r < mat.size() && c >=0 && c < mat[0].size() && mat[r][c] != '#' && mat[r][c] != 'M' && !vis[r][c] ){
            if(dfs(r,c,mat,vis)) return true;
        }
    }

    path.pop_back();

    return false;
}

void printPath(){
    cout << "YES" << endl;
    reverse(path.begin(),path.end());
    cout << path.size() - 1 << endl;
    for(int i=0;i+1<path.size();i++){
        int i1 = path[i].first, j1 = path[i].second;
        int i2  = path[i+1].first, j2 = path[i+1].second;
        if(i1 < i2) cout << 'D';
        if(i1 > i2) cout << 'U';
        if(j1 < j2) cout << 'R';
        if(j1 > j2) cout << 'L';
    }
}

void solve(){
    int n,m; cin >> n >> m;
    vector<vector<char>> mat(n,vector<char>(m));
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            char ch; cin >> ch;
            mat[i][j] = ch;
            if(ch == 'A'){
                X = i, Y = j;
            }
        }
    }

    vector<vector<int>> vis(n,vector<int>(m,0));
    // Iterate on the boundary ::
    for(int c = 0; c < m; c++){
        if( mat[0][c] != '#' && mat[0][c] != 'M' && !vis[0][c] ){
            if(dfs(0,c,mat,vis) == true){
                printPath();
                return;
            }
        }
        if( mat[n-1][c] != '#' && mat[n-1][c] != 'M' && !vis[n-1][c] ){
            if(dfs(n-1,c,mat,vis)){
                printPath();
                return;
            }
        }
    }
    for(int r = 0; r < n; r++){
        if( mat[r][0] != '#' && mat[r][0] != 'M' && !vis[r][0] ){
            if(dfs(r,0,mat,vis)){
                printPath();
                return;
            }
        }
        if( mat[r][m-1] != '#' && mat[r][m-1] != 'M' && !vis[r][m-1] ){
            if(dfs(r,m-1,mat,vis)){
                printPath();
                return;
            }
        }
    }
    
    cout << "NO" << endl;

}

int main(){
    solve();
    return 0;
}