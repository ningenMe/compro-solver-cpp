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

template<long long mod> class Garner{
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
public:
	// O(N^2) x mod m_i = b_i なる x を返却　, b_iがすべて0のときは0ではなくm_iのlcmを返す
    // return x
	inline static long long garner(vector<long long> b, vector<long long> m){
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
			for(auto& e:m) (lcm*=e)%=mod;
			return lcm;
		}
		m.push_back(mod);
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
};



int main() {
	int N; cin >> N;
	vector<ll> b(N), m(N);
	int flg = 1;
	for(int i = 0; i < N; ++i){
		cin >> b[i] >> m[i];
	}
	cout << Garner<MOD>::garner(b,m) << endl;
	
	return 0;
}