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
 * @title Dinic - Dinicフロー
 * @docs md/graph/Dinic.md
 */
template <class T> class Dinic {
public:
    struct info {
        int to, rev;
        T cap;
    };
    T ini, inf;
    vector<vector<info>> edge;
    vector<int> level, iter;

    inline void bfs(int start) {
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

    inline T dfs(int from, int goal, T flow) {
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

    Dinic(int N, T ini, T inf) : edge(N), level(N), iter(N), ini(ini), inf(inf) {
        // do nothing
    }

    inline void make_edge(int from, int to, T cap) {
        edge[from].push_back({ to, (int)edge[to].size(), cap });
        edge[to].push_back({ from, (int)edge[from].size() - 1, ini });
    }

    inline T maxflow(int start, int goal) {
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

/*
 * @title Eratosthenes - エラトステネスの篩
 * @docs md/math/Eratosthenes.md
 */
inline static vector<int> Eratosthenes(int N) {
    vector<int> res(N + 1, 1);
    res[0] = res[1%(N+1)] = 0;
    for (int i = 1; i*i <= N; i++) if (res[i]) for (int j = 2 * i; j <= N; j += i) res[j] = 0;
    return res;
}

/**
 * @url 
 * @est
 */ 
int main() {
    cin.tie(0);ios::sync_with_stdio(false);
    auto E = Eratosthenes(20000010);
    int N; cin >> N;
    vector<pair<int64,int64>> AB(N);
    for(int i=0;i<N;++i) {
        int64 a,b; cin >> a >> b;
        AB[i] = {a,b};
    }
    sort(ALL(AB));
    Dinic<int64> di(N+2,0,LOWINF);
    int S = N, G = N+1;

    for(int i=0;i<N;++i) {
        auto [a,b] = AB[i];
        if(a%2==0) continue;
        for(int j=0;j<N;++j) {
            auto [c,d] = AB[j];
            if(c%2==1) continue;
            if(E[a+c]) {
                di.make_edge(i,j,b+d);
            }
        }
    }    
    for(int i=0;i<N;++i) {
        auto [a,b] = AB[i];
        if(a%2==1) {
            di.make_edge(S,i,b);
        }
        else {
            di.make_edge(i,G,b);
        }
    }    

    int64 sum = di.maxflow(S,G);

    // for(int i=0;i<N;++i) {
    //     cout << i << " " << AB[i] << " ::: ";
    //     for(int j=0;j<di.edge[i].size(); ++j) {
    //         cout << "{ " << di.edge[i][j].to << ", " << di.edge[i][j].cap << " }, ";
    //     }
    //     cout << "\n";
    // }
    int64 rr = 0;
    {
        for(int j=0;j<di.edge[S].size(); ++j) {
            if(AB[di.edge[S][j].to].first == 1) {
                rr = max(di.edge[S][j].cap,0LL);
            }
            // cout << "{ " << di.edge[S][j].to << ", " << di.edge[S][j].cap << " }, ";
        }
        // cout << "\n";
    }
    cout << sum + rr / 2 << endl;

    return 0;
}
