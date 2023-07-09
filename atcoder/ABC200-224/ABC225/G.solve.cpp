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
};

//verify https://atcoder.jp/contests/arc085/tasks/arc085_c

/**
 * @url 
 * @est
 */ 
int main() {
    cin.tie(0);ios::sync_with_stdio(false);
    int64 H,W,C;
    read(H),read(W),read(C);
    auto A = multivector(H,W,0LL);
    for(int i=0;i<H;++i) {
        for(int j=0;j<W;++j) {
            read(A[i][j]);
        }
    }
    int64 inf = HIGHINF;
    Dinic<int64> di(H*W+2*H*W+2,0,inf);
    int S = H*W+2*H*W; 
    int G = S+1;
    int64 ans = 0;
    for(int i=0;i<H;++i) {
        for(int j=0;j<W;++j) {
            int64 cost = A[i][j]-2*C;
            if(cost >= 0) {
                ans+=cost;
                di.make_edge(i*W+j,G,cost);
            }
            else {
                di.make_edge(S,i*W+j,-cost);
            }
        }
    }
    int k = H*W;
    for(int i=0;i+1<H;++i) {
        for(int j=0;j<W;++j) {
            if(0<=j-1) {
                ans += C;
                di.make_edge(i*W+j,k,inf);
                di.make_edge((i+1)*W+j-1,k,inf);
                di.make_edge(k,G,C);
                k++;
            }
            if(j+1<W) {
                ans += C;
                di.make_edge(i*W+j,k,inf);
                di.make_edge((i+1)*W+j+1,k,inf);
                di.make_edge(k,G,C);
                k++;
            }
        }
    }
    ans=ans-di.maxflow(S,G);
    cout << ans << endl;

    return 0;
}
