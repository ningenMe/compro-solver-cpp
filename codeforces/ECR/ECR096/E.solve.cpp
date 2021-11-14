#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define ALL(obj) (obj).begin(),(obj).end()
template<class T> using priority_queue_reverse = priority_queue<T,vector<T>,greater<T>>;

constexpr long long MOD = 1'000'000'000LL + 7; //'
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
vector<string> split(const string &str, const char delemiter) {vector<string> res;stringstream ss(str);string buffer; while( getline(ss, buffer, delemiter) ) res.push_back(buffer); return res;}
int msb(int x) {return x?31-__builtin_clz(x):-1;}
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
	
	//[0,N) constructed, inplace [0,1) + [1,N+1)
	//you can ignore inplace offset
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
	inline static constexpr TypeNode func_node(const TypeNode& l,const TypeNode& r){return l+r;}
	// Binary Search for first index where func_check is true
	inline static constexpr bool func_check(const TypeNode nodeVal,const TypeNode& val){return val <= nodeVal;}
};

template<class TypeNode> struct NodeUpdatePrefixGcd {
	TypeNode unit_node = 0;
	TypeNode func_node(const TypeNode& l,const TypeNode& r){return ((r == 0) ? l : func_node(r, l % r));}
	// Binary Search for first index at where func_check is true
	bool func_check(const TypeNode nodeVal,const TypeNode& var){return var == nodeVal;}
};

//verify https://atcoder.jp/contests/abc036/tasks/abc036_c


int main() {
    cin.tie(0);ios::sync_with_stdio(false);
    int N; cin >> N;
    string S,T; cin >> S; T = S;
    reverse(ALL(T));
    vector<queue<int>> cq(26);
    vector<int> A(N);
    for(int i=0;i<N;++i) {
        int c = T[i]-'a';
        cq[c].push(i);
    }
    for(int i=0;i<N;++i) {
        int c = S[i]-'a';
        int j=cq[c].front(); cq[c].pop();
        A[i]=j;
    }
    BinaryIndexedTree<NodePrefixSumPointAdd<ll>> bit(N);
	ll cnt = 0;
	for(int i=0;i<N;++i) {
		cnt += bit.get(N)-bit.get(A[i]+1);
		bit.update(A[i],1);
	}
    cout << cnt << endl;
    return 0;
}
