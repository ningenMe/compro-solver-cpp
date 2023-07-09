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
 * @title StaticTree - 木
 * @docs md/graph/StaticTree.md
 */
template<class Operator> class StaticTreeBuilder;
template<class Operator> class StaticTree {
private:
    using TypeEdge = typename Operator::TypeEdge;
    size_t num;
    size_t ord;
    Graph<TypeEdge>& g;
    friend StaticTreeBuilder<Operator>;
    StaticTree(Graph<TypeEdge>& graph):
            g(graph),
            num(graph.size()),
            depth(graph.size(),-1),
            order(graph.size()),
            edge_dist(graph.size()){
    }
    //for make_depth
    void dfs(int curr, int prev){
        for(const auto& e:g.edges[curr]){
            const int& next = e.first;
            if(next==prev) continue;
            depth[next] = depth[curr] + 1;
            edge_dist[next]  = Operator::func_edge_merge(edge_dist[curr],e.second);
            dfs(next,curr);
            order[ord++] = next;
        }
    }
    //for make_eulertour
    void dfs(int from){
        eulertour.push_back(from);
        for(auto& e:child[from]){
            int to = e.first;
            dfs(to);
            eulertour.push_back(from);
        }
    }
    void make_root(const int root) {
        depth[root] = 0;
        edge_dist[root] = Operator::unit_edge;
        ord = 0;
        dfs(root,-1);
        order[ord++] = root;
        reverse_copy(order.begin(),order.end(),back_inserter(reorder));
    }
    void make_root() {
        ord = 0;
        for(int i=0;i<num;++i) {
            if(depth[i]!=-1) continue;
            depth[i] = 0;
            edge_dist[i] = Operator::unit_edge;
            dfs(i,-1);
            order[ord++] = i;
        }
        reverse_copy(order.begin(),order.end(),back_inserter(reorder));
    }
    void make_child(const int root = 0) {
        child.resize(num);
        for (size_t i = 0; i < num; ++i) for (auto& e : g.edges[i]) if (depth[i] < depth[e.first]) child[i].push_back(e);
    }
    void make_subtree_size() {
        subtree_size.resize(num,1);
        for (size_t i:order) for (auto e : child[i]) subtree_size[i] += subtree_size[e.first];
    }
    void make_parent() {
        parent.resize(num,make_pair(num,Operator::unit_edge));
        for (size_t i = 0; i < num; ++i) for (auto& e : g.edges[i]) if (depth[i] > depth[e.first]) parent[i] = e;
    }
    void make_ancestor() {
        ancestor.resize(num);
        for (size_t i = 0; i < num; ++i) ancestor[i][0] = (parent[i].first!=num?parent[i]:make_pair(i,Operator::unit_lca_edge));
        for (size_t j = 1; j < Operator::bit; ++j) {
            for (size_t i = 0; i < num; ++i) {
                size_t k = ancestor[i][j - 1].first;
                ancestor[i][j] = Operator::func_lca_edge_merge(ancestor[k][j - 1],ancestor[i][j - 1]);
            }
        }
    }
    pair<size_t,TypeEdge> lca_impl(size_t l, size_t r) {
        if (depth[l] < depth[r]) swap(l, r);
        int diff = depth[l] - depth[r];
        auto ancl = make_pair(l,Operator::unit_lca_edge);
        auto ancr = make_pair(r,Operator::unit_lca_edge);
        for (int j = 0; j < Operator::bit; ++j) {
            if (diff & (1 << j)) ancl = Operator::func_lca_edge_merge(ancestor[ancl.first][j],ancl);
        }
        if(ancl.first==ancr.first) return ancl;
        for (int j = Operator::bit - 1; 0 <= j; --j) {
            if(ancestor[ancl.first][j].first!=ancestor[ancr.first][j].first) {
                ancl = Operator::func_lca_edge_merge(ancestor[ancl.first][j],ancl);
                ancr = Operator::func_lca_edge_merge(ancestor[ancr.first][j],ancr);
            }
        }
        ancl = Operator::func_lca_edge_merge(ancestor[ancl.first][0],ancl);
        ancr = Operator::func_lca_edge_merge(ancestor[ancr.first][0],ancr);
        return Operator::func_lca_edge_merge(ancl,ancr);
    }
    pair<TypeEdge,vector<size_t>> diameter_impl() {
        StaticTree tree = StaticTree::builder(g).build();
        size_t root = 0;
        {
            tree.make_root(0);
        }
        root = max_element(tree.edge_dist.begin(),tree.edge_dist.end()) - tree.edge_dist.begin();
        {
            tree.make_root(root);
        }
        size_t leaf = max_element(tree.edge_dist.begin(),tree.edge_dist.end()) - tree.edge_dist.begin();
        TypeEdge sz = tree.edge_dist[leaf];
        vector<size_t> st;
        {
            tree.make_parent();
            while(leaf != root) {
                st.push_back(leaf);
                leaf = tree.parent[leaf].first;
            }
            st.push_back(root);
        }
        return make_pair(sz,st);
    }
    template<class TypeReroot> vector<TypeReroot> rerooting_impl(vector<TypeReroot> rerootdp,vector<TypeReroot> rerootparent) {
        for(size_t pa:order) for(auto& e:child[pa]) rerootdp[pa] = Operator::func_reroot_dp(rerootdp[pa],rerootdp[e.first]);
        for(size_t pa:reorder) {
            if(depth[pa]) rerootdp[pa] = Operator::func_reroot_dp(rerootdp[pa],rerootparent[pa]);
            size_t m = child[pa].size();
            for(int j = 0; j < m && depth[pa]; ++j){
                size_t ch = child[pa][j].first;
                rerootparent[ch] = Operator::func_reroot_dp(rerootparent[ch],rerootparent[pa]);
            }
            if(m <= 1) continue;
            vector<TypeReroot> l(m),r(m);
            for(int j = 0; j < m; ++j) {
                size_t ch = child[pa][j].first;
                l[j] = rerootdp[ch];
                r[j] = rerootdp[ch];
            }
            for(int j = 1; j+1 < m; ++j) l[j] = Operator::func_reroot_merge(l[j],l[j-1]);
            for(int j = m-2; 0 <=j; --j) r[j] = Operator::func_reroot_merge(r[j],r[j+1]);
            size_t chl = child[pa].front().first;
            size_t chr = child[pa].back().first;
            rerootparent[chl] = Operator::func_reroot_dp(rerootparent[chl],r[1]);
            rerootparent[chr] = Operator::func_reroot_dp(rerootparent[chr],l[m-2]);
            for(int j = 1; j+1 < m; ++j) {
                size_t ch = child[pa][j].first;
                rerootparent[ch] = Operator::func_reroot_dp(rerootparent[ch],l[j-1]);
                rerootparent[ch] = Operator::func_reroot_dp(rerootparent[ch],r[j+1]);
            }
        }
        return rerootdp;
    }
    void make_eulertour() {
        dfs(reorder.front());
        eulertour_range.resize(num);
        for(int i = 0; i < eulertour.size(); ++i) eulertour_range[eulertour[i]].second = i+1;
        for(int i = eulertour.size()-1; 0 <= i; --i) eulertour_range[eulertour[i]].first = i;
    }
    void make_heavy_light_decomposition(){
        head.resize(num);
        hld.resize(num);
        iota(head.begin(),head.end(),0);
        for(size_t& pa:reorder) {
            pair<size_t,size_t> maxi = {0,num};
            for(auto& p:child[pa]) maxi = max(maxi,{subtree_size[p.first],p.first});
            if(maxi.first) head[maxi.second] = head[pa];
        }
        stack<size_t> st_head,st_sub;
        size_t cnt = 0;
        //根に近い方から探索
        for(size_t& root:reorder){
            if(depth[root]) continue;
            //根をpush
            st_head.push(root);
            while(st_head.size()){
                size_t h = st_head.top();
                st_head.pop();
                //部分木の根をpush
                st_sub.push(h);
                while (st_sub.size()){
                    size_t pa = st_sub.top();
                    st_sub.pop();
                    //部分木をカウントしていく
                    hld[pa] = cnt++;
                    //子を探索
                    for(auto& p:child[pa]) {
                        //子のheadが親と同じなら、そのまま進む
                        if(head[p.first]==head[pa]) st_sub.push(p.first);
                            //そうじゃない場合は、そこから新しく部分木としてみなす
                        else st_head.push(p.first);
                    }
                }
            }
        }
    }
    //type 0: vertex, 1: edge
    vector<pair<size_t,size_t>> path_impl(size_t u,size_t v,int type = 0) {
        vector<pair<size_t,size_t>> path;
        while(1){
            if(hld[u]>hld[v]) swap(u,v);
            if(head[u]!=head[v]) {
                path.push_back({hld[head[v]],hld[v]});
                v=parent[head[v]].first;
            }
            else {
                path.push_back({hld[u],hld[v]});
                break;
            }
        }
        reverse(path.begin(),path.end());
        if(type) path.front().first++;
        return path;
    }
    pair<vector<pair<size_t,size_t>>,vector<pair<size_t,size_t>>> ordered_path_impl(size_t u,size_t v,int type = 0) {
        vector<pair<size_t,size_t>> path_lca_to_u;
        vector<pair<size_t,size_t>> path_lca_to_v;
        while(1){
            if(head[u] == head[v]) {
                if(depth[u] < depth[v]) path_lca_to_v.emplace_back(hld[u]+type,hld[v]);
                else path_lca_to_u.emplace_back(hld[v]+type,hld[u]);
                break;
            }
            else if(hld[u] < hld[v]) {
                path_lca_to_v.emplace_back(hld[head[v]],hld[v]);
                v = parent[head[v]].first;
            }
            else if(hld[u] > hld[v]) {
                path_lca_to_u.emplace_back(hld[head[u]],hld[u]);
                u = parent[head[u]].first;
            }
        }
        reverse(path_lca_to_v.begin(),path_lca_to_v.end());
        return {path_lca_to_u,path_lca_to_v};
    }
    size_t lca_idx_impl(size_t u,size_t v){
        while(1){
            if(hld[u]>hld[v]) swap(u,v);
            if(head[u]==head[v]) return u;
            v=parent[head[v]].first;
        }
    }
    vector<size_t> head;
public:
    vector<size_t> depth;
    vector<size_t> order;
    vector<size_t> reorder;
    vector<size_t> subtree_size;
    vector<pair<size_t,TypeEdge>> parent;
    vector<vector<pair<size_t,TypeEdge>>> child;
    vector<TypeEdge> edge_dist;
    vector<array<pair<size_t,TypeEdge>,Operator::bit>> ancestor;
    vector<size_t> eulertour;
    vector<pair<size_t,size_t>> eulertour_range;
    vector<size_t> hld;

    /**
     * O(N) builder
     */
    static StaticTreeBuilder<Operator> builder(Graph<TypeEdge>& graph) { return StaticTreeBuilder<Operator>(graph);}
    /**
     * O(logN) after make_ancestor
     * return {lca,lca_dist} l and r must be connected
     */
    pair<size_t,TypeEdge> lca(size_t l, size_t r) {return lca_impl(l,r);}
    /**
     * O(N) anytime
     * return {diameter size,diameter set}
     */
    pair<TypeEdge,vector<size_t>> diameter(void){return diameter_impl();}
    /**
     * O(N) after make_child
     */
    template<class TypeReroot> vector<TypeReroot> rerooting(const vector<TypeReroot>& rerootdp,const vector<TypeReroot>& rerootparent) {return rerooting_impl(rerootdp,rerootparent);}
    /**
     * O(logN)
     */
    vector<pair<size_t,size_t>> vertex_set_on_path(size_t u, size_t v) {return path_impl(u,v,0);}
    /**
    /**
     * O(logN)
     */
    vector<pair<size_t,size_t>> edge_set_on_path(size_t u, size_t v) {return path_impl(u,v,1);}
    /**
     * O(logN)
     * {lca to u path,lca to v path}
     */
    pair<vector<pair<size_t,size_t>>,vector<pair<size_t,size_t>>> vertex_ordered_set_on_path(size_t u, size_t v) {return ordered_path_impl(u,v,0);}
    /**
     * O(logN)
     * {lca to u path,lca to v path}
     */
    pair<vector<pair<size_t,size_t>>,vector<pair<size_t,size_t>>> edge_ordered_set_on_path(size_t u, size_t v) {return ordered_path_impl(u,v,1);}
    /**
     * O(logN) ancestorのlcaより定数倍軽め。idxだけ
     */
    size_t lca_idx(size_t u, size_t v) {return lca_idx_impl(u,v);}
};

template<class Operator> class StaticTreeBuilder {
    bool is_root_made =false;
    bool is_child_made =false;
    bool is_parent_made=false;
    bool is_subtree_size_made=false;
public:
    using TypeEdge = typename Operator::TypeEdge;
    StaticTreeBuilder(Graph<TypeEdge>& g):tree(g){}
    StaticTreeBuilder& root(const int rt) { is_root_made=true; tree.make_root(rt); return *this;}
    StaticTreeBuilder& root() { is_root_made=true; tree.make_root(); return *this;}
    StaticTreeBuilder& child() { assert(is_root_made); is_child_made=true;  tree.make_child();  return *this;}
    StaticTreeBuilder& parent() { assert(is_root_made); is_parent_made=true; tree.make_parent(); return *this;}
    StaticTreeBuilder& subtree_size() { assert(is_child_made); is_subtree_size_made=true; tree.make_subtree_size(); return *this;}
    StaticTreeBuilder& ancestor() { assert(is_parent_made); tree.make_ancestor(); return *this;}
    StaticTreeBuilder& eulertour() { assert(is_child_made); tree.make_eulertour(); return *this;}
    StaticTreeBuilder& heavy_light_decomposition() { assert(is_subtree_size_made); assert(is_parent_made); tree.make_heavy_light_decomposition(); return *this;}
    StaticTree<Operator>&& build() {return move(tree);}
private:
    StaticTree<Operator> tree;
};
template<class T> struct StaticTreeOperator{
    using TypeEdge = T;
    inline static constexpr size_t bit = 20;
    inline static constexpr TypeEdge unit_edge = 0;
    inline static constexpr TypeEdge unit_lca_edge = 0;
    inline static constexpr TypeEdge func_edge_merge(const TypeEdge& parent,const TypeEdge& w){return parent+w;}
    inline static constexpr pair<size_t,TypeEdge> func_lca_edge_merge(const pair<size_t,TypeEdge>& l,const pair<size_t,TypeEdge>& r){return make_pair(l.first,l.second+r.second);}
    template<class TypeReroot> inline static constexpr TypeReroot func_reroot_dp(const TypeReroot& l,const TypeReroot& r) {return {l.first+r.first+r.second,l.second+r.second};}
    template<class TypeReroot> inline static constexpr TypeReroot func_reroot_merge(const TypeReroot& l,const TypeReroot& r) {return {l.first+r.first,l.second+r.second};}
};
//auto tree = StaticTree<StaticTreeOperator<int>>::builder(g).build();

/**
 * @url 
 * @est
 */ 
int main() {
    cin.tie(0);ios::sync_with_stdio(false);

    int N; read(N);
    Graph<int> g(N);
    int M; read(M);
    for(int i=1;i<N;++i) {
        int p; read(p); p--;
        g.make_bidirectional_edge(i,p,1);
    }
    vector<int> dp(N,0);
    while(M--) {
        int x,y; read(x),read(y);
        x--;
        chmax(dp[x],y+1);
    }
    auto tree = StaticTree<StaticTreeOperator<int>>::builder(g).root(0).parent().build();
    for(int ch: tree.reorder) {
        if(ch==0) continue;
        auto [p,_] = tree.parent[ch];
        chmax(dp[ch], dp[p]-1);
    }
    int sum=0;
    for(int i=0;i<N;++i) if(dp[i]>0) sum++;
    cout << sum << endl;

    return 0;
}
