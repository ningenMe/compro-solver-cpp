#include <bits/stdc++.h>
using namespace std;
using int128 = __int128_t;
using int64 = long long;

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

int64 N,A,B,C,D;
vector<int64> x,acc;

int64 rec(int64 l, int64 r, int flg, vector<vector<vector<int64>>>& dp) {
    if(l==r) {
        return flg ? x[l] : -x[l];
    }
    if(dp[l][r][flg]  != HIGHINF) return dp[l][r][flg];
    if(flg) {
        int64 sum = 0;
        chmax(sum, rec(l+1,r,!flg,dp) + x[l]);
        chmax(sum, rec(l,r-1,!flg,dp) + x[r]);
        if(r-l+1<=B) {
            chmax(sum, acc[r] - acc[l-1] - A);
        }
        else {
            for(int i=l;i+B<=r;++i) {
                chmax(sum, (acc[i]-acc[l-1]) + rec(i+1, i+B, !flg, dp) + (acc[r]-acc[i+B]) - A);
            }
        }
        return dp[l][r][flg]=sum;
    }
    else {
        int64 sum = LOWINF;
        chmin(sum, -rec(l+1,r,!flg,dp) - x[l]);
        chmin(sum, -rec(l,r-1,!flg,dp) - x[r]);
        if(r-l+1<=D) {
            chmin(sum, -(acc[r] - acc[l-1]) + C);
        }
        else {
            for(int i=l;i+D<=r;++i) {
                chmin(sum, -(acc[i]-acc[l-1]) -rec(i+1, i+D, !flg, dp) -(acc[r]-acc[i+D]) + C);
            }
        }
        return dp[l][r][flg]=sum;
    }
}

/**
 * @url 
 * @est
 */ 
int main() {
    cin.tie(0);ios::sync_with_stdio(false);
    cin >> N >> A >> B >> C >> D;
    vector<int64> tmp; tmp.push_back(0);
    for(int i=1;i<=N;++i) {
        int a; cin >> a; tmp.push_back(a);
    }
    x = tmp;
    acc = tmp;
    for(int i=1;i<=N;++i) acc[i]=acc[i-1] + tmp[i-1];
    auto dp = multivector(N+1,N+1,2,HIGHINF);
    cout << rec(1,N,1,dp) << endl;
    return 0;
}
