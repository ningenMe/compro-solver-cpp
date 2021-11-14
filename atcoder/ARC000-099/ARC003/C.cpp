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

int main() {
	int N,M; cin >> N >> M;
	vector<string> S(N);
	for(int i = 0; i < N; ++i) cin >> S[i];
	int sy,sx,gy,gx;
	for(int i = 0; i < N; ++i){
		for(int j = 0; j < M; ++j){
			if(S[i][j]=='s') sy=i,sx=j;
			if(S[i][j]=='g') gy=i,gx=j;
		}
	}
	long double ok = 0,ng = LOWINF,md;
	auto dp = multivector(N,M,0);
	vector<long double> X(N*M);
	X[0] = 1;
	for(int i = 1; i < N*M; ++i) X[i] = X[i-1]*0.99L; 
	int flg2 = 0;
	long double eps = 1e-11;
	for(int n = 0; n < 300; ++n) {
		md = (ok+ng)/2;
		for(int i = 0; i < N; ++i) for(int j = 0; j < M; ++j) dp[i][j] = N*M+10;
		queue<pair<int,int>> q;
		q.push({sy,sx});
		dp[sy][sx] = 0;
		int flg = 0;
		while (q.size()){
			int y = q.front().first;
			int x = q.front().second;
			q.pop();
			ll cnt = dp[y][x];
			if(y+1<N && S[y+1][x]=='g'){
				flg = 1;
				break;
			}
			if(0<y && S[y-1][x]=='g'){
				flg = 1;
				break;
			}
			if(x+1<M && S[y][x+1]=='g'){
				flg = 1;
				break;
			}
			if(0<x && S[y][x-1]=='g'){
				flg = 1;
				break;
			}
			if(y+1<N && S[y+1][x]!='#' && dp[y+1][x]>cnt+1){
				ll z = S[y+1][x]-'0';
				long double w = z*X[cnt+1];
				if(w+eps>=md){
					dp[y+1][x] = cnt+1;
					q.push({y+1,x});
				}
			}
			if(0<y && S[y-1][x]!='#' && dp[y-1][x]>cnt+1){
				ll z = S[y-1][x]-'0';
				long double w = z*X[cnt+1];
				if(w+eps>=md){
					dp[y-1][x] = cnt+1;
					q.push({y-1,x});
				}
			}
			if(x+1<M && S[y][x+1]!='#' && dp[y][x+1]>cnt+1){
				ll z = S[y][x+1]-'0';
				long double w = z*X[cnt+1];
				if(w+eps>=md){
					dp[y][x+1] = cnt+1;
					q.push({y,x+1});
				}
			}
			if(0<x && S[y][x-1]!='#' && dp[y][x-1]>cnt+1){
				ll z = S[y][x-1]-'0';
				long double w = z*X[cnt+1];
				if(w+eps>=md){
					dp[y][x-1] = cnt+1;
					q.push({y,x-1});
				}
			}
		}
		flg2 += flg;
		(flg?ok:ng)=md;		
	}
	corner(!flg2,-1);
	printf("%.15Lf",ok);

    return 0;
}
