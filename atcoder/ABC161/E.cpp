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
    ll N,K,C; cin >> N >> K >> C;
    string S; cin >> S;
    if(C==0) {
        int cnt = 0;
        for(int i = 0; i < N; ++i) if(S[i]=='o') cnt++;
        corner(cnt!=K,"");
        for(int i = 0; i < N; ++i) if(S[i]=='o') cout << i+1 << endl;
        return 0;
    }
    if(N==1){
        if(S[0]=='o') cout << 1 << endl;
        return 0;
    }
    S = "x" + S;
    vector<ll> dpR(2*N+1,0),dpL(2*N+1,0);
    for(int i = N; 0 <= i; --i){
        if(S[i]=='o') chmax(dpR[i],dpR[i+C+1]+1);
        chmax(dpR[i],dpR[i+1]);
    }    
    for(int i = 1; i <= N; ++i){
        if(S[i]=='o') chmax(dpL[i+C],dpL[i-1]+1);
        chmax(dpL[i],dpL[i-1]);
    }
    corner(*max_element(ALL(dpL)) > K,"");
    corner(*max_element(ALL(dpR)) > K,"");
    map<pair<int,int>,vector<int>> mv;
    for(int i = 1; i <= N; ++i) {
        if(S[i] != 'o') continue;
        if(dpL[i-1]+dpR[i+C+1]==K-1) {
            mv[{dpL[i-1],dpR[i+C+1]}].push_back(i);
        }
    }
    for(auto& v:mv) if(v.second.size()==1) cout << v.second.front() << endl;

    return 0;
}
