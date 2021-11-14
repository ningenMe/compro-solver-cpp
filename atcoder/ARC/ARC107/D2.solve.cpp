#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
constexpr long long MOD2 = 998244353;

/*
 * @title ModInt
 * @docs md/util/ModInt.md
 */
template<long long mod> class ModInt {
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
using modint = ModInt<MOD2>;

constexpr int M = 3000;
array<array<modint,M+1>,M+1> dp;
array<modint,M+1> tp;

/**
 * @url https://atcoder.jp/contests/arc107/tasks/arc107_d
 * @est 600
 */ 
int main() {
    int N,K; 
    scanf("%d%d",&N,&K);
    dp[N-K][K]=1;
    for(int i=N-K; 0 < i; --i) {

        for(int j=0; j <= N; ++j) {
            tp[j] = 0;
        }

        for(int j=1; j <= N; ++j) {
            modint val = dp[i][j];
            int l = 1, r = min(i,j);
            tp[l] += val;
            tp[r+1] -= val; 
        }

        for(int j=1; j <= N; ++j) {
            tp[j] += tp[j-1];
        }

        for(int j=1; 0 <= i-j && 2*j <= N; ++j) {
            int y=i-j, x = 2*j;
            dp[y][x] += tp[j];
        }

    }
    modint ans = 0;
    {
        for(int j = 0; j <= N; ++j) {
            ans += dp[0][j];
        }
    }
    cout << ans << "\n";
    return 0;
}