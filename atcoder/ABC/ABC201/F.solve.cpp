#include <bits/stdc++.h> 
using namespace std; 
using int128  = __int128_t; 
using int64   = long long; 
using int32   = int; 
using uint128 = __uint128_t; 
using uint64  = unsigned long long; 
using uint32  = unsigned int; 

#define ALL(obj) (obj).begin(),(obj).end() 
template<class T> using priority_queue_reverse = priority_queue<T,vector<T>,greater<T>>; 

constexpr int64 MOD = 1'000'000'000LL + 7; //' 
constexpr int64 MOD2 = 998244353; 
constexpr int64 HIGHINF = 1'000'000'000'000'000'000LL; 
constexpr int64 LOWINF = 1'000'000'000'000'000LL; //' 
constexpr long double PI = 3.1415926535897932384626433L; 

template <class T> vector<T> multivector(size_t N,T init){return vector<T>(N,init);} 
template <class... T> auto multivector(size_t N,T... t){return vector<decltype(multivector(t...))>(N,multivector(t...));} 
template <class T> void corner(bool flg, T hoge) {if (flg) {cout << hoge << endl; exit(0);}} 
template <class T, class U>ostream &operator<<(ostream &o, const map<T, U>&obj) {o << "{"; for (auto &x : obj) o << " {" << x.first << " : " << x.second << "}" << ","; o << " }"; return o;} 
template <class T>ostream &operator<<(ostream &o, const set<T>&obj) {o << "{"; for (auto itr = obj.begin(); itr != obj.end(); ++itr) o << (itr != obj.begin() ? ", " : "") << *itr; o << "}"; return o;} 
template <class T>ostream &operator<<(ostream &o, const multiset<T>&obj) {o << "{"; for (auto itr = obj.begin(); itr != obj.end(); ++itr) o << (itr != obj.begin() ? ", " : "") << *itr; o << "}"; return o;} 
template <class T>ostream &operator<<(ostream &o, const vector<T>&obj) {o << "{"; for (int i = 0; i < (int)obj.size(); ++i)o << (i > 0 ? ", " : "") << obj[i]; o << "}"; return o;} 
template <class T>ostream &operator<<(ostream &o, const deque<T>&obj) {o << "{"; for (int i = 0; i < (int)obj.size(); ++i)o << (i > 0 ? ", " : "") << obj[i]; o << "}"; return o;} 
template <class T, class U>ostream &operator<<(ostream &o, const pair<T, U>&obj) {o << "{" << obj.first << ", " << obj.second << "}"; return o;} 
void print(void) {cout << endl;} 
template <class Head> void print(Head&& head) {cout << head;print();} 
template <class Head, class... Tail> void print(Head&& head, Tail&&... tail) {cout << head << " ";print(forward<Tail>(tail)...);} 
template <class T> void chmax(T& a, const T b){a=max(a,b);} 
template <class T> void chmin(T& a, const T b){a=min(a,b);} 
vector<string> split(const string &str, const char delemiter) {vector<string> res;stringstream ss(str);string buffer; while( getline(ss, buffer, delemiter) ) res.push_back(buffer); return res;} 
inline constexpr int msb(int x) {return x?31-__builtin_clz(x):-1;} 
inline constexpr int64 ceil_div(const int64 a,const int64 b) {return (a+(b-1))/b;}// return ceil(a/b) 
void YN(bool flg) {cout << (flg ? "YES" : "NO") << endl;} 
void Yn(bool flg) {cout << (flg ? "Yes" : "No") << endl;} 
void yn(bool flg) {cout << (flg ? "yes" : "no") << endl;} 

/*
 * @title UnionFindTree - Union Find 木
 * @docs md/graph/UnionFindTree.md
 */
class UnionFindTree {
	vector<int> parent,maxi,mini;
	inline int root(int n) {
		return (parent[n]<0?n:parent[n] = root(parent[n]));
	}
public:
	UnionFindTree(int N = 1) : parent(N,-1),maxi(N),mini(N){
		iota(maxi.begin(),maxi.end(),0);
		iota(mini.begin(),mini.end(),0);
	}
	inline bool connected(int n, int m) {
		return root(n) == root(m);
	}
	inline void merge(int n, int m) {
		n = root(n);
		m = root(m);
		if (n == m) return;
		if(parent[n]>parent[m]) swap(n, m);
		parent[n] += parent[m];
		parent[m] = n;
		maxi[n] = std::max(maxi[n],maxi[m]);
		mini[n] = std::min(mini[n],mini[m]);
	}
	inline int min(int n) {
		return mini[root(n)];
	}
	inline int max(int n) {
		return maxi[root(n)];
	}
	inline int size(int n){
		return (-parent[root(n)]);
	}
	inline int operator[](int n) {
		return root(n);
	}
	inline void print() {
		for(int i = 0; i < parent.size(); ++i) cout << root(i) << " ";
		cout << endl;
	}
};

/*
 * @title DisjointSparseTable
 * @docs md/data-structure/data-structure/DisjointSparseTable.md
 */
template<class Operator> class DisjointSparseTable{
public:
	using TypeNode = typename Operator::TypeNode;
	size_t depth;
	size_t length;
	vector<TypeNode> node;
	vector<size_t> msb;

	DisjointSparseTable(const vector<TypeNode>& vec) {
		for(depth = 0;(1<<depth)<=vec.size();++depth);
		length = (1<<depth);
		
		//msb
		msb.resize(length,0);
		for(int i = 0; i < length; ++i) for(int j = 0; j < depth; ++j) if(i>>j) msb[i] = j;

		//init value
		node.resize(depth*length,Operator::unit_node);
		for(int i = 0; i < vec.size(); ++i) node[i] = vec[i];

		for(int i = 1; i < depth; ++i) {
			for(int r = (1<<i),l = r-1; r < length; r += (2<<i),l = r-1){
				//init accumulate
				node[i*length+l] = node[l];
				node[i*length+r] = node[r];
				//accumulate
				for(int k = 1; k < (1<<i); ++k) {
					node[i*length+l-k] = Operator::func_fold(node[i*length+l-k+1],node[l-k]);
					node[i*length+r+k] = Operator::func_fold(node[i*length+r+k-1],node[r+k]);
				}
			}
		}
	}

	//[l,r)
	TypeNode fold(int l,int r) {
		r--;
		return (l>r||l<0||length<=r) ? Operator::unit_node: (l==r ? node[l] : Operator::func_fold(node[msb[l^r]*length+l],node[msb[l^r]*length+r]));
	}
};

//sum
template<class T> struct NodeSum {
	using TypeNode = T;
	inline static constexpr TypeNode unit_node = 0;
	inline static constexpr TypeNode func_fold(TypeNode l,TypeNode r){return l+r;}
};

/** 
 * @url  
 * @est 
 */  
int main() { 
    cin.tie(0);ios::sync_with_stdio(false);
    int N; cin >> N;
    vector<int> P(N);
    for(int i=0;i<N;++i) cin >> P[i], P[i]--;
    UnionFindTree uf(N);
    {
        vector<int> tmp(N,0);
        for(int i=0;i<N;++i) {
            tmp[P[i]]++;
            if(P[i] && tmp[P[i]-1]) uf.merge(P[i],P[i]-1);
        }
    }
    vector<int64> L(N),R(N),A(N);
    for(int i=0;i<N;++i) {
        int a,b,c; cin >> a >> b >> c;
        chmin(b,a);
        chmin(c,a);
        L[i] = b;
        R[i] = c;
        A[i] = a;
    }
    DisjointSparseTable<NodeSum<int64>> dstL(L),dstR(R),dstA(A);
    int64 ans = HIGHINF;
    using tp = tuple<int,int64,int64,int64>;
    vector<tp> vtp;
    for(int i=0;i<N;++i) {
        int l = uf.min(i);
        int r = uf.max(i);
        vtp.emplace_back(l,dstL.fold(l,r+1),dstA.fold(l,r+1),dstR.fold(l,r+1));
    }
    vtp.erase(unique(vtp.begin(),vtp.end()),vtp.end());
    int M = vtp.size();
    auto dp = multivector(M+1,6,LOWINF);
    dp[M][0] = 0;
    for(int i=M-1;0<=i;--i) {
        int64 l = get<1>(vtp[i]);
        int64 a = get<2>(vtp[i]);
        int64 r = get<3>(vtp[i]);
        chmin(dp[i][1],dp[i+1][0]+r);
        chmin(dp[i][1],dp[i+1][1]+r);
        chmin(dp[i][2],dp[i+1][0]);
        chmin(dp[i][2],dp[i+1][1]);
        chmin(dp[i][3],dp[i+1][2]+a);
        chmin(dp[i][3],dp[i+1][3]+a);
        chmin(dp[i][4],dp[i+1][0]);
        chmin(dp[i][4],dp[i+1][3]);
        chmin(dp[i][5],dp[i+1][2]+l);
        chmin(dp[i][5],dp[i+1][4]+l);
        chmin(dp[i][5],dp[i+1][5]+l);
        print(get<0>(vtp[i]),l,a,r,dp[i]);
    }
    cout << *min_element(ALL(dp[0])) << endl;
    return 0; 
} 