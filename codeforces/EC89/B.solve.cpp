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

//Seat Pressure O(NlogN)
template<class T> vector<int> Zarts(const vector<T> & ar, int cnt = 0) {
    vector<int> res;
    map<T, int> mp;
    for (auto &e : ar) mp[e] = 0;
    for (auto &e : mp) e.second = cnt++;
    for (auto &e : ar) res.push_back(mp[e]);
    return res;
}

//verify https://atcoder.jp/contests/abc036/tasks/abc036_c

int main() {
    SPEED
    int t; cin >> t;
    while(t--){
        ll N,M,X;
        cin >> N >> X >> M;
        vector<ll> B(2*M+1);
        B[2*M]=X;
        for(int i = 0; i < M; ++i) {
            cin >> B[i] >> B[i+M];
        }
        auto Z = Zarts(B);
        int Y = *max_element(ALL(Z))+1;
        vector<int> C(Y,0);
        C[Z.back()]++;
        map<ll,int> mp;
        for(int i = 0; i < 2*M; ++i) mp[Z[i]]=B[i];
        for(int i = 0; i < M; ++i) {
            int L = Z[i],R = Z[i+M];
            int maxi = 0;
            for(int j = L; j <= R; ++j) chmax(maxi,C[j]);
            for(int j = L; j <= R; ++j) C[j]=maxi;
        }
        int s,g;
        for(int i = 0; i < Y; ++i) if(C[i]) g = i;
        for(int i = Y-1; 0 <= i; --i) if(C[i]) s = i;
        cout << mp[g]-mp[s]+1 << endl;
    }

    return 0;
}
