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

void solve(){
    ll y,x; cin >> y >> x;
    vector<ll> c(7);
    for(int i=1;i<7;++i) cin >> c[i];
    auto e = multivector(7,7,0LL);
    ll inf = LOWINF;
    //      0    1    2    3    4    5    6  
    e[0] = {0   ,c[1],c[2],c[3],c[4],c[5],c[6]};
    e[1] = {c[4],0   ,c[3],inf ,inf ,inf ,c[5]};
    e[2] = {c[5],c[6],0   ,c[4],inf ,inf ,inf };
    e[3] = {c[6],inf ,c[1],0   ,c[5],inf ,inf };
    e[4] = {c[1],inf ,inf ,c[2],0   ,c[6],inf };
    e[5] = {c[2],inf ,inf ,inf ,c[3] ,0  ,c[1]};
    e[6] = {c[3],c[2],inf ,inf ,inf ,c[4],0   };

    for(int k=0;k<7;++k) for(int i=0;i<7;++i) for(int j=0;j<7;++j) chmin(e[i][j],e[i][k]+e[k][j]);
    for(int i=0;i<7;++i) c[i]=e[0][i];
    ll ans = 2LL*HIGHINF;
    // x,y
    {
        ll dx = x;
        ll dy = y;
        ll cnt = 0;
        if(dx >= 0) cnt += c[2]*abs(dx);
        else cnt += c[5]*abs(dx);
        if(dy >= 0) cnt += c[6]*abs(dy);
        else cnt += c[3]*abs(dy);
        chmin(ans,cnt);
    }
    // x,z
    {
        ll dz = x-y;
        ll dx = dz;
        ll dy = y;
        ll cnt = 0;
        if(dx >= 0) cnt += c[2]*abs(dx);
        else cnt += c[5]*abs(dx);
        if(dy >= 0) cnt += c[1]*abs(dy);
        else cnt += c[4]*abs(dy);
        chmin(ans,cnt);        
    }
    // z,y
    {
        ll dz = x-y;
        ll dy = y + dz;
        ll cnt = 0;
        if(dz >= 0) cnt += c[3]*abs(dz);
        else cnt += c[6]*abs(dz);
        if(dy >= 0) cnt += c[1]*abs(dy);
        else cnt += c[4]*abs(dy);
        chmin(ans,cnt);        
    }
    cout << ans << endl;
}
int main() {
    cin.tie(0);ios::sync_with_stdio(false);
    int T; cin >> T;
    while(T--) {
        solve();
    }
    return 0;
}
