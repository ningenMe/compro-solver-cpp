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
    int N,W,C; cin >> N >> W >> C;
    int M=50;
    vector<vector<pair<int,int>>> vvp(51);
    for(int i=0;i<N;++i){
        int w,v,c; cin >> w >> v >> c;
        vvp[c].emplace_back(w,v);
    }
    auto dp=multivector(M+1,W+1,-6000000);
    dp[0][0]=0;
    int ans=0;
    for(int i=1; i <= 50; ++i){
        auto& vp=vvp[i];
        auto tp1=multivector(M+1,W+1,-6000000);
        auto tp2=multivector(M+1,W+1,-6000000);
        for(auto& p:vp){
            int w=p.first,v=p.second;
            for(int j=M; 0<=j; --j){
                for(int k=W; 0<=k; --k) {
                    if(j+1<=M&&k+w<=W) chmax(tp1[j+1][k+w],dp[j][k]+v);
                    if(k+w<=W) chmax(tp1[j][k+w],tp1[j][k]+v);
                    chmax(tp2[j][k],dp[j][k]);
                }
            }
        }
        {
            for(int j=M; 0<=j; --j){
                for(int k=W; 0<=k; --k) {
                    chmax(dp[j][k],tp1[j][k]);
                    chmax(dp[j][k],tp2[j][k]);
                    if(j<=C)chmax(ans,dp[j][k]);
                }
            }
        }
    }
    cout << ans << endl;
    return 0;
}
