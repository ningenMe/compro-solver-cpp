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

vector<long long> NBase(long long X,long long N) {
    assert(abs(N)>1);
    vector<long long> res;
    while(1) {
        long long b = (X%abs(N)+abs(N)) % abs(N);
        res.push_back(b);
        (X -= b) /= N;
        if(X==0) break;
    }
    return res;
}

string solve(ll X,ll Y){
    ll U = (X+Y);
    ll V = (X-Y);
    string res = "";
    for(int i = 40; 0 <= i; --i) {
        ll E = (U+(1LL<<i)-1)/2;
        ll F = (V+(1LL<<i)-1)/2;
        if(E<0 || F<0) continue;
        auto A = NBase(E,2);
        auto B = NBase(F,2);
        int M = max(A.size(),B.size());
        while(A.size()<40) A.push_back(0);
        while(B.size()<40) B.push_back(0);
        string S = "";
        for(int j = 0; j < 40; ++j){
            if(A[j] &&  B[j]) S.push_back('E');
            if(A[j] && !B[j]) S.push_back('N');
            if(!A[j] &&!B[j]) S.push_back('W');
            if(!A[j] && B[j]) S.push_back('S');
        }
        ll C = 0, D = 0;
        for(int j = 0; j < S.size(); ++j){
            if(S[j]=='E') C += (1LL<<j);
            if(S[j]=='N') D += (1LL<<j);
            if(S[j]=='W') C -= (1LL<<j);
            if(S[j]=='S') D -= (1LL<<j);
            if(C == X && D == Y) res = S.substr(0,j+1);
        }
    }
    return res;
}

int main() {
    SPEED
    int T; cin >> T;
    for(int t = 1; t <= T; ++t) {
        ll X,Y; cin >> X >> Y;
        string ans = "";
        if((abs(X)+abs(Y))%2==0) {
            ans = "IMPOSSIBLE";
        }
        else{
            ans = solve(X,Y);
        }
        cout << "Case #" << t << ": " << ans << endl;  
    }
    return 0;
}
