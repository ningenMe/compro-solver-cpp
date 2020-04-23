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

ll inf = 1000000000LL, dinf = inf / 5;

void solve(){
    ll s,t;
    for(ll X = -inf; X <= inf; X += dinf){
        for(ll Y = -inf; Y <= inf; Y += dinf){
            cout << X << " " << Y << endl;
            string S; cin >> S;
            if(S=="CENTER") return;
            if(S=="HIT") s=X,t=Y;
        }
    }
    ll rok = s, rng = inf+1,rmd;
    while(abs(rng-rok)>1){
        rmd = (rok+rng)/2;
        cout << rmd << " " << t << endl;
        string S; cin >> S;
        if(S=="CENTER") return;
        (S=="HIT" ? rok:rng) = rmd;
    }
    ll lok = s, lng = -inf-1,lmd;
    while(abs(lng-lok)>1){
        lmd = (lok+lng)/2;
        cout << lmd << " " << t << endl;
        string S; cin >> S;
        if(S=="CENTER") return;
        (S=="HIT" ? lok:lng) = lmd;
    }
    ll uok = s, ung = inf+1,umd;
    while(abs(ung-uok)>1){
        umd = (uok+ung)/2;
        cout << s << " " << umd << endl;
        string S; cin >> S;
        if(S=="CENTER") return;
        (S=="HIT" ? uok:ung) = umd;
    }
    ll dok = s, dng = -inf-1,dmd;
    while(abs(dng-dok)>1){
        dmd = (dok+dng)/2;
        cout << s << " " << dmd << endl;
        string S; cin >> S;
        if(S=="CENTER") return;
        (S=="HIT" ? dok:dng) = dmd;
    }
    cout << (rok+lok)/2 << " " << (uok+dok)/2 << endl;
    string S; cin >> S;
    if(S=="CENTER") return;
}

int main() {
    SPEED
    ll T,A,B; cin >> T >> A >> B;
    for(int t = 1; t <= T; ++t) {
        solve();
    }
    return 0;
}
