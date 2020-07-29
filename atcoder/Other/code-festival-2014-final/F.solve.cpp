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

int f(const string& T){
	int N = T.size();
	int cnt = N;
	string S=".."+T;
	//dp[0]:1手目が何もしない、dp[1]:1手目が周り浄化
	auto dp=multivector(2,N+3,N);
	dp[0][0]=dp[0][1]=dp[1][0]=dp[1][1]=0;
	dp[0][2]=(S[2]=='0'?0:N);dp[1][2]=dp[1][3]=1;
	for(int i = 3; i < N+2; ++i) {
		for(int j=0;j<2;++j){
			if(S[i]=='0'){
				//何もしないとき
				chmin(dp[j][i],dp[j][i-1]);
				//周り浄化
				chmin(dp[j][i],dp[j][i-2]+1);
				//周り浄化
				chmin(dp[j][i+1],dp[j][i-2]+1);
			}
			else{
				//周り浄化
				chmin(dp[j][i],dp[j][i-2]+1);
				//周り浄化
				chmin(dp[j][i+1],dp[j][i-2]+1);
			}
		}
	}
	chmin(cnt,dp[0][N+1]);
	chmin(cnt,dp[1][N]);
	return cnt;
}

int main() {
	int N; cin >> N;
	vector<ll> A(N),B(N),C(N);
	for(int i = 0; i < N; ++i) cin >> B[i];
	corner(N==1,0);
	for(int i = 0; i < N; ++i) A[i]=Gcd::lcm(B[i],B[(i-1+N)%N]);
	for(int i = 0; i < N; ++i) C[i]=Gcd::gcd(A[i],A[(i+1)%N]);
	string T="";
	for(int i = 0; i < N; ++i) T+=(B[i]==C[i]?"0":"1");
	int ans = N;
	chmin(ans,f(T));
	T=T.substr(1,T.size())+T.front();
	chmin(ans,f(T));
	cout << ans << endl;
    return 0;
}
