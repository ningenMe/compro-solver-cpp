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
    int N; cin >> N;
    vector<string> vs(N);
    for(int i=0;i<N;++i) cin >> vs[i];
    vector<int> y(5),x(5);
    y[0]=N-1,x[0]=N-3;
    y[1]=N-2,x[1]=N-2;
    y[2]=N-3,x[2]=N-1;
    y[3]=N-1,x[3]=N-2;
    y[4]=N-2,x[4]=N-1;
    vector<int> u(5);
    {
        for(int j=0;j<5;++j) u[j]=(vs[y[j]][x[j]]=='1');
    }
    for(int i=0;i<(1<<5);++i) {
        vector<int> v(5);
        for(int j=0;j<5;++j) v[j]=((i>>j)&1);
        if(!(v[0]==v[1]&&v[1]==v[2]&&v[2]!=v[3]&&v[3]==v[4])) continue;
        vector<int> ans;
        for(int j=0;j<5;++j) {
            if(v[j]!=u[j]) ans.push_back(j);
        }
        if(ans.size()<=2) {
            cout << ans.size() << endl;
            for(int j:ans) cout << y[j]+1 << " " << x[j]+1 << endl;
            return;
        }
    }
}
int main() {
    cin.tie(0);ios::sync_with_stdio(false);
    int T; cin >> T;
    while(T--) {
        solve();
    }
    return 0;
}
