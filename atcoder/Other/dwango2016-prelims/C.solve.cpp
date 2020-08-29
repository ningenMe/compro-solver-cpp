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

constexpr long long MOD = (long long)1e9 + 7;
constexpr long long MOD2 = 998244353;
constexpr long long HIGHINF = (long long)1e18;
constexpr long long LOWINF = (long long)1e15;
constexpr long double PI = 3.1415926535897932384626433;

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
	vector<int> dp;
	void resize(const int N) {
		edge.resize(N);
		cost.resize(N);
		dp.resize(N);
	}
public:
	Dijkstra(int N,T inf):inf(inf),num_list(1,N),sum(1,1),N(N){
		resize(N);
	}
	Dijkstra(initializer_list<long long> size_list,T inf):num_list(size_list),inf(inf),N(1){
		for(long long& e:num_list) N *= e;
		sum.resize(num_list.size(),1);
		for(int i = 0; i < num_list.size(); ++i) {
			for(int j = i + 1; j < num_list.size(); ++j) {
				sum[i] *= num_list[j];
			}
		}
		resize(N);
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
		for(int i = 0; i < N; ++i) cost[i] = inf, dp[i] = -1;
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
					dp[to] = from;
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
	//vertex [start->node1->node2->...->idx]
	vector<int> restore(int idx) {
		vector<int> res = {idx};
		while(dp[idx] != -1) {
			idx = dp[idx];
			res.push_back(idx);
		}
		reverse(res.begin(),res.end());
		return res;
	}
    void print() {
        cout << "{" << get(0);
        for(int i = 1; i < N; ++i) cout <<  ", " << get(i);
        cout << "}" << endl;
    }
};

int main() {
    int N,M,s,g; cin >> N >> M >> s >> g;
    vector<vector<pair<int,ll>>> edge1(N),edge2(N);
    Dijkstra<ll> dijk(N,HIGHINF);
    while(M--) {
        int L; cin >> L;
        vector<int> x(L);
        vector<ll> w(L-1);
        for(int i=0;i<L;++i) cin >> x[i];
        for(int i=0;i<L-1;++i) cin >> w[i];
        int sum;
        {
            sum=0;
            for(int i=L-2;0<=i;--i) {
                sum += w[i];
                dijk.make_edge(x[i],x[i+1],w[i]);
                edge1[x[i]].push_back({x[i+1],w[i]});
                edge2[x[i]].push_back({x.back(),sum});
            }
        }
        {
            sum=0;
            for(int i=1;i<L;++i) {
                sum += w[i-1];
                dijk.make_edge(x[i],x[i-1],w[i-1]);
                edge1[x[i]].push_back({x[i-1],w[i-1]});
                edge2[x[i]].push_back({x.front(),sum});
            }
        }
    }
    dijk.solve(g);

    ll ok = HIGHINF,ng = 0,md;
    while(ok - ng > 1){
        md = (ok + ng) / 2;
        vector<ll> dp(N,LOWINF);
        PQR<pair<ll,int>> pq;
        pq.push({0,s});
        dp[s]=0;
        while(pq.size()) {
            auto p = pq.top(); pq.pop();
            ll cost = p.first;
            ll from = p.second;
            for(int i=0;i < edge1[from].size();++i) {                
                int to       = edge1[from][i].first;
                ll  w        = edge1[from][i].second;
                int worse_to = edge2[from][i].first;
                ll  worse_w  = edge2[from][i].second;
                ll next_cost  = cost + w;
                ll next_worst = cost + worse_w + dijk.get(worse_to);

                if(md >= next_worst && dp[to] > next_cost) {
                    dp[to] = next_cost;
                    pq.push({next_cost,to});
                }
            }
        }
        (dp[g]<LOWINF?ok:ng)=md;
    }
    ll ans=ok;
    cout << ans << endl;
    return 0;
}
