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
void print(void) {cout << endl;}
template <class Head> void print(Head&& head) {cout << head;print();}
template <class Head, class... Tail> void print(Head&& head, Tail&&... tail) {cout << head << " ";print(forward<Tail>(tail)...);}
template <class T> void chmax(T& a, const T b){a=max(a,b);}
template <class T> void chmin(T& a, const T b){a=min(a,b);}
std::vector<std::string> split(const std::string &str, const char delemiter) {std::vector<std::string> res;std::stringstream ss(str);std::string buffer; while( std::getline(ss, buffer, delemiter) ) res.push_back(buffer); return res;}
int msb(int x) {return x?31-__builtin_clz(x):-1;}
void YN(bool flg) {cout << (flg ? "YES" : "NO") << endl;}
void Yn(bool flg) {cout << (flg ? "Yes" : "No") << endl;}
void yn(bool flg) {cout << (flg ? "yes" : "no") << endl;}

int main() {
    int N; cin >> N;
    vector<int> X(N),Y(N);
    vector<char> U(N);
    for(int i = 0; i < N; ++i) cin >> X[i] >> Y[i] >> U[i];
    map<ll,map<char,set<int>>> mv1,mv2,mv3,mv4;
    for(int i = 0; i < N; ++i) if(U[i]=='U'||U[i]=='D') mv1[X[i]][U[i]].insert(Y[i]);
    for(int i = 0; i < N; ++i) if(U[i]=='L'||U[i]=='R') mv2[Y[i]][U[i]].insert(X[i]);
    for(int i = 0; i < N; ++i) mv3[X[i]+Y[i]][U[i]].insert(X[i]);
    for(int i = 0; i < N; ++i) mv4[X[i]-Y[i]][U[i]].insert(X[i]);
    int ans = 12345678;
    for(auto& m:mv1) {
        auto& u=m.second['U'];
        auto& d=m.second['D'];
        for(auto& e:u) {
            auto itr=d.lower_bound(e);
            if(itr!=d.end()) chmin(ans,abs(*itr-e)*5);
        }
    }
    for(auto& m:mv2) {
        auto& r=m.second['R'];
        auto& l=m.second['L'];
        for(auto& e:r) {
            auto itr=l.lower_bound(e);
            if(itr!=l.end()) chmin(ans,abs(*itr-e)*5);
        }
    }
    for(auto& m:mv3) {
        auto& u=m.second['R'];
        auto& d=m.second['U'];
        for(auto& e:u) {
            auto itr=d.lower_bound(e);
            if(itr!=d.end()) chmin(ans,abs(*itr-e)*10);
        }
    }
    for(auto& m:mv3) {
        auto& u=m.second['D'];
        auto& d=m.second['L'];
        for(auto& e:u) {
            auto itr=d.lower_bound(e);
            if(itr!=d.end()) chmin(ans,abs(*itr-e)*10);
        }
    }
    for(auto& m:mv4) {
        auto& u=m.second['R'];
        auto& d=m.second['D'];
        for(auto& e:u) {
            auto itr=d.lower_bound(e);
            if(itr!=d.end()) chmin(ans,abs(*itr-e)*10);
        }
    }
    for(auto& m:mv4) {
        auto& u=m.second['U'];
        auto& d=m.second['L'];
        for(auto& e:u) {
            auto itr=d.lower_bound(e);
            if(itr!=d.end()) chmin(ans,abs(*itr-e)*10);
        }
    }
    if(ans==12345678) {
        cout << "SAFE" << endl;
    }
    else{
        cout << ans << endl;
    }
    return 0;
}
