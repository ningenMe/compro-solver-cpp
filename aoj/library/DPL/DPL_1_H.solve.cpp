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

int main() {
    cin.tie(0);ios::sync_with_stdio(false);
    ll N,W; cin >> N >> W;
    vector<ll> v(N),w(N);
    for(int i=0;i<N;++i) cin >> v[i] >> w[i];
    corner(N==1,v[0]*(w[0]<=W));
    int L = N/2;
    int R = N - L;
    vector<ll> lv,lw,rv,rw;
    for(int i=0;i<N;++i) {
        (i<L?lv:rv).push_back(v[i]);
        (i<L?lw:rw).push_back(w[i]);
    }
    vector<pair<ll,ll>> dpl(1<<L),dpr(1<<R);
    for(int i=1;i<(1<<L);++i) {
        int j=msb(i);
        dpl[i].first =dpl[i^(1<<j)].first +lw[j];
        dpl[i].second=dpl[i^(1<<j)].second+lv[j];
    }
    for(int i=1;i<(1<<R);++i) {
        int j=msb(i);
        dpr[i].first =dpr[i^(1<<j)].first +rw[j];
        dpr[i].second=dpr[i^(1<<j)].second+rv[j];
    }
    sort(ALL(dpr));
    vector<ll> dpwr,dpvr;
    for(auto p:dpr) dpwr.push_back(p.first),dpvr.push_back(p.second);
    dpwr.push_back(HIGHINF),dpvr.push_back(HIGHINF);
    for(int i=1;i<dpvr.size();++i) chmax(dpvr[i],dpvr[i-1]);
    ll ans = 0;
    for(auto& p:dpl) {
        if(p.first>W) continue;
        ll x = W - p.first;
        ll ul = p.second;
        int i = (upper_bound(ALL(dpwr),x)-dpwr.begin()) - 1;
        ll ur = dpvr[i];
        chmax(ans,ul+ur);
    }
    cout << ans << endl;
    return 0;
}
