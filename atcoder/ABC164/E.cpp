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
	ll N,M,S; cin >> N >> M >> S;
	vector<vector<int>> edge(N);
	vector<ll> U(M),V(M),A(M),B(M);
	for(int i = 0; i < M; ++i) {
		cin >> U[i] >> V[i] >> A[i] >> B[i];
		U[i]--;
		V[i]--;
		edge[U[i]].push_back(i);
		edge[V[i]].push_back(i);
	}
	vector<ll> C(N),D(N);
	for(int i = 0; i < N; ++i) {
		cin >> C[i] >> D[i];
	}
	auto dp = multivector(N,50*N+1,LOWINF);
	dp[0][min(S,50*N)]=0;
	PQR<pair<ll,pair<int,ll>>> pq;
	pq.push({0,{0,min(S,50*N)}});
	while(pq.size()) {
		auto p = pq.top();
		int from = p.second.first;
		ll silv = p.second.second;
		ll cost = p.first;
		pq.pop();
		if(dp[from][silv]<cost) continue;
		for(int idx:edge[from]){
			int to;
			to = U[idx];
			if(silv >= A[idx] && dp[to][silv-A[idx]] > dp[from][silv] + B[idx]){
				dp[to][silv-A[idx]] = dp[from][silv] + B[idx];
				pq.push({dp[to][silv-A[idx]],{to,silv-A[idx]}});
			}
			to = V[idx];
			if(silv >= A[idx] && dp[to][silv-A[idx]] > dp[from][silv] + B[idx]){
				dp[to][silv-A[idx]] = dp[from][silv] + B[idx];
				pq.push({dp[to][silv-A[idx]],{to,silv-A[idx]}});
			}
		}
		{
			int to = from;
			if(dp[to][min(silv+C[to],50*N)] > dp[from][silv] + D[from]){
				dp[to][min(silv+C[to],50*N)] = dp[from][silv] + D[from];
				pq.push({dp[to][min(silv+C[to],50*N)],{to,min(silv+C[to],50*N)}});
			}
		}		
	}
	for(int i = 1; i < N; ++i) {
		cout << *min_element(ALL(dp[i])) << endl;
	}
    return 0;
}
