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

#include <bits/stdc++.h>
using namespace std;

template <class T> class Dinic {
	struct info {
		int to, rev;
		T cap;
	};
	T ini, inf;
	vector<vector<info>> edge;
	vector<int> level, iter;

	void bfs(int start) {
		for (int i = 0; i < level.size(); ++i) level[i] = -1;
		queue<int> q;
		level[start] = 0;
		q.push(start);
		while (q.size()) {
			int from = q.front();
			q.pop();
			for (auto& e : edge[from]) {
				if (e.cap > 0 && level[e.to] < 0) {
					level[e.to] = level[from] + 1;
					q.push(e.to);
				}
			}
		}
	}

	T dfs(int from, int goal, T flow) {
		if (from == goal) return flow;
		for (int& i = iter[from]; i < edge[from].size(); ++i) {
			auto& e = edge[from][i];
			if (e.cap <= 0 || level[from] >= level[e.to]) continue;
			T dflow = dfs(e.to, goal, min(flow, e.cap));
			if (dflow <= 0) continue;
			e.cap -= dflow;
			edge[e.to][e.rev].cap += dflow;
			return dflow;
		}
		return ini;
	}

public:

	Dinic(int N, T ini, T inf) : edge(N), level(N), iter(N), ini(ini), inf(inf) {
		// do nothing
	}

	void makeEdge(int from, int to, T cap) {
		edge[from].push_back({ to, (int)edge[to].size(), cap });
		edge[to].push_back({ from, (int)edge[from].size() - 1, ini });
	}

	T maxFlow(int start, int goal) {
		T maxflow = ini;
		while (1) {
			bfs(start);
			if (level[goal] < 0) return maxflow;
			for (int i = 0; i < iter.size(); ++i) iter[i] = 0;
			T flow;
			while ((flow = dfs(start, goal, inf))>0) maxflow += flow;
		}
	}
};

//verify https://atcoder.jp/contests/arc085/tasks/arc085_c

int main() {
    int N; cin >> N;
    vector<int> xa(N),ya(N),xb(N),yb(N);
    for(int i = 0; i < N; ++i){
        cin >> xa[i] >> ya[i];
    }
    for(int i = 0; i < N; ++i){
        cin >> xb[i] >> yb[i];
    }
    Dinic<int> d(2*N+2,0,1234567);
    for(int i = 0; i < N; ++i){
        d.makeEdge(2*N,i,1);
        d.makeEdge(N+i,2*N+1,1);
        for(int j = 0; j < N; ++j){
            if(xa[i]<xb[j]&&ya[i]<yb[j]) d.makeEdge(i,N+j,1);
        }
    }
    cout << d.maxFlow(2*N,2*N+1) << endl;
    return 0;
}
