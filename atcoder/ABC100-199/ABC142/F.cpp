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
 * @title RadixHeap - 64bit型非負整数heap
 * @docs md/heap/RadixHeap.md
 */
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

/*
 * @title Graph
 * @docs md/graph/Graph.md
 */
template<class T> class Graph{
private:
    const size_t N;
public:
    vector<vector<pair<size_t,T>>> edges;
    Graph(const size_t N):N(N), edges(N) {}
    void make_edge(size_t from, size_t to, T w) {
        edges[from].emplace_back(to,w);
    }
    size_t size(){return N;}
};

/*
 * @title MinimumDirectedClosedCircuit - 有向グラフの最小閉路検出
 * @docs md/graph/MinimumDirectedClosedCircuit.md
 */
template<class T> class MinimumDirectedClosedCircuit {
    //Tは整数型のみ
    static_assert(std::is_integral<T>::value, "template parameter T must be integral type");
    Graph<T>& graph;
    vector<T> dist;
    vector<int> parent;
    size_t N;
    T inf;
    int last,root;
private:

    T solve_impl() {
        T mini = inf;
        last = -1;
        RadixHeap<int> q(0);
        q.push({0,root});
        dist[root] = 0;
        while (q.size()) {
            auto top =  q.pop();
            size_t curr = top.second;
            for(auto& edge:graph.edges[curr]){
                size_t next = edge.first;
                T w  = edge.second;                
                if(dist[next] > dist[curr]+w) {
                    dist[next]   = dist[curr] + w;
                    parent[next] = curr;
                    q.push({dist[next],next});
                }
                //根に返って来てるなら閉路候補
                if(next == root && mini > dist[curr]+w) {
                    mini = dist[curr]+w;
                    last = curr;
                }                
            }
        }
        return mini;
    }
public:
    MinimumDirectedClosedCircuit(Graph<T>& graph, T inf)
     : graph(graph),N(graph.size()),dist(graph.size()),parent(graph.size()),inf(inf) {
    }
    //rootを含む最小閉路の集合を返す O(NlogN) 閉路がないときは空集合
    inline T solve(size_t rt){
        root = rt;
        //初期化
        for(int i = 0; i < N; ++i) dist[i] = inf, parent[i] = -1;
        //最小閉路の大きさを決める
        T mini = solve_impl();
        return mini;
    }
    vector<int> restore() {
        vector<int> res;
        if(last == -1) return res;
        int curr = last;
        res.push_back(curr);
        while(curr != root) res.push_back(curr = parent[curr]);
        reverse(res.begin(),res.end());
        return res;
    }
};

int main() {
    int N,M; cin >> N >> M;
	Graph<int> graph(N);
    for(int i = 0; i < M; ++i){
        int u,v; cin >> u >> v;
        u--,v--;
		graph.make_edge(u,v,1);
    }
    int inf = 12345;
    MinimumDirectedClosedCircuit<int> mdcc(graph,inf);
    vector<int> ans;
    int mini = inf;
    for(int i = 0; i < N; ++i){
        auto tmp = mdcc.solve(i);
        if(mini > tmp) {
            mini = tmp;
            ans = mdcc.restore();
        }
    }
    corner(ans.empty(),-1);
    cout << ans.size() << endl;
    for(int e:ans) cout << e+1 << endl;

    return 0;
}
