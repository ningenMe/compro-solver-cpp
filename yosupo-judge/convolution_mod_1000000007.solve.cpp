#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod_1000000007"

#include <vector>
#include <iostream>
#include <numeric>
#include <algorithm>
#include <array>
using namespace std;

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
 * @docs md/math/NumberTheoreticalTransform.md
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

    template<int prime> inline static void butterfly(vector<ModInt<prime>>& a, const array<ModInt<prime>,log2n_max>& base) {
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
    template<int prime> inline static void ibutterfly(vector<ModInt<prime>>& a, const array<ModInt<prime>,log2n_max>& base) {
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
    template<int prime> inline static vector<ModInt<prime>> convolution_friendrymod(
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
    template<int prime, int ZZ> class Inner {
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
    template<int prime> class Inner<prime, prime_998244353> {
    public:
        inline static vector<ModInt<prime>> convolution_impl(const vector<ModInt<mod>>& g,const vector<ModInt<mod>>& h) { 
            return convolution_friendrymod<prime>(g,h,base_998244353,ibase_998244353,pow2_inv_998244353);
        }
    }; 
public:
    inline static vector<ModInt<mod>> convolution(const vector<ModInt<mod>>& g,const vector<ModInt<mod>>& h){return Inner<mod,mod>::convolution_impl(g,h);}
};


int main(void){
	cin.tie(0);ios::sync_with_stdio(false);
    int N,M; read(N),read(M);
    vector<ModInt<MOD_1000000007>> A(N),B(M);
    for(int i = 0; i < N; ++i) {
        int a; read(a); A[i]=a;
    }
    for(int i = 0; i < M; ++i) {
        int b; read(b); B[i]=b;
    }
	auto C = NumberTheoreticalTransform<MOD_1000000007>::convolution(A,B);
    for(int i = 0; i < N+M-1; ++i) cout << C[i] << " \n"[i==N+M-2];
	return 0;
}