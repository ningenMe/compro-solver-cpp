#include <bits/stdc++.h>
using namespace std;
using int128 = __int128_t;
using int64 = long long;

#define ALL(obj) (obj).begin(),(obj).end()
template<class T> using priority_queue_reverse = priority_queue<T,vector<T>,greater<T>>;

constexpr int64 MOD = 1'000'000'000LL + 7; //'
constexpr int64 MOD2 = 998244353;
constexpr int64 HIGHINF = 1'000'000'000'000'000'000LL;
constexpr int64 LOWINF = 1'000'000'000'000'000LL; //'
constexpr long double PI = 3.1415926535897932384626433L;

template <class T> vector<T> multivector(size_t N,T init){return vector<T>(N,init);}
template <class... T> auto multivector(size_t N,T... t){return vector<decltype(multivector(t...))>(N,multivector(t...));}
template <class T> void corner(bool flg, T hoge) {if (flg) {cout << hoge << endl; exit(0);}}
template <class T, class U>ostream &operator<<(ostream &o, const map<T, U>&obj) {o << "{"; for (auto &x : obj) o << " {" << x.first << " : " << x.second << "}" << ","; o << " }"; return o;}
template <class T>ostream &operator<<(ostream &o, const set<T>&obj) {o << "{"; for (auto itr = obj.begin(); itr != obj.end(); ++itr) o << (itr != obj.begin() ? ", " : "") << *itr; o << "}"; return o;}
template <class T>ostream &operator<<(ostream &o, const multiset<T>&obj) {o << "{"; for (auto itr = obj.begin(); itr != obj.end(); ++itr) o << (itr != obj.begin() ? ", " : "") << *itr; o << "}"; return o;}
template <class T>ostream &operator<<(ostream &o, const vector<T>&obj) {o << "{"; for (int i = 0; i < (int)obj.size(); ++i)o << (i > 0 ? ", " : "") << obj[i]; o << "}"; return o;}
template <class T>ostream &operator<<(ostream &o, const deque<T>&obj) {o << "{"; for (int i = 0; i < (int)obj.size(); ++i)o << (i > 0 ? ", " : "") << obj[i]; o << "}"; return o;}
template <class T, class U>ostream &operator<<(ostream &o, const pair<T, U>&obj) {o << "{" << obj.first << ", " << obj.second << "}"; return o;}
void print(void) {cout << endl;}
template <class Head> void print(Head&& head) {cout << head;print();}
template <class Head, class... Tail> void print(Head&& head, Tail&&... tail) {cout << head << " ";print(forward<Tail>(tail)...);}
template <class T> void chmax(T& a, const T b){a=max(a,b);}
template <class T> void chmin(T& a, const T b){a=min(a,b);}
vector<string> split(const string &str, const char delemiter) {vector<string> res;stringstream ss(str);string buffer; while( getline(ss, buffer, delemiter) ) res.push_back(buffer); return res;}
inline constexpr int msb(int x) {return x?31-__builtin_clz(x):-1;}
inline constexpr int64 ceil_div(const int64 a,const int64 b) {return (a+(b-1))/b;}// return ceil(a/b)
void YN(bool flg) {cout << (flg ? "YES" : "NO") << endl;}
void Yn(bool flg) {cout << (flg ? "Yes" : "No") << endl;}
void yn(bool flg) {cout << (flg ? "yes" : "no") << endl;}

/*
 * @title Graph
 * @docs md/graph/Graph.md
 */
template<class T> class Graph{
private:
    const size_t N,H,W;
public:
    vector<vector<pair<size_t,T>>> edges;
    Graph(const size_t N):H(-1),W(-1),N(N), edges(N) {}
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
 * @title RadixHeapInt - 32bit型非負整数heap
 * @docs md/heap/RadixHeapInt.md
 */
template<class T> class RadixHeapInt{
    using TypeNode = pair<unsigned int, T>;
    array<vector<TypeNode>,33> vq;
    unsigned int size_num;
    TypeNode last;
    inline int bit(int a) {
        return a ? 32 - __builtin_clz(a) : 0;
    }
public:
    RadixHeapInt(T mini) : size_num(0), last(make_pair(0,mini)) {
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
    inline void emplace(unsigned int key,T val){
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
    T inf;
    int last_l,last_r,root;
private:
    void solve_impl() {
        RadixHeapInt<int> q(0);
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
                    label[next]  = (curr==root?next:label[curr]);
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
    }
    //rootを含む最小閉路の集合を返す O(NlogN) 閉路がないときは空集合
    inline T solve(size_t rt){
        root = rt;
        //初期化
        for(int i = 0; i < N; ++i) dist[i] = inf, parent[i] = -1;
        solve_impl();
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

/*
 * @title UnionFindTree - Union Find 木
 * @docs md/graph/UnionFindTree.md
 */
class UnionFindTree {
    vector<int> parent,maxi,mini;
    inline int root(int n) {
        return (parent[n]<0?n:parent[n] = root(parent[n]));
    }
public:
    UnionFindTree(int N = 1) : parent(N,-1),maxi(N),mini(N){
        iota(maxi.begin(),maxi.end(),0);
        iota(mini.begin(),mini.end(),0);
    }
    inline bool connected(int n, int m) {
        return root(n) == root(m);
    }
    inline void merge(int n, int m) {
        n = root(n);
        m = root(m);
        if (n == m) return;
        if(parent[n]>parent[m]) swap(n, m);
        parent[n] += parent[m];
        parent[m] = n;
        maxi[n] = std::max(maxi[n],maxi[m]);
        mini[n] = std::min(mini[n],mini[m]);
    }
    inline int min(int n) {
        return mini[root(n)];
    }
    inline int max(int n) {
        return maxi[root(n)];
    }
    inline int size(int n){
        return (-parent[root(n)]);
    }
    inline int operator[](int n) {
        return root(n);
    }
    inline void print() {
        for(int i = 0; i < parent.size(); ++i) cout << root(i) << " ";
        cout << endl;
    }
};

/*
 * @title Zarts - 座標圧縮
 * @docs md/util/Zarts.md
 */
template<class T> class Zarts{
    vector<T> value;
    map<T,int> key;
    size_t sz;
public:
    vector<int> compressed;
    Zarts(const vector<T> & ar, int light_flag = 0, T pre=-1) : compressed(ar.size()) {
        if(!light_flag) {
            for (auto &e : ar) key[e];
            int cnt=0;
            for (auto &e : key) e.second = cnt++;
            for (int i=0;i<ar.size();++i) compressed[i]=key[ar[i]];
            value.resize(key.size());
            for (auto &e : key) value[e.second] = e.first;
            sz = cnt;
        }
        else {
            vector<pair<int,int>> ord(ar.size());
            for(int i=0;i<ar.size();++i) ord[i]={ar[i],i};
            sort(ord.begin(),ord.end());
            int cnt=-1;
            for(int i=0;i<ar.size();++i) {
                if(pre < ord[i].first) cnt++;
                compressed[ord[i].second] = cnt;
                pre = ord[i].first;
            }
            sz = cnt+1;
        }
    }
    T get_value(int key) {
        return value[key];
    }
    int get_key(T value) {
        assert(key.count(value));
        return key[value];
    }
    size_t size() {
        return sz;
    }
};

/**
 * @url 
 * @est
 */ 
int main() {
    cin.tie(0);ios::sync_with_stdio(false);
    int N,M; cin >> N >> M;
    UnionFindTree uf(2*N);
    vector<int> deg(2*N,0);
    for(int i=0;i<N;++i) {
        uf.merge(i,i+N);
        deg[i]++;
        deg[i+N]++;
    }
    while(M--) {
        int a; cin >> a;
        char b; cin >> b;
        int c; cin >> c;
        char d; cin >> d;
        a--,c--;
        if(b=='B') a+=N;
        if(d=='B') c+=N;
        uf.merge(a,c);
        deg[a]++;
        deg[c]++;
    }
    map<int,set<int>> mp;
    for(int i=0;i<2*N;++i) mp[uf[i]].insert(deg[i]);
    int X=0,Y=0;
    for(auto [_,st]:mp) {
        ((st.size() == 1 && (*st.begin()) == 2)? X:Y)++;
    }
    print(X,Y);
    return 0;
}
