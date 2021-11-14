#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define ALL(obj) (obj).begin(),(obj).end()
template<class T> using priority_queue_reverse = priority_queue<T,vector<T>,greater<T>>;

constexpr long long MOD = 1'000'000'000LL + 7; //'
constexpr long long MOD2 = 998244353;
constexpr long long HIGHINF = (long long)1e18;
constexpr long long LOWINF = (long long)1e15;
constexpr long double PI = 3.1415926535897932384626433L;

template <class T> vector<T> multivector(size_t N,T init){return vector<T>(N,init);}
template <class... T> auto multivector(size_t N,T... t){return vector<decltype(multivector(t...))>(N,multivector(t...));}
template <class T> void corner(bool flg, T hoge) {if (flg) {cout << hoge << endl; exit(0);}}
template <class T, class U>ostream &operator<<(ostream &o, const map<T, U>&obj) {o << "{"; for (auto &x : obj) o << " {" << x.first << " : " << x.second << "}" << ","; o << " }"; return o;}
template <class T>ostream &operator<<(ostream &o, const set<T>&obj) {o << "{"; for (auto itr = obj.begin(); itr != obj.end(); ++itr) o << (itr != obj.begin() ? ", " : "") << *itr; o << "}"; return o;}
template <class T>ostream &operator<<(ostream &o, const multiset<T>&obj) {o << "{"; for (auto itr = obj.begin(); itr != obj.end(); ++itr) o << (itr != obj.begin() ? ", " : "") << *itr; o << "}"; return o;}
template <class T>ostream &operator<<(ostream &o, const vector<T>&obj) {o << "{"; for (int i = 0; i < (int)obj.size(); ++i)o << (i > 0 ? ", " : "") << obj[i]; o << "}"; return o;}
template <class T, class U>ostream &operator<<(ostream &o, const pair<T, U>&obj) {o << "{" << obj.first << ", " << obj.second << "}"; return o;}
void print(void) {cout << endl;}
template <class Head> void print(Head&& head) {cout << head;print();}
template <class Head, class... Tail> void print(Head&& head, Tail&&... tail) {cout << head << " ";print(forward<Tail>(tail)...);}
template <class T> void chmax(T& a, const T b){a=max(a,b);}
template <class T> void chmin(T& a, const T b){a=min(a,b);}
vector<string> split(const string &str, const char delemiter) {vector<string> res;stringstream ss(str);string buffer; while( getline(ss, buffer, delemiter) ) res.push_back(buffer); return res;}
int msb(int x) {return x?31-__builtin_clz(x):-1;}
void YN(bool flg) {cout << (flg ? "YES" : "NO") << endl;}
void Yn(bool flg) {cout << (flg ? "Yes" : "No") << endl;}
void yn(bool flg) {cout << (flg ? "yes" : "no") << endl;}

vector<vector<pair<int,int>>> edge;
vector<int> dp;
int N;

void dfs(int curr, int prev, int prev_to_curr_label) {
    if(prev != -1) {
        dp[curr]=prev_to_curr_label;
        for(auto p:edge[curr]) {
            int next = p.first;
            int curr_to_next_label = p.second;
            if(dp[next]!=-1) continue;
            if(dp[curr]!=curr_to_next_label) {
                dfs(next,curr,curr_to_next_label);
            }
            else {
                dfs(next,-1,curr_to_next_label);
            }
        }
    }
    else {
        set<int> st;
        int ok=-1;
        for(auto p:edge[curr]) {
            int curr_to_next_label = p.second;
            st.insert(curr_to_next_label);
        }
        for(int i=0;i<N && ok==-1; ++i) if(!st.count(i)) ok=i;
        dp[curr] = ok;
        for(auto p:edge[curr]) {
            int next = p.first;
            int curr_to_next_label = p.second;
            if(dp[next]!=-1) continue;
            dfs(next,curr,curr_to_next_label);
        }
    }
}

/**
 * @url https://atcoder.jp/contests/arc108/tasks/arc108_c
 * @est 500
 */ 
int main() {
    cin.tie(0);ios::sync_with_stdio(false);
    int M; cin >> N >> M;
    edge.resize(N);
    dp.resize(N,-1);
    for(int i=0;i<M;++i) {
        int u,v,c; cin >> u >> v >> c;
        u--,v--,c--;
        edge[u].emplace_back(v,c);
        edge[v].emplace_back(u,c);
    }
    dfs(0,-1,-1);
    for(int i=0;i<N;++i) cout << dp[i]+1 << endl;
    return 0;
}
