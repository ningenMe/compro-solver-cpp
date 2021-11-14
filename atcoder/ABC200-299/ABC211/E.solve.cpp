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

/**
 * @url 
 * @est
 */ 
int main() {
    cin.tie(0);ios::sync_with_stdio(false);
    int N,K;
    cin >> N >> K;
    vector<string> VS(N);
    for(int i=0;i<N;++i) cin >> VS[i];
    set<uint64> dp,tp;
    {
        for(int i=0;i<N;++i) {
            for(int j=0;j<N;++j) {
                uint64 k = i*N+j;
                if(VS[i][j]=='.') {
                    dp.insert(1ul<<k);
                }
            }
        }
    }
    for(int n=1;n<K;++n) {
        tp.clear();
        for(uint64 bit:dp) {
            auto a = multivector(N,N,0);
            for(int i=0;i<N;++i) {
                for(int j=0;j<N;++j) {
                    uint64 k = i*N+j;
                    if(bit & (1ul << k)) a[i][j]=1;
                }
            }
            for(int i=0;i<N;++i) {
                for(int j=0;j<N;++j) {
                    uint64 k = i*N+j;
                    int flg = 0;
                    if(a[i][j]) continue;
                    if(VS[i][j]=='#') continue;
                    if(i+1<N &&a[i+1][j]) flg = 1;
                    if(0<=i-1&&a[i-1][j]) flg = 1;
                    if(j+1<N &&a[i][j+1]) flg = 1;
                    if(0<=j-1&&a[i][j-1]) flg = 1;
                    if(flg) {
                        tp.insert(bit ^ (1ul<<k));
                    }
                }
            }
        }
        dp = tp;
    }
    cout << dp.size() << endl;
    return 0;
}
