#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;

#define REP(i,n) for(long long i = 0; i < (n); i++)
#define FOR(i, m, n) for(long long i = (m);i < (n); ++i)
#define ALL(obj) (obj).begin(),(obj).end()
#define SPEED cin.tie(0);ios::sync_with_stdio(false);

template<class T> using V = vector<T>;
template<class T, class U> using P = pair<T, U>;
template<class T> using PQ = priority_queue<T>;
template<class T> using PQR = priority_queue<T,vector<T>,greater<T>>;

constexpr long long MOD = (long long)1e9 + 7;
constexpr long long MOD2 = 998244353;
constexpr long long HIGHINF = (long long)1e18;
constexpr long long LOWINF = (long long)1e15;
constexpr long double PI = 3.1415926535897932384626433;

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
    ll N,M; cin >> N >> M;
    vector<ll> A(N+2,LOWINF),B;
    for(int i = 1; i <= N; ++i) cin >> A[i];
    vector<ll> X(M),W(M);
    for(int i = 0; i < M; ++i) cin >> X[i] >> W[i];
    ll sum = accumulate(ALL(W),0LL);
    B = A;
    for(int i = 0; i < M; ++i) B[X[i]] -= W[i];
    for(int i = 1; i <= N; ++i) corner(B[i]<=0,-1);
    int flg = 1;
    for(int i = 0; i < N; ++i) if(A[i]<=sum) flg = 0;
    corner(flg,0);
    ll ok = 1e11,ng = 0,md;

    vector<ll> L(N+2,0),R(N+2,0),C(N+2,0);
    while(ok-ng>1){
        md = (ok+ng)/2;
        for(int i = 0; i <= N+1; ++i) L[i] = R[i] = 0;
        for(int i = 0; i < M; ++i){
            ll n = W[i]/md;
            L[X[i]+1] += md;
            L[min(X[i]+1+n,N+1)] += -md;
            R[X[i]-1] += md;
            R[max(0LL,X[i]-n-1)] += -md;
        }
        for(int i = 1; i <= N; ++i) L[i] += L[i-1];
        for(int i = N; 1 <= i; --i) R[i] += R[i+1];
        for(int i = 0; i < M; ++i){
            ll n = W[i]/md;
            L[min(X[i]+1+n,N+1)] += W[i]%md;
            R[max(0LL,X[i]-n-1)] += W[i]%md;
        }
        for(int i = 1; i <= N; ++i) L[i] += L[i-1];
        for(int i = N; 1 <= i; --i) R[i] += R[i+1];
        int flg = 1;
        for(int i = 1; i <= N; ++i){
            C[i] = sum - (L[i] + R[i]);
            if(C[i]>=A[i]) flg = 0;
        }
        (flg?ok:ng)=md;
    }
    cout << ok << endl;
    return 0;
}
