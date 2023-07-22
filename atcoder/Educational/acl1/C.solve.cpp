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
 * @title PrimalDualMinCostFlow - 最短路反復の最小費用流
 * @docs md/graph/PrimalDualMinCostFlow.md
 */
template<class TypeFlow, class TypeCost> class PrimalDualMinCostFlow {
    using Pair = pair<TypeCost,size_t>;
    struct Edge {
        size_t to;
        size_t rev;
        TypeFlow cap;
        TypeCost cost; 
    };
    vector<vector<Edge>> edge;
    const size_t N;
    const TypeCost inf_cost;
    vector<TypeCost> min_cost;
    vector<TypeCost> potential;
    vector<size_t> prev_vertex,prev_edge;
    TypeFlow max_flow=0;
public:
    PrimalDualMinCostFlow(const size_t N, const TypeCost inf_cost) 
        : N(N), edge(N), min_cost(N), potential(N,0), prev_vertex(N,N), prev_edge(N,N), inf_cost(inf_cost) {}
    // costは単位流量あたりのコスト
    inline void make_edge(const size_t from, const size_t to, const TypeFlow cap, const TypeCost cost) {
        assert(cost < inf_cost);
        edge[from].push_back({ to, edge[to].size(), cap, cost });
        edge[to].push_back({ from, edge[from].size() - 1, 0, -cost });
        max_flow += cap;
    }
    pair<TypeFlow,TypeCost> min_cost_flow(const size_t s, const size_t g) {
        return min_cost_flow(s,g,max_flow);
    }
    pair<TypeFlow,TypeCost> min_cost_flow(const size_t s, const size_t g, const TypeFlow limit_flow) {
        assert(0 <= s && s < N && 0 <= g && g < N && s != g);
        priority_queue<Pair,vector<Pair>,greater<Pair>> pq;

        TypeCost sum_cost=0;
        TypeFlow sum_flow=0;
        while(sum_flow < limit_flow) {
            min_cost.assign(N, inf_cost);
            {
                pq.emplace(0,s);
                min_cost[s]=0;
            }
            while(pq.size()) {
                auto [from_cost, from] = pq.top(); pq.pop();
                if(min_cost[from] < from_cost) continue;

                for(int i=0; i < edge[from].size(); ++i) {
                    auto [to, rev, cap, cost] = edge[from][i];
                    TypeCost to_cost = from_cost + cost + (potential[from] - potential[to]);
                    if(cap > 0 && min_cost[to] > to_cost) {
                        pq.emplace(to_cost, to);
                        prev_vertex[to] = from;
                        prev_edge[to] = i;
                        min_cost[to] = to_cost;
                    }
                }
            }
            if(min_cost[g]==inf_cost) break;
            for(size_t i=0; i<N; ++i) potential[i] += min_cost[i];

            TypeFlow diff_flow = limit_flow - sum_flow;
            for(size_t i=g; i!=s; i = prev_vertex[i]) {
                diff_flow = min(diff_flow, edge[prev_vertex[i]][prev_edge[i]].cap);
            }
            sum_flow += diff_flow;
            sum_cost += diff_flow * potential[g];
            for(size_t i=g; i!=s; i = prev_vertex[i]) {
                auto& [_to,rev,cap,_cost] = edge[prev_vertex[i]][prev_edge[i]];
                auto& [_r_to,_r_rev,r_cap,_r_cost] = edge[i][rev];

                cap -= diff_flow;
                r_cap += diff_flow;
            }
        }
        return {sum_flow, sum_cost};
    }

};

/**
 * @url 
 * @est
 */ 
int main() {
    cin.tie(0);ios::sync_with_stdio(false);
    int H,W; 
    read(H),read(W);
    vector<string> vs(H);
    vector<int> cy,cx;
    for(int i = 0; i < H; ++i) {
        read(vs[i]);
        for(int j = 0; j < W; ++j) {
            if(vs[i][j]=='o') cy.push_back(i),cx.push_back(j);
        }
    }
    int64 c = cy.size();
    int64 inf = 123456789;
    PrimalDualMinCostFlow<int,int64> mcf(c+H*W+2, inf+1);
    int s = c+H*W,g = c+H*W+1;
    for(int i = 0; i < c; ++i) {
        int ty = cy[i],tx = cx[i];
        auto dp = multivector(H,W,-1LL);
        queue<int> q;
        q.push(ty*W+tx);
        dp[ty][tx]=0;
        while(q.size()){
            auto p=q.front(); q.pop();
            int y = p/W, x = p%W;
            if(y+1<H && vs[y+1][x]!='#' && dp[y+1][x] == -1) {
                dp[y+1][x]=dp[y][x]+1;
                q.push((y+1)*W+x);
            }
            if(x+1<W && vs[y][x+1]!='#' && dp[y][x+1] == -1) {
                dp[y][x+1]=dp[y][x]+1;
                q.push(y*W+x+1);
            }
        }
        for(int y=0; y < H; ++y) {
            for(int x=0; x < W; ++x) {
                if(dp[y][x]!=-1) {
                    mcf.make_edge(i,c+y*W+x,1,inf-dp[y][x]);
                }
            }
        }
        mcf.make_edge(s,i,1,0);
    }
    {
        for(int y=0; y < H; ++y) {
            for(int x=0; x < W; ++x) {
                mcf.make_edge(c+y*W+x,g,1,0);
            }
        }
    }
    int64 ans = inf*c;
    auto [flow,cost] = mcf.min_cost_flow(s,g);
    ans -= cost;
    cout << ans << endl;
    return 0;
}
