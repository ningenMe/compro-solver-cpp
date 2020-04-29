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



//Union Find Tree
class UnionFindTree {
public:
	vector<int> parent;
	vector<int> rank;

	UnionFindTree(int N) : parent(N), rank(N,0){
		for (int i = 0; i < N; ++i) parent[i] = i;
	}
 
	int root(int n) {
		return (parent[n] == n ? n : parent[n] = root(parent[n]));
	}

	int same(int n, int m) {
		return root(n) == root(m);
	}
 
	void unite(int n, int m) {
		n = root(n);
		m = root(m);
		if (n == m) return;
		if(rank[n]<rank[m]) {
			parent[n] = m;
		}
		else{
			parent[m] = n;
			if(rank[n] == rank[m]) rank[n]++;
		}
	}
};

//verify https://atcoder.jp/contests/abc097/tasks/arc097_b

int main() {
	SPEED
	int H,W; cin >> H >> W;
	vector<vector<int>> A(H,vector<int>(W));
	for(int i = 0; i < H; ++i) {
		for(int j = 0; j < W; ++j) {
			cin >> A[i][j];
		}
	}
	vector<int> dy = {-1,1,0,0};
	vector<int> dx = {0,0,-1,1};
	int cnt = 2;
	for(int i = 0; i < H; ++i) {
		for(int j = 0; j < W; ++j) {
			if(A[i][j]!=1) continue;
			queue<pair<int,int>> q;
			A[i][j] = cnt;
			q.push({i,j});
			while(q.size()){
				auto [s,t] = q.front();
				q.pop();
				for(int k = 0; k < 4; ++k){
					int y = s + dy[k];
					int x = t + dx[k];
					if(0 <= y && y < H && 0 <= x && x < W && A[y][x]==1) {
						A[y][x] = cnt;
						q.push({y,x});
					}
				}
			}
			cnt++;
		}
	}
	cout << cnt-2 << endl;


	return 0;
}
