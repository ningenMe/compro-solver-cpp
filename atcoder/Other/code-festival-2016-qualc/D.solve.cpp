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

int main() {
	int H,W; cin >> H >> W;
	vector<string> S(H+1);
	//1が一番下段
	for(int i = H; 1 <= i; --i) cin >> S[i];
	S[0]=string(W,'.');

	int inf=12345678;
	int ans=0;
	for(int x=0 ; x+1 < W; ++x) {
		//左i段右j段残ってる時のコスト
		auto cost=multivector(H+1,H+1,0);
		S[0][x]='.',S[0][x+1]='#';
		//H固定で前計算
		{
			for(int j=0;j<=H;j++){
				for(int k=1; j+k<=H; ++k) cost[H][H-j]+=(S[k][x]==S[j+k][x+1]);
			}
			for(int j=1;j<=H;j++){
				for(int k=1; j+k<=H; ++k) cost[H-j][H]+=(S[j+k][x]==S[k][x+1]);
			}
		}
		for(int i=1;i<H;++i) {
			for(int j=1;j<H;++j) {
				cost[H-i][H-j]=cost[H-(i-1)][H-(j-1)]-(S[i][x]==S[j][x+1]);
			}
		}
		auto dp=multivector(H+1,H+1,inf);
		dp[H][H]=0;
		for(int i=H;0<=i;--i) {
			for(int j=H;0<=j;--j) {
				if(i) chmin(dp[i-1][j],dp[i][j]+cost[i][j]);
				if(j) chmin(dp[i][j-1],dp[i][j]+cost[i][j]);
			}
		}
		ans+=dp[0][0];
	}
	cout << ans << endl;
    return 0;
}
