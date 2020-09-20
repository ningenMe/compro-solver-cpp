#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define SPEED cin.tie(0);ios::sync_with_stdio(false);


/*
 * @title SegmentTree
 */
template<class Operator> class SegmentTree {
	using TypeNode = typename Operator::TypeNode; 
	size_t length;
	size_t num;
	vector<TypeNode> node;
	vector<pair<int,int>> range;
    inline void init() {
		for (int i = length - 1; i >= 0; --i) node[i] = Operator::func_node(node[(i<<1)+0],node[(i<<1)+1]);
        range.resize(2 * length);
		for (int i = 0; i < length; ++i) range[i+length] = make_pair(i,i+1);
		for (int i = length - 1; i >= 0; --i) range[i] = make_pair(range[(i<<1)+0].first,range[(i<<1)+1].second);
    }
public:

	//unitで初期化
	SegmentTree(const size_t num): num(num) {
		for (length = 1; length <= num; length *= 2);
		node.resize(2 * length, Operator::unit_node);
        init();
	}

	//vectorで初期化
	SegmentTree(const vector<TypeNode> & vec) : num(vec.size()) {
		for (length = 1; length <= vec.size(); length *= 2);
		node.resize(2 * length, Operator::unit_node);
		for (int i = 0; i < vec.size(); ++i) node[i + length] = vec[i];
        init();
	}
 
	//同じinitで初期化
	SegmentTree(const size_t num, const TypeNode init) : num(num) {
		for (length = 1; length <= num; length *= 2);
		node.resize(2 * length, Operator::unit_node);
		for (int i = 0; i < length; ++i) node[i+length] = init;
        init();
	}
	
	//[idx,idx+1)
	void update(size_t idx, const TypeNode var) {
		if(idx < 0 || length <= idx) return;
		idx += length;
		node[idx] = Operator::func_merge(node[idx],var);
		while(idx >>= 1) node[idx] = Operator::func_node(node[(idx<<1)+0],node[(idx<<1)+1]);
	}

	//[l,r)
	TypeNode get(int l, int r) {
		if (l < 0 || length <= l || r < 0 || length < r) return Operator::unit_node;
		TypeNode vl = Operator::unit_node, vr = Operator::unit_node;
		for(l += length, r += length; l < r; l >>=1, r >>=1) {
			if(l&1) vl = Operator::func_node(vl,node[l++]);
			if(r&1) vr = Operator::func_node(node[--r],vr);
		}
		return Operator::func_node(vl,vr);
	}

	//range[l,r) return [l,r] search max right
	int prefix_binary_search(int l, int r, TypeNode var) {
		assert(0 <= l && l < length && 0 < r && r <= length);
		TypeNode ret = Operator::unit_node;
		size_t off = l;
		for(size_t idx = l+length; idx < 2*length && off < r; ){
			if(range[idx].second<=r && !Operator::func_check(Operator::func_node(ret,node[idx]),var)) {
				ret = Operator::func_node(ret,node[idx]);
				off = range[idx++].second;
				if(!(idx&1)) idx >>= 1;			
			}
			else{
				idx <<=1;
			}
		}
		return off;
	}

	//range(l,r] return [l,r] search max left
	int suffix_binary_search(const int l, const int r, const TypeNode var) {
		assert(-1 <= l && l < (int)length-1 && 0 <= r && r < length);
		TypeNode ret = Operator::unit_node;
		int off = r;
		for(size_t idx = r+length; idx < 2*length && l < off; ){
			if(l < range[idx].first && !Operator::func_check(Operator::func_node(node[idx],ret),var)) {
				ret = Operator::func_node(node[idx],ret);
				off = range[idx--].first-1;
				if(idx&1) idx >>= 1;
			}
			else{
				idx = (idx<<1)+1;
			}
		}
		return off;
	}

	void print(){
		// cout << "node" << endl;
		// for(int i = 1,j = 1; i < 2*length; ++i) {
		// 	cout << node[i] << " ";
		// 	if(i==((1<<j)-1) && ++j) cout << endl;
		// }
		cout << "vector" << endl;
		cout << "{ " << get(0,1);
		for(int i = 1; i < length; ++i) cout << ", " << get(i,i+1);
		cout << " }" << endl;
	}
};

class Gcd{
public:
	inline static long long impl(long long n, long long m) {
		static constexpr long long K = 5;
		long long t,s;
		for(int i = 0; t = n - m, s = n - m * K, i < 80; ++i) {
			if(t<m){
				if(!t) return m;
				n = m, m = t;
			}
			else{
				if(!m) return t;
				n=t;
				if(t >= m * K) n = s;
			}
		}
		return impl(m, n % m);
	}
	inline static long long pre(long long n, long long m) {
		long long t;
		for(int i = 0; t = n - m, i < 4; ++i) {
			(t < m ? n=m,m=t : n=t);
			if(!m) return n;
		}
		return impl(n, m);
	}
	inline static long long gcd(long long n, long long m) {
		return (n>m ? pre(n,m) : pre(m,n));
	}
	inline static constexpr long long pureGcd(long long a, long long b) {
		return (b ? pureGcd(b, a % b):a);
	}
	inline static constexpr long long lcm(long long a, long long b) {
		return (a*b ? (a / gcd(a, b)*b): 0);
	}
	inline static constexpr long long extGcd(long long a, long long b, long long &x, long long &y) {
		if (b == 0) return x = 1, y = 0, a;
		long long d = extGcd(b, a%b, y, x);
		return y -= a / b * x, d;
	}
};


template<class T> struct NodeGcdPointUpdate {
	using TypeNode = T;
	inline static constexpr TypeNode unit_node = 0;
	static constexpr TypeNode func_node(const TypeNode l,const TypeNode r){return Gcd::gcd(l,r);}
	static constexpr TypeNode func_merge(const TypeNode l,const TypeNode r){return r;}
	static constexpr bool func_check(const TypeNode nodeVal,const TypeNode var){return var == nodeVal;}
};

// solution by binary search in prefix range on segment tree 
int main() {
	SPEED
	ll N; cin >> N;
	vector<ll> A(N);
	for(int i = 0; i < N; ++i) cin >> A[i];
	SegmentTree<NodeGcdPointUpdate<ll>> seg(A);
	ll ans = N;
	for(int i = N-1; 0 <= i; --i) {
		ans += seg.suffix_binary_search(-1,i,1);
	}
	// for(int i = 0; i < N; ++i) {
    //     ans += N - seg.prefix_binary_search(i,N,1);
	// }
	cout << ans << endl;
}