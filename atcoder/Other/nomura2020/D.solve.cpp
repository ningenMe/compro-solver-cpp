#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define ALL(obj) (obj).begin(),(obj).end()
template<class T> using priority_queue_reverse = priority_queue<T,vector<T>,greater<T>>;

constexpr long long MOD = 1'000'000'000LL + 7;
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

/*
 * @title ModInt
 */
template<long long mod> class ModInt {
public:
	long long x;
	constexpr ModInt():x(0) {
		// do nothing
	}
	constexpr ModInt(long long y) : x(y>=0?(y%mod): (mod - (-y)%mod)%mod) {
		// do nothing
	}
	ModInt &operator+=(const ModInt &p) {
		if((x += p.x) >= mod) x -= mod;
		return *this;
	}
	ModInt &operator+=(const long long y) {
		ModInt p(y);
		if((x += p.x) >= mod) x -= mod;
		return *this;
	}
	ModInt &operator+=(const int y) {
		ModInt p(y);
		if((x += p.x) >= mod) x -= mod;
		return *this;
	}
	ModInt &operator-=(const ModInt &p) {
		if((x += mod - p.x) >= mod) x -= mod;
		return *this;
	}
	ModInt &operator-=(const long long y) {
		ModInt p(y);
		if((x += mod - p.x) >= mod) x -= mod;
		return *this;
	}
	ModInt &operator-=(const int y) {
		ModInt p(y);
		if((x += mod - p.x) >= mod) x -= mod;
		return *this;
	}
	ModInt &operator*=(const ModInt &p) {
		x = (x * p.x % mod);
		return *this;
	}
	ModInt &operator*=(const long long y) {
		ModInt p(y);
		x = (x * p.x % mod);
		return *this;
	}
	ModInt &operator*=(const int y) {
		ModInt p(y);
		x = (x * p.x % mod);
		return *this;
	}
	ModInt &operator^=(const ModInt &p) {
		x = (x ^ p.x) % mod;
		return *this;
	}
	ModInt &operator^=(const long long y) {
		ModInt p(y);
		x = (x ^ p.x) % mod;
		return *this;
	}
	ModInt &operator^=(const int y) {
		ModInt p(y);
		x = (x ^ p.x) % mod;
		return *this;
	}
	ModInt &operator/=(const ModInt &p) {
		*this *= p.inv();
		return *this;
	}
	ModInt &operator/=(const long long y) {
		ModInt p(y);
		*this *= p.inv();
		return *this;
	}
	ModInt &operator/=(const int y) {
		ModInt p(y);
		*this *= p.inv();
		return *this;
	}
	ModInt operator=(const int y) {
		ModInt p(y);
		*this = p;
		return *this;
	}
	ModInt operator=(const long long y) {
		ModInt p(y);
		*this = p;
		return *this;
	}
	ModInt operator-() const { return ModInt(-x); }
	ModInt operator++() { 
		x++;
		if(x>=mod) x-=mod;
		return *this; 
	}
	ModInt operator--() { 
		x--;
		if(x<0) x+=mod;
		return *this; 
	}
	ModInt operator+(const ModInt &p) const { return ModInt(*this) += p; }
	ModInt operator-(const ModInt &p) const { return ModInt(*this) -= p; }
	ModInt operator*(const ModInt &p) const { return ModInt(*this) *= p; }
	ModInt operator/(const ModInt &p) const { return ModInt(*this) /= p; }
	ModInt operator^(const ModInt &p) const { return ModInt(*this) ^= p; }
	bool operator==(const ModInt &p) const { return x == p.x; }
	bool operator!=(const ModInt &p) const { return x != p.x; }
	ModInt inv() const {
		int a = x, b = mod, u = 1, v = 0, t;
		while(b > 0) {
			t = a / b;
			swap(a -= t * b, b);
			swap(u -= t * v, v);
		}
		return ModInt(u);
	}
	ModInt pow(long long n) const {
		ModInt ret(1), mul(x);
		while(n > 0) {
			if(n & 1) ret *= mul;
			mul *= mul;
			n >>= 1;
		}
		return ret;
	}
	friend ostream &operator<<(ostream &os, const ModInt &p) {
		return os << p.x;
	}
	friend istream &operator>>(istream &is, ModInt &a) {
		long long t;
		is >> t;
		a = ModInt<mod>(t);
		return (is);
	}
};
using modint = ModInt<MOD>;

/*
 * @title Mod
 */
class Mod{
public:
	//Pow_Mod O(log(n))
	inline static long long pow(long long x, long long n, long long mod) {
		long long res = 1;
		for (x %= mod; n > 0; n >>= 1, (x *= x) %= mod) if (n & 1) (res *= x) %= mod;
		return res;
	}
	//Inv_Mod O(log(mod))
	inline static long long inv(long long x, long long mod){
		return pow(x,mod-2,mod); 
	}
};

/*
 * @title CombinationMod
 */
template<long long mod> class CombinationMod {
	vector<long long> fac,finv,inv;
public:
	CombinationMod(int N) : fac(N + 1), finv(N + 1), inv(N + 1) {
		fac[0] = fac[1] = finv[0] = finv[1] = inv[1] = 1;
		for (int i = 2; i <= N; ++i) {
			fac[i] = fac[i - 1] * i % mod;
			inv[i] = mod - inv[mod%i] * (mod / i) % mod;
			finv[i] = finv[i - 1] * inv[i] % mod;
		}
	}
	inline long long binom(int n, int k) {
		return ((n < 0 || k < 0 || n < k) ? 0 : fac[n] * (finv[k] * finv[n - k] % mod) % mod);
	}
	inline long long factorial(int n) {
		return fac[n];
	}
};

int main() {
    cin.tie(0);ios::sync_with_stdio(false);
    ll N; cin >> N;
    vector<ll> P(N),A;
    for(int i = 0; i < N; ++i) cin >> P[i],P[i]--;
    UnionFindTree uf(N);

    ll M = 0;
    for(int i = 0; i < N; ++i) {
        if(P[i]!=-2) uf.merge(i,P[i]);
    }

    map<int,ll> mp1,mp2;
    for(int i = 0; i < N; ++i) {
        mp1[uf.min(i)];
        if(P[i]==-2) mp2[uf.min(i)];
    }
    for(auto& p:mp2) mp1.erase(p.first);

    for(auto& p:mp1) p.second = uf.size(p.first);
    for(auto& p:mp2) p.second = uf.size(p.first);

    ll K = mp2.size();
    modint ans = 0;
    for(auto p:mp1) {
        ans += (p.second-1)*Mod::pow(N-1,K,MOD);
    }
    for(auto p:mp2) {
        ans += (p.second-1)*Mod::pow(N-1,K,MOD);
    }

    for(auto l:mp2) {
        for(auto r:mp1) {
            modint cnt = Mod::pow(N-1,K-1,MOD)*r.second;
            ans += cnt;
        }
        for(auto r:mp2) {
            if(l.first==r.first) continue;
            modint cnt = Mod::pow(N-1,K-1,MOD)*r.second;
            ans += cnt;
        }
    }

    auto dp = multivector(K+1,K+1,modint(0));
    dp[0][0] = 1;
    {
        int i = 1;
        for(auto p:mp2) {
            for(int j = 0; j < K; ++j) {
                dp[i][j+1] += dp[i-1][j]*p.second;
                dp[i][j]   += dp[i-1][j];
            }
            i++;
        }
    }
    
    CombinationMod<MOD> CM(K);
    for(int j = 2; j <= K; ++j) {
        modint cnt = Mod::pow(N-1,K-j,MOD);
        cnt *= dp[K][j]*CM.factorial(j-1);
        ans -= cnt;
    }

    cout << ans << endl;
    return 0;
}
