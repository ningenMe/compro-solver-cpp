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

/**
 * @url https://atcoder.jp/contests/abc184/tasks/abc184_e
 * @est 400
 */ 
int main() {
    cin.tie(0);ios::sync_with_stdio(false);
    int H,W; cin >> H >> W;
    vector<string> vs(H);
    for(int i=0;i<H;++i) {
        cin >> vs[i];
    }
    int N = H*W;
    vector<vector<int>> edge0(N+26),edge1(N+26);
    int S,G;
    for(int i=0;i<H;++i) {
        for(int j=0;j<W;++j) {
            if(vs[i][j]=='S') S = i*W+j;
            if(vs[i][j]=='G') G = i*W+j;
            int from = i*W+j;
            if(0 < i && vs[i-1][j]!='#') edge1[from].push_back((i-1)*W+j); 
            if(0 < j && vs[i][j-1]!='#') edge1[from].push_back(i*W+j-1); 
            if(i+1< H&& vs[i+1][j]!='#') edge1[from].push_back((i+1)*W+j); 
            if(j+1< W&& vs[i][j+1]!='#') edge1[from].push_back(i*W+j+1); 
            int c = vs[i][j]-'a';
            if(0 <= c && c < 26) {
                edge1[from].push_back(N+c);
                edge0[N+c].push_back(from);
            }
        }
    }
    deque<int> dq;
    int inf = 12345678;
    vector<int> dp(N+26,inf);
    dq.push_back(S);
    dp[S]=0;
    while(dq.size()) {
        int from = dq.front();
        dq.pop_front();
        for(int to:edge0[from]) {
            if(dp[to]>dp[from]) {
                dp[to]=dp[from];
                dq.push_front(to);
            }
        }
        for(int to:edge1[from]) {
            if(dp[to]>dp[from]+1) {
                dp[to]=dp[from]+1;
                dq.push_back(to);
            }
        }
    }
    int ans = dp[G];
    if(ans == inf) ans = -1;
    cout << ans << endl;
    return 0;
}
