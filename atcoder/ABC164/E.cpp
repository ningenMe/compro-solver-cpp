#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define SPEED cin.tie(0);ios::sync_with_stdio(false);

//Dijkstra
template<class T> class Dijkstra {
	vector<long long> num_list;
	vector<long long> sum;
	int N;
	T inf;
	vector<vector<pair<T,int>>> edge;
	vector<T> cost;
public:
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
	SPEED
	ll N,M,S,K; cin >> N >> M >> S;
	K = 50*N;
	Dijkstra<ll> dijk({N,K+1},1LL<<50);

	vector<ll> U(M),V(M),A(M),B(M);
	for(int i = 0; i < M; ++i) {
		cin >> U[i] >> V[i] >> A[i] >> B[i];
		U[i]--;
		V[i]--;
		for(int j = 0; j <= K; ++j) {
			dijk.make_edge({U[i],j},{V[i],j-A[i]},B[i]);
			dijk.make_edge({V[i],j},{U[i],j-A[i]},B[i]);
		}
	}
	vector<ll> C(N),D(N);
	for(int i = 0; i < N; ++i) {
		cin >> C[i] >> D[i];
		for(int j = 0; j <= K; ++j) {
			dijk.make_edge({i,j},{i,min(K,j+C[i])},D[i]);
		}
	}
	dijk.solve({0,min(S,K)});
	for(int i = 1; i < N; ++i) {
		ll mini = 1LL<<50;
		for(int j = 0; j <= K; ++j) {
			mini=min(mini,dijk.get({i,j}));
		}
		cout << mini << endl;
	}
    return 0;
}
