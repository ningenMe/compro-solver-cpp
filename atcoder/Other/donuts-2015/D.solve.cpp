#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define ALL(obj) (obj).begin(),(obj).end()
template<class T> using priority_queue_reverse = priority_queue<T,vector<T>,greater<T>>;

constexpr long long MOD = 1'000'000'000LL + 7;
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
vector<string> split(const string &str, const char delemiter) {vector<string> res;stringstream ss(str);string buffer; while( getline(ss, buffer, delemiter) ) res.push_back(buffer); return res;}
int msb(int x) {return x?31-__builtin_clz(x):-1;}
void YN(bool flg) {cout << (flg ? "YES" : "NO") << endl;}
void Yn(bool flg) {cout << (flg ? "Yes" : "No") << endl;}
void yn(bool flg) {cout << (flg ? "yes" : "no") << endl;}

int main() {
    cin.tie(0);ios::sync_with_stdio(false);
	int N,K; cin >> N >> K;
	vector<ll> C(N+1);
	multiset<ll> c,l,r;
	c.insert(-LOWINF);
	for(int i = 1; i <= N; ++i) {
		cin >> C[i];
		c.insert(C[i]);
	}
	ll sum = 0;
	auto itr = c.begin();
	while(1) {
		ll d;
		{
			ll x = *itr;
			itr++;
			if(itr == c.end()) break;
			ll y = *itr;
			d = y - x;
		}
		if(r.size() < K) {
			r.insert(d);
		}
		else if(*r.begin() < d) {
			ll x = *r.begin();
			l.insert(x);
			sum += x;
			r.erase(r.find(x));
			r.insert(d);
		}
		else {
			l.insert(d);
			sum += d;
		}
	}
	cout << sum << endl;
	int Q; cin >> Q;
	while (Q--) {
		int i; cin >> i;
		auto itr = c.lower_bound(C[i]);
		auto nxt=itr;
		auto prv=itr;
		nxt++;
		prv--;
		if(nxt != c.end()) {
			ll d = *nxt - *itr;
			if(r.find(d)!=r.end()) {
				r.erase(r.find(d));
			}
			else {
				l.erase(l.find(d));
				sum -= d;				
			}
		}
		{
			ll d = *itr - *prv;
			if(r.find(d)!=r.end()) {
				r.erase(r.find(d));
			}
			else {
				l.erase(l.find(d));
				sum -= d;				
			}
		}
		if(nxt != c.end()) {
			r.insert(*nxt - *prv);
		}
		c.erase(itr);
		while(r.size() > K) {
			l.insert(*r.begin());
			sum += *r.begin();
			r.erase(r.begin());
		}
		while(r.size()<K) {
			r.insert(*l.rbegin());
			sum -= *l.rbegin();
			l.erase(l.find(*l.rbegin()));
		}
		cout << sum << endl;
	}
    return 0;
}
