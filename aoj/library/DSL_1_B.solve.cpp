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
 * @title PotentializedUnionFindTree - ポテンシャル付きUnionFind木
 * @docs md/graph/PotentializedUnionFindTree.md
 */
template<class T> class PotentializedUnionFindTree {
	vector<int> parent,rank;
	vector<T> potential;
	inline int root(int n) {
		if (parent[n] == n) {
            return n;
        }
		else {
			int r = root(parent[n]);
			potential[n] += potential[parent[n]];
			return parent[n] = r;
		}
	}
    inline T updated_dist(int x) {
		root(x);
		return potential[x];
	}
public:
	PotentializedUnionFindTree(int N = 1, T ini = 0) : parent(N),rank(N,1),potential(N,ini) {
        iota(parent.begin(),parent.end(),0);
    }
	inline bool connected(int n, int m) {
		return root(n) == root(m);
	}
    /*
    * potential[m] = potential[n] + dとなるようにマージする
    */
	bool merge(int n, int m, T d=0) {
		d += updated_dist(n);
		d -= updated_dist(m);
		n = root(n); m = root(m);
		if (n == m) return false;
		if (rank[n] < rank[m]) {
			swap(n, m);
			d = -d;
		}
		if (rank[n] == rank[m]) ++rank[n];
		parent[m] = n;
		potential[m] = d;
		return true;
	}
    /*
    * potential[m] - potential[n]
    */
	T diff(int n, int m) {
		return updated_dist(m) - updated_dist(n);
	}
	inline int operator[](int n) {
		return root(n);
	}
	inline void print() {
		for(int i = 0; i < parent.size(); ++i) cout << root(i) << " ";
		cout << endl;
	}
};

//verify https://atcoder.jp/contests/abc087/tasks/arc090_b 

int main() {
    cin.tie(0);ios::sync_with_stdio(false);
    int N,Q; cin >> N >> Q;
    PotentializedUnionFindTree<int> uf(N);
    while(Q--) {
        int q; cin >> q;
        if(q) {
            int x,y; cin >> x >> y;
            if(uf.connected(y,x)) cout << uf.diff(x,y) << endl;
            else cout << "?" << endl;
        }
        else {
            int x,y,z; cin >> x >> y >> z;
            uf.merge(x,y,z);
        }
    }
    return 0;
}
