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
void print(void) {cout << endl;}
template <class Head> void print(Head&& head) {cout << head;print();}
template <class Head, class... Tail> void print(Head&& head, Tail&&... tail) {cout << head << " ";print(forward<Tail>(tail)...);}
template <class T> void chmax(T& a, const T b){a=max(a,b);}
template <class T> void chmin(T& a, const T b){a=min(a,b);}
std::vector<std::string> split(const std::string &str, const char delemiter) {std::vector<std::string> res;std::stringstream ss(str);std::string buffer; while( std::getline(ss, buffer, delemiter) ) res.push_back(buffer); return res;}
void YN(bool flg) {cout << (flg ? "YES" : "NO") << endl;}
void Yn(bool flg) {cout << (flg ? "Yes" : "No") << endl;}
void yn(bool flg) {cout << (flg ? "yes" : "no") << endl;}

/*
 * @title SegmentTree
 */
template<class Operator> class SegmentTree {
	using TypeNode = typename Operator::TypeNode; 
	size_t length;
	size_t num;
	vector<TypeNode> node;
	vector<pair<size_t,size_t>> range;
public:

	//unitで初期化
	SegmentTree(const size_t num): num(num) {
		for (length = 1; length <= num; length *= 2);
		node.resize(2 * length, Operator::unit_node);
		range.resize(2 * length);
		for (int i = 0; i < length; ++i) range[i+length] = make_pair(i,i+1);
		for (int i = length - 1; i >= 0; --i) range[i] = make_pair(range[(i<<1)+0].first,range[(i<<1)+1].second);
	}

	//vectorで初期化
	SegmentTree(const vector<TypeNode> & vec) : num(vec.size()) {
		for (length = 1; length <= vec.size(); length *= 2);
		node.resize(2 * length, Operator::unit_node);
		for (int i = 0; i < vec.size(); ++i) node[i + length] = vec[i];
		for (int i = length - 1; i >= 0; --i) node[i] = Operator::func_node(node[(i<<1)+0],node[(i<<1)+1]);
		range.resize(2 * length);
		for (int i = 0; i < length; ++i) range[i+length] = make_pair(i,i+1);
		for (int i = length - 1; i >= 0; --i) range[i] = make_pair(range[(i<<1)+0].first,range[(i<<1)+1].second);
	}
 
	//同じinitで初期化
	SegmentTree(const size_t num, const TypeNode init) : num(num) {
		for (length = 1; length <= num; length *= 2);
		node.resize(2 * length, Operator::unit_node);
		range.resize(2 * length);
		for (int i = 0; i < length; ++i) node[i+length] = init;
		for (int i = length - 1; i >= 0; --i) node[i] = Operator::func_node(node[(i<<1)+0],node[(i<<1)+1]);
		for (int i = 0; i < length; ++i) range[i+length] = make_pair(i,i+1);
		for (int i = length - 1; i >= 0; --i) range[i] = make_pair(range[(i<<1)+0].first,range[(i<<1)+1].second);
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

	//return [0,length]
	int prefix_binary_search(TypeNode var) {
		if(!Operator::func_check(node[1],var)) return num;
		TypeNode ret = Operator::unit_node;
		size_t idx = 2;
		for(; idx < 2*length; idx<<=1){
			if(!Operator::func_check(Operator::func_node(ret,node[idx]),var)) {
				ret = Operator::func_node(ret,node[idx]);
				idx++;
			}
		}
		return min((idx>>1) - length,num);
	}

	//range[l,r) return [l,r]
	int binary_search(size_t l, size_t r, TypeNode var) {
		if (l < 0 || length <= l || r < 0 || length < r) return -1;
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

	void print(){
		// cout << "node" << endl;
		// for(int i = 1,j = 1; i < 2*length; ++i) {
		// 	cout << node[i] << " ";
		// 	if(i==((1<<j)-1) && ++j) cout << endl;
		// }
		// cout << "lazy" << endl;
		// for(int i = 1,j = 1; i < 2*length; ++i) {
		// 	cout << lazy[i] << " ";
		// 	if(i==((1<<j)-1) && ++j) cout << endl;
		// }
		cout << "vector" << endl;
		cout << "{ " << get(0,1);
		for(int i = 1; i < length; ++i) cout << ", " << get(i,i+1);
		cout << " }" << endl;
	}
};

//一点更新 区間最小
template<class T> struct NodeMinPointUpdate {
	using TypeNode = T;
	inline static constexpr TypeNode unit_node = 1234567;
	inline static constexpr TypeNode func_node(TypeNode l,TypeNode r){return min(l,r);}
	inline static constexpr TypeNode func_merge(TypeNode l,TypeNode r){return r;}
	inline static constexpr bool func_check(TypeNode nodeVal,TypeNode var){return var > nodeVal;}
};

int main() {
	int N; cin >> N;
	vector<ll> C(N),A(N);
	for(int i = 1; i < N; ++i) cin >> C[i] >> A[i];
	SegmentTree<NodeMinPointUpdate<ll>> seg(N,-1);
	seg.update(0,0);
	int ans=0;
	for(int i = 1; i < N; ++i) {
		ll l = i-C[i];
		ll g = seg.prefix_binary_search(l);
		seg.update(g,i);
		if(A[i]%2) ans ^= g;
	}
	cout << (ans?"First":"Second") << endl;
    return 0;
}
