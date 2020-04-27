#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;

#define REP(i,n) for(long long i = 0; i < (n); i++)
#define FOR(i, m, n) for(long long i = (m);i < (n); ++i)
#define ALL(obj) (obj).begin(),(obj).end()
#define SPEED cin.tie(0);ios::sync_with_stdio(false);

template<class T> using V = vector<T>;
template<class T, class U> using P = pair<T, U>;
template<class T> using PQ = priority_queue<T>;
template<class T> using PQR = priority_queue<T,vector<T>,greater<T>>;

constexpr ll MOD = (ll)1e9 + 7;
constexpr ll MOD2 = 998244353;
constexpr ll HIGHINF = (ll)1e18;
constexpr ll LOWINF = (ll)1e15;
constexpr long double PI = 3.1415926535897932384626433;

template<typename T> vector<T> make_v(size_t N,T init){return vector<T>(N,init);}
template<typename... T> auto make_v(size_t N,T... t){return vector<decltype(make_v(t...))>(N,make_v(t...));}
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
template <class T> void chmax(T& a, const T b){a=max<T>(a,b);}
template <class T> void chmin(T& a, const T b){a=min<T>(a,b);}
void YN(bool flg) {cout << ((flg) ? "YES" : "NO") << endl;}
void Yn(bool flg) {cout << ((flg) ? "Yes" : "No") << endl;}
void yn(bool flg) {cout << ((flg) ? "yes" : "no") << endl;}

template<class T> class RadixHeap{
	using TypeNode = pair<unsigned long long, T>;
	array<vector<TypeNode>,65> vq;
	unsigned long long size_num;
	TypeNode last;
	inline int bit(unsigned long long a) {
		return a ? 64 - __builtin_clzll(a) : 0;
	}
public:
	RadixHeap(T mini) : size_num(0), last(make_pair(0,mini)) {
		// do nothing
	}
	inline bool empty() {
		return size_num == 0;
	}
	inline size_t size(){
		return size_num;
	}
	inline void push(TypeNode x){
		++size_num;
		vq[bit(x.first^last.first)].push_back(x);
	}
	inline void emplace(unsigned long long key,T val){
		++size_num;
		vq[bit(key^last.first)].emplace_back(key,val);
	}
	inline TypeNode pop() {
		if(vq[0].empty()) {
			int i = 1;
			while(vq[i].empty()) ++i;
			last = *min_element(vq[i].begin(),vq[i].end());
			for(auto &p : vq[i]) vq[bit(p.first ^ last.first)].push_back(p);
			vq[i].clear();
		}
		--size_num;
		auto res = vq[0].back();
		vq[0].pop_back();
		return res;
	}
};

//Dijkstra
template<class T> class Dijkstra {
public:
	int N;
	T inf;
	vector<T> cost; 
	vector<vector<pair<T, int>>> edge;

	Dijkstra(const int N, T inf) : N(N), inf(inf),cost(N), edge(N) {
	}

	void make_edge(int from, int to, T w) {
		edge[from].push_back({ w,to });
	}

	void solve(int start) {
		for(int i = 0; i < N; ++i) cost[i] = inf;

		// priority_queue<pair<T, int>, vector<pair<T, int>>, greater<pair<T, int>>> pq;
		RadixHeap<int> pq(0);
		cost[start] = 0;
		pq.push({ 0,start });

		while (!pq.empty()) {
			auto p = pq.pop();
			if(cost[p.second]<p.first) continue;
			T v = p.first;
			int from = p.second;
			for (auto u : edge[from]) {
				T w = v + u.first;
				int to = u.second;
				if (w < cost[to]) {
					cost[to] = w;
					pq.push({ w,to });
				}
			}
		}
		return;
	}
};

int main() {
	ll N,M,P,Q,T;
	cin >> N >> M >> P >> Q >> T;
	P--,Q--;
	Dijkstra<ll> dijk(N,1<<30);
	for(int i = 0; i < M; ++i){
		int a,b,c; cin >> a >> b >> c;
		a--,b--;
		dijk.make_edge(a,b,c);
		dijk.make_edge(b,a,c);
	}

	auto cost = make_v(N,N,0LL);
	for(int i = 0; i < N; ++i){
		if(i==0||i==P||i==Q){
			dijk.solve(i);
			cost[i] = dijk.cost;
		}
	}
	corner(cost[0][P]+cost[P][Q]+cost[Q][0]<=T,T);
	ll ans = -1;
	for(int i = 0; i < N; ++i){
		for(int j = 0; j < N; ++j){
			ll sum = 0;
			sum += cost[0][i];
			sum += max(cost[P][i]+cost[P][j],cost[Q][i]+cost[Q][j]);
			sum += cost[0][j];
			if(sum<=T) chmax(ans,T - max(cost[P][i]+cost[P][j],cost[Q][i]+cost[Q][j]));
		}		
	}
	cout << ans << endl;
    return 0;
}
