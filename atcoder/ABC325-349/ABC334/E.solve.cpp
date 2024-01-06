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
 * @title UnionFindTree - Union Find Tree
 * @docs md/union-find-tree/UnionFindTree.md
 */
class UnionFindTree {
    vector<int> parent,maxi,mini;
    inline int root(int n) {
        return (parent[n]<0?n:parent[n] = root(parent[n]));
    }
public:
    UnionFindTree(const int N = 1) : parent(N,-1),maxi(N),mini(N){
        iota(maxi.begin(),maxi.end(),0);
        iota(mini.begin(),mini.end(),0);
    }
    inline bool connected(const int n, const int m) {
        return root(n) == root(m);
    }
    inline void merge(int n,int m) {
        n = root(n);
        m = root(m);
        if (n == m) return;
        if(parent[n]>parent[m]) swap(n, m);
        parent[n] += parent[m];
        parent[m] = n;
        maxi[n] = std::max(maxi[n],maxi[m]);
        mini[n] = std::min(mini[n],mini[m]);
    }
    inline int min(const int n) {
        return mini[root(n)];
    }
    inline int max(const int n) {
        return maxi[root(n)];
    }
    inline int size(const int n){
        return (-parent[root(n)]);
    }
    inline int operator[](const int n) {
        return root(n);
    }
    inline void print() {
        for(int i = 0; i < parent.size(); ++i) cout << root(i) << " ";
        cout << endl;
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

using Mint = ModInt<MOD_998244353>;
/**
 * @url 
 * @est
 */ 
int main() {
    cin.tie(0);ios::sync_with_stdio(false);
    int H,W; read(H),read(W);
    UnionFindTree uf(H*W);
    vector<string> vs(H);
    for(int i=0; i<H; ++i) {
        read(vs[i]);
    }
    for(int i=0;i<H;++i) {
        for(int j=0; j<W;++j) {
            if(vs[i][j]!='#') continue;
            if(i+1<H && vs[i+1][j]=='#') {
                uf.merge(i*W+j,(i+1)*W+j);
            }
            if(j+1<W && vs[i][j+1]=='#') {
                uf.merge(i*W+j,i*W+j+1);
            }
        }
    }
    set<int> st;
    for(int i=0;i<H;++i) {
        for(int j=0; j<W;++j) {
            if(vs[i][j]!='#') continue;
            st.insert(uf[i*W+j]);
        }
    }
    Mint ave = st.size();
    Mint ans = 0;

    vector<int> dy = {-1,1,0,0};
    vector<int> dx = {0,0,-1,1};
    int cc = 0;
    for(int i=0;i<H;++i) {
        for(int j=0; j<W;++j) {
            if(vs[i][j]!='.') continue;
            set<int> tmp;
            for(int k=0;k<4;++k) {
                int y = i + dy[k];
                int x = j + dx[k];
                if(0 <= y && y < H && 0<= x && x<W) {
                    if(vs[y][x]=='#') tmp.insert(uf[y*W+x]);
                }
            }
            if(tmp.size() == 0) {
                ans += ave+1;
            }
            if(tmp.size() == 1) {
                ans += ave;
            }
            if(tmp.size() == 2) {
                ans += ave-1;
            }
            if(tmp.size() == 3) {
                ans += ave-2;
            }
            if(tmp.size() == 4) {
                ans += ave-3;
            }
            cc += 1;
        }
    }
    if(cc) ans /= cc;
    cout << ans << endl;

    return 0;
}
