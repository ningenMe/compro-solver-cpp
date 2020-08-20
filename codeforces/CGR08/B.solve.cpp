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
    ll k; cin >> k;
    // codeforces
    vector<ll> c(10,1);
    while(1) {
        ll mul = 1;
        for(ll& x:c) mul *= x;
        if(mul >= k) break;
        c.front()++;
        sort(ALL(c));
    }
    string ans = "";
    for(int i = 0; i < c[0]; ++i) ans.push_back('c');
    for(int i = 0; i < c[1]; ++i) ans.push_back('o');
    for(int i = 0; i < c[2]; ++i) ans.push_back('d');
    for(int i = 0; i < c[3]; ++i) ans.push_back('e');
    for(int i = 0; i < c[4]; ++i) ans.push_back('f');
    for(int i = 0; i < c[5]; ++i) ans.push_back('o');
    for(int i = 0; i < c[6]; ++i) ans.push_back('r');
    for(int i = 0; i < c[7]; ++i) ans.push_back('c');
    for(int i = 0; i < c[8]; ++i) ans.push_back('e');
    for(int i = 0; i < c[9]; ++i) ans.push_back('s');

    cout << ans << endl;
    return 0;
}
