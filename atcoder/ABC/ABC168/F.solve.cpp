#pragma GCC target("avx2")
#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define ALL(obj) (obj).begin(),(obj).end()
template<class T> using priority_queue_reverse = priority_queue<T,vector<T>,greater<T>>;

constexpr long long MOD = 1'000'000'000LL + 7; //'
constexpr long long MOD2 = 998244353;
constexpr long long HIGHINF = (long long)1e18;
constexpr long long LOWINF = (long long)1e9+10;
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

//Seat Pressure O(NlogN)
template<class T> class Zarts{
public:
    vector<T> val;
    map<T, int> idx;
    int M;
    Zarts(const vector<T> & ar) : M(0) {
        for (auto &e : ar) idx[e] = 0;
        for (auto &e : idx) e.second = M++;
        val.resize(M);
        for (auto &e : idx) val[e.second]=e.first;
    }
};

/*
 * @title UnionFindTree
 */
template<class T> class UnionFindTree {
	vector<int> parent,maxi,mini;
    vector<T> sum;
	inline int root(int n) {
		return (parent[n]<0?n:parent[n] = root(parent[n]));
	}
public:
	UnionFindTree(int N = 1) : parent(N,-1),maxi(N),mini(N),sum(N){
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
        sum[n] += sum[m];
		maxi[n] = std::max(maxi[n],maxi[m]);
		mini[n] = std::min(mini[n],mini[m]);
	}
    inline void set(int n,T val) {
        sum[n] = val;
    }
    inline T get(int n) {
        return sum[root(n)];
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

int main() {
    cin.tie(0);ios::sync_with_stdio(false);
    int N,M; cin >> N >> M;
    vector<ll> X(N+2*M+3),Y(2*N+M+3);
    for(int i = 0; i < N; ++i) cin >> Y[2*i] >> Y[2*i+1] >> X[i];
    for(int i = 0; i < M; ++i) cin >> Y[2*N+i] >> X[N+2*i] >> X[N+2*i+1];
    Y[2*N+M]=X[N+2*M]=0;
    Y[2*N+M+1]=X[N+2*M+1]=-LOWINF;
    Y[2*N+M+2]=X[N+2*M+2]=LOWINF;

    Zarts<ll> ZY(Y),ZX(X);
    int H = ZY.M,W = ZX.M;

    //y1,y2,x;
    vector<set<pair<int,int>>> stx(W); 
    for(int i=0; i<N; ++i) {
        int zy1 = ZY.idx[Y[2*i]],zy2 = ZY.idx[Y[2*i+1]], zx = ZX.idx[X[i]];
        for(int j = zy1; j+1<=zy2; ++j) stx[zx].insert({j,j+1});
    }
    //y,x1,x2;
    vector<set<pair<int,int>>> sty(H); 
    for(int i=0; i<M; ++i) {
        int zy = ZY.idx[Y[2*N+i]],zx1 = ZX.idx[X[N+2*i]], zx2 = ZX.idx[X[N+2*i+1]];
        for(int j = zx1; j+1<=zx2; ++j) sty[zy].insert({j,j+1});
    }
    
    UnionFindTree<ll> uf(H*W);
    for(int i = 0; i+1 < H; ++i) {
        for(int j = 0; j+1 < W; ++j) {
            ll dy = ZY.val[i+1]-ZY.val[i];
            ll dx = ZX.val[j+1]-ZX.val[j];
            int from = i*W+j;
            uf.set(from,dy*dx);
        }
    }

    int s = ZY.idx[0]*W+ZX.idx[0];
    for(int i = 0; i+1 < H; ++i) {
        for(int j = 0; j+1 < W; ++j) {
            int from = i*W+j;            
            if(!stx[j+1].count({i,i+1})) {
                int to = i*W+j+1;
                uf.merge(from,to);
            }
            if(!sty[i+1].count({j,j+1})) {
                int to = (i+1)*W+j;
                uf.merge(from,to);
            }
        }
        corner(uf.connected(s,0),"INF");
    }
    cout << uf.get(s) << endl;
    return 0;
}
