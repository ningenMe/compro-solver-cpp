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

ll f(ll a,ll b, ll c, ll p, ll q, ll r) {
    return abs(p-a)+abs(q-b)+max(r-c,0LL);
}

int main() {
    cin.tie(0);ios::sync_with_stdio(false);
    int N; cin >> N;
    vector<ll> X(N),Y(N),Z(N);
    for(int i=0;i<N;++i) cin >> X[i] >> Y[i] >> Z[i];
    auto dp = multivector(1<<N,N,LOWINF);
    dp[0][0] = 0;
    for(int i=0; i < (1<<N); ++i) {
        for(int j=0;j<N;++j) {
            if(dp[i][j]>=LOWINF) continue;
            for(int k=0;k<N;++k) {
                if(i&(1<<k)) continue;
                ll d = f(X[j],Y[j],Z[j],X[k],Y[k],Z[k]);
                chmin(dp[i^(1<<k)][k],dp[i][j]+d);
            }
        }
    }
    ll ans = LOWINF;
    {
        for(int j=0;j<N;++j) {
            ll d = f(X[j],Y[j],Z[j],X[0],Y[0],Z[0]);
            chmin(ans,dp[(1<<N)-1][j]+d);
        }
    }
    cout << ans << endl;
    return 0;
}
