#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define ALL(obj) (obj).begin(),(obj).end()
template<class T> using priority_queue_reverse = priority_queue<T,vector<T>,greater<T>>;

constexpr long long MOD = 1'000'000'000LL + 7;
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

vector<int> rec(vector<int> A,int M) {
    vector<int> ret(M+1,0LL);
    if(A.size()<=2) return ret;
    
    for(int l = 0; l+1 < A.size(); ++l) {
        if(!A[l]) continue;
        for(int r = l+1; r < A.size(); ++r) {
            if(A[r]) continue;
            int cost = r-l;
            vector<int> L;
            vector<int> R;
            for(int k = 0; k < l; ++k) L.push_back(A[k]);
            L.push_back(A[r]);
            for(int k = l+1; k < r; ++k) L.push_back(A[k]);
            for(int k = r+1; k < A.size(); ++k) R.push_back(A[k]);
            int L0=0,R0=0;
            for(auto& e:L) L0 += (1-e);
            for(auto& e:R) R0 += (1-e);
            L0 *= R0;
            auto recL = rec(L,M);
            auto recR = rec(R,M);

            for(int k = 0; k <= M; ++k) for(int m = 0; m <= M; ++m) if(k+m+cost<=M) chmax(ret[k+m+cost],recL[k]+recR[m]+L0);
        }
    }

    for(int r = A.size()-1; 0 < r; --r) {
        if(!A[r]) continue;
        for(int l = r-1; 0 <= l; --l) {
            if(A[l]) continue;
            int cost = r-l;
            vector<int> L;
            vector<int> R;
            for(int k = 0; k < l; ++k) L.push_back(A[k]);
            for(int k = l+1; k < r; ++k) R.push_back(A[k]);
            L.push_back(A[l]);
            for(int k = r+1; k < A.size(); ++k) R.push_back(A[k]);
            int L0=0,R0=0;
            for(auto& e:L) L0 += (1-e);
            for(auto& e:R) R0 += (1-e);
            L0 *= R0;
            auto recL = rec(L,M);
            auto recR = rec(R,M);

            for(int k = 0; k <= M; ++k) for(int m = 0; m <= M; ++m) if(k+m+cost<=M) chmax(ret[k+m+cost],recL[k]+recR[m]+L0);
        }
    }
    return ret;
}

int main() {
    cin.tie(0);ios::sync_with_stdio(false);
    int N; cin >> N;
    vector<int> A(N);
    for(int i = 0; i < N; ++i) cin >> A[i];
    int M = N*(N-1)/2;
    auto dp = rec(A,M);
    for(int i=0;i<=M;++i) cout << dp[i] << " \n"[i==M];
    return 0;
}
