#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define ALL(obj) (obj).begin(),(obj).end()
#define SPEED cin.tie(0);ios::sync_with_stdio(false);

template<class T> using PQ = priority_queue<T>;
template<class T> using PQR = priority_queue<T,vector<T>,greater<T>>;

constexpr long long MOD = (long long)1e9 + 7;
constexpr long long MOD2 = 998244353;
constexpr long long HIGHINF = (long long)1e18;
constexpr long long LOWINF = (long long)1e15;
constexpr long double PI = 3.1415926535897932384626433L;

template <class T> vector<T> multivector(size_t N,T init){return vector<T>(N,init);}
template <class... T> auto multivector(size_t N,T... t){return vector<decltype(multivector(t...))>(N,multivector(t...));}
template <class T> void corner(bool flg, T hoge) {if (flg) {cout << hoge << endl; exit(0);}}
template <class T, class U>ostream &operator<<(ostream &o, const map<T, U>&obj) {o << "{"; for (auto &x : obj) o << " {" << x.first << " : " << x.second << "}" << ","; o << " }"; return o;}
template <class T>ostream &operator<<(ostream &o, const set<T>&obj) {o << "{"; for (auto itr = obj.begin(); itr != obj.end(); ++itr) o << (itr != obj.begin() ? ", " : "") << *itr; o << "}"; return o;}
template <class T>ostream &operator<<(ostream &o, const multiset<T>&obj) {o << "{"; for (auto itr = obj.begin(); itr != obj.end(); ++itr) o << (itr != obj.begin() ? ", " : "") << *itr; o << "}"; return o;}
template <class T>ostream &operator<<(ostream &o, const vector<T>&obj) {o << "{"; for (int i = 0; i < (int)obj.size(); ++i)o << (i > 0 ? ", " : "") << obj[i]; o << "}"; return o;}
template <class T, class U>ostream &operator<<(ostream &o, const pair<T, U>&obj) {o << "{" << obj.first << ", " << obj.second << "}"; return o;}
template <template <class tmp>  class T, class U> ostream &operator<<(ostream &o, const T<U> &obj) {o << "{"; for (auto itr = obj.begin(); itr != obj.end(); ++itr)o << (itr != obj.begin() ? ", " : "") << *itr; o << "}"; return o;}
void print(void) {cout << endl;}
template <class Head> void print(Head&& head) {cout << head;print();}
template <class Head, class... Tail> void print(Head&& head, Tail&&... tail) {cout << head << " ";print(forward<Tail>(tail)...);}
template <class T> void chmax(T& a, const T b){a=max(a,b);}
template <class T> void chmin(T& a, const T b){a=min(a,b);}
void YN(bool flg) {cout << (flg ? "YES" : "NO") << endl;}
void Yn(bool flg) {cout << (flg ? "Yes" : "No") << endl;}
void yn(bool flg) {cout << (flg ? "yes" : "no") << endl;}

/*
 * @title NumberTheoreticTransform
 */
template<int mod, int root = 3> class NumberTheoreticTransform {
	inline static constexpr long long gcd(long long a, long long b) {
		return (b ? gcd(b, a % b):a);
	}
	inline static long long ext_gcd(long long a, long long b, long long &x, long long &y) {
		long long res;
		if (b == 0) res = a,x = 1,y = 0;
		else res = ext_gcd(b, a%b, y, x), y -= a/b * x;
		return res;
	}
	inline static long long inv_mod(long long a, long long b) {
		long long x, y;
		ext_gcd(a, b, x, y);
		return (x%b+b)%b;
	}
	inline static long long pow_mod(long long x, long long n, long long m) {
		long long res = 1;
		for (; n > 0; n >>= 1, (x *= x) %= m) if (n & 1) (res *= x) %= m;
		return res;
	}
	inline static long long garner(vector<long long> b, vector<long long> m, long long d){
		int N=b.size();
		vector<long long> coe(N+1,1),val(N+1,0);
		long long g,gl,gr,sum=accumulate(b.begin(),b.end(),0LL);
		//互いに素になるように処理
		for (int l = 0; l < N; ++l) {
			for (int r = l+1; r < N; ++r) {
				g = gcd(m[l], m[r]);
				if (sum && (b[l] - b[r]) % g != 0) return -1;
				m[l] /= g, m[r] /= g;
				gl = gcd(m[l], g), gr = g/gl;
				do {
					g = gcd(gl, gr);
					gl *= g, gr /= g;
				} while (g != 1);
				m[l] *= gl, m[r] *= gr;
				b[l] %= m[l], b[r] %= m[r];
			}
		}
		if(!sum) {
			long long lcm = 1;
			for(auto& e:m) (lcm*=e)%=d;
			return lcm;
		}
		m.push_back(d);
		for(int i = 0; i < N; ++i) {
			long long t = (b[i] - val[i]) * inv_mod(coe[i], m[i]);
			((t %= m[i]) += m[i]) %= m[i];
			for (int j = i+1; j <= N; ++j) {
				(val[j] += t * coe[j]) %= m[j];
				(coe[j] *= m[i]) %= m[j];
			}
		}
		return val.back();
	}
	inline static void ntt(vector<long long>& f,int sgn=1) {
		int N = f.size();
		int h = pow_mod(root, (mod - 1) / N, mod);
		if (sgn == -1) h = inv_mod(h, mod);
		for (int i = 0,j = 1; j < N - 1; ++j) {
			for (int k = N >> 1; k > (i ^= k); k >>= 1);
			if (j < i) swap(f[i], f[j]);
		}
		for (int i = 1,j = 2; i < N; i *= 2, j *= 2) {
			long long w = 1, base = pow_mod(h, N / j, mod);
			for(int k= 0;k < i; ++k, (w *= base) %= mod) {
				for (int l = k; l < N; l += j) {
					long long u = f[l];
					long long d = f[l + i] * w % mod;
					f[l] = u + d;
					if (f[l] >= mod) f[l] -= mod;
					f[l + i] = u - d;
					if (f[l + i] < 0) f[l + i] += mod;
				}
			}
		}
		for (auto& x : f) if (x < 0) x += mod;
	}
public:
	inline static vector<long long> convolution(vector<long long> g,vector<long long> h){
		int N; for(N=1;N<g.size()+h.size(); N*=2);
		vector<long long> f(N);
		g.resize(N); h.resize(N);
		ntt(g);	ntt(h);
		for(int i = 0; i < N; ++i) (f[i] = g[i]*h[i]) %= mod;
		ntt(f,-1);
		long long inv = inv_mod(N, mod);
		for (auto& x : f) x = x * inv % mod;
		return f;
	}
	inline static vector<long long> convolution_arbitrarymod(vector<long long> g, vector<long long> h){
		for (auto& a : g) a %= mod;
		for (auto& a : h) a %= mod;
		const int mod1=167772161;
		const int mod2=469762049;
		const int mod3=1224736769;
		auto x = NumberTheoreticTransform<mod1>::convolution(g, h);
		auto y = NumberTheoreticTransform<mod2>::convolution(g, h);
		auto z = NumberTheoreticTransform<mod3>::convolution(g, h);
		vector<long long> res(x.size()),b(3),m(3);
		for(int i=0; i < x.size(); ++i){
			m[0] = mod1, b[0] = x[i];
			m[1] = mod2, b[1] = y[i];
			m[2] = mod3, b[2] = z[i];
			res[i] = garner(b, m, mod);
		}
		return res;
	}
};

vector<vector<ll>> v;
vector<ll> rec(int l, int r) {
    if(r-l==1) return v[l];
    if(r-l==2) return NumberTheoreticTransform<MOD2>::convolution(v[l],v[l+1]);
    auto vl=rec(l,(l+r)/2);
    auto vr=rec((l+r)/2,r);
    return NumberTheoreticTransform<MOD2>::convolution(vl,vr);
}

int main() {
    SPEED
    int N,Q; cin >> N >> Q;
    vector<ll> A(N),B(Q);
    for(int i = 0; i < N; ++i) cin >> A[i],A[i] %= MOD2;
    for(int i = 0; i < Q; ++i) cin >> B[i];
    v.resize(N);
    for(int i = 0; i < N; ++i) v[i].push_back(A[i]-1),v[i].push_back(1);
    auto c = rec(0,N);
    for(int i = 0; i < Q; ++i) {
        cout << c[B[i]] << endl;
    }
    return 0;
}
