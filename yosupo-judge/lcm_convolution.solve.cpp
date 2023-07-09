#include <bits/stdc++.h>
using namespace std;
using int128 = __int128_t;
using int64 = long long;

#define ALL(obj) (obj).begin(),(obj).end()

/*
 * @title FastIO
 * @docs md/util/FastIO.md
 */
class FastIO{
private:
    inline static constexpr int ch_0='0';
    inline static constexpr int ch_9='9';
    inline static constexpr int ch_n='-';
    inline static constexpr int ch_s=' ';
    inline static constexpr int ch_l='\n';
    inline static void endline_skip(char& ch) {
        while(ch==ch_l) ch=getchar();
    }
    template<typename T> inline static void read_integer(T &x) {
        int neg=0; char ch; x=0;
        ch=getchar();
        endline_skip(ch);
        if(ch==ch_n) neg=1,ch=getchar();
        for(;(ch_0 <= ch && ch <= ch_9); ch = getchar()) x = x*10 + (ch-ch_0);
        if(neg) x*=-1;
    }
    template<typename T> inline static void read_unsigned_integer(T &x) {
        char ch; x=0;
        ch=getchar();
        endline_skip(ch);
        for(;(ch_0 <= ch && ch <= ch_9); ch = getchar()) x = x*10 + (ch-ch_0);
    }
    inline static void read_string(string &x) {
        char ch; x="";
        ch=getchar();
        endline_skip(ch);
        for(;(ch != ch_s && ch!=ch_l); ch = getchar()) x.push_back(ch);
    }
    inline static void read_char(char &x) {
        char ch;
        ch=getchar();
        endline_skip(ch);
        for(;(ch != ch_s && ch!=ch_l); ch = getchar()) x=ch;
    }
    inline static char ar[40];
    inline static char *ch_ar;
    template<typename T> inline static void write_integer(T x) {
        ch_ar=ar;
        if(x< 0) putchar(ch_n), x=-x;
        if(x==0) putchar(ch_0);
        for(;x;x/=10) *ch_ar++=(ch_0+x%10);
        while(ch_ar--!=ar) putchar(*ch_ar);
    }
public:
    inline static void read(int &x) {read_integer<int>(x);}
    inline static void read(long long &x) {read_integer<long long>(x);}
    inline static void read(unsigned int &x) {read_unsigned_integer<unsigned int>(x);}
    inline static void read(unsigned long long &x) {read_unsigned_integer<unsigned long long>(x);}
    inline static void read(string &x) {read_string(x);}
    inline static void read(char &x) {read_char(x);}
    inline static void read(__int128_t &x) {read_integer<__int128_t>(x);}
    inline static void write(__int128_t x) {write_integer<__int128_t>(x);}
    inline static void write(char x) {putchar(x);}
};
#define read(arg) FastIO::read(arg)
#define write(arg) FastIO::write(arg)

template<class T> using priority_queue_reverse = priority_queue<T,vector<T>,greater<T>>;

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
    constexpr ModInt &operator+=(const ModInt &p) {if((x += p.x) >= mod) x -= mod;return *this;}
    constexpr ModInt &operator+=(const long long y) {ModInt p(y);if((x += p.x) >= mod) x -= mod;return *this;}
    constexpr ModInt &operator+=(const int y) {ModInt p(y);if((x += p.x) >= mod) x -= mod;return *this;}
    constexpr ModInt &operator-=(const ModInt &p) {if((x += mod - p.x) >= mod) x -= mod;return *this;}
    constexpr ModInt &operator-=(const long long y) {ModInt p(y);if((x += mod - p.x) >= mod) x -= mod;return *this;}
    constexpr ModInt &operator-=(const int y) {ModInt p(y);if((x += mod - p.x) >= mod) x -= mod;return *this;}
    constexpr ModInt &operator*=(const ModInt &p) {x = (x * p.x % mod);return *this;}
    constexpr ModInt &operator*=(const long long y) {ModInt p(y);x = (x * p.x % mod);return *this;}
    constexpr ModInt &operator*=(const int y) {ModInt p(y);x = (x * p.x % mod);return *this;}
    constexpr ModInt &operator^=(const ModInt &p) {x = (x ^ p.x) % mod;return *this;}
    constexpr ModInt &operator^=(const long long y) {ModInt p(y);x = (x ^ p.x) % mod;return *this;}
    constexpr ModInt &operator^=(const int y) {ModInt p(y);x = (x ^ p.x) % mod;return *this;}
    constexpr ModInt &operator/=(const ModInt &p) {*this *= p.inv();return *this;}
    constexpr ModInt &operator/=(const long long y) {ModInt p(y);*this *= p.inv();return *this;}
    constexpr ModInt &operator/=(const int y) {ModInt p(y);*this *= p.inv();return *this;}
    constexpr ModInt operator=(const int y) {ModInt p(y);*this = p;return *this;}
    constexpr ModInt operator=(const long long y) {ModInt p(y);*this = p;return *this;}
    constexpr ModInt operator-() const {return ModInt(-x); }
    constexpr ModInt operator++() {x++;if(x>=mod) x-=mod;return *this;}
    constexpr ModInt operator--() {x--;if(x<0) x+=mod;return *this;}
    constexpr ModInt operator+(const ModInt &p) const { return ModInt(*this) += p; }
    constexpr ModInt operator-(const ModInt &p) const { return ModInt(*this) -= p; }
    constexpr ModInt operator*(const ModInt &p) const { return ModInt(*this) *= p; }
    constexpr ModInt operator/(const ModInt &p) const { return ModInt(*this) /= p; }
    constexpr ModInt operator^(const ModInt &p) const { return ModInt(*this) ^= p; }
    constexpr bool operator==(const ModInt &p) const { return x == p.x; }
    constexpr bool operator!=(const ModInt &p) const { return x != p.x; }
    // ModInt inv() const {int a=x,b=mod,u=1,v=0,t;while(b > 0) {t = a / b;swap(a -= t * b, b);swap(u -= t * v, v);} return ModInt(u);}
    constexpr ModInt inv() const {int a=x,b=mod,u=1,v=0,t=0,tmp=0;while(b > 0) {t = a / b;a-=t*b;tmp=a;a=b;b=tmp;u-=t*v;tmp=u;u=v;v=tmp;} return ModInt(u);}
    constexpr ModInt pow(long long n) const {ModInt ret(1), mul(x);for(;n > 0;mul *= mul,n >>= 1) if(n & 1) ret *= mul;return ret;}
    friend ostream &operator<<(ostream &os, const ModInt &p) {return os << p.x;}
    friend istream &operator>>(istream &is, ModInt &a) {long long t;is >> t;a = ModInt<mod>(t);return (is);}
};
constexpr long long MOD_998244353 = 998244353;
constexpr long long MOD_1000000007 = 1'000'000'000LL + 7; //'

/*
 * @title Eratosthenes - エラトステネスの篩
 * @docs md/math/Eratosthenes.md
 */
class Eratosthenes {
    unsigned int sz;
public:
    vector<unsigned int> sieve;
    vector<long long> prime;
    Eratosthenes(unsigned int N):sz(N+1),sieve(N+1, 1) {
        sieve[0]=sieve[1]=0;
        for(int i=1; i <= N/i; ++i) if(sieve[i]) for(int j=2*i;j<=N;j+=i) sieve[j]=0;
        for(int i=1; i <= N  ; ++i) if(sieve[i]) prime.push_back(i);
    }
    size_t size() const {
        return sz;
    }
};

/*
 * @title DivisorZetaMoebiusTransform - 約数のゼータ・メビウス変換 (gcd/lcm畳み込み)
 * @docs md/math/DivisorZetaMoebiusTransform.md
 */
class DivisorZetaMoebiusTransform {
    template<class T> inline static void zeta_multiple(vector<T>& v, const Eratosthenes& eratosthenes) {
        assert(v.size()); int N = v.size();
        for(const int& p:eratosthenes.prime) for(int i=(N-1)/p; i; --i) v[i] += v[i*p];
    }
    template<class T> inline static void mobius_multiple(vector<T>& v, const Eratosthenes& eratosthenes) {
        assert(v.size()); int N = v.size();
        for(const int& p:eratosthenes.prime) for(int i=1; i*p<N; ++i) v[i] -= v[i*p];
    }
    template<class T> inline static void zeta_divisor(vector<T>& v, const Eratosthenes& eratosthenes) {
        assert(v.size()); int N = v.size();
        for(const int& p:eratosthenes.prime) for(int i=1; i*p<N; ++i) {v[i*p] += v[i];}
    }
    template<class T> inline static void mobius_divisor(vector<T>& v, const Eratosthenes& eratosthenes) {
        assert(v.size()); int N = v.size();
        for(const int& p:eratosthenes.prime) for(int i=(N-1)/p; i; --i) {v[i*p] -= v[i];}
    }
public:
    template<class T> inline static vector<T> gcd_convolution(const vector<T>& a,const vector<T>& b, const Eratosthenes& eratosthenes) {
        int N = max(a.size(),b.size());
        assert(N <= eratosthenes.size());
        vector<T> f(N,0),g(N,0);
        for(int i=0;i<N;++i) f[i] = a[i];
        for(int i=0;i<N;++i) g[i] = b[i];
        zeta_multiple(f,eratosthenes);zeta_multiple(g,eratosthenes);
        for(int i=0;i<N;++i) f[i] = f[i]*g[i];
        mobius_multiple(f,eratosthenes);
        return f;
    }
    template<class T> inline static vector<T> lcm_convolution(const vector<T>& a,const vector<T>& b, const Eratosthenes& eratosthenes) {
        int N = max(a.size(),b.size());
        assert(N <= eratosthenes.size());
        vector<T> f(N,0),g(N,0);
        for(int i=0;i<N;++i) f[i] = a[i];
        for(int i=0;i<N;++i) g[i] = b[i];
        zeta_divisor(f,eratosthenes);zeta_divisor(g,eratosthenes);
        for(int i=0;i<N;++i) f[i] = f[i]*g[i];
        mobius_divisor(f,eratosthenes);
        return f;
    }
};

// h(1) = f(1)g(1)
// h(2) = f(1)g(2) + f(2)g(1) + f(2)g(2)
// h(3) = f(1)g(3) + f(3)g(1) + f(3)g(3)
// h(6) = f(1)g(6) + {f(2)g(3) + f(2)g(6)} + {f(3)g(2) + f(3)g(6)} + {f(6)g(1) + f(6)g(2) + f(6)g(3) + f(6)g(6)}

// H(6) = h(1) + h(2) + h(3) + h(6)
//      = f(1)g(1) + f(1)g(2) + f(2)g(1) + f(2)g(2) + f(1)g(3) + f(3)g(1) + f(3)g(3) + f(1)g(6) + {f(2)g(3) + f(2)g(6)} + {f(3)g(2) + f(3)g(6)} + {f(6)g(1) + f(6)g(2) + f(6)g(3) + f(6)g(6)}
//      = f(1){g(1) + g(2) + g(3) + g(6)} + f(2){g(1) + g(2) + g(3) + g(6)} + f(3){g(1) + g(3) + g(2) + g(6)} + f(6){g(1) + g(2) + g(3) + g(6)}
//      = {f(1) + f(2) + f(3) + f(6)}{g(1) + g(2) + g(3) + g(6)}
//      = F(6)G(6) 

/**
 * @url 
 * @est
 */ 
int main() {
    cin.tie(0);ios::sync_with_stdio(false);
    using Mint = ModInt<MOD_998244353>;
    int N; read(N);
    vector<Mint> a(N+1,0),b(N+1,0);
    auto e = Eratosthenes(N);
    for(int i=1;i<=N;++i) {
        int t; read(t); a[i]=t;
    }
    for(int i=1;i<=N;++i) {
        int t; read(t); b[i]=t;
    }
    auto c = DivisorZetaMoebiusTransform::lcm_convolution(a,b,e);
    for(int i=1;i<=N;++i) {
        cout << c[i] << " \n"[i==N];
    }

    return 0;
}
