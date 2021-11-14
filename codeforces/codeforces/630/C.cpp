#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;

#define REP(i,n) for(long long i = 0; i < (n); i++)
#define FOR(i, m, n) for(long long i = (m);i < (n); ++i)
#define ALL(obj) (obj).begin(),(obj).end()
#define SPEED cin.tie(0);ios::sync_with_stdio(false);

template<class T> using V = vector<T>;
template<class T, class U> using P = pair<T, U>;
template<class T> using PQ = priority_queue<T>;
template<class T> using PQR = priority_queue<T,vector<T>,greater<T>>;

constexpr long long MOD = (long long)1e9 + 7;
constexpr long long MOD2 = 998244353;
constexpr long long HIGHINF = (long long)1e18;
constexpr long long LOWINF = (long long)1e15;
constexpr long double PI = 3.1415926535897932384626433;

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



//Union Find Tree
class UnionFindTree {
public:
	vector<int> parent;
    vector<int> rank;

    UnionFindTree(int N) : parent(N), rank(N,0){
		for (int i = 0; i < N; ++i) parent[i] = i;
	}
 
	int root(int n) {
		return (parent[n] == n ? n : parent[n] = root(parent[n]));
	}

    int same(int n, int m) {
		return root(n) == root(m);
	}
 
	void unite(int n, int m) {
		n = root(n);
		m = root(m);
		if (n == m) return;
		if(rank[n]<rank[m]) {
            parent[n] = m;
        }
        else{
            parent[m] = n;
            if(rank[n] == rank[m]) rank[n]++;
        }
	}
};

//verify https://atcoder.jp/contests/abc097/tasks/arc097_b

int main() {
    SPEED
    int t; cin >> t;
    while(t--){
        int N,K; cin >> N >> K;
        string S; cin >> S;
        UnionFindTree uf(N);
        for(int i = 0; i < K; ++i) {
            for(int j = i; j + K < N; j += K){
                uf.unite(j,j+K);
            }
        }
        for(int l = 0, r = N-1; l < r; l++,r--) {
            uf.unite(l,r);
        }
        vector<vector<int>> c(N,vector<int>(26,0));
        for(int i = 0; i < N; ++i) {
            c[uf.root(i)][S[i]-'a']++;            
        }
        int ans = 0;
        for(int i = 0; i < N; ++i) {
            int sum = 0,maxi = 0;
            for(int j = 0; j < 26; ++j) {
                sum += c[i][j];
                chmax(maxi,c[i][j]);
            }
            ans += sum - maxi;
        }
        cout << ans << endl;
    }
	
}
