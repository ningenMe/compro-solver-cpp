#include <bits/stdc++.h>
using namespace std;
using ll = __int128_t;

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

int main() {
	long long L_;cin >> L_;
	ll L=L_; 
	ll x,y,z;
	{
		ll ok=0,ng=LOWINF,md;
		while (ng-ok>1) {
			md=(ok+ng)/2;
			ll b=md;
			ll c=2*b-2;
			(b>=c ? ok:ng)=md;
		}
		x=ok;
	}
	{
		ll ok=x,ng=LOWINF,md;
		while (ng-ok>1) {
			md=(ok+ng)/2;
			ll b=md;
			ll c=2*b-2;
			(b<c && L-(2*b-1)>=2*b-2 ? ok:ng)=md;
		}
		y=ok;
	}
	{
		ll ok=y,ng=LOWINF,md;
		while (ng-ok>1) {
			md=(ok+ng)/2;
			ll b=md;
			ll c=L-(2*b-1);
			(b<c && L-(2*b-1)<2*b-2 ? ok:ng)=md;
		}
		z=ok;
	}
	ll cnt1=0;
	cnt1+=(y*(y+1)/2-2*y) - (x*(x+1)/2-2*x);
	cnt1+=((L+1)*z-3*z*(z+1)/2) - ((L+1)*y-3*y*(y+1)/2);

	ll s,t,u;
	{
		ll ok=0,ng=LOWINF,md;
		while (ng-ok>1) {
			md=(ok+ng)/2;
			ll b=md;
			(L-(2*b+1)>=b-1 ? ok:ng)=md;
		}
		t=ok;
	}
	{
		ll ok=0,ng=t,md;
		while (ng-ok>1) {
			md=(ok+ng)/2;
			ll b=md;
			ll a=b-1;
			(a<2 ? ok:ng)=md;
		}
		s=ok;
	}
	{
		ll ok=t,ng=LOWINF,md;
		while (ng-ok>1) {
			md=(ok+ng)/2;
			ll b=md;
			ll a=L-(2*b+1);
			(1<a ? ok:ng)=md;
		}
		u=ok;
	}
	ll cnt2=0;
	cnt2+=(t*(t+1)/2-2*t) - (s*(s+1)/2-2*s);
	cnt2+=((L-1)*z-z*(z+1)) - ((L-1)*y-y*(y+1));

	ll v,w;
	v=2;
	{
		ll ok=v,ng=LOWINF,md;
		while (ng-ok>1) {
			md=(ok+ng)/2;
			ll b=md;
			(3*b<=L ? ok:ng)=md;
		}
		w=ok;
	}
	ll cnt3=w-v;
	long long ans=(cnt1+cnt2-cnt3) % MOD;
	ans += MOD;
	ans %= MOD;
	cout << ans << endl;
	return 0;
}
