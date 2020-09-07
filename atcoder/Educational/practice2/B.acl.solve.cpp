#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;

int main() {
    cin.tie(0);ios::sync_with_stdio(false);
    int N,Q; cin >> N >> Q;
	atcoder::fenwick_tree<long long> bit(N);
	for(int i=0;i<N;++i) {
		int a; cin >> a; bit.add(i,a);
	}
    while(Q--){
        int t,l,r; cin >> t >> l >> r;
        if(t) cout << bit.sum(l,r) << "\n";
        else bit.add(l,r);
    }
    return 0;
}
