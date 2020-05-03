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
    N++;
    vector<vector<ll>> A(N,vector<ll>(3,LOWINF));
    for(int i = 1; i < N; ++i) {
        cin >> A[i][0] >> A[i][1] >> A[i][2];
    }
    auto dp = multivector(1<<N,N,3,0LL);
    for(int i = 1; i < (1<<N); ++i) {
        for(int j = 0; j < N; ++j) {
            if(!(i&(1<<j))) continue;

            for(int k = 0; k < N; ++k) {
                if(i&(1<<k)) continue;

                for(int l = 0; l < 3; ++l) {
                    for(int m = 0; m < 3; ++m) {
                        ll s,t,u,v;
                        if(l==0) s=A[j][1],t=A[j][2];
                        if(l==1) s=A[j][0],t=A[j][2];
                        if(l==2) s=A[j][0],t=A[j][1];
                        if(s>=t) swap(s,t);

                        if(m==0) u=A[k][1],v=A[k][2];
                        if(m==1) u=A[k][0],v=A[k][2];
                        if(m==2) u=A[k][0],v=A[k][1];
                        if(u>=v) swap(u,v);

                        if(s<=u&&t<=v){
                            chmax(dp[i^(1<<k)][k][m],dp[i][j][l]+A[j][l]);
                        }
                    }
                }

            }            
        }
    }
    ll ans = 0;
    for(int i = 0; i < (1<<N); ++i) {
        for(int j = 0; j < N; ++j) {
            for(int k = 0; k < 3; ++k) {
                chmax(ans,dp[i][j][k]);
            }
        }
    }
    cout << ans << endl;
    return 0;
}
