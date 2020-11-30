#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define ALL(obj) (obj).begin(),(obj).end()
template<class T> using priority_queue_reverse = priority_queue<T,vector<T>,greater<T>>;

constexpr long long MOD = 1'000'000'000LL + 7; //'
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
    const size_t N,H,W;
public:
    vector<vector<pair<size_t,T>>> edges;
    Graph(const size_t N):N(N), edges(N) {}
    Graph(const size_t H, const size_t W):H(H),W(W),N(H*W), edges(H*W) {}
    inline void make_edge(size_t from, size_t to, T w) {
        edges[from].emplace_back(to,w);
    }
    //{from_y,from_x} -> {to_y,to_x} 
    inline void make_edge(pair<size_t,size_t> from, pair<size_t,size_t> to, T w) {
        make_edge(from.first*W+from.second,to.first*W+to.second,w);
    }
    inline void make_bidirectional_edge(size_t from, size_t to, T w) {
        make_edge(from,to,w);
        make_edge(to,from,w);
    }
    inline void make_bidirectional_edge(pair<size_t,size_t> from, pair<size_t,size_t> to, T w) {
        make_edge(from.first*W+from.second,to.first*W+to.second,w);
        make_edge(to.first*W+to.second,from.first*W+from.second,w);
    }
    inline size_t size(){return N;}
    inline size_t idx(pair<size_t,size_t> yx){return yx.first*W+yx.second;}
};

/*
 * @title MinimumUndirectedClosedCircuit - 無向グラフの最小閉路検出
 * @docs md/graph/MinimumUndirectedClosedCircuit.md
 */
template<class T> class MinimumUndirectedClosedCircuit {
    //Tは整数型のみ
    static_assert(std::is_integral<T>::value, "template parameter T must be integral type");
    Graph<T> graph;
    vector<T> dist;
    vector<int> parent,label;
    size_t N;
    bool is_same_weighted;
    T inf;
    int last_l,last_r,root;
private:
    void solve_same_weighted() {
        queue<int> q;
        q.push(root);
        dist[root] = 0;
        while (q.size()) {
            size_t curr = q.front(); q.pop();;
            for(auto& edge:graph.edges[curr]){
                size_t next = edge.first;
                T w  = edge.second;
                if(parent[curr] == next) continue;
                if(dist[next] > dist[curr] + w) {
                    dist[next]   = dist[curr] + w;
                    parent[next] = curr;
                    label[next] = (curr==root?next:label[curr]);
                    q.push(next);
                }
            }
        }
    }
    void solve_diff_weighted() {
        RadixHeap<int> q(0);
        q.push({0,root});
        dist[root] = 0;
        while (q.size()) {
            auto top =  q.pop();
            size_t curr = top.second;
            if(top.first > dist[curr]) continue;
            for(auto& edge:graph.edges[curr]){
                size_t next = edge.first;
                T w  = edge.second;
                if(parent[curr] == next) continue;
                if(dist[next] > dist[curr] + w) {
                    dist[next]   = dist[curr] + w;
                    parent[next] = curr;
                    label[next] = (curr==root?next:label[curr]);
                    q.push({dist[next],next});
                }
            }
        }
    }
    T solve_cycle() {
        T mini = inf;
        last_l=-1,last_r=-1;
        for(int l=0;l<N;++l) {
            if(l==root) continue;
            for(auto& edge:graph.edges[l]){
                int r = edge.first;
                T   w = edge.second;
                if(mini <= dist[l] + dist[r] + w) continue;
                if( (r==root && l!=label[l]) || (r!=root && label[l]!=label[r]) ) {
                    mini = dist[l] + dist[r] + w;
                    last_l = l;
                    last_r = r;
                }            
            }
        }
        return mini;
    }
public:
    MinimumUndirectedClosedCircuit(Graph<T>& graph, T inf)
     : graph(graph),N(graph.size()),dist(graph.size()),parent(graph.size()),label(graph.size()),inf(inf) {
        assert(!graph.edges.empty());
        //重みが一律かどうか判定 面倒だからここはlogつき
        set<T> st;
        for(int i=0;i<N;++i) for(auto& edge:graph.edges[i]) st.insert(edge.second);        
        is_same_weighted = (st.size() == 1);
    }
    //rootを含む最小閉路の集合を返す O(NlogN) 閉路がないときは空集合
    inline T solve(size_t rt){
        root = rt;
        //初期化
        for(int i = 0; i < N; ++i) dist[i] = inf, parent[i] = -1;
        if(is_same_weighted) solve_same_weighted(); //重み一律
        else solve_diff_weighted(); //重みがバラバラ
        T mini=solve_cycle();
        return mini;
    }
    //復元
    vector<int> restore() {
        stack<int> s;
        queue<int> q;
        vector<int> res;
        if(last_l != -1 && last_r != -1){
            for(int curr = last_l; curr != -1; curr = parent[curr]) s.push(curr);
            for(int curr = last_r; curr != root; curr = parent[curr]) q.push(curr);
            while(s.size()) res.push_back(s.top())  ,s.pop();
            while(q.size()) res.push_back(q.front()),q.pop();
        }
        return res;
    }
};

/**
 * @url https://yukicoder.me/problems/no/13
 * @est 300
 */ 
int main() {
    cin.tie(0);ios::sync_with_stdio(false);
    int W,H; cin >> W >> H;
    Graph<int> g(H,W);
    vector<int> a(W),b(W);
    {
        for(int j=0;j  <W;++j) cin >> a[j];
        for(int j=0;j+1<W;++j) if(a[j]==a[j+1]) g.make_bidirectional_edge({0,j},{0,j+1},1);        
    }
    for(int i=1;i<H;++i) {
        b=a;
        for(int j=0;j  <W;++j) cin >> a[j];
        for(int j=0;j  <W;++j) if(b[j]==a[j]) g.make_bidirectional_edge({i,j},{i-1,j},1);
        for(int j=0;j+1<W;++j) if(a[j]==a[j+1]) g.make_bidirectional_edge({i,j},{i,j+1},1);
    }
    int inf = 12345678;
    MinimumUndirectedClosedCircuit<int> mucc(g,inf);
    int flg = 0;
    for(int i=0;i<H;++i) for(int j=0;j<W;++j) {
        int sz = mucc.solve(g.idx({i,j}));
        if(sz < inf) flg = 1;
    }
    cout << (flg?"possible":"impossible") << endl;
    return 0;
}
