#include <bits/stdc++.h>
using namespace std;

/*
 * @title ModInt
 * @docs md/util/ModInt.md
 */
template<long long& mod> class ModInt {
public:
    long long x;
    constexpr ModInt():x(0) {}
    constexpr ModInt(long long y) : x(y>=0?(y%mod): (mod - (-y)%mod)%mod) {}
    ModInt &operator+=(const ModInt &p) {if((x += p.x) >= mod) x -= mod;return *this;}
    ModInt &operator+=(const long long y) {ModInt p(y);if((x += p.x) >= mod) x -= mod;return *this;}
    ModInt &operator+=(const int y) {ModInt p(y);if((x += p.x) >= mod) x -= mod;return *this;}
    ModInt &operator-=(const ModInt &p) {if((x += mod - p.x) >= mod) x -= mod;return *this;}
    ModInt &operator-=(const long long y) {ModInt p(y);if((x += mod - p.x) >= mod) x -= mod;return *this;}
    ModInt &operator-=(const int y) {ModInt p(y);if((x += mod - p.x) >= mod) x -= mod;return *this;}
    ModInt &operator*=(const ModInt &p) {x = (x * p.x % mod);return *this;}
    ModInt &operator*=(const long long y) {ModInt p(y);x = (x * p.x % mod);return *this;}
    ModInt &operator*=(const int y) {ModInt p(y);x = (x * p.x % mod);return *this;}
    ModInt &operator^=(const ModInt &p) {x = (x ^ p.x) % mod;return *this;}
    ModInt &operator^=(const long long y) {ModInt p(y);x = (x ^ p.x) % mod;return *this;}
    ModInt &operator^=(const int y) {ModInt p(y);x = (x ^ p.x) % mod;return *this;}
    ModInt &operator/=(const ModInt &p) {*this *= p.inv();return *this;}
    ModInt &operator/=(const long long y) {ModInt p(y);*this *= p.inv();return *this;}
    ModInt &operator/=(const int y) {ModInt p(y);*this *= p.inv();return *this;}
    ModInt operator=(const int y) {ModInt p(y);*this = p;return *this;}
    ModInt operator=(const long long y) {ModInt p(y);*this = p;return *this;}
    ModInt operator-() const {return ModInt(-x); }
    ModInt operator++() {x++;if(x>=mod) x-=mod;return *this;}
    ModInt operator--() {x--;if(x<0) x+=mod;return *this;}
    ModInt operator+(const ModInt &p) const { return ModInt(*this) += p; }
    ModInt operator-(const ModInt &p) const { return ModInt(*this) -= p; }
    ModInt operator*(const ModInt &p) const { return ModInt(*this) *= p; }
    ModInt operator/(const ModInt &p) const { return ModInt(*this) /= p; }
    ModInt operator^(const ModInt &p) const { return ModInt(*this) ^= p; }
    bool operator==(const ModInt &p) const { return x == p.x; }
    bool operator!=(const ModInt &p) const { return x != p.x; }
    ModInt inv() const {int a=x,b=mod,u=1,v=0,t;while(b > 0) {t = a / b;swap(a -= t * b, b);swap(u -= t * v, v);} return ModInt(u);}
    ModInt pow(long long n) const {ModInt ret(1), mul(x);for(;n > 0;mul *= mul,n >>= 1) if(n & 1) ret *= mul;return ret;}
    friend ostream &operator<<(ostream &os, const ModInt &p) {return os << p.x;}
    friend istream &operator>>(istream &is, ModInt &a) {long long t;is >> t;a = ModInt<mod>(t);return (is);}
};
long long mod;
using mint = ModInt<mod>;

int main() {
    cin.tie(0);ios::sync_with_stdio(false);
    int N,K;
    cin >> N >> K >> mod;

    int L = N*(N-1)/2*K;
    vector<vector<mint>> dp(N,vector<mint>(L+1,0)); 
    dp[0][0]=1;
    for(int i=1;i<N;++i) {
        dp[i]=dp[i-1];
        //jの値をj,j+1*i,j+2*i,...,j+K*iに加算したい
        //累積和で考えると、j+(K+1)*i,j+(K+2)*i,...に足しすぎる。
        //imosを考えると先に j+(K+1)*iからjの分を引けば良い。
        for(int j=L; 0 <= j; --j) if(j + (K+1)*i <= L) dp[i][j + (K+1)*i] -= dp[i][j];
        for(int j=0;j<=L; ++j) if(j + i <= L) dp[i][j+i] += dp[i][j];
    }
    vector<mint> ans(N+1);
    for(int i=1;i<=N;++i) {
        int l = i-1;
        int r = N-i;
        mint sum = 0;
        for(int j=0;j<=L;++j) sum += dp[l][j]*dp[r][j];
        ans[i]=sum*(K+1) - 1;
    }
    for(int i=1;i<=N;++i) {
        cout << ans[i] << "\n";
    }

    return 0;
}
