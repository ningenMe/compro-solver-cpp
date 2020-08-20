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
	ll D,L,Q,N=100000; cin >> D >> L >> Q;
	vector<vector<ll>> vst(N+1);
	vector<vector<ll>> acc(N+1);

	for(int i = 1; i <= D; ++i) {
		int c; cin >> c;
		vst[c].push_back(i);
		vst[c].push_back(i+D);
		acc[c].push_back(1);
		acc[c].push_back(1);
	}

	for(int i = 1; i <= N; ++i) {
		if(vst[i].empty()) continue;
		sort(ALL(vst[i]));

		for(int j = 1; j < vst[i].size(); ++j) {
			acc[i][j] += ((vst[i][j]-vst[i][j-1])-1) / L;
		}

		for(int j = 1; j < vst[i].size(); ++j) {
			acc[i][j] += acc[i][j-1];
		}
	}

	while(Q--) {
		ll K,F,T; cin >> K >> F >> T;
		ll M = vst[K].size() / 2;
		ll ans = 0;
		do{
			if(vst[K].empty()) break;
			ll j = lower_bound(ALL(vst[K]),F)-vst[K].begin(); 
			//初手変なところの時
			if(vst[K][j] > F) {
				T--;
				T -= (vst[K][j]-F-1) / L;
			}
			if(T<=0) break;

			T--;
			ans++;
			
			ll one_loop_num = acc[K][M]-acc[K][0];
			ans += (T/one_loop_num) * M;
			T %= one_loop_num;
			if(T<=0) break;

			ll ok = 0, ng = M, md;
			while(ng-ok>1) {
				md=(ok+ng)/2;
				ll diff = acc[K][j+md] - acc[K][j];
				(diff<=T?ok:ng)=md;
			}
			ans += ok;

		} while (false);	
		cout << ans << endl;	
	}
    return 0;
}
