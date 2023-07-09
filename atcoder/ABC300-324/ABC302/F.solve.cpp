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
 * @title Dijkstra - 多次元ダイクストラ
 * @docs md/graph/Dijkstra.md
 */
template<class T> class Dijkstra {
    vector<long long> num_list;
    vector<long long> sum;
    int N;
    T inf;
    vector<vector<pair<T,int>>> edge;
    vector<T> cost;
    vector<int> dp;
    void resize(const int N) {
        edge.resize(N);
        cost.resize(N);
        dp.resize(N);
    }
public:
    Dijkstra(int N,T inf):inf(inf),num_list(1,N),sum(1,1),N(N){
        resize(N);
    }
    Dijkstra(initializer_list<long long> size_list,T inf):num_list(size_list),inf(inf),N(1){
        for(long long& e:num_list) N *= e;
        sum.resize(num_list.size(),1);
        for(int i = 0; i < num_list.size(); ++i) {
            for(int j = i + 1; j < num_list.size(); ++j) {
                sum[i] *= num_list[j];
            }
        }
        resize(N);
    }
    void make_edge(int from, int to, T w) {
        if(from < 0 || N <= from || to < 0 || N <= to) return;
        edge[from].push_back({ w,to });
    }
    void make_edge(initializer_list<long long> from_list, initializer_list<long long> to_list, T w) {
        int from = 0, to = 0;
        auto from_itr = from_list.begin(),to_itr = to_list.begin();
        for(int i = 0; i < num_list.size(); ++i) {
            if(*from_itr < 0 || num_list[i] <= *from_itr || *to_itr < 0 || num_list[i] <= *to_itr) return;
            from += (*from_itr)*sum[i];
            to   += (*to_itr)*sum[i];
            from_itr++;
            to_itr++;
        }
        edge[from].push_back({ w,to });
    }
    void solve(initializer_list<long long> start_list) {
        int start = 0;
        auto start_itr = start_list.begin();
        for(int i = 0; i < num_list.size(); ++i) {
            start += (*start_itr)*sum[i];
            start_itr++;
        }
        solve(start);
    }
    void solve(int start) {
        for(int i = 0; i < N; ++i) cost[i] = inf, dp[i] = -1;
        priority_queue<pair<T, int>, vector<pair<T, int>>, greater<pair<T, int>>> pq;
        cost[start] = 0;
        pq.push({ 0,start });
        while (!pq.empty()) {
            auto [v,from] = pq.top();
            pq.pop();
            if(cost[from] < v) continue;
            for (auto [u,to] : edge[from]) {
                T w = v + u;
                if (w < cost[to]) {
                    cost[to] = w;
                    dp[to] = from;
                    pq.push({ w,to });
                }
            }
        }
        return;
    }
    T get(int idx){
        return cost[idx];
    }
    T get(initializer_list<long long> idx_list){
        int idx = 0;
        auto idx_itr = idx_list.begin();
        for(int i = 0; i < num_list.size(); ++i) {
            idx += (*idx_itr)*sum[i];
            idx_itr++;
        }
        return get(idx);
    }
    //vertex [start->node1->node2->...->idx]
    vector<int> restore(int idx) {
        vector<int> res = {idx};
        while(dp[idx] != -1) {
            idx = dp[idx];
            res.push_back(idx);
        }
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
    int N,M; cin >> N >> M;
    int64 inf = LOWINF;
    Dijkstra<int64> di(M+N, inf); //0..M-1, N+,,,
    for(int i=0;i<N;++i) {
        int a; cin >> a;
        for(int j=0;j<a;++j) {
            int b; cin >> b;
            b--;
            di.make_edge(b,M+i,0LL);
            di.make_edge(M+i,b,1LL);
        }
    }
    di.solve(0);
    int64 ans = di.get(M-1);
    if(ans >= inf) ans = -1;
    else ans -= 1;
    cout << ans << endl;

    return 0;
}
