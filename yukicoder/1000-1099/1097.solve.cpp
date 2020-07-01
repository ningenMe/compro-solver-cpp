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
	int N; cin >> N;
    vector<ll> A(N+1,0),B(N+1,0),C(N+1,0),D(N+1,0);
    for(int i = 0; i < N; ++i) cin >> A[i];
    for(int i = 0; i < N; ++i) B[i]=(i+A[i])%N;
    B.back()=0;
    {
        int from = N;
        while(1){
            int to = B[from];
            if(C[to]==2) break;
            C[to]++;
            if(C[to]==1) D[to] = A[to]+D[from];
            from=to;
        }
    }
    vector<ll> E,F,G(N+1,0);
    E.push_back(0);
    {
        int from = N;
        while(1){
            int to = B[from];
            if(G[to]) break;
            if(C[to]==1) E.push_back(D[to]);
            if(C[to]==2) F.push_back(D[to]-E.back());
            from=to;
            G[to]=1;
        }
    }
    ll M = E.size();
    ll L = F.size();
    int Q; cin >> Q;
    while(Q--){
        ll K; cin >> K;
        ll ans = 0;
        if(K<M) {
            ans += E[K];
        }
        else {
            ans += E.back();
            K -= M;
            ans += F.back()*(K/L) + F[K%L];
        }
        cout << ans << endl;
    }
    return 0;
}
