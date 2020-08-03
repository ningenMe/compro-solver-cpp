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
void print(void) {cout << endl;}
template <class Head> void print(Head&& head) {cout << head;print();}
template <class Head, class... Tail> void print(Head&& head, Tail&&... tail) {cout << head << " ";print(forward<Tail>(tail)...);}
template <class T> void chmax(T& a, const T b){a=max(a,b);}
template <class T> void chmin(T& a, const T b){a=min(a,b);}
std::vector<std::string> split(const std::string &str, const char delemiter) {std::vector<std::string> res;std::stringstream ss(str);std::string buffer; while( std::getline(ss, buffer, delemiter) ) res.push_back(buffer); return res;}
int msb(int x) {return x?31-__builtin_clz(x):-1;}
void YN(bool flg) {cout << (flg ? "YES" : "NO") << endl;}
void Yn(bool flg) {cout << (flg ? "Yes" : "No") << endl;}
void yn(bool flg) {cout << (flg ? "yes" : "no") << endl;}

/*
 * @title Gcd
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

//Matrix_Repeated_Multiplication_Mod O((N^3)(logK))
vector<vector<long long>> Matrix_Repeated_Multiplication_Mod(vector<vector<long long>> mat, long long K, long long mod) {
    int N = mat.size();
    vector<vector<long long>> res(N, vector<long long>(N)), tmp(N, vector<long long>(N));
 
    for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) res[i][j] = (i == j);
    for (; K > 0; K /= 2) {
        if (K & 1) {
            for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) tmp[i][j] = 0;
            for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) for (int k = 0; k < N; ++k) (tmp[i][j] += (mat[i][k] * res[k][j]) % mod) %= mod;
            res = tmp;
        }
        for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) tmp[i][j] = 0;
        for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) for (int k = 0; k < N; ++k) (tmp[i][j] += (mat[i][k] * mat[k][j]) % mod) %= mod;
        mat = tmp;
    }
    return res;
}

//Pow_Mod O(log(n))
long long PowMod(long long x, long long n, long long mod) {
    long long res = 1;
    for (; n > 0; n >>= 1, (x *= x) %= mod) if (n & 1) (res *= x) %= mod;
    return res;
}

//Inv_Mod O(log(mod))
long long InvMod(long long x, long long mod){
	return PowMod(x,mod-2,mod); 
}

int main() {
    ll A,B,M; cin >> A >> B >> M;
    ll G = Gcd::gcd(A,B);
    auto mat1=multivector(3,3,0LL);
    mat1[0]={1,10,0};
    mat1[1]={0,10,0};
    mat1[2]={0,1 ,0};
    auto ma=Matrix_Repeated_Multiplication_Mod(mat1,A-1,M);
    ll a=(ma[0][0]+ma[0][1])%M;
    auto mat2=multivector(3,3,0LL);
    mat2[0]={1,PowMod(10,G,M),0};
    mat2[1]={0,PowMod(10,G,M),0};
    mat2[2]={0,1             ,0};
    auto mb=Matrix_Repeated_Multiplication_Mod(mat2,(B/G)-1,M);
    ll b=(mb[0][0]+mb[0][1])%M;
    ll ans=(a*b)%M;
    cout << ans << endl;
    return 0;
}
