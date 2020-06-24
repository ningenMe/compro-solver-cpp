#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define ALL(obj) (obj).begin(),(obj).end()
#define SPEED cin.tie(0);ios::sync_with_stdio(false);

template<class T> using PQ = priority_queue<T>;
template<class T> using PQR = priority_queue<T,vector<T>,greater<T>>;

constexpr long long MOD = (long long)1e9 + 7;
constexpr long long MOD2 = 998244353;
constexpr long long HIGHINF = (long long)1e18;
constexpr long long LOWINF = (long long)1e15;
constexpr long double PI = 3.1415926535897932384626433L;

template <class T> vector<T> multivector(size_t N,T init){return vector<T>(N,init);}
template <class... T> auto multivector(size_t N,T... t){return vector<decltype(multivector(t...))>(N,multivector(t...));}
template <class T> void corner(bool flg, T hoge) {if (flg) {cout << hoge << endl; exit(0);}}
template <class T, class U>ostream &operator<<(ostream &o, const map<T, U>&obj) {o << "{"; for (auto &x : obj) o << " {" << x.first << " : " << x.second << "}" << ","; o << " }"; return o;}
template <class T>ostream &operator<<(ostream &o, const set<T>&obj) {o << "{"; for (auto itr = obj.begin(); itr != obj.end(); ++itr) o << (itr != obj.begin() ? ", " : "") << *itr; o << "}"; return o;}
template <class T>ostream &operator<<(ostream &o, const multiset<T>&obj) {o << "{"; for (auto itr = obj.begin(); itr != obj.end(); ++itr) o << (itr != obj.begin() ? ", " : "") << *itr; o << "}"; return o;}
template <class T>ostream &operator<<(ostream &o, const vector<T>&obj) {o << "{"; for (int i = 0; i < (int)obj.size(); ++i)o << (i > 0 ? ", " : "") << obj[i]; o << "}"; return o;}
template <class T, class U>ostream &operator<<(ostream &o, const pair<T, U>&obj) {o << "{" << obj.first << ", " << obj.second << "}"; return o;}
template <template <class tmp>  class T, class U> ostream &operator<<(ostream &o, const T<U> &obj) {o << "{"; for (auto itr = obj.begin(); itr != obj.end(); ++itr)o << (itr != obj.begin() ? ", " : "") << *itr; o << "}"; return o;}
void print(void) {cout << endl;}
template <class Head> void print(Head&& head) {cout << head;print();}
template <class Head, class... Tail> void print(Head&& head, Tail&&... tail) {cout << head << " ";print(forward<Tail>(tail)...);}
template <class T> void chmax(T& a, const T b){a=max(a,b);}
template <class T> void chmin(T& a, const T b){a=min(a,b);}
void YN(bool flg) {cout << (flg ? "YES" : "NO") << endl;}
void Yn(bool flg) {cout << (flg ? "Yes" : "No") << endl;}
void yn(bool flg) {cout << (flg ? "yes" : "no") << endl;}

/*
 * @title BinaryIndexedTree
 */
template<class Operator> class BinaryIndexedTree {
	using TypeNode = typename Operator::TypeNode;
	size_t depth;         
	size_t length;
	size_t num;
	vector<TypeNode> node;
public:
	BinaryIndexedTree(const size_t num) : num(num) {
		for (depth = 1,length = 1; length < num; depth++,length *= 2);
		node.resize(length+1, Operator::unit_node);
	}
 
	//[idx,idx+1) update
	void update(size_t idx, TypeNode var) {
		assert(0 <= idx && idx < length);
		for (++idx; idx <= length; idx += idx & -idx) node[idx] = Operator::func_node(node[idx],var);
	}

	//[0,idx) get
	TypeNode get(size_t idx) {
		TypeNode ret = Operator::unit_node;
		for (idx = min(length,idx); idx > 0; idx -= idx & -idx) ret = Operator::func_node(ret,node[idx]);
		return ret;
	}

	//return [0,length]
	int binary_search(TypeNode var) {
		if(!Operator::func_check(node.back(),var)) return num;
		TypeNode ret = Operator::unit_node;
		size_t off = 0;
		for(size_t idx = length; idx; idx >>= 1){
			if(off + idx <= length && !Operator::func_check(Operator::func_node(ret,node[off+idx]),var)) {
				off += idx;
				ret = Operator::func_node(ret,node[off]);
			}
		}
		return min(off,num);
	}

	void print() {
		cout << "{ " << get(1);
		for(int i = 1; i < length; ++i) cout << ", " << get(i+1);
		cout << " }" << endl;
	}
};

template<class T> struct NodePrefixSumPointAdd {
	using TypeNode = T;
	inline static constexpr TypeNode unit_node = 0;
	inline static constexpr TypeNode func_node(TypeNode l,TypeNode r){return l+r;}
	// Binary Search for first index where func_check is true
	inline static constexpr bool func_check(TypeNode nodeVal,TypeNode val){return val < nodeVal;}
};

template<class TypeNode> struct nodeUpdatePrefixGCD {
	TypeNode unit_node = 0;
	TypeNode func_node(TypeNode l,TypeNode r){return ((r == 0) ? l : func_node(r, l % r));}
	// Binary Search for first index at where func_check is true
	bool func_check(TypeNode nodeVal,TypeNode var){return var == nodeVal;}
};

//verify https://atcoder.jp/contests/chokudai_S001/tasks/chokudai_S001_j
//verify https://atcoder.jp/contests/abc130/tasks/abc130_d

//Seat Pressure O(NlogN)
template<class T> vector<int> Zarts(const vector<T> & ar, int cnt = 0) {
    vector<int> res;
    map<T, int> mp;
    for (auto &e : ar) mp[e] = 0;
    for (auto &e : mp) e.second = cnt++;
    for (auto &e : ar) res.push_back(mp[e]);
    return res;
}


//verify https://atcoder.jp/contests/abc036/tasks/abc036_c

int main() {
	SPEED
	int N,Q; cin >> N >> Q;
	vector<ll> A(N),B(N);
	vector<multiset<pair<ll,ll>>> vmsp(200000);
	for(int i = 0; i < N; ++i) {
		cin >> A[i] >> B[i];
		B[i]--;
		vmsp[B[i]].insert({A[i],i});
	}
	auto Z = Zarts(A);
	map<ll,int> mp,mp2;
	for(int i = 0; i < N; ++i) mp[A[i]]=Z[i];
	for(int i = 0; i < N; ++i) mp2[Z[i]]=A[i];
	BinaryIndexedTree<NodePrefixSumPointAdd<ll>> bit(N);
	for(auto& msp:vmsp) {
		if(msp.empty()) continue;
		ll val = (*msp.rbegin()).first;
		bit.update(mp[val],1);
	}
	while(Q--) {
		int C,D; cin >> C >> D;
		C--,D--;
		int pre = B[C],aft=D;
		ll val;
		if(vmsp[pre].size()) {
			val = (*vmsp[pre].rbegin()).first;
			bit.update(mp[val],-1);
		}
		if(vmsp[aft].size()) {
			val = (*vmsp[aft].rbegin()).first;
			bit.update(mp[val],-1);
		}

		B[C]=aft;
		vmsp[pre].erase({A[C],C});
		vmsp[aft].insert({A[C],C});

		if(vmsp[pre].size()) {
			val = (*vmsp[pre].rbegin()).first;
			bit.update(mp[val],1);
		}
		if(vmsp[aft].size()) {
			val = (*vmsp[aft].rbegin()).first;
			bit.update(mp[val],1);
		}

		int idx = bit.binary_search(0);
		cout << mp2[idx] << endl;
	}
    return 0;
}
