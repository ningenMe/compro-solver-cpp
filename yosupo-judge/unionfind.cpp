#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

//Union Find Tree
class UnionFindTree {
public:
	vector<int> parent;
    vector<int> rank;

    UnionFindTree(int N) : parent(N), rank(N,0){
		iota(parent.begin(),parent.end(),0);
	} 
	int root(int n) {
		return (parent[n] == n ? n : parent[n] = root(parent[n]));
	}
    inline int same(int n, int m) {
		return root(n) == root(m);
	}
	inline void unite(int n, int m) {
		n = root(n);
		m = root(m);
		if (n == m) return;
		if (rank[n]<rank[m]) {
            parent[n] = m;
        }
        else{
            parent[m] = n;
            if(rank[n] == rank[m]) rank[n]++;
        }
	}
};

int main(){
    int N,Q; cin >> N >> Q;
    UnionFindTree uf(N);
    while(Q--){
        int q,a,b; cin >> q >> a >> b;
        if(q) cout << uf.same(a,b) << endl;
        else uf.unite(a,b);
    }
}

