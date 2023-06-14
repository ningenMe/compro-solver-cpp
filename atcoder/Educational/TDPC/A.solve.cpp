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
 * @title NumberTheoreticalTransform - 数論変換
 * @docs md/convolution/NumberTheoreticalTransform.md
 */
template<long long mod> class NumberTheoreticalTransform {
    inline static constexpr int prime_1004535809 =1004535809;
    inline static constexpr int prime_998244353  =998244353;
    inline static constexpr int prime_985661441  =985661441;
    inline static constexpr int prime_998244353_1004535809 = ModInt<prime_998244353>(prime_1004535809).inv().x;
    inline static constexpr int prime_985661441_1004535809 = ModInt<prime_985661441>(prime_1004535809).inv().x;
    inline static constexpr int prime_985661441_998244353 = ModInt<prime_985661441>(prime_998244353).inv().x;
    inline static constexpr long long prime12=((long long)prime_1004535809) * prime_998244353;
    inline static constexpr int log2n_max = 21;
    template<int prime> inline static constexpr array<ModInt<prime>,log2n_max> get_pow2_inv() {
        array<ModInt<prime>,log2n_max>  ar;
        ModInt<prime> v=1; ar[0]=v;
        for(int i=1;i<log2n_max;++i) ar[i]=ar[i-1]/2;
        return ar;
    }
    inline static constexpr array<ModInt<prime_1004535809>,log2n_max> pow2_inv_1004535809 = get_pow2_inv<prime_1004535809>();
    inline static constexpr array<ModInt<prime_998244353>, log2n_max> pow2_inv_998244353  = get_pow2_inv<prime_998244353>();
    inline static constexpr array<ModInt<prime_985661441>, log2n_max> pow2_inv_985661441  = get_pow2_inv<prime_985661441>();

    template<int prime> inline static constexpr array<ModInt<prime>,log2n_max> get_base(int inv=0) {
        array<ModInt<prime>,log2n_max> base, es, ies;
        //TODO 3のハードコーディングを直す
        ModInt<prime> e = ModInt<prime>(3).pow((prime - 1) >> log2n_max), ie = e.inv();
        for (int i = log2n_max; i >= 2; --i) {
            es[i - 2]  = e, ies[i - 2] = ie;
            e *= e, ie *= ie;
        }
        ModInt<prime> acc = 1;
        if(!inv) {
            for (int i = 0; i < log2n_max - 2; ++i) {
                base[i] = es[i] * acc;
                acc *= ies[i];
            }
        }
        else {
            for (int i = 0; i < log2n_max - 2; ++i) {
                base[i] = ies[i] * acc;
                acc *= es[i];
            }
        }
        return base;
    }
    inline static constexpr array<ModInt<prime_1004535809>,log2n_max> base_1004535809=get_base<prime_1004535809>();
    inline static constexpr array<ModInt<prime_1004535809>,log2n_max> ibase_1004535809=get_base<prime_1004535809>(1);
    inline static constexpr array<ModInt<prime_998244353>,log2n_max> base_998244353=get_base<prime_998244353>();
    inline static constexpr array<ModInt<prime_998244353>,log2n_max> ibase_998244353=get_base<prime_998244353>(1);
    inline static constexpr array<ModInt<prime_985661441>,log2n_max> base_985661441=get_base<prime_985661441>();
    inline static constexpr array<ModInt<prime_985661441>,log2n_max> ibase_985661441=get_base<prime_985661441>(1);

    using Mint1 = ModInt<prime_1004535809>;
    using Mint2 = ModInt<prime_998244353>;
    using Mint3 = ModInt<prime_985661441>;
    inline static ModInt<mod> garner(const Mint1& b1,const Mint2& b2,const Mint3& b3) {Mint2 t2 = (b2-b1.x)*prime_998244353_1004535809;Mint3 t3 = ((b3-b1.x)*prime_985661441_1004535809-t2.x)*prime_985661441_998244353;return ModInt<mod>(ModInt<mod>(prime12)*t3.x+b1.x+prime_1004535809*t2.x);}

    template<long long prime> inline static void butterfly(vector<ModInt<prime>>& a, const array<ModInt<prime>,log2n_max>& base) {
        int h = __builtin_ctz(a.size());
        for (int i = 0; i < h; i++) {
            int w = 1 << i, p = 1 << (h - (i+1));
            ModInt<prime> acc = 1;
            for (unsigned int s = 0; s < w; s++) {
                int offset = s << (h - i);
                for (int j = 0; j < p; ++j) {
                    auto l = a[j + offset];
                    auto r = a[j + offset + p] * acc;
                    a[j + offset] = l + r;
                    a[j + offset + p] = l - r;
                }
                acc *= base[__builtin_ctz(~s)];
            }
        }
    }
    template<long long prime> inline static void ibutterfly(vector<ModInt<prime>>& a, const array<ModInt<prime>,log2n_max>& base) {
        int h = __builtin_ctz(a.size());
        for (int i = h-1; 0 <= i; i--) {
            int w = 1 << i, p = 1 << (h - (i+1));
            ModInt<prime> acc = 1;
            for (unsigned int s = 0; s < w; s++) {
                int offset = s << (h - i);
                for (int j = 0; j < p; ++j) {
                    auto l = a[j + offset];
                    auto r = a[j + offset + p];
                    a[j + offset] = l + r;
                    a[j + offset + p] = (l - r) * acc;
                }
                acc *= base[__builtin_ctz(~s)];
            }
        }
    }
    template<long long prime> inline static vector<ModInt<prime>> convolution_friendrymod(
        const vector<ModInt<mod>>& a,
        const vector<ModInt<mod>>& b,
        const array<ModInt<prime>,log2n_max>& base,
        const array<ModInt<prime>,log2n_max>& ibase,
        const array<ModInt<prime>,log2n_max>& pow2_inv
    ){
        int n = a.size(), m = b.size();
        if (!n || !m) return {};
        if (min(n, m) <= 60) {
            vector<ModInt<prime>> f(n+m-1);
            if (n >= m) for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) f[i+j]+=a[i].x*b[j].x;
            else for (int j = 0; j < m; j++) for (int i = 0; i < n; i++) f[i+j]+=a[i].x*b[j].x;
            return f;
        }

        int N,L,M=n+m-1; for(N=1,L=0;N<M;N*=2,++L);
        ModInt<prime> inverse = pow2_inv[L];
        vector<ModInt<prime>> g(N,0),h(N,0);
        for(int i=0;i<a.size();++i) g[i]=a[i].x;
        for(int i=0;i<b.size();++i) h[i]=b[i].x;

        butterfly<prime>(g,base);
        butterfly<prime>(h,base);
        for(int i = 0; i < N; ++i) g[i] *= h[i];
        ibutterfly<prime>(g,ibase);
        for (int i = 0; i < n + m - 1; i++) g[i] *= inverse;
        return g;
    }
    template<long long prime, long long ZZ> class Inner {
    public:
        inline static vector<ModInt<prime>> convolution_impl(const vector<ModInt<mod>>& g,const vector<ModInt<mod>>& h){
            auto f1 = convolution_friendrymod<prime_1004535809>(g, h, base_1004535809, ibase_1004535809, pow2_inv_1004535809);
            auto f2 = convolution_friendrymod<prime_998244353> (g, h, base_998244353,  ibase_998244353,  pow2_inv_998244353);
            auto f3 = convolution_friendrymod<prime_985661441> (g, h, base_985661441,  ibase_985661441,  pow2_inv_985661441);

            vector<ModInt<prime>> f(f1.size());
            for(int i=0; i<f1.size(); ++i) f[i] = garner(f1[i],f2[i],f3[i]);
            return f;
        }
    };
    template<long long prime> class Inner<prime, prime_998244353> {
    public:
        inline static vector<ModInt<prime>> convolution_impl(const vector<ModInt<mod>>& g,const vector<ModInt<mod>>& h) { 
            return convolution_friendrymod<prime>(g,h,base_998244353,ibase_998244353,pow2_inv_998244353);
        }
    }; 
public:
    inline static vector<ModInt<mod>> convolution(const vector<ModInt<mod>>& g,const vector<ModInt<mod>>& h){return Inner<mod,mod>::convolution_impl(g,h);}
};

/*
 * @title FormalPowerSeries - 形式的冪級数
 * @docs md/polynomial/FormalPowerSeries.md
 */
template<long long prime, class T = ModInt<prime>> struct FormalPowerSeries : public vector<T> {
    using vector<T>::vector;
    using Mint  = T;
    using Fps   = FormalPowerSeries<prime>;
    inline static constexpr int N_MAX = 1000000;
    Fps even(void) const {Fps ret;for(int i = 0; i < this->size(); i+=2) ret.push_back((*this)[i]);return ret;}
    Fps odd(void)  const {Fps ret;for(int i = 1; i < this->size(); i+=2) ret.push_back((*this)[i]);return ret;}
    Fps symmetry(void) const {Fps ret(this->size());for(int i = 0; i < ret.size(); ++i) ret[i] = (*this)[i]*(i&1?-1:1);return ret;}
public:
    //a0 + a_1*x^1 + a_2*x^2 + ... + a_(n-1)*x^(n-1)
    FormalPowerSeries(const vector<Mint>& v){*this=FormalPowerSeries(v.size());for(int i=0;i<v.size();++i) (*this)[i]=v[i];}
    //TODO constexprにする
    inline static vector<Mint> invs;
    static void invs_build() {
        if(invs.size()) return;
        vector<Mint> fac(N_MAX+1,1),finv(N_MAX+1,1);
        invs.resize(N_MAX+1);
        for(int i=1;i<=N_MAX;i++) fac[i]=fac[i-1]*i;
        finv[N_MAX]=fac[N_MAX].inv();
        for(int i=N_MAX;i>=1;i--) finv[i-1]=finv[i]*i;
        for(int i=1;i<=N_MAX;i++) invs[i]=finv[i]*fac[i-1];
    }
    Fps operator*(const int r) const {return Fps(*this) *= r; }
    Fps &operator*=(const int r) {for(int i=0;i< this->size(); ++i) (*this)[i] *= r; return *this; }
    Fps operator*(const long long int r) const {return Fps(*this) *= r; }
    Fps &operator*=(const long long int r) {for(int i=0;i< this->size(); ++i) (*this)[i] *= r; return *this; }
    Fps operator*(const Mint r) const {return Fps(*this) *= r; }
    Fps &operator*=(const Mint r) {for(int i=0;i< this->size(); ++i) (*this)[i] *= r; return *this; }
    Fps operator/(const int r) const {return Fps(*this) /= r; }
    Fps &operator/=(const int r) {return (*this) *= Mint(r).inv(); }
    Fps operator+(const int r) const {return Fps(*this) += r; }
    Fps &operator+=(const int r) {for(int i=0;i< this->size(); ++i) (*this)[i] += r; return *this; }
    Fps operator-(void) const {return Fps(*this) *= (-1);}
    Fps operator-(const int r) const {return Fps(*this) -= r; }
    Fps &operator-=(const int r) {for(int i=0;i< this->size(); ++i) (*this)[i] -= r; return *this; }
    Fps prefix(size_t n) const {
        return Fps(this->begin(),this->begin()+min(n,this->size()));
    }
    Fps inv(size_t n) const {
        Fps ret({Mint(1)/(*this)[0]});
        for(size_t i=2,m=(n<<1);i < m; i<<=1) {
            Fps h = mul(mul(ret,ret),(this->prefix(i)));
            ret.resize(i);
            for(int j=i>>1;j<i;++j) ret[j] -= h[j];
        }
        return ret.prefix(n);
    }
    Fps inv(void) const {return inv(this->size());}
    Fps diff(void) const {
        Fps ret(max(0,int(this->size())-1));
        for(int i=0;i<ret.size(); ++i) ret[i]=(*this)[i+1]*(i+1);
        return ret;
    }
    Fps intg(size_t n) const {
        invs_build();
        Fps ret(min(this->size()+1,n));
        for(int i=1;i<ret.size(); ++i) ret[i]=(*this)[i-1]*invs[i];
        return ret;
    }
    Fps log(size_t n) const {
        return mul(this->diff(),this->inv(n)).intg(n);
    }
    Fps log(void) const {return log(this->size());}
    Fps exp(size_t n) const {
        Fps ret(1,1);
        for(size_t i=2,m=(n<<1);i<m;i<<=1) {
            Fps h = mul(ret,(sub(this->prefix(i),ret.log(i))));
            ret.resize(i);
            for(int j=i>>1;j<i;++j) ret[j] += h[j];
        }
        return ret.prefix(n);
    }
    Fps exp(void) const {return exp(this->size());}
    Fps pow(long long k,size_t n) const {
        Fps ret(n,0);
        for(size_t i=0,m = min(n,this->size()); i < m && i*k < n; ++i) {
            if((*this)[i].x == 0) continue;
            Mint t0=(*this)[i], t0_inv=t0.inv();
            Fps tmp(n-i);for(int j=i;j<m; ++j) tmp[j-i]=(*this)[j]*t0_inv;
            tmp = (tmp.log(n)*k).exp(n)*(t0.pow(k));
            for(int j=0;j+i*k<n;++j) ret[j+i*k] = tmp[j];
            break;
        }
        return ret;
    }
    Fps pow(long long k) const {return pow(k,this->size());}
    Mint eval(Mint x) const {
        Mint base = 1,ret = 0;
        for(size_t i=0;i<this->size();++i) {
            ret += (*this)[i]*base;
            base *= x;
        }
        return ret;
    }
    inline static Fps add(const Fps& lhs,const Fps& rhs) {
        size_t n = lhs.size(), m = rhs.size();
        Fps res(max(n,m),0);
        for(int i=0;i<n;++i) res[i] += lhs[i];
        for(int i=0;i<m;++i) res[i] += rhs[i];
        return res;
    }
    inline static Fps sub(const Fps& lhs,const Fps& rhs) {
        size_t n = lhs.size(), m = rhs.size();
        Fps res(max(n,m),0);
        for(int i=0;i<n;++i) res[i] += lhs[i];
        for(int i=0;i<m;++i) res[i] -= rhs[i];
        return res;
    }
    inline static Fps mul(const Fps& lhs, const Fps& rhs) {
        return NumberTheoreticalTransform<prime>::convolution(lhs,rhs);
    }
    inline static Fps div(Fps lhs, Fps rhs) {
        while(lhs.size() && lhs.back().x == 0) lhs.pop_back();
        while(rhs.size() && rhs.back().x == 0) rhs.pop_back();
        int n = lhs.size(), m = rhs.size();
        if(n < m) return Fps(1,0);
        reverse(lhs.begin(),lhs.end());
        reverse(rhs.begin(),rhs.end());
        auto f = mul(lhs,rhs.inv(n-m+1)).prefix(n-m+1);
        reverse(f.begin(),f.end());
        return f;
    }
    inline static Fps mod(const Fps& lhs, const Fps& rhs) {
        int m = rhs.size();
        auto f = sub(lhs,mul(div(lhs,rhs).prefix(m),rhs)).prefix(m);
        while(f.size() && f.back().x==0) f.pop_back();
        return f;
    }
    inline static Fps fold_all(vector<Fps> vfps) {
        if(vfps.empty()) return {};
        priority_queue<pair<size_t,size_t>, vector<pair<size_t,size_t>>, greater<>> pq;
        for(size_t i=0;i<vfps.size(); ++i) pq.emplace(vfps[i].size(), i);
        while(pq.size()>1) {
            auto l=pq.top().second; pq.pop();
            auto r=pq.top().second; pq.pop();
            vfps[l]=mul(vfps[l],vfps[r]);
            vfps[r]={};
            pq.emplace(vfps[l].size(), l);
        }
        auto ret=pq.top().second; pq.pop();
        return vfps[ret];
    }
    vector<Mint> multipoint_evaluation(vector<Mint> x) {
        int n = x.size(),m;
        for(m=1;m<n;m<<=1);
        vector<Fps> f(2*m,Fps(1,1));
        for(int i=0;i<n;++i) f[i+m] = Fps({-x[i],1});
        for(int i=m-1;i;--i) f[i] = mul(f[(i<<1)|0],f[(i<<1)|1]);
        f[1] = mod(*this,f[1]);
        for(int i=2;i<m+n;++i) f[i] = mod(f[i>>1],f[i]);
        for(int i=0;i<n;++i)   x[i] = f[i+m][0];
        return x;
    }
    inline static Fps interpolation(const vector<Mint>& x,const vector<Mint>& y) {
        int n = x.size(),m;
        for(m=1;m<n;m<<=1);
        vector<Fps> f(2*m,Fps(1,1)),g(2*m);
        for(int i=0;i<n;++i) f[i+m] = Fps({-x[i],1});
        for(int i=m-1;i;--i) f[i] = mul(f[(i<<1)|0],f[(i<<1)|1]);
        g[1] = mod(f[1].diff(), f[1]);
        for(int i=2;i<m+n;++i) g[i] = mod(g[i>>1],f[i]);
        for(int i=0;i<n;++i) g[i+m] = Fps(1, y[i] / g[i+m][0]);
        for(int i=m-1;i;--i) g[i] = add(mul(g[(i<<1)|0],f[(i<<1)|1]),mul(f[(i<<1)|0],g[(i<<1)|1]));
        return g[1];
    }
    inline static Mint nth_term(long long n, Fps numerator,Fps denominator) {
        while(n) {
            numerator    = mul(numerator,denominator.symmetry());
            numerator    = ((n&1)?numerator.odd():numerator.even());
            denominator  = mul(denominator,denominator.symmetry());
            denominator  = denominator.even();
            n >>= 1;
        }
        return numerator[0];
    }

    friend ostream &operator<<(ostream &os, const Fps& fps) {os << "{" << fps[0];for(int i=1;i<fps.size();++i) os << ", " << fps[i];return os << "}";}
};

/**
 * @url 
 * @est
 */ 
int main() {
    cin.tie(0);ios::sync_with_stdio(false);
    int N; read(N);
    using Fps = FormalPowerSeries<MOD_998244353>;
    vector<Fps> vf;
    for(int i=0;i<N;++i) {
        int a; read(a);
        Fps f(101,0);
        f[0]=1;
        f[a]=1;
        vf.push_back(f);
    }
    auto g=Fps::fold_all(vf);
    int sum=0;
    for(int i=0;i<g.size();++i) if(g[i].x > 0) ++sum;
    cout << sum << endl;
    return 0;
}
