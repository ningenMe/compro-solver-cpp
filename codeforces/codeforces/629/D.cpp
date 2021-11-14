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

void pp(vector<int> C){
    cout << *max_element(ALL(C)) << endl;
    for(int e: C) cout << e << " ";
    cout << endl;    
}
int main() {
    SPEED
    int t; cin >> t;
    while(t--){
        int N; cin >> N;
        vector<int> A(N),C(N,1);
        for(int i = 0; i < N; ++i) cin >> A[i];
        int flg = 1;
        for(int i = 1; i < N; ++i) if(A[i] != A[i-1]) flg = 0;
        if(flg) {
            pp(C);
            continue;
        }
        for(int i = 0; i < N; ++i) C[i] = 1 + (i&1);
        
        if(N%2==0) {
            pp(C);
            continue;
        }

        flg = 0;
        for(int i = 0; i < N; ++i) if(A[i] == A[(i+1)%N]) flg = 1;

        if(!flg){
            C[0] = 3;
            pp(C);
            continue;
        }

        int idx;
        for(int i = 0; i < N; ++i) if(A[i] == A[(i+1)%N]) idx = i;
        for(int i = 0; i < N; ++i) C[i] = -1;
        C[idx] = C[(idx+1)%N] = 1;
        for(int i = (idx + 2) % N; C[i] == -1; (i += 1) %= N ) C[i] = (C[(i-1+N)%N]==1?2:1);
        pp(C); 
    }    

    return 0;
}
