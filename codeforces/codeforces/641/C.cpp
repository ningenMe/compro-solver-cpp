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
	SPEED
	int H,W,Q; cin >> H >> W >> Q;
	vector<string> S(H);
	for(int i = 0; i < H; ++i) {
		cin >> S[i];
	}
	auto A = multivector(H,W,-1);
	queue<pair<int,int>> q0;
	for(int i = 0; i < H; ++i) {
		for(int j = 0; j < W; ++j) {
			int flg = 0;
			if(i+1<H &&S[i+1][j]==S[i][j]) flg = 1;
			if(0<=i-1&&S[i-1][j]==S[i][j]) flg = 1;
			if(j+1<W &&S[i][j+1]==S[i][j]) flg = 1;
			if(0<=j-1&&S[i][j-1]==S[i][j]) flg = 1;
			if(flg) {
				A[i][j] = 0;
				q0.push({i,j});
			}
		}
	}
	while(q0.size()) {
		auto [i,j] = q0.front();
		q0.pop();
		if(i+1<H && S[i+1][j]!=S[i][j] && A[i+1][j]==-1) {
			A[i+1][j] = A[i][j]+1;
			q0.push({i+1,j});
		}
		if(0<=i-1&&S[i-1][j]!=S[i][j] && A[i-1][j]==-1) {
			A[i-1][j] = A[i][j]+1;
			q0.push({i-1,j});
		}
		if(j+1<W &&S[i][j+1]!=S[i][j] && A[i][j+1]==-1) {
			A[i][j+1] = A[i][j]+1;
			q0.push({i,j+1});
		}
		if(0<=j-1&&S[i][j-1]!=S[i][j] && A[i][j-1]==-1) {
			A[i][j-1] = A[i][j]+1;
			q0.push({i,j-1});
		}
	}
	while(Q--){
		int y,x; ll p; cin >> y >> x >> p;
		y--,x--;
		int ans = S[y][x]-'0';
		if(A[y][x]!=-1) {
			if(A[y][x] <= p) {
				int prt = (p-A[y][x])%2;
				ans ^= prt;
			}
		}
		cout << ans << endl;
	}
    return 0;
}
