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

template<class T> vector<T> MaximumSubarray(const vector<T>& vec, T unit=0) {
	assert(!vec.empty());
	vector<T> dp(vec.size());
	dp[0] = max(vec[0],unit);
	for(int i = 1; i < vec.size(); ++i) dp[i] = max(dp[i-1]+vec[i],unit);
	return dp;
}

template<class T> class Accumulate2D {
	vector<vector<T>> acc;
public:
	//arg grid is 0-indexed 
	Accumulate2D(const vector<vector<T>>& grid)
	: acc(grid.size()+1,vector<T>(grid.front().size()+1)){
		for(int i = 1; i < acc.size(); ++i) {
			for(int j = 1; j < acc[i].size(); ++j) {
				acc[i][j]+=grid[i-1][j-1]+acc[i][j-1]+acc[i-1][j]-acc[i-1][j-1];
			}
		}
	}
	// 左上[y1,x1] 右下[y2,x2] 0-indexed
	inline T get(int y1,int x1,int y2,int x2) {
		y2++,x2++;
		return acc[y2][x2]-acc[y2][x1]-acc[y1][x2]+acc[y1][x1];
	}
};

int main() {
	int H,W; cin >> H >> W;
	auto grid=multivector(H,W,0LL);
	int cnt = 0;
	PQR<ll> pq;
	for(int i = 0; i < H; ++i) {
		for(int j = 0; j < W; ++j) {
			cin >> grid[i][j];
			cnt+=(grid[i][j]>=0);
			pq.push(grid[i][j]);
			while(pq.size()>2) pq.pop();
		}
	}
	ll ans = 0;
	ans += pq.top(); pq.pop();		
	ans += pq.top(); pq.pop();		
	corner(cnt<=2,ans);
	Accumulate2D<ll> acc(grid);

	//[0,i]
	vector<ll> umaxi(H,0);
	//[i,H-1]
	vector<ll> dmaxi(H,0);
	//[0,j]
	vector<ll> lmaxi(W,0);
	//[j,W-1]
	vector<ll> rmaxi(W,0);

	//[y1,y2]
	for(int y1=0; y1 < H; ++y1) {
		for(int y2=y1; y2 < H; ++y2) {
			vector<ll> a(W,0);
			for(int j = 0; j < W; ++j) a[j]=acc.get(y1,j,y2,j);
			auto b = MaximumSubarray(a);
			ll maxi = *max_element(ALL(b));
			chmax(umaxi[y2],maxi);
			chmax(dmaxi[y1],maxi);
		}
	}
	//[x1,x2]
	for(int x1=0; x1 < W; ++x1) {
		for(int x2=x1; x2 < W; ++x2) {
			vector<ll> a(H,0);
			for(int i = 0; i < H; ++i) a[i]=acc.get(i,x1,i,x2);
			auto b = MaximumSubarray(a);
			ll maxi = *max_element(ALL(b));
			chmax(lmaxi[x2],maxi);
			chmax(rmaxi[x1],maxi);
		}
	}
	for(int i = 1; i < H; ++i) {
		chmax(umaxi[i],umaxi[i-1]);
	}
	for(int i = H-2; 0 <= i; --i) {
		chmax(dmaxi[i],dmaxi[i+1]);
	}
	for(int j = 1; j < W; ++j) {
		chmax(lmaxi[j],lmaxi[j-1]);
	}
	for(int j = W-2; 0 <= j; --j) {
		chmax(rmaxi[j],rmaxi[j+1]);
	}
	for(int i = 0; i+1 < H; ++i) chmax(ans,umaxi[i]+dmaxi[i+1]);
	for(int j = 0; j+1 < W; ++j) chmax(ans,lmaxi[j]+rmaxi[j+1]);
	cout << ans << endl;
	return 0;
}
