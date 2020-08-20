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
	int H,W; cin >> H >> W;
	vector<string> grid(H);
	int sy,sx,gy,gx;
	for(int i = 0; i < H; ++i) {
		cin >> grid[i];
		for(int j=0;j<W;++j) {
			if(grid[i][j]=='S') sy=i,sx=j;
			if(grid[i][j]=='G') gy=i,gx=j;
		}
	}
	auto dp = multivector(H*W,10,LOWINF);
	priority_queue_reverse<pair<pair<ll,int>,int>> pq;
	pq.push({{0,0},sy*W+sx});
	dp[sy*W+sx][0]=0;
	int dy[4] = {-1,1,0,0};
	int dx[4] = {0,0,-1,1};
	while(pq.size()) {
		auto p = pq.top(); pq.pop();
		int y=p.second / W, x = p.second % W;
		int maxi = -p.first.second;
		for(int i=0;i<4;++i) {
			int u=y+dy[i],v=x+dx[i];
			if(!(0<=u&&u<H&&0<=v&&v<W)) continue;
			int w;
			if(grid[u][v]=='S'||grid[u][v]=='G') {
				w = maxi;
			}
			else if((grid[u][v]-'0') == maxi + 1) {
				w = maxi + 1;
			}
			else {
				w = maxi;
			}
			if(dp[u*W+v][w] > dp[y*W+x][maxi]+1) {
				dp[u*W+v][w] = dp[y*W+x][maxi]+1;
				pq.push({{dp[u*W+v][w],-w},u*W+v});
			}
		}
	}
	ll ans = dp[gy*W+gx][9];
	if(ans == LOWINF) ans = -1;
	cout << ans << endl;
    return 0;
}
