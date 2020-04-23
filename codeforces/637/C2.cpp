#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define ALL(obj) (obj).begin(),(obj).end()
#define SPEED cin.tie(0);ios::sync_with_stdio(false);

template<class T> using PQ = priority_queue<T>;
template<class T> using PQR = priority_queue<T,vector<T>,greater<T>>;

constexpr long long MOD = (long long)1e9 + 7;
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
template <template <class tmp>  class T, class U> ostream &operator<<(ostream &o, const T<U> &obj) {o << "{"; for (auto itr = obj.begin(); itr != obj.end(); ++itr)o << (itr != obj.begin() ? ", " : "") << *itr; o << "}"; return o;}
void print(void) {cout << endl;}
template <class Head> void print(Head&& head) {cout << head;print();}
template <class Head, class... Tail> void print(Head&& head, Tail&&... tail) {cout << head << " ";print(forward<Tail>(tail)...);}
template <class T> void chmax(T& a, const T b){a=max(a,b);}
template <class T> void chmin(T& a, const T b){a=min(a,b);}
void YN(bool flg) {cout << (flg ? "YES" : "NO") << endl;}
void Yn(bool flg) {cout << (flg ? "Yes" : "No") << endl;}
void yn(bool flg) {cout << (flg ? "yes" : "no") << endl;}

int main() {
    SPEED
    int N,M; cin >> N >> M;
    vector<int> A(M);
    for(int i = 0; i < M; ++i) cin >> A[i];
    sort(ALL(A));
    int G,R; cin >> G >> R;
    int X = G+1;
    ll inf = LOWINF;
    auto dp = multivector(M*(G+1),inf);
    dp[0*0] = 0;
    PQR<pair<ll,int>> pq;
    pq.push({0,0});
    while(pq.size()) {
        auto p = pq.top();
        pq.pop();
        int from = p.second / X;
        int mod = p.second % X;
        int to;
        to = from - 1;
        if(0 <= to && to < M) {
            ll d = abs(A[to]-A[from]);
            if(mod + d <= G && dp[to*X+mod+d] > dp[from*X+mod]+d){
                dp[to*X+mod+d] = dp[from*X+mod]+d;
                pq.push({dp[to*X+mod+d],to*X+mod+d});
            }
        }
        to = from + 1;
        if(0 <= to && to < M) {
            ll d = abs(A[to]-A[from]);
            if(mod + d <= G && dp[to*X+mod+d] > dp[from*X+mod]+d){
                dp[to*X+mod+d] = dp[from*X+mod]+d;
                pq.push({dp[to*X+mod+d],to*X+mod+d});
            }
        }
        to = from;
        if(mod == G) {
            ll d = R;
            if(dp[to*X+0] > dp[from*X+mod]+d){
                dp[to*X+0] = dp[from*X+mod]+d;
                pq.push({dp[to*X+0],to*X+0});
            }
        }
    }
    ll ans = inf;
    for(int i = 0; i <= G; ++i) {
        chmin(ans,dp[(M-1)*X+i]);
    }
    if(ans == inf) ans = -1;
    cout << ans << endl;
    return 0;
}
