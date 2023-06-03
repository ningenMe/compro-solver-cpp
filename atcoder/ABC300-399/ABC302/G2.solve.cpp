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

public:
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
    void print() {
        for(int i=0;i<edge.size();++i) {
            cout << i << ": ";
            for(int j=0;j<edge[i].size();++j) {
                cout << "{" << edge[i][j].to << " " << edge[i][j].cap << "},";
            }
            cout << endl;
        }
    }
};

//verify https://atcoder.jp/contests/arc085/tasks/arc085_c

/**
 * @url 
 * @est
 */ 
int main() {
    cin.tie(0);ios::sync_with_stdio(false);
    int N; cin >> N;
    vector<int> A(N);
    for(int i=0;i<N;++i) cin >> A[i];
    auto B = A;
    sort(ALL(B));
    Dinic<int> di(N+N+4+2,0,10*N);
    int S = N+N+4,G = S+1;
    for(int i=0;i<N;++i) {
        A[i]--,B[i]--;
        di.make_edge(S,i,1);
        di.make_edge(N+i,G,1);
        if(A[i]==B[i]) continue;
        di.make_edge(i,N+N+A[i],1);
        di.make_edge(N+N+B[i],N+i,1);
    }

    int ans = di.maxflow(S,G);
    di.print();
    cout << ans << endl;
    return 0;
}
