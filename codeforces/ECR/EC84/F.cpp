#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define SPEED cin.tie(0);ios::sync_with_stdio(false);
template<class T> using PQ = priority_queue<T>;
template<class T> using PQR = priority_queue<T,vector<T>,greater<T>>;
constexpr long long MOD2 = 998244353;
template <class T> void chmax(T& a, const T b){a=max(a,b);}

template<long long mod> class ModInt {
public:
	long long x;
	ModInt():x(0) {
		// do nothing
	}
	ModInt(long long y) : x(y>=0?(y%mod): (mod - (-y)%mod)%mod) {
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
using modint = ModInt<MOD2>;

int main() {
    SPEED
    ll N,M,K; cin >> N >> K >> M;
    vector<ll> L(M),R(M),X(M),A(K*(N+2),0);
    for(int i = 0; i < M; ++i) cin >> L[i] >> R[i] >> X[i];
    for(int i = 0; i < N; ++i) L[i],R[i];
    for(int i = 0; i < K; ++i) {
        for(int j = 0; j < M; ++j) {
            A[i*(N+2)+L[j]] += ((X[j]>>i)&1);
            A[i*(N+2)+R[j]+1] -= ((X[j]>>i)&1);
        }
        for(int j = 1; j <= N+1; ++j) {
            A[i*(N+2)+j] += A[i*(N+2)+j-1];
        }
    }
    vector<vector<int>> edge(N+2);
    for(int i = 0; i < M; ++i) edge[R[i]].push_back(i);
    modint ans = 1;
    vector<modint> dp(N+2,0);
    for(int i = 0; i < K; ++i) {
        for(int j = 0; j <= N+1; ++j) dp[j] = 0;
        dp[0] = 1;
        ll l = 0;
        modint sum = 1;
        for(int j = 1; j <= N+1; ++j) {
            if(!A[i*(N+2)+j]) {
                dp[j] = sum;
                sum += dp[j];
            }
            ll x = l;
            for(int e:edge[j]) if(!((X[e]>>i)&1)) chmax(x,L[e]);
            for(;l < x; l++) sum -= dp[l];            
        }
        ans *= dp[N+1];
    }
    cout << ans << endl;
    return 0;
}
