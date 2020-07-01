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
template <class T> void chmax(T& a, const T b){a=max(a,b);}
template <class T> void chmin(T& a, const T b){a=min(a,b);}
void YN(bool flg) {cout << (flg ? "YES" : "NO") << endl;}
void Yn(bool flg) {cout << (flg ? "Yes" : "No") << endl;}
void yn(bool flg) {cout << (flg ? "yes" : "no") << endl;}

int main() {
    ll N,M,K; cin >> N >> M >> K;
    vector<ll> A(N+1,0),B(M+1,0);
    for(int i = 1; i <= N; ++i) cin >> A[i];
    for(int i = 1; i <= M; ++i) cin >> B[i];
    for(int i = 1; i <= N; ++i) A[i]+=A[i-1];
    for(int i = 1; i <= M; ++i) B[i]+=B[i-1];
    int ans = 0;
    for(int i = 0; i <= N; ++i) {
        if(A[i]>K) continue;
        int cnt = i;
        ll L = K - A[i];
        cnt += (upper_bound(ALL(B),L)-B.begin())-1;
        chmax(ans,cnt);
    }
    cout << ans << endl;

    return 0;
}
