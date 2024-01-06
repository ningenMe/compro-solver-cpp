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
 * @title DinicMaxFlow - Dinicフロー
 * @docs md/graph/DinicMaxFlow.md
 */
template <class TypeFlow> class DinicMaxFlow {
    struct Edge {
        size_t to, rev;
        TypeFlow cap;
    };
    vector<vector<Edge>> edge;
    vector<int> level, iter;
    TypeFlow inf_flow;

    inline void bfs(const size_t start) {
        for (int i = 0; i < level.size(); ++i) level[i] = -1;
        queue<size_t> q;
        level[start] = 0;
        q.push(start);
        while (q.size()) {
            auto from = q.front();
            q.pop();
            for (auto& e : edge[from]) {
                if (e.cap > 0 && level[e.to] < 0) {
                    level[e.to] = level[from] + 1;
                    q.push(e.to);
                }
            }
        }
    }

    inline TypeFlow dfs(size_t from, size_t goal, TypeFlow flow) {
        if (from == goal) return flow;
        for (int& i = iter[from]; i < edge[from].size(); ++i) {
            //TODO 参照が効いてなくて冗長
            auto& e = edge[from][i];
            if (e.cap <= 0 || level[from] >= level[e.to]) continue;
            TypeFlow dflow = dfs(e.to, goal, min(flow, e.cap));
            if (dflow <= 0) continue;
            e.cap -= dflow;
            edge[e.to][e.rev].cap += dflow;
            return dflow;
        }
        return 0;
    }

public:
    DinicMaxFlow(const size_t N) : edge(N), level(N), iter(N), inf_flow(0) {
        // do nothing
    }

    inline void make_edge(const size_t from,const size_t to, TypeFlow cap) {
        edge[from].push_back({ to, edge[to].size(), cap });
        edge[to].push_back({ from, edge[from].size() - 1, 0});
        inf_flow += cap;
    }

    inline TypeFlow flow(const size_t start,const size_t goal) {
        TypeFlow max_flow = 0;
        while (1) {
            bfs(start);
            if (level[goal] < 0) return max_flow;
            for (int i = 0; i < iter.size(); ++i) iter[i] = 0;
            TypeFlow flow;
            while ((flow = dfs(start, goal, inf_flow))>0) max_flow += flow;
        }
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
    int N,M; read(N),read(M);
    vector<string> vs(N);
    for(int i=0;i<N;++i) read(vs[i]);

    unordered_map<int,unordered_map<int,vector<int>>> mp1;
    for(int i=0;i<N;++i) {
        for(int j=0;j<M;++j) {
            mp1[vs[i][j]-'0'][i].push_back(j);
        }
    }
    unordered_map<int,vector<tuple<int,int>>> mp2;
    for(int n= 0; n<10; ++n) {
        for(int i=0;i<N;++i) {
            auto v = mp1[n][i];
            int L = v.size();
            if(L==0) continue;
            for(int j=0;j<N;++j) {
                int x = i;
                int y = v[j%L];
                int t = (j/L)*M + y;
                mp2[n].emplace_back(t,x);
            }
        }
    }
    int inf = 123456789;
    int ans = inf;
    for(int n=0;n<10;++n) {
        auto vtp = mp2[n];
        vector<int> cnt(N,0);
        for(auto [t,x]: vtp) cnt[x]=1;
        if(accumulate(ALL(cnt),0) < N) continue;
        vector<int> vt;
        set<int> stt;
        for(auto [t,x]: vtp) vt.push_back(t);
        Zarts vzt(vt);
        int L = vzt.size();
        sort(ALL(vt));
        vt.erase(unique(ALL(vt)),vt.end());

        int ok = inf, ng = -1, md;
        while(ok-ng>1) {
            md = (ok+ng)/2;
            DinicMaxFlow<int> mf(L + N + 2);
            int S = L+N;
            int G = S+1;
            for(auto t: vt) {
                if(md<t) continue;
                int zt = vzt.get_key(t);
                mf.make_edge(S,zt,1);
            }
            for(auto [t,x]: vtp) {
                if(md<t) continue;
                int zt = vzt.get_key(t);
                mf.make_edge(zt, L + x, 1);
            }
            for(int i=0;i<N;++i) mf.make_edge(L + i, G, 1);
            auto c = mf.flow(S,G);
            (c>=N?ok:ng)=md;
        }
        chmin(ans,ok);
    }
    if(ans>=inf) ans=-1;
    cout << ans << endl;

    return 0;
}
