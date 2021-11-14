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
int msb(int x) {return x?31-__builtin_clz(x):-1;}
void YN(bool flg) {cout << (flg ? "YES" : "NO") << endl;}
void Yn(bool flg) {cout << (flg ? "Yes" : "No") << endl;}
void yn(bool flg) {cout << (flg ? "yes" : "no") << endl;}

/*
 * @title UnionFindTree
 */
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


//Prime Factorization O(sqrt(N))
vector<pair<long long,long long>> PrimeFactorization(long long N) {
    vector<pair<long long,long long>> ret;
    if (N == 1) ret.push_back({1,0});
    for (long long i = 2,M = N; i*i <= M; ++i) {
        if (N%i == 0) {
            long long cnt = 0;
            while (N%i == 0) N /= i, cnt++;
            ret.push_back({i,cnt});
        }
    }
    if (N != 1) ret.push_back({N,1});
    return ret;
}


int main() {
    int H,W; cin >> H >> W;
    vector<string> S(H);
    for(int i = 0; i < H; ++i) {
        cin >> S[i];
    }
    UnionFindTree uf(H*W);
    for(int i = 0; i < H; ++i) {
        for(int j = 0; j < W; ++j) {
            if(S[i][j]!='o') continue;
            if(i+1<H&&S[i+1][j]=='o') uf.unite(i*W+j,(i+1)*W+j);
            if(j+1<W&&S[i][j+1]=='o') uf.unite(i*W+j,i*W+j+1);
            if(i+1<H&&j+1<W&&S[i+1][j+1]=='o') uf.unite(i*W+j,(i+1)*W+j+1);
            if(0<=i-1&&j+1<W&&S[i-1][j+1]=='o') uf.unite(i*W+j,(i-1)*W+j+1);
        }
    }
    map<int,int> mp;
    for(int i = 0; i < H; ++i) {
        for(int j = 0; j < W; ++j) {
            if(S[i][j]!='o') continue;
            mp[uf.root(i*W+j)]++;
        }
    }
    map<int,int> mp2;
    for(auto& e:mp) {
        auto P = PrimeFactorization(e.second);
        int cnt=1;
        for(auto p:P) if(p.second%2) cnt *= p.first;
        mp2[cnt]++;
    }
    print(mp2[3],mp2[1],mp2[11]);
    return 0;
}
