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

void solve() {
    int N; cin >> N;
    vector<vector<int>> edge(N);
    vector<int> deg(N,0);
    string col(N,'P');
    for(int i=0;i+1<N;++i) {
        int u,v; cin >> u >> v;
        u--,v--;
        edge[u].push_back(v);
        edge[v].push_back(u);
        deg[u]++; deg[v]++;
    }
    string S; cin >> S;
    queue<int> q;
    set<int> st;
    for(int i=0;i<N;++i) if(deg[i]==1) {
        q.push(i);
        st.insert(i);
    }

    string ans = "";
    while(q.size()) {
        int from=q.front(); q.pop();

        int P=0,C=0,B=0,W=0;
        int M=0;
        for(int to:edge[from]) {
            if(col[to]=='P') P++;
            if(col[to]=='C') C++;
            if(col[to]=='B') B++;
            if(col[to]=='W') W++;
            
            deg[to]--;
            if(deg[to]<=1 && !st.count(to)) {
                st.insert(to);
                q.push(to);
            }
            M++;
        }
        if(S[from]=='B') {
            //まずCをBにする
            for(int to:edge[from]) {
                if((M+1)/2>B && col[to]=='C') {
                    C--; B++;
                    col[to]='B';
                }
            }
            for(int to:edge[from]) {
                if((M+1)/2>B && col[to]=='P') {
                    P--; B++;
                    col[to]='B';
                }
            }
            if((M+1)/2>B) {
                ans = "-1";
                break;
            }
        }
        if(S[from]=='W') {
            //まずCをWにする
            for(int to:edge[from]) {
                if((M+1)/2>W && col[to]=='C') {
                    C--; W++;
                    col[to]='W';
                }
            }
            for(int to:edge[from]) {
                if((M+1)/2>W && col[to]=='P') {
                    P--; W++;
                    col[to]='W';
                }
            }
            if((M+1)/2>W) {
                ans = "-1";
                break;
            }
        }
        if(col[from]=='P') col[from]='C';
    }
    if(ans=="-1") {
        cout << ans << endl;
        return;
    }
    ans = col;
    for(int i=0;i<N;++i) if(ans[i]=='C' || ans[i]=='P') ans[i]='W';
    cout << ans << endl;
}

/**
 * @url 
 * @est
 */ 
int main() {
    cin.tie(0);ios::sync_with_stdio(false);
    int T; cin >> T;
    while(T--) {
        solve();
    }
    return 0;
}
