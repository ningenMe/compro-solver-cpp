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

/*
 * @title LazySegmentTree - 非再帰抽象化遅延評価セグメント木
 * @docs md/segment-tree/LazySegmentTree.md
 */
template<class Monoid> class LazySegmentTree {
    using TypeNode = typename Monoid::TypeNode;
    using TypeLazy = typename Monoid::TypeLazy;
    size_t num;
    size_t length;
    size_t height;
    vector<TypeNode> node;
    vector<TypeLazy> lazy;
    vector<pair<size_t,size_t>> range;

    void propagate(int k) {
        if(lazy[k] == Monoid::unit_lazy) return;
        node[k] = Monoid::func_operate(node[k],lazy[k],range[k].first,range[k].second);
        if(k < length) lazy[2*k+0] = Monoid::func_lazy(lazy[2*k+0],lazy[k]);
        if(k < length) lazy[2*k+1] = Monoid::func_lazy(lazy[2*k+1],lazy[k]);
        lazy[k] = Monoid::unit_lazy;
    }

    void build() {
        for (int i = length - 1; i >= 0; --i) node[i] = Monoid::func_fold(node[(i<<1)+0],node[(i<<1)+1]);
        range.resize(2 * length);
        for (int i = 0; i < length; ++i) range[i+length] = make_pair(i,i+1);
        for (int i = length - 1; i >= 0; --i) range[i] = make_pair(range[(i<<1)+0].first,range[(i<<1)+1].second);
    }
public:

    //unitで初期化
    LazySegmentTree(const size_t num) : num(num) {
        for (length = 1,height = 0; length <= num; length *= 2, height++);
        node.resize(2 * length, Monoid::unit_node);
        lazy.resize(2 * length, Monoid::unit_lazy);
        for (int i = 0; i < num; ++i) node[i + length] = Monoid::unit_node;
        build();
    }

    // //同じinitで初期化
    LazySegmentTree(const size_t num, const TypeNode init) : num(num) {
        for (length = 1,height = 0; length <= num; length *= 2, height++);
        node.resize(2 * length, Monoid::unit_node);
        lazy.resize(2 * length, Monoid::unit_lazy);
        for (int i = 0; i < num; ++i) node[i + length] = init;
        build();
    }

    //vectorで初期化
    LazySegmentTree(const vector<TypeNode>& vec) : num(vec.size()) {
        for (length = 1,height = 0; length <= vec.size(); length *= 2, height++);
        node.resize(2 * length, Monoid::unit_node);
        lazy.resize(2 * length, Monoid::unit_lazy);
        for (int i = 0; i < vec.size(); ++i) node[i + length] = vec[i];
        build();
    }

    //operate [a,b)
    void operate(int a, int b, TypeLazy x) {
        int l = a + length, r = b + length - 1;
        for (int i = height; 0 < i; --i) propagate(l >> i), propagate(r >> i);
        for(r++; l < r; l >>=1, r >>=1) {
            if(l&1) lazy[l] = Monoid::func_lazy(lazy[l],x), propagate(l),l++;
            if(r&1) --r,lazy[r] = Monoid::func_lazy(lazy[r],x), propagate(r);
        }
        l = a + length, r = b + length - 1;
        while ((l>>=1),(r>>=1),l) {
            if(lazy[l] == Monoid::unit_lazy) node[l] = Monoid::func_fold(Monoid::func_operate(node[(l<<1)+0],lazy[(l<<1)+0],range[(l<<1)+0].first,range[(l<<1)+0].second),Monoid::func_operate(node[(l<<1)+1],lazy[(l<<1)+1],range[(l<<1)+1].first,range[(l<<1)+1].second));
            if(lazy[r] == Monoid::unit_lazy) node[r] = Monoid::func_fold(Monoid::func_operate(node[(r<<1)+0],lazy[(r<<1)+0],range[(r<<1)+0].first,range[(r<<1)+0].second),Monoid::func_operate(node[(r<<1)+1],lazy[(r<<1)+1],range[(r<<1)+1].first,range[(r<<1)+1].second));
        }
    }

    //fold [a,b)
    TypeNode fold(int a, int b) {
        int l = a + length, r = b + length - 1;
        for (int i = height; 0 < i; --i) propagate(l >> i), propagate(r >> i);
        TypeNode vl = Monoid::unit_node, vr = Monoid::unit_node;
        for(r++; l < r; l >>=1, r >>=1) {
            if(l&1) vl = Monoid::func_fold(vl,Monoid::func_operate(node[l],lazy[l],range[l].first,range[l].second)),l++;
            if(r&1) r--,vr = Monoid::func_fold(Monoid::func_operate(node[r],lazy[r],range[r].first,range[r].second),vr);
        }
        return Monoid::func_fold(vl,vr);
    }

    //return [0,length]
    int prefix_binary_search(TypeNode var) {
        int l = length, r = 2*length - 1;
        for (int i = height; 0 < i; --i) propagate(l >> i), propagate(r >> i);
        if(!Monoid::func_check(node[1],var)) return num;
        TypeNode ret = Monoid::unit_node;
        size_t idx = 2;
        for(; idx < 2*length; idx<<=1){
            if(!Monoid::func_check(Monoid::func_fold(ret,Monoid::func_operate(node[idx],lazy[idx],range[idx].first,range[idx].second)),var)) {
                ret = Monoid::func_fold(ret,Monoid::func_operate(node[idx],lazy[idx],range[idx].first,range[idx].second));
                idx++;
            }
        }
        return min((idx>>1) - length,num);
    }

    //range[l,r) return [l,r]
    int binary_search(size_t l, size_t r, TypeNode var) {
        if (l < 0 || length <= l || r < 0 || length < r) return -1;
        for (int i = height; 0 < i; --i) propagate((l+length) >> i), propagate((r+length-1) >> i);
        TypeNode ret = Monoid::unit_node;
        size_t off = l;
        for(size_t idx = l+length; idx < 2*length && off < r; ){
            if(range[idx].second<=r && !Monoid::func_check(Monoid::func_fold(ret,Monoid::func_operate(node[idx],lazy[idx],range[idx].first,range[idx].second)),var)) {
                ret = Monoid::func_fold(ret,Monoid::func_operate(node[idx],lazy[idx],range[idx].first,range[idx].second));
                off = range[idx++].second;
                if(!(idx&1)) idx >>= 1;
            }
            else{
                idx <<=1;
            }
        }
        return off;
    }

    void print(){
        // cout << "node" << endl;
        // for(int i = 1,j = 1; i < 2*length; ++i) {
        // 	cout << node[i] << " ";
        // 	if(i==((1<<j)-1) && ++j) cout << endl;
        // }
        // cout << "lazy" << endl;
        // for(int i = 1,j = 1; i < 2*length; ++i) {
        // 	cout << lazy[i] << " ";
        // 	if(i==((1<<j)-1) && ++j) cout << endl;
        // }
        cout << "vector" << endl;
        cout << "{ " << fold(0,1);
        for(int i = 1; i < length; ++i) cout << ", " << fold(i,i+1);
        cout << " }" << endl;
    }
};

/*
 * @title MonoidRangeSumRangeAdd - fold:区間和, opearate:区間加算
 * @docs md/operator/monoid-lazy/MonoidRangeSumRangeAdd.md
 */
template<class T, class U> struct MonoidRangeFoldSumRangeOperateAdd {
	using TypeNode = T;
	using TypeLazy = U;
	inline static TypeNode unit_node = 0;
	inline static TypeLazy unit_lazy = 0;
	inline static constexpr TypeNode func_fold(TypeNode l,TypeNode r){return l+r;}
	inline static constexpr TypeLazy func_lazy(TypeLazy old_lazy,TypeLazy new_lazy){return old_lazy+new_lazy;}
	inline static constexpr TypeNode func_operate(TypeNode node,TypeLazy lazy,int l, int r){return node+lazy*(r-l);}
	inline static constexpr bool func_check(TypeNode nodeVal,TypeNode var){return var <= nodeVal;}
};

/**
 * @url 
 * @est
 */ 
int main() {
    cin.tie(0);ios::sync_with_stdio(false);
    int N,P; read(N),read(P);
    runtime_mod = P;

    //i文字になってて、sがj文字になるときの数
    auto dp = multivector(N,N+2,Mint(0));
    dp[0][0]+=1;
    dp[0][1]-=1;

    for(int i=0;i<N;++i) {
        for(int j=1;j<=N;++j) dp[i][j]+=dp[i][j-1];
        for(int j=0;j<N;++j) {
            //文字種類
            int c = (j==0?26:25);
            //1+1,1+2,1+3,1+4 の 4種類？
            auto d = dp[i][j]*c;
            {
                int k=i+1+1,l=j+1,r=min(j+9,N)+1;
                if(k<N&&l<r) dp[k][l]+=d,dp[k][r]-=d;
            }
            {
                int k=i+1+2,l=j+10,r=min(j+99,N)+1;
                if(k<N&&l<r) dp[k][l]+=d,dp[k][r]-=d;
            }
            {
                int k=i+1+3,l=j+100,r=min(j+999,N)+1;
                if(k<N&&l<r) dp[k][l]+=d,dp[k][r]-=d;
            }
            {
                int k=i+1+4,l=j+1000,r=min(j+9999,N)+1;
                if(k<N&&l<r) dp[k][l]+=d,dp[k][r]-=d;
            }
        }
    }
    Mint ans=0;
    for(int i=0;i<N;++i) ans+=dp[i][N];
    cout << ans << endl;
    return 0;
}