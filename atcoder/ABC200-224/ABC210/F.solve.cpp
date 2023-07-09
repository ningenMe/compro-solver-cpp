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
 * @title Prime - 高速素因数分解・ミラーラビン素数判定・Gcd・Lcm
 * @docs md/math/Prime.md
 */
class Prime{
    using u128 = __uint128_t;
    using u64 = unsigned long long;
    using u32 = unsigned int;
    class MontgomeryMod {
        u64 mod,inv_mod,pow2_128;
        inline u64 reduce(const u128& val) {
            return (val + u128(u64(val) * u64(-inv_mod)) * mod) >> 64;
        }
        inline u128 init_reduce(const u64& val) {
            return reduce((u128(val) + mod) * pow2_128);
        }
        inline u64 mul_impl(const u64 l, const u64 r) {
            return reduce(u128(l)*r);
        }
    public:
        MontgomeryMod(const u64 mod):mod(mod),pow2_128(-u128(mod)%mod) {
            inv_mod = mod;
            for (int i = 0; i < 5; ++i) inv_mod *= 2 - mod * inv_mod;
        }
        //x^n % mod
        inline u64 pow(const u64& x, u64 n) {
            u64 mres = init_reduce(1);
            for (u64 mx = init_reduce(x); n > 0; n >>= 1, mx=mul_impl(mx,mx)) if (n & 1) mres = mul_impl(mres,mx);
            mres=reduce(mres);
            return mres >= mod ? mres - mod : mres;
        }
        inline u64 mul(const u64& l, const u64& r) {
            u64 ml=init_reduce(l),mr=init_reduce(r);
            u64 mres=reduce(mul_impl(ml,mr));
            return mres >= mod ? mres - mod : mres;
        }
        inline u64 mmul(const u64& l, const u64& r) {
            u64 ml=init_reduce(l),mr=init_reduce(r);
			return mul_impl(ml,mr);
        }
		//NOTE lはmontgomery modの状態
        inline u64 add(u64 ml, const u64& r) {
            u64 mr=init_reduce(r);
			if ((ml += mr) >= 2 * mod) ml -= 2 * mod;
            u64 mres=reduce(ml);
            return mres >= mod ? mres - mod : mres;
        }
    };
    inline static constexpr long long pow_uint128(long long x, long long n, long long mod) {
        long long res = 1;
        for (x %= mod; n > 0; n >>= 1, x=(u128(x)*x)%mod) if (n & 1) res = (u128(res)*x)%mod;
        return res;
    }
    template<size_t sz> inline static constexpr bool miller_rabin_uint128(const u64& n, const array<u64,sz>& ar) {
        u32 i,s=0; 
        u64 m = n - 1;
        for (;!(m&1);++s,m>>=1);
        MontgomeryMod mmod(n);
        for (const u64& a: ar) {
            if(a>=n) break;
            u64 r=pow_uint128(a,m,n);
            if(r != 1) {
                for(i=0; i<s; ++i) {
                    if(r == n-1) break;
                    r = (u128(r)*r)%n;
                }
                if(i==s) return false;
            }
        }
        return true;
    }
    template<size_t sz> inline static constexpr bool miller_rabin_montgomery(const u64& n, const array<u64,sz>& ar) {
        u32 i,s=0; 
        u64 m = n - 1;
        for (;!(m&1);++s,m>>=1);
        MontgomeryMod mmod(n);
        for (const u64& a: ar) {
            if(a>=n) break;
            u64 r=mmod.pow(a,m);
            if(r != 1) {
                for(i=0; i<s; ++i) {
                    if(r == n-1) break;
                    r = mmod.mul(r,r);
                }
                if(i==s) return false;
            }
        }
        return true;
    }
    inline static constexpr long long K = 5;
    inline static constexpr long long gcd_impl(long long n, long long m) {
        long long t=0,s=0;
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
        long long t = 0;
        for(int i = 0; t = n - m, i < 4; ++i) {
            (t < m ? n=m,m=t : n=t);
            if(!m) return n;
        }
        return gcd_impl(n, m);
    }
    inline static constexpr array<u64,3> ar1={2ULL, 7ULL, 61ULL};
    inline static constexpr array<u64,7> ar2={2ULL,325ULL,9375ULL,28178ULL,450775ULL,9780504ULL,1795265022ULL};
    inline static u64 rho(const u64& n){
        if(miller_rabin(n)) return n;
        if((n&1) == 0) return 2;
		MontgomeryMod mmod(n);
        for(u64 c=1,x=2,y=2,d=0;;c++){
            do{
				x=mmod.add(mmod.mmul(x,x),c);
				y=mmod.add(mmod.mmul(y,y),c);
				y=mmod.add(mmod.mmul(y,y),c);
                d=gcd(x-y+n,n);
            }while(d==1);
            if(d<n) return d;
        }
    }
    inline static vector<u64> factor(const u64& n, bool is_root) {
        if(n <= 1) return {};
        u64 p = rho(n);
        if(p == n) return {p};
        auto l = factor(p, false);
        auto r = factor(n / p, false);
        copy(r.begin(), r.end(), back_inserter(l));
		if(is_root) sort(l.begin(),l.end());
        return l;
    }
    inline static constexpr bool miller_rabin(const u64 n) {
        if(n <= 1) return false;
        if(n == 2) return true;
        if(n%2 == 0) return false;
        if(n == 3) return true;
        if(n%3 == 0) return false;
        if(n < 4759123141ULL) return miller_rabin_montgomery(n, ar1);
		if(n <= 1000'000'000'000'000'000ULL) miller_rabin_montgomery(n, ar2); //'
        return miller_rabin_uint128(n, ar2);
    }
    inline static vector<pair<u64,u64>> factorization_impl(const u64 n) {
		// queue<u64> q; q.push(n);
		// vector<u64> v;
		// while(q.size()) {
		// 	u64 tn = q.front(); q.pop();
		// 	if(tn<=1) continue;
		// 	u64 p = rho(tn);
		// 	if(p!=tn) q.push(p),q.push(tn/p);
		// 	else v.push_back(p);
		// }
        auto v = factor(n, true);
        vector<pair<u64,u64>> vp;
        u64 prev = 0;
        for(u64& p:v) {
            if(p == prev) vp.back().second++;
            else vp.emplace_back(p,1);
            prev=p;
        }
        return vp;
    }
    inline static vector<u64> divisor_impl(const u64 n) {
        auto fac = factorization_impl(n);
        vector<u64> res = {1};
        for(auto& [p,m]: fac) {
            u32 sz = res.size();
            for(u32 i=0;i<sz;++i) {
                u64 d = 1;
                for(u32 j=0;j<m;++j) {
                    d *= p;
                    res.push_back(res[i]*d);
                }
            }
        }
        return res;
    }
public:
    inline static constexpr bool is_prime(const u64 n) { return miller_rabin(n); }
	//{素因数,個数}のvectorが返却される
    inline static vector<pair<u64,u64>> factorization(const u64 n) {return factorization_impl(n);}
	//素因数が愚直に昇順で返却される
    inline static vector<u64> factor(const u64 n) {return factor(n, true);}
    //約数が昇順で列挙される
    inline static vector<u64> divisor(const u64 n) {return divisor_impl(n); }
    inline static constexpr long long gcd(long long n, long long m) { return (n>m ? pre(n,m) : pre(m,n));}
    inline static constexpr long long naive_gcd(long long a, long long b) { return (b ? naive_gcd(b, a % b):a);}
    inline static constexpr long long lcm(long long a, long long b) {return (a*b ? (a / gcd(a, b)*b): 0);}
    inline static constexpr long long ext_gcd(long long a, long long b, long long &x, long long &y) {
        if (b == 0) return x = 1, y = 0, a; long long d = ext_gcd(b, a%b, y, x); return y -= a / b * x, d;
    }
};

/*
 * @title StronglyConnectedComponents - 強連結成分分解
 * @docs md/graph/StronglyConnectedComponents.md
 */
class StronglyConnectedComponents{
    int num,is_2sat,half,max_id,cnt;
    vector<vector<int>> edge;
    vector<int> label,order,low;
    stack<size_t> st;
    inline int rev(int i) { return i < half ? i + half : i - half; }
    inline void dfs(int& from) {
        low[from]=order[from]=cnt++;
        st.push(from);
        for(int& to:edge[from]) {
            if(order[to]==-1) {
                dfs(to);
                low[from]=min(low[from],low[to]);
            }
            else {
                low[from]=min(low[from],order[to]);
            }
        }
        if (low[from] == order[from]) {
            while(st.size()) {
                int u = st.top();st.pop();
                order[u] = num;
                label[u] = max_id;
                if (u == from) break;
            }
            max_id++;
        }
    }
public:
    StronglyConnectedComponents(const int n, bool is_2sat=0):num(n),max_id(0),cnt(0),is_2sat(is_2sat){
        if(is_2sat) num<<=1;
        edge.resize(num);
        label.resize(num);
        order.resize(num,-1);
        low.resize(num);
        half=(num>>1);
    }
    inline int operator[](int idx) {
        return label[idx];
    }
    inline void make_edge(const int from,const int to) {
        edge[from].push_back(to);
    }
    //xがflg_xならばyがflg_y
    inline void make_condition(int x, bool flg_x, int y, bool flg_y) {
        if (!flg_x) x = rev(x);
        if (!flg_y) y = rev(y);
        make_edge(x, y);
        make_edge(rev(y), rev(x));
    }
    //is_2sat=1のときに、2satを満たすかを返却する
    inline bool solve(void) {
        for (int i = 0; i < num; i++) if (order[i] == -1) dfs(i);
        for (int& id:label) id = max_id-1-id;
        if(!is_2sat) return true;
        for (int i = 0; i < num; ++i) if (label[i] == label[rev(i)]) return false;
        return true;
    }
    vector<vector<int>> topological_sort(void) {
        vector<vector<int>> ret(max_id);
        for(int i=0;i<num;++i) ret[label[i]].push_back(i);
        return ret;
    }
    int is_true(int i) {
        return label[i] > label[rev(i)];
    }
    void print(void) {
        for(auto id:label) cout << id << " ";
        cout << endl;
    }
};

/**
 * @url 
 * @est
 */ 
int main() {
    cin.tie(0);ios::sync_with_stdio(false);
    int N; read(N);
    StronglyConnectedComponents scc(N,1);
    vector<int> A(N),B(N);
    for(int i=0;i<N;++i) read(A[i]),read(B[i]);
    int M = 2000010;
    vector<vector<pair<int,int>>> C(M);
    for(int i=0;i<N;++i) C[A[i]].push_back({i,1});
    for(int i=0;i<N;++i) C[B[i]].push_back({i,0});
    vector<int> dp(M,1);
    for(int i=2;i<M;++i) {
        if(!dp[i]) continue;
        vector<pair<int,int>> vp;
        for(int j=i; j<M; j+=i) {
            dp[j]=0;
            for(auto p: C[j]) vp.push_back(p);
        }
        int L = vp.size();
        for(int j=0;j<L;++j) {
            for(int k=j+1; k<L;++k) {
                if(vp[j].first >= vp[k].first) continue;
                scc.make_condition(vp[j].first, vp[j].second, vp[k].first, !vp[k].second);
            }
        }
    }

    Yn(scc.solve());

    return 0;
}
