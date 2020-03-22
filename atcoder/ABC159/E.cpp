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
    SPEED
    int H,W,K; cin >> H >> W >> K;
    vector<string> S(H);
    for(int i = 0; i < H; ++i) cin >> S[i];
    ll ans = H*W+10;
    for(int i = 0; i < (1<<H); ++i) {
        vector<int> c(H);
        iota(ALL(c),0);
        ll cnt = 0;
        for(int j = 1; j < H; ++j) {
            int l = bool(i&(1<<(j-1)));
            int r = bool(i&(1<<j));
            if(l==r) c[j] = c[j-1];
            else cnt++;
        }
        vector<int> D(H,0);
        int flg2 = 0;
        for(int j = 0; j < W; ++j){
            for(int k = 0; k < H; ++k){
                D[c[k]] += (S[k][j]=='1');
            }
            int flg = 0;
            for(int k = 0; k < H; ++k){
                if(D[k]>K) flg = 1;
            }
            if(flg){
                cnt++;
                for(int k = 0; k < H; ++k){
                    D[k] = 0;
                }
                for(int k = 0; k < H; ++k){
                    D[c[k]] += (S[k][j]=='1');
                }
                for(int k = 0; k < H; ++k){
                    if(D[k]>K) {
                        flg2 = 1;
                        break;
                    }
                }
            }
            if(flg2) break;
        }
        if(flg2) continue;
        chmin(ans,cnt);
    }
    cout << ans << endl;


    return 0;
}
