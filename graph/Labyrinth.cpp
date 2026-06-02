#include <bits/stdc++.h>
using namespace std;

void solve(){
    int n,m; cin >> n >> m;
    vector<vector<char>> mat(n,vector<char>(m));
    int x = -1, y = -1;;
    int X = -1, Y = -1;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            char ch; cin >> ch;
            mat[i][j] = ch;
            if(ch == 'A'){
                x = i, y = j;
            }
            if(ch == 'B'){
                X = i, Y = j;
            }
        }
    }

    vector<vector<int>> vis(n,vector<int>(m,0));
    vector<vector<int>> par_row(n,vector<int>(m,-1));
    vector<vector<int>> par_col(n,vector<int>(m,-1));
    vector<vector<char>> par_dir(n,vector<char>(m,'X'));
    queue< pair<int,int> > q;
    q.push({x,y});
    vis[x][y] = 1;

    int dist = 0;
    while(!q.empty()){
        int neib_cnt = q.size();
        while(neib_cnt--){
            pair<int,int> node = q.front(); q.pop();
            int i = node.first, j = node.second;

            /* Node B is found */
            if(i == X && j == Y){
                cout << "YES" << endl;
                cout << dist << endl;
                /* Build the string */
                string path = "";
                while(true){
                    if(i == x && j == y ) break;
                    path += par_dir[i][j];
                    int r = par_row[i][j];
                    int c = par_col[i][j];
                    i = r, j = c;
                }
                
                reverse(path.begin(),path.end());
                cout << path;
                return;
            }

            /* Push all the feasible neighbours -> Unvisited, '.' */
            int delRow[] = {-1,0,1,0};
            int delCol[] = {0,1,0,-1};
            char dir[] = {'U', 'R', 'D', 'L'};
            for(int k=0;k<4;k++){
                int r = i + delRow[k], c = j + delCol[k];
                if( r >= 0 && r < mat.size() && c >= 0 && c < mat[0].size() && mat[r][c] != '#' && !vis[r][c] ){
                    q.push({r,c});
                    vis[r][c] = 1;
                    par_row[r][c] = i;
                    par_col[r][c] = j;
                    par_dir[r][c] = dir[k];
                }
            }
        }
        dist += 1;
    }

    cout << "NO" << endl;
}

int main(){
    solve();
    return 0;
}