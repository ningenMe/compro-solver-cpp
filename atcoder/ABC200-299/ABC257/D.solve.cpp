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
 * @title Distance - 距離
 * @docs md/geometory/Distance.md
 */
template<class T> class Distance{
public:
    //Euclidean distance
    inline static constexpr T euclid(const T& x1, const T& y1, const T& x2, const T& y2) {
        return sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
    }
    //Chebyshev distance
    inline static constexpr T chebyshev(T x1, T y1, T x2, T y2) {
        return max(abs(x1 - x2),abs(y1 - y2));
    }
    //Manhattan distance
    inline static constexpr T manhattan(T x1, T y1, T x2, T y2) {
        return abs(x1 - x2)+abs(y1 - y2);
    }
    inline static constexpr T between_point_and_line(const T& x,const T& y,const T& x1,const T& y1,const T& x2,const T& y2){
        return abs((y2 - y1)*x+(x1 - x2)*y-(y2-y1)*x1+(x2-x1)*y1)/sqrt((y2 - y1)*(y2 - y1)+(x1 - x2)*(x1 - x2));
    }
};

/**
 * @url 
 * @est
 */ 
int main() {
    cin.tie(0);ios::sync_with_stdio(false);
    int64 N; cin >> N;
    vector<int64> x(N),y(N),p(N),dp(N);
    for(int i=0;i<N;++i) {
        cin >> x[i] >> y[i] >> p[i];
    }
    int64 ng = 0, ok = 5000000000LL, md;
    auto edges = multivector(N,N,0);

    while(ok - ng > 1) {
        md = (ok+ng)/2;
        int64 S = md;
        StronglyConnectedComponents scc(N);
        for(int i=0;i<N;++i) {
            for(int j=0;j<N;++j) {
                edges[i][j] = 0;
                if(i==j) continue;
                int64 flg = (p[i]*S >= Distance<int64>::manhattan(x[i],y[i],x[j],y[j]));
                edges[i][j] = flg;
                if(flg) scc.make_edge(i,j);
            }
        }        
        scc.solve();
        auto ts = scc.topological_sort();
        int s = ts[0][0];

        for(int i=0;i<N;++i) dp[i]=0;

        queue<int> q;
        q.push(s);
        dp[s] = 1;

        while(q.size()) {
            int from = q.front(); q.pop();
            for(int to=0;to<N;++to) {
                if(edges[from][to] != 1) continue;
                if(dp[to] == 0) {
                    dp[to] = 1;
                    q.push(to);
                }
            }
        }
        int sum = accumulate(ALL(dp),0);
        (sum == N ? ok:ng) = md;
    }
    cout << ok << endl;
    return 0;
}
