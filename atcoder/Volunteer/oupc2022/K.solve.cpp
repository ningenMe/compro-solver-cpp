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
 * @title Gcd - 高速GCD
 * @docs md/math/Gcd.md
 */
class Gcd{
public:
    inline static long long impl(long long n, long long m) {
        static constexpr long long K = 5;
        long long t,s;
        for(int i = 0; t = n - m, s = n - m * K, i < 80; ++i) {
            if(t<m){
                if(!t) return m;
                n = m, m = t;
            }
            else{
                if(!m) return t;
                n=t;
                if(t >= m * K) n = s;
            }
        }
        return impl(m, n % m);
    }
    inline static long long pre(long long n, long long m) {
        long long t;
        for(int i = 0; t = n - m, i < 4; ++i) {
            (t < m ? n=m,m=t : n=t);
            if(!m) return n;
        }
        return impl(n, m);
    }
    inline static long long gcd(long long n, long long m) {
        return (n>m ? pre(n,m) : pre(m,n));
    }
    inline static constexpr long long pureGcd(long long a, long long b) {
        return (b ? pureGcd(b, a % b):a);
    }
    inline static constexpr long long lcm(long long a, long long b) {
        return (a*b ? (a / gcd(a, b)*b): 0);
    }
    inline static constexpr long long extGcd(long long a, long long b, long long &x, long long &y) {
        if (b == 0) return x = 1, y = 0, a;
        long long d = extGcd(b, a%b, y, x);
        return y -= a / b * x, d;
    }
};

/*
 * @title Prime - 高速素因数分解・ミラーラビン素数判定
 * @docs md/math/Prime.md
 */
class Prime{
    using int128 = __int128_t;
    using int64  = long long;
    long long pow(long long x, long long n, long long mod) {
        long long res = 1;
        for (x %= mod; n > 0; n >>= 1, x=(int128(x)*x)%mod) if (n & 1) res = (int128(res)*x)%mod;
        return res;
    }
    int64 rho(int64 n){
        if(miller_rabin(n)) return n;
        if(n%2 == 0) return 2;
        for(int64 c=1,x=2,y=2,d;;c++){
            do{
                x=(int128(x)*x+c)%n;
                y=(int128(y)*y+c)%n;
                y=(int128(y)*y+c)%n;
                d=Gcd::gcd(x-y+n,n);
            }while(d==1);
            if(d<n) return d;
        }
    }
    vector<int64> factor(int64 n) {
        if(n <= 1) return {};
        int64 p = rho(n);
        if(p == n) return {p};
        auto l = factor(p);
        auto r = factor(n / p);
        copy(r.begin(), r.end(), back_inserter(l));
        return l;
    }
public:
    int miller_rabin(const int64 n) {
        if(n == 2) return 1;
        if(n < 2 || n%2 == 0) return 0;
        int64 m = n - 1;
        for (;!(m&1);m>>=1);
        for (int64 a: {2,325,9375,28178,450775,9780504,1795265022}) {
            if(a>=n) break;
            int64 x=m,r=pow(a,x,n);
            for(;x != n-1 && r != 1 && r != n-1;x <<= 1) r = (int128(r)*r)%n;
            if(r!=n-1 && x%2==0) return 0;
        }
        return 1;
    }
    vector<pair<int64,int64>> factorization(int64 n) {
        auto v = factor(n);
        vector<pair<int64,int64>> vp;
        sort(v.begin(),v.end());
        int64 prev = 0;
        for(int64 p:v) {
            if(p == prev) vp.back().second++;
            else vp.emplace_back(p,1);
            prev=p;
        }
        return vp;
    }
};

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
using modint = ModInt<MOD>;

/**
 * @url 
 * @est
 */ 
int main() {
    cin.tie(0);ios::sync_with_stdio(false);
    int N; cin >> N;
    vector<int> A(N);
    for(int i = 0; i < N; ++i) cin >> A[i];
    if(N==1) {
        int ans = 0;
        for(int i = 1; i<= 15; ++i) {
            if(i*i==A[i]) ans++;
        }
        cout << ans << endl;
        return 0;
    }
    vector<int> L,R;
    for(int i = 0; i < N; ++i) (i%2?L:R).push_back(A[i]);
    int mL = L.size(), mR = R.size();
    vector<vector<int>> fL(mL),fR(mR);
    vector<modint> gL(mL,1),gR(mR,1);

    Prime prime;
    for(int i=0;i<mL;++i) {
        auto vp = prime.factorization(L[i]);
        for(auto p:vp){
            if(p.second % 2) {
                fL[i].push_back(p.first);
                for(int j=0;j<p.second-1;++j) gL[i] *= p.first;
            }
            else {
                for(int j=0;j<p.second;++j) gL[i] *= p.first;
            }            
        }
    }
    for(int i=0;i<mR;++i) {
        auto vp = prime.factorization(R[i]);
        for(auto p:vp){
            if(p.second % 2) {
                fR[i].push_back(p.first);
                for(int j=0;j<p.second-1;++j) gR[i] *= p.first;
            }
            else {
                for(int j=0;j<p.second;++j) gR[i] *= p.first;
            }
        }
    }
    vector<vector<int>> ffL(1<<mL);

    map<vector<int>,modint> mpL;
    for(int i=0;i<(1<<mL);++i) {
        map<int,int> mp;
        modint g = 1;
        for(int j=0;j<mL;++j) {
            if(!((1<<j)&i)) continue;
            for(int p:fL[j]) mp[p]+=1;
            g *= gL[j];
        }
        for(auto [p,cnt]:mp){
            if(cnt % 2) {
                ffL[i].push_back(p);
                for(int j=0;j<cnt - 1;++j) g *= p;
            }
            else {
                for(int j=0;j<cnt;++j) g *= p;
            }
        }
        sort(ALL(ffL[i]));
        mpL[ffL[i]]+=g;
    }
    modint ans = 0;
    for(int i=0;i<(1<<mR);++i) {
        map<int,int> mp;
        modint g = 1;
        for(int j=0;j<mR;++j) {
            if(!((1<<j)&i)) continue;
            for(int p:fR[j]) mp[p]+=1;
            g *= gR[j];
        }
        vector<int> ffR;
        for(auto [p,cnt]:mp){
            if(cnt % 2) {
                ffR.push_back(p);
                for(int j=0;j<cnt - 1;++j) g *= p;
            }
            else {
                for(int j=0;j<cnt;++j) g *= p;
            }
        }
        sort(ALL(ffR));
        if(mpL.count(ffR)) {
            for(int x:ffR) g *= (x*x);
            ans += mpL[ffR]*g;
        }
    }
    ans -= 1;
    cout << ans << endl;

    return 0;
}
