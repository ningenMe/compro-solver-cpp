#include <bits/stdc++.h>
using namespace std;
using int128 = __int128_t;
using int64 = long long;

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

/**
 * @url 
 * @est
 */ 
int main() {
    cin.tie(0);ios::sync_with_stdio(false);
    int64 N; cin >> N;
    int64 p2 = 0;
    while(N%2==0) {
        N/=2;
        p2++;
    }
    int64 p3 = 0;
    while(N%3==0) {
        N/=3;
        p3++;
    }
    int64 p5 = 0;
    while(N%5==0) {
        N/=5;
        p5++;
    }
    corner(N!=1,0);
    auto dp = multivector(p2+1,p3+1,p5+1,modint(0));
    modint inv5 = modint(5).inv();
    dp[p2][p3][p5] = 1;
    for(int i=p2;0<=i;--i) {
        for(int j=p3;0<=j;--j) {
            for(int k=p5;0<=k;--k) {
                if(i==p2 && j==p3 && k==p5) continue;
                modint cnt = 0;
                if(i+1<=p2) cnt += dp[i+1][j][k];
                if(j+1<=p3) cnt += dp[i][j+1][k];
                if(i+2<=p2) cnt += dp[i+2][j][k];
                if(k+1<=p5) cnt += dp[i][j][k+1];
                if(i+1<=p2 && j+1<=p3) cnt += dp[i+1][j+1][k];
                cnt *= inv5;
                dp[i][j][k] = cnt;
            }
        }
    }
    cout << dp[0][0][0] << endl;
    return 0;
}
