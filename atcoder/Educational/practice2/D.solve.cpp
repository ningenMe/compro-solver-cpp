#include <bits/stdc++.h>
using namespace std;

class BipartiteMatching {
	vector<vector<int>> edge;
	vector<int> match, used;
    size_t N;

    int dfs(int prev) {
        used[prev] = 1;
        for(int curr:edge[prev]){
            int next = match[curr];
            if(next < 0 || (!used[next] && dfs(next)) ) {
                match[prev] = curr;
                match[curr] = prev;
                return 1;
            }
        }
        return 0;
    }

public:

	BipartiteMatching(int N) : N(N), edge(N), match(N,-1), used(N) {
		// do nothing
	}

	void make_edge(int from, int to) {
		edge[from].push_back(to);
	}

	int max_flow() {
		int res = 0;
        for(int i = 0; i < N; ++i) {
            if(match[i] < 0) {
                for(int j = 0; j < N; ++j) used[j] = 0;
                if(dfs(i)) res++;
            }
        }
        return res;
	}
    vector<pair<int,int>> restoration(){
        vector<pair<int,int>> vp;
        for(int i = 0; i < N; ++i) {
            if(match[i] >= 0 && i < match[i]) vp.push_back({i,match[i]});
        }
        return vp;
    }
};

int main() {
    cin.tie(nullptr);ios::sync_with_stdio(false);
    int H,W; cin >> H >> W;
    vector<string> c(H);
    for(int i = 0; i < H; ++i) {
        cin >> c[i];
    }    
    BipartiteMatching bm(H*W);
    for(int i = 0; i < H; ++i) {
        for(int j = 0; j < W; ++j) {
            if(i+1<H&&c[i][j]=='.'&&c[i+1][j]=='.') {
                int u=i*W+j,v=(i+1)*W+j;
                bm.make_edge(u,v);
                bm.make_edge(v,u);
            }
            if(j+1<W&&c[i][j]=='.'&&c[i][j+1]=='.') {
                int u=i*W+j,v=i*W+j+1;
                bm.make_edge(u,v);
                bm.make_edge(v,u);
            }
        }
    }    
    cout << bm.max_flow() << "\n";
    auto vp = bm.restoration();
    for(auto& p:vp) {
        if(p.first>p.second) swap(p.first,p.second);
        int sy=p.first/W, sx=p.first%W;
        int ty=p.second/W,tx=p.second%W;
        if(p.first + W == p.second) c[sy][sx]='v',c[ty][tx]='^';
        else c[sy][sx]='>',c[ty][tx]='<';
    }
    for(int i = 0; i < H; ++i) {
        cout << c[i] << "\n";
    }    
    return 0;
}