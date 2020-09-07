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

/*
 * @title RangeIndex
 */
class RangeIndex{
	int length;
public:
	RangeIndex(const int N) {
		for (length = 1; length <= N; length *= 2);
	}
	//[l,r)
	vector<int> range(int l,int r) {
		vector<int> res;
		for(l += length, r += length; l < r; l >>=1, r >>=1) {
			if(l&1) res.push_back(l++);
			if(r&1) res.push_back(--r);
		}
		return res;
	}
	// ranges that include x
	vector<int> include_range(int x) {
		vector<int> res;
        for(int i=x+length; i; i >>= 1) res.push_back(i);
		return res;
	}
	inline int operator[](int idx) {
		return idx+length;
	}
	inline size_t size(void){
		return 2*length;
	}
};


/*
 * @title Dijkstra
 * @docs md/graph/Dijkstra.md
 */
template<class T> class Dijkstra {
	vector<long long> num_list;
	vector<long long> sum;
	int N;
	T inf;
	vector<vector<pair<T,int>>> edge;
	vector<T> cost;
public:
	Dijkstra(int N,T inf):inf(inf),num_list(1,N),sum(1,1),N(N){
		edge.resize(N);
		cost.resize(N);
	}
	Dijkstra(initializer_list<long long> size_list,T inf):num_list(size_list),inf(inf),N(1){
		for(long long& e:num_list) N *= e;
		sum.resize(num_list.size(),1);
		for(int i = 0; i < num_list.size(); ++i) {
			for(int j = i + 1; j < num_list.size(); ++j) {
				sum[i] *= num_list[j];
			}
		}
		edge.resize(N);
		cost.resize(N);
	}
	void make_edge(int from, int to, T w) {
		if(from < 0 || N <= from || to < 0 || N <= to) return;
		edge[from].push_back({ w,to });
	}
	void make_edge(initializer_list<long long> from_list, initializer_list<long long> to_list, T w) {
		int from = 0, to = 0;
		auto from_itr = from_list.begin(),to_itr = to_list.begin();
		for(int i = 0; i < num_list.size(); ++i) {
			if(*from_itr < 0 || num_list[i] <= *from_itr || *to_itr < 0 || num_list[i] <= *to_itr) return;
			from += (*from_itr)*sum[i];
			to   += (*to_itr)*sum[i];
			from_itr++;
			to_itr++;
		}
		edge[from].push_back({ w,to });
	}
	void solve(initializer_list<long long> start_list) {
		int start = 0;
		auto start_itr = start_list.begin();
		for(int i = 0; i < num_list.size(); ++i) {
			start += (*start_itr)*sum[i];
			start_itr++;
		}
		solve(start);
	}
	void solve(int start) {
		for(int i = 0; i < N; ++i) cost[i] = inf;
		priority_queue<pair<T, int>, vector<pair<T, int>>, greater<pair<T, int>>> pq;
		cost[start] = 0;
		pq.push({ 0,start });
		while (!pq.empty()) {
			auto [v,from] = pq.top();
			pq.pop();
			if(cost[from] < v) continue;
			for (auto [u,to] : edge[from]) {
				T w = v + u;
				if (w < cost[to]) {
					cost[to] = w;
					pq.push({ w,to });
				}
			}
		}
		return;
	}
	T get(int idx){
		return cost[idx];
	}
	T get(initializer_list<long long> idx_list){
		int idx = 0;
		auto idx_itr = idx_list.begin();
		for(int i = 0; i < num_list.size(); ++i) {
			idx += (*idx_itr)*sum[i];
			idx_itr++;
		}
		return get(idx);
	}
};

int main() {
    cin.tie(0);ios::sync_with_stdio(false);
	int N,M; cin >> N >> M;
	RangeIndex ri(N+M);
	int offset = ri.size();
	Dijkstra<ll> dijk(2*offset+M,LOWINF);
	for(int i=0;i<M;++i){
		int l,r,c; cin >> l >> r >> c;
		l--;
		auto range=ri.range(l,r);
		for(auto& e1:range) {
			dijk.make_edge(e1+offset,2*offset+i,c);
		}
		for(auto& e1:range) {
			dijk.make_edge(2*offset+i,e1,0);
		}
	}
	for(int i=0;i<N;++i){
		auto incl = ri.include_range(i);
		for(auto& e:incl) dijk.make_edge(e,ri[i],0);
		for(auto& e:incl) dijk.make_edge(ri[i]+offset,e+offset,0);
		dijk.make_edge(ri[i],ri[i]+offset,0);
	}
	dijk.solve(ri[0]);
	ll ans = dijk.get(ri[N-1]);
	if(ans == LOWINF) ans = -1;
	cout << ans << endl;
    return 0;
}
