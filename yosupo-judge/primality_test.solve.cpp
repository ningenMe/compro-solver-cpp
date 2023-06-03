#include <iostream>
#include <vector>
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
 * @title Prime - 高速素因数分解・ミラーラビン素数判定
 * @docs md/math/Prime.md
 */
class Prime{
    using int128 = __int128_t;
    using int64  = long long;
    using u64 = unsigned long long;
    using u32 = unsigned int;
    inline static long long gcd_impl(long long n, long long m) {
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
        return gcd_impl(m, n % m);
    }
    inline static constexpr long long pre(long long n, long long m) {
        long long t = n - m;
        for(int i = 0; t = n - m, i < 4; ++i) {
            (t < m ? n=m,m=t : n=t);
            if(!m) return n;
        }
        return gcd_impl(n, m);
    }
    inline static constexpr long long pow(long long x, long long n, long long mod) {
        long long res = 1;
        for (x %= mod; n > 0; n >>= 1, x=(int128(x)*x)%mod) if (n & 1) res = (int128(res)*x)%mod;
        return res;
    }
    inline static constexpr array<u64,3> ar1={2ULL, 7ULL, 61ULL};
    inline static constexpr array<u64,7> ar2={2ULL,325ULL,9375ULL,28178ULL,450775ULL,9780504ULL,1795265022ULL};
    inline static constexpr int64 rho(int64 n){
        if(miller_rabin(n)) return n;
        if(n%2 == 0) return 2;
        for(int64 c=1,x=2,y=2,d=0;;c++){
            do{
                x=(int128(x)*x+c)%n;
                y=(int128(y)*y+c)%n;
                y=(int128(y)*y+c)%n;
                d=gcd(x-y+n,n);
            }while(d==1);
            if(d<n) return d;
        }
    }
    inline static vector<int64> factor(const int64 n) {
        if(n <= 1) return {};
        int64 p = rho(n);
        if(p == n) return {p};
        auto l = factor(p);
        auto r = factor(n / p);
        copy(r.begin(), r.end(), back_inserter(l));
        return l;
    }
    template<size_t sz> inline static constexpr bool miller_rabin(const u64& n, const array<u64,sz>& ar) {
        u32 i,s=0; 
        u64 m = n - 1;
        for (;!(m&1);++s,m>>=1);
        for (const u64& a: ar) {
            if(a>=n) break;
            u64 r=pow(a,m,n);
            if(r != 1) {
                for(i=0; i<s; ++i) {
                    if(r == n-1) break;
                    r = (int128(r)*r)%n;
                }
                if(i==s) return false;
            }
        }
        return true;
    }
    inline static constexpr bool miller_rabin(const u64 n) {
        if(n <= 1) return false;
        if(n == 2) return true;
        if(n%2 == 0) return false;
        if(n == 3) return true;
        if(n%3 == 0) return false;
        if(n < 4759123141LL) return miller_rabin(n, ar1);
        return miller_rabin(n, ar2);
    }
    inline static vector<pair<int64,int64>> factorization_impl(const int64 n) {
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
public:
    inline static constexpr bool is_prime(const u64 n) { return is_prime(n); }
    inline static vector<pair<int64,int64>> factorization(const int64 n) {return factorization_impl(n);}
    inline static constexpr long long gcd(long long n, long long m) { return (n>m ? pre(n,m) : pre(m,n));}
    inline static constexpr long long naive_gcd(long long a, long long b) { return (b ? naive_gcd(b, a % b):a);}
    inline static constexpr long long lcm(long long a, long long b) {return (a*b ? (a / gcd(a, b)*b): 0);}
    inline static constexpr long long ext_gcd(long long a, long long b, long long &x, long long &y) {
        if (b == 0) return x = 1, y = 0, a; long long d = ext_gcd(b, a%b, y, x); return y -= a / b * x, d;
    }
};

int main(void){
    cin.tie(0);ios::sync_with_stdio(false);
    int Q; read(Q);
    while(Q--) {
        unsigned long long n; read(n);
        cout << (Prime::is_prime(n) ? "Yes" : "No") << "\n";
	}
	return 0;
}