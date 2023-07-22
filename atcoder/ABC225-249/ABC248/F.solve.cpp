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
 * @title RuntimeModInt - 実行時ModInt
 * @docs md/util/RuntimeModInt.md
 */
template<long long& mod> class RuntimeModInt {
public:
    long long x;
    constexpr RuntimeModInt():x(0) {}
    constexpr RuntimeModInt(long long y) : x(y>=0?(y%mod): (mod - (-y)%mod)%mod) {}
    RuntimeModInt &operator+=(const RuntimeModInt &p) {if((x += p.x) >= mod) x -= mod;return *this;}
    RuntimeModInt &operator+=(const long long y) {RuntimeModInt p(y);if((x += p.x) >= mod) x -= mod;return *this;}
    RuntimeModInt &operator+=(const int y) {RuntimeModInt p(y);if((x += p.x) >= mod) x -= mod;return *this;}
    RuntimeModInt &operator-=(const RuntimeModInt &p) {if((x += mod - p.x) >= mod) x -= mod;return *this;}
    RuntimeModInt &operator-=(const long long y) {RuntimeModInt p(y);if((x += mod - p.x) >= mod) x -= mod;return *this;}
    RuntimeModInt &operator-=(const int y) {RuntimeModInt p(y);if((x += mod - p.x) >= mod) x -= mod;return *this;}
    RuntimeModInt &operator*=(const RuntimeModInt &p) {x = (x * p.x % mod);return *this;}
    RuntimeModInt &operator*=(const long long y) {RuntimeModInt p(y);x = (x * p.x % mod);return *this;}
    RuntimeModInt &operator*=(const int y) {RuntimeModInt p(y);x = (x * p.x % mod);return *this;}
    RuntimeModInt &operator^=(const RuntimeModInt &p) {x = (x ^ p.x) % mod;return *this;}
    RuntimeModInt &operator^=(const long long y) {RuntimeModInt p(y);x = (x ^ p.x) % mod;return *this;}
    RuntimeModInt &operator^=(const int y) {RuntimeModInt p(y);x = (x ^ p.x) % mod;return *this;}
    RuntimeModInt &operator/=(const RuntimeModInt &p) {*this *= p.inv();return *this;}
    RuntimeModInt &operator/=(const long long y) {RuntimeModInt p(y);*this *= p.inv();return *this;}
    RuntimeModInt &operator/=(const int y) {RuntimeModInt p(y);*this *= p.inv();return *this;}
    RuntimeModInt operator=(const int y) {RuntimeModInt p(y);*this = p;return *this;}
    RuntimeModInt operator=(const long long y) {RuntimeModInt p(y);*this = p;return *this;}
    RuntimeModInt operator-() const {return RuntimeModInt(-x); }
    RuntimeModInt operator++() {x++;if(x>=mod) x-=mod;return *this;}
    RuntimeModInt operator--() {x--;if(x<0) x+=mod;return *this;}
    RuntimeModInt operator+(const RuntimeModInt &p) const { return RuntimeModInt(*this) += p; }
    RuntimeModInt operator-(const RuntimeModInt &p) const { return RuntimeModInt(*this) -= p; }
    RuntimeModInt operator*(const RuntimeModInt &p) const { return RuntimeModInt(*this) *= p; }
    RuntimeModInt operator/(const RuntimeModInt &p) const { return RuntimeModInt(*this) /= p; }
    RuntimeModInt operator^(const RuntimeModInt &p) const { return RuntimeModInt(*this) ^= p; }
    bool operator==(const RuntimeModInt &p) const { return x == p.x; }
    bool operator!=(const RuntimeModInt &p) const { return x != p.x; }
    RuntimeModInt inv() const {int a=x,b=mod,u=1,v=0,t;while(b > 0) {t = a / b;swap(a -= t * b, b);swap(u -= t * v, v);} return RuntimeModInt(u);}
    RuntimeModInt pow(long long n) const {RuntimeModInt ret(1), mul(x);for(;n > 0;mul *= mul,n >>= 1) if(n & 1) ret *= mul;return ret;}
    friend ostream &operator<<(ostream &os, const RuntimeModInt &p) {return os << p.x;}
    friend istream &operator>>(istream &is, RuntimeModInt &a) {long long t;is >> t;a = RuntimeModInt<mod>(t);return (is);}
};
long long runtime_mod;
using Mint = RuntimeModInt<runtime_mod>;

/**
 * @url 
 * @est
 */ 
int main() {
    cin.tie(0);ios::sync_with_stdio(false);
    int N,P; read(N),read(P);
    runtime_mod = P;
    auto dp = multivector(2,N,Mint(0));
    auto tp = dp;
    dp[0][0]=1;
    dp[1][1]=1;
    for(int i=1;i<N;++i) {
        for(int j=0;j<N;++j) tp[0][j]=tp[1][j]=0;
        for(int j=0;j<N;++j) {
            // ○-○
            //   |
            // ○-○
            if(j  <N) tp[0][j]+=dp[0][j]+dp[1][j];
            // ○-○    ○ ○     ○-○
            //     or   |  or   |
            // ○-○    ○-○     ○ ○
            if(j+1<N) tp[0][j+1]+=dp[0][j]*3;
            // ○-○    ○ ○
            //     or     
            // ○ ○    ○-○
            if(j+2<N) tp[1][j+2]+=dp[0][j]*2;
            // ○-○  
            //     
            // ○-○ 
            if(j+1<N) tp[1][j+1]+=dp[1][j];
        }
        swap(dp,tp);
    }
    for(int i=1;i<N;++i) cout << dp[0][i] << " \n"[i==N-1];

    return 0;
}
