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
 * @title UnionFindTree
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


int main() {
    int N; cin >> N;
    vector<int> P(N);
    for(int i = 0; i < N; ++i) cin >> P[i],P[i]--;
    UnionFindTree uf(N);
    for(int i = 0; i < N; ++i) {
        uf.merge(i,P[i]);
    }    
    for(int i = 0; i < N; ++i) {
        cout << uf.size(i) << " ";
    }    
    cout << endl;

    return 0;
}
