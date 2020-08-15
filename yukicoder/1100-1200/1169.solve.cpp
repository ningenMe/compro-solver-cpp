#pragma GCC target("avx2")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;
int main() {
    cin.tie(0);ios::sync_with_stdio(false);
    int N; cin >> N;
    array<array<int,500>,500> grid;
    for(int i=0;i<N;++i) {
        for(int j=0;j<N;++j) {
            grid[(2*i+j)%N][(i+j)%N]=j%N+1;
        }
    }
    string ans="";
    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < N; ++j) ans += to_string(grid[i][j])+" ";
        ans += "\n";
    }
    cout << ans;
    return 0;
}
