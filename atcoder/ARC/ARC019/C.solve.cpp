#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define ALL(obj) (obj).begin(),(obj).end()
#define SPEED cin.tie(0);ios::sync_with_stdio(false);

template<class T> using priority_queue_reverse = priority_queue<T,vector<T>,greater<T>>;

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

void f(int sy, int sx, vector<vector<vector<ll>>>& cost,const vector<vector<int>>& grid){
	int H = cost.size();
	int W = cost.front().size();
	int K = cost.front().front().size();
	cost[sy][sx][0]=0;
	priority_queue_reverse<pair<ll,int>> pq;
	pq.push({0,sy*W*K+sx*K+0});
	vector<int> dy={-1,1,0,0};
	vector<int> dx={0,0,-1,1};
	while (pq.size()){
		auto p=pq.top(); pq.pop();
		ll c=p.first;
		int k=p.second%K;
		int x=(p.second/K)%W;
		int y=(p.second/K)/W;
		if(cost[y][x][k]<c) continue;
		for(int i = 0; i < 4; ++i){
			int nx=x+dx[i];
			int ny=y+dy[i];
			if(!(0<=nx&&nx<W&&0<=ny&&ny<H)) continue;
			if(grid[ny][nx]==-1) continue;
			int nk = k+grid[ny][nx];
			if(nk >= K) continue;
			if(c+1<cost[ny][nx][nk]){
				cost[ny][nx][nk]=c+1;
				pq.push({c+1,ny*W*K+nx*K+nk});
			}
		}
	}		
}

int main() {
	int H,W,K; cin >> H >> W >> K;
	auto grid=multivector(H,W,0);
	int sy=-1,sx=-1,gy=-1,gx=-1,cy=-1,cx=-1;
	for(int i = 0; i < H; ++i) {
		string S; cin >> S;
		for(int j=0;j<W;++j) {
			int a=0;
			if(S[j]=='T') a=-1;
			if(S[j]=='E') a=1;
			if(S[j]=='S') sy=i,sx=j;
			if(S[j]=='C') cy=i,cx=j;
			if(S[j]=='G') gy=i,gx=j;
			grid[i][j]=a;
		}
	}
	ll inf = LOWINF;
	corner(sy<0||sx<0||gy<0||gx<0||cy<0||cx<0,-1);
	auto cost_s=multivector(H,W,K+3,inf);
	auto cost_c=multivector(H,W,K+3,inf);
	auto cost_g=multivector(H,W,K+3,inf);
	f(sy,sx,cost_s,grid);
	f(cy,cx,cost_c,grid);
	f(gy,gx,cost_g,grid);
	ll ans=inf;
	for(int i = 0; i < H; ++i) {
		for(int j=0;j<W;++j) {
			if(grid[i][j]==-1) continue;
			vector<ll> dp(K+3,inf);
			vector<ll> tp(K+3,inf);
			dp[0]=0;
			for(int k=0;k<=K+2;++k) tp[k]=inf;			
			for(int k=0;k<=K+2;++k) {
				for(int l=0;l+k<=K+2;++l) {
					chmin(tp[l+k],dp[k]+cost_s[i][j][l]);
				}
			}
			dp=tp;
			for(int k=0;k<=K+2;++k) tp[k]=inf;			
			for(int k=0;k<=K+2;++k) {
				for(int l=0;l+k<=K+2;++l) {
					chmin(tp[l+k],dp[k]+2*cost_c[i][j][l]);
				}
			}
			dp=tp;
			for(int k=0;k<=K+2;++k) tp[k]=inf;			
			for(int k=0;k<=K+2;++k) {
				for(int l=0;l+k<=K+2;++l) {
					chmin(tp[l+k],dp[k]+cost_g[i][j][l]);
				}
			}
			dp=tp;
			for(int k=0;k<=K+grid[i][j]*2;++k) chmin(ans,dp[k]); 			
		}
	}
	if(ans>=inf) ans=-1;
	cout << ans << endl;

    return 0;
}
