#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;

int main() {
    cin.tie(0);ios::sync_with_stdio(false);
    int N,M; cin >> N >> M;
	atcoder::scc_graph scc(N);
    while(M--) {
        int u,v; cin >> u >> v;
        scc.add_edge(u,v);
    }
    auto vv=scc.scc();
    cout << vv.size() << "\n";
    for(auto& v:vv) {
        cout << v.size();
        for(auto& e:v) cout << " " << e;
        cout << "\n";
    }
    return 0;
}
