#include <bits/stdc++.h>
using namespace std;
using int128 = __int128_t;
using int64 = long long;

#define ALL(obj) (obj).begin(),(obj).end()

/*
 * @title FastIO
 * @docs md/util/FastIO.md
 */
class FastIO{
private:
    inline static constexpr int ch_0='0';
    inline static constexpr int ch_9='9';
    inline static constexpr int ch_n='-';
    inline static constexpr int ch_s=' ';
    inline static constexpr int ch_l='\n';
    inline static void endline_skip(char& ch) {
        while(ch==ch_l) ch=getchar();
    }
    template<typename T> inline static void read_integer(T &x) {
        int neg=0; char ch; x=0;
        ch=getchar();
        endline_skip(ch);
        if(ch==ch_n) neg=1,ch=getchar();
        for(;(ch_0 <= ch && ch <= ch_9); ch = getchar()) x = x*10 + (ch-ch_0);
        if(neg) x*=-1;
    }
    template<typename T> inline static void read_unsigned_integer(T &x) {
        char ch; x=0;
        ch=getchar();
        endline_skip(ch);
        for(;(ch_0 <= ch && ch <= ch_9); ch = getchar()) x = x*10 + (ch-ch_0);
    }
    inline static void read_string(string &x) {
        char ch; x="";
        ch=getchar();
        endline_skip(ch);
        for(;(ch != ch_s && ch!=ch_l); ch = getchar()) x.push_back(ch);
    }
    inline static char ar[40];
    inline static char *ch_ar;
    template<typename T> inline static void write_integer(T x) {
        ch_ar=ar;
        if(x< 0) putchar(ch_n), x=-x;
        if(x==0) putchar(ch_0);
        for(;x;x/=10) *ch_ar++=(ch_0+x%10);
        while(ch_ar--!=ar) putchar(*ch_ar);
    }
public:
    inline static void read(int &x) {read_integer<int>(x);}
    inline static void read(long long &x) {read_integer<long long>(x);}
    inline static void read(unsigned int &x) {read_unsigned_integer<unsigned int>(x);}
    inline static void read(unsigned long long &x) {read_unsigned_integer<unsigned long long>(x);}
    inline static void read(string &x) {read_string(x);}
    inline static void read(__int128_t &x) {read_integer<__int128_t>(x);}
    inline static void write(__int128_t x) {write_integer<__int128_t>(x);}
    inline static void write(char x) {putchar(x);}
};
#define read(arg) FastIO::read(arg)
#define write(arg) FastIO::write(arg)

template<class T> using priority_queue_reverse = priority_queue<T,vector<T>,greater<T>>;

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
 * @title RadixHeap - 非負整数heap
 * @docs md/queue/RadixHeap.md
 */
template<class T, class Key = unsigned long long> class RadixHeap{
    using TypeNode = pair<Key, T>;
    template<class InnerKey, class ZZ=InnerKey> class Inner{};
    template<class InnerKey> class Inner<InnerKey, unsigned long long>{
        array<vector<TypeNode>,65> vq;
        unsigned long long size_num;
        TypeNode last;
        inline int bit(unsigned long long a) { return a ? 64 - __builtin_clzll(a) : 0;}
    public:
        Inner(T mini) : size_num(0), last(make_pair(0, mini)) {}
        inline bool empty() { return size_num == 0; }
        inline size_t size(){ return size_num; }
        inline void push(TypeNode x){ ++size_num; vq[bit(x.first^last.first)].push_back(x);}
        inline void emplace(unsigned long long key,T val){ ++size_num; vq[bit(key^last.first)].emplace_back(key,val);}
        inline TypeNode pop() {
            if(vq[0].empty()) {
                int i = 1;
                while(vq[i].empty()) ++i;
                last = *min_element(vq[i].begin(),vq[i].end());
                for(auto &p : vq[i]) vq[bit(p.first ^ last.first)].push_back(p);
                vq[i].clear();
            }
            --size_num;
            auto res = vq[0].back(); vq[0].pop_back();
            return res;
        }
    };
    template<class InnerKey> class Inner<InnerKey, unsigned int>{
        array<vector<TypeNode>,33> vq;
        unsigned int size_num;
        TypeNode last;
        inline int bit(unsigned int a) { return a ? 32 - __builtin_clz(a) : 0;}
    public:
        Inner(T mini) : size_num(0), last(make_pair(0, mini)) {}
        inline bool empty() { return size_num == 0; }
        inline size_t size(){ return size_num; }
        inline void push(TypeNode x){ ++size_num; vq[bit(x.first^last.first)].push_back(x);}
        inline void emplace(unsigned int key,T val){ ++size_num; vq[bit(key^last.first)].emplace_back(key,val);}
        inline TypeNode pop() {
            if(vq[0].empty()) {
                int i = 1;
                while(vq[i].empty()) ++i;
                last = *min_element(vq[i].begin(),vq[i].end());
                for(auto &p : vq[i]) vq[bit(p.first ^ last.first)].push_back(p);
                vq[i].clear();
            }
            --size_num;
            auto res = vq[0].back(); vq[0].pop_back();
            return res;
        }
    };
    Inner<Key,Key> inner;
public:
    RadixHeap(T mini) : inner(mini) {}
    inline bool empty() { return inner.empty();}
    inline size_t size(){ return inner.size();}
    inline void push(TypeNode x){ inner.push(x);}
    inline void emplace(unsigned long long key,T val){ inner.emplace(key,val);}
    inline TypeNode pop() { return inner.pop(); }
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
 * @title StronglyConnectedComponents - 強連結成分分解
 * @docs md/graph/StronglyConnectedComponents.md
 */
class StronglyConnectedComponents{
    int num,is_2sat,half,max_id,cnt;
    vector<vector<int>> edge;
    vector<int> label,order,low;
    stack<size_t> st;
    inline int rev(int i) { return i < half ? i + half : i - half; }
    inline void dfs(int& from) {
        low[from]=order[from]=cnt++;
        st.push(from);
        for(int& to:edge[from]) {
            if(order[to]==-1) {
                dfs(to);
                low[from]=min(low[from],low[to]);
            }
            else {
                low[from]=min(low[from],order[to]);
            }
        }
        if (low[from] == order[from]) {
            while(st.size()) {
                int u = st.top();st.pop();
                order[u] = num;
                label[u] = max_id;
                if (u == from) break;
            }
            max_id++;
        }
    }
public:
    StronglyConnectedComponents(const int n, bool is_2sat=0):num(n),max_id(0),cnt(0),is_2sat(is_2sat){
        if(is_2sat) num<<=1;
        edge.resize(num);
        label.resize(num);
        order.resize(num,-1);
        low.resize(num);
        half=(num>>1);
    }
    inline int operator[](int idx) {
        return label[idx];
    }
    inline void make_edge(const int from,const int to) {
        edge[from].push_back(to);
    }
    //xがflg_xならばyがflg_y
    inline void make_condition(int x, bool flg_x, int y, bool flg_y) {
        if (!flg_x) x = rev(x);
        if (!flg_y) y = rev(y);
        make_edge(x, y);
        make_edge(rev(y), rev(x));
    }
    //is_2sat=1のときに、2satを満たすかを返却する
    inline bool solve(void) {
        for (int i = 0; i < num; i++) if (order[i] == -1) dfs(i);
        for (int& id:label) id = max_id-1-id;
        if(!is_2sat) return true;
        for (int i = 0; i < num; ++i) if (label[i] == label[rev(i)]) return false;
        return true;
    }
    vector<vector<int>> topological_sort(void) {
        vector<vector<int>> ret(max_id);
        for(int i=0;i<num;++i) ret[label[i]].push_back(i);
        return ret;
    }
    int is_true(int i) {
        return label[i] > label[rev(i)];
    }
    void print(void) {
        for(auto id:label) cout << id << " ";
        cout << endl;
    }
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
        RadixHeap<int, unsigned int> q(0);
        q.push({0,root});
        dist[root] = 0;
        while (q.size()) {
            auto top =  q.pop();
            size_t curr = top.second;
            if(top.first > dist[curr]) continue;
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

/**
 * @url 
 * @est
 */ 
int main() {
    cin.tie(0);ios::sync_with_stdio(false);
    int N; read(N);
    Graph<int> g(N);
    StronglyConnectedComponents scc(N);
    for(int i=0;i<N;++i) {
        int a; read(a); a--;
        scc.make_edge(i,a);
        g.make_edge(i,a,1);
    }
    scc.solve();
    auto vv = scc.topological_sort();
    int x=-1;
    for(auto v: vv) {
        if(v.size()==1) continue;
        x = v.front();
    }
    MinimumDirectedClosedCircuit<int> mdcc(g,1234567);
    mdcc.solve(x);
    auto res = mdcc.restore();
    int M = res.size();
    cout << M << "\n";
    for(int i=0;i<M;++i) cout << res[i]+1 << " \n"[i==M-1];
    
    return 0;
}
