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
    ll N,M,A; cin >> N >> M >> A;
    vector<ll> a(M);
    for(int i = 0; i < M; ++i) cin >> a[i];
    vector<vector<pair<ll,ll>>> vbc(M);
    for(int i = 0; i < N; ++i) {
        ll d; cin >> d; d--;
        ll b,c; cin >> b >> c;
        vbc[d].push_back({b,c});
    }
    ll K = 1000;
    auto dp1 = multivector(M,K+1,LOWINF);
    for(int i = 0; i < M; ++i){
        dp1[i][0] = 0;
        for(auto& e:vbc[i]){
            ll b = e.first, c = e.second;
            for(int j = K; 0 <= j; --j) {
                chmin(dp1[i][min(j+c,K)],dp1[i][j]+b);
            }
        }
    }
    vector<ll> dp2(K+1,LOWINF),tmp(K+1,LOWINF);
    dp2[0] = 0;
    for(int i = 0; i < M; ++i){
        for(int j = 0; j <= K; ++j) tmp[j] = LOWINF;
        for(ll j = 0; j <= K; ++j) {
            for(ll k = a[i]; k <= K; ++k){
                chmin(tmp[min(j+k,K)],dp2[j]+dp1[i][k]);
            }
        }
        dp2 = tmp;
    }
    ll ans = LOWINF;
    for(int i = A; i <= K; ++i) chmin(ans,dp2[i]);
    cout << ans << endl;
    return 0;
}
