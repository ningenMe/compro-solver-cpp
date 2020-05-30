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

//Dijkstra
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
 
/*
 * @title Distance
 */
template<class T> class Distance{
public:
    //Euclidean distance
    inline static constexpr T euclid(const T& x1, const T& y1, const T& x2, const T& y2) {
        return sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
    }
    //Chebyshev distance
    inline static constexpr T chebyshev(T x1, T y1, T x2, T y2) {
        return max(abs(x1 - x2),abs(y1 - y2));
    }
    //Manhattan distance
    inline static constexpr T manhattan(T x1, T y1, T x2, T y2) {
        return abs(x1 - x2)+abs(y1 - y2);
    }
    inline static constexpr T between_point_and_line(const T& x,const T& y,const T& x1,const T& y1,const T& x2,const T& y2){
        return abs((y2 - y1)*x+(x1 - x2)*y-(y2-y1)*x1+(x2-x1)*y1)/sqrt((y2 - y1)*(y2 - y1)+(x1 - x2)*(x1 - x2));
    }
};

int main() {
    int N,M; cin >> N >> M;
    Dijkstra<double> dij(N,LOWINF);
    int s,t; cin >> s >> t; s--,t--;
    vector<double> p(N),q(N); 
    for(int i = 0; i < N; ++i) {
        cin >> p[i] >> q[i];
    }
    for(int i = 0; i < M; ++i) {
        int u,v; cin >> u >> v;
        u--,v--;
        double cost = Distance<double>::euclid(p[u],q[u],p[v],q[v]);
        dij.make_edge(u,v,cost);
        dij.make_edge(v,u,cost);
    }
    dij.solve(s);
    printf("%.10f",dij.get(t));    

    return 0;
}
