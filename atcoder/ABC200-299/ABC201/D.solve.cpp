#include <bits/stdc++.h> 
using namespace std; 
using int128  = __int128_t; 
using int64   = long long; 
using int32   = int; 
using uint128 = __uint128_t; 
using uint64  = unsigned long long; 
using uint32  = unsigned int; 

#define ALL(obj) (obj).begin(),(obj).end() 
template<class T> using priority_queue_reverse = priority_queue<T,vector<T>,greater<T>>; 

constexpr int64 MOD = 1'000'000'000LL + 7; //' 
constexpr int64 MOD2 = 998244353; 
constexpr int64 HIGHINF = 1'000'000'000'000'000'000LL; 
constexpr int64 LOWINF = 1'000'000'000'000'000LL; //' 
constexpr long double PI = 3.1415926535897932384626433L; 

template <class T> vector<T> multivector(size_t N,T init){return vector<T>(N,init);} 
template <class... T> auto multivector(size_t N,T... t){return vector<decltype(multivector(t...))>(N,multivector(t...));} 
template <class T> void corner(bool flg, T hoge) {if (flg) {cout << hoge << endl; exit(0);}} 
template <class T, class U>ostream &operator<<(ostream &o, const map<T, U>&obj) {o << "{"; for (auto &x : obj) o << " {" << x.first << " : " << x.second << "}" << ","; o << " }"; return o;} 
template <class T>ostream &operator<<(ostream &o, const set<T>&obj) {o << "{"; for (auto itr = obj.begin(); itr != obj.end(); ++itr) o << (itr != obj.begin() ? ", " : "") << *itr; o << "}"; return o;} 
template <class T>ostream &operator<<(ostream &o, const multiset<T>&obj) {o << "{"; for (auto itr = obj.begin(); itr != obj.end(); ++itr) o << (itr != obj.begin() ? ", " : "") << *itr; o << "}"; return o;} 
template <class T>ostream &operator<<(ostream &o, const vector<T>&obj) {o << "{"; for (int i = 0; i < (int)obj.size(); ++i)o << (i > 0 ? ", " : "") << obj[i]; o << "}"; return o;} 
template <class T>ostream &operator<<(ostream &o, const deque<T>&obj) {o << "{"; for (int i = 0; i < (int)obj.size(); ++i)o << (i > 0 ? ", " : "") << obj[i]; o << "}"; return o;} 
template <class T, class U>ostream &operator<<(ostream &o, const pair<T, U>&obj) {o << "{" << obj.first << ", " << obj.second << "}"; return o;} 
void print(void) {cout << endl;} 
template <class Head> void print(Head&& head) {cout << head;print();} 
template <class Head, class... Tail> void print(Head&& head, Tail&&... tail) {cout << head << " ";print(forward<Tail>(tail)...);} 
template <class T> void chmax(T& a, const T b){a=max(a,b);} 
template <class T> void chmin(T& a, const T b){a=min(a,b);} 
vector<string> split(const string &str, const char delemiter) {vector<string> res;stringstream ss(str);string buffer; while( getline(ss, buffer, delemiter) ) res.push_back(buffer); return res;} 
inline constexpr int msb(int x) {return x?31-__builtin_clz(x):-1;} 
inline constexpr int64 ceil_div(const int64 a,const int64 b) {return (a+(b-1))/b;}// return ceil(a/b) 
void YN(bool flg) {cout << (flg ? "YES" : "NO") << endl;} 
void Yn(bool flg) {cout << (flg ? "Yes" : "No") << endl;} 
void yn(bool flg) {cout << (flg ? "yes" : "no") << endl;} 

int get_point(char c) {
    return (c=='+'?1:-1);
}

/** 
 * @url  
 * @est 
 */  
int main() { 
    cin.tie(0);ios::sync_with_stdio(false); 
    int H,W; 
    cin >> H >> W;
    vector<string> A(H);
    auto dp = multivector(H,W,0);
    for(int i=0;i<H;++i) cin >> A[i];
    int inf = 12345678;
    for(int i=H-1;0<=i;--i) {
        for(int j=W-1;0<=j;--j) {
            if(i==H-1 && j==W-1) continue;
            if((i+j) % 2 == 0) {
                int cnt = -inf;
                if(i+1<H) chmax(cnt,get_point(A[i+1][j]) + dp[i+1][j]);
                if(j+1<W) chmax(cnt,get_point(A[i][j+1]) + dp[i][j+1]);
                dp[i][j] = cnt;
            }
            if((i+j) % 2 == 1) {
                int cnt = inf;
                if(i+1<H) chmin(cnt,-get_point(A[i+1][j]) + dp[i+1][j]);
                if(j+1<W) chmin(cnt,-get_point(A[i][j+1]) + dp[i][j+1]);
                dp[i][j] = cnt;
            }
        }
    }
    string ans = "Draw";
    if(dp[0][0] > 0) ans = "Takahashi";
    if(dp[0][0] < 0) ans = "Aoki";
    cout << ans << endl;
    return 0; 
} 