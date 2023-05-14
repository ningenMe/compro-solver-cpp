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

int H,W,T;
vector<vector<int64>> vv(6, vector<int64>(6,0));
int64 ans = HIGHINF;

void dfs(vector<tuple<int,int,int,int>> vt) {
    if(vt.size() == T+1) {
        int64 maxi = 0, mini = HIGHINF;
        for(auto [y1,x1,y2,x2]:vt) {
            int64 sum = 0;
            for(int i=y1;i<=y2;++i) {
                for(int j=x1;j<=x2;++j) {
                    sum += vv[i][j];
                }
                chmax(maxi,sum);
                chmin(mini,sum);
            }
        }
        chmin(ans,maxi-mini);
        return;
    }
    for(int n=0;n<vt.size();++n) {
        auto [y1,x1,y2,x2] = vt[n];
        vector<tuple<int,int,int,int>> vt2;
        for(int k=0;k<vt.size();++k) {
                if(n==k) continue;
                vt2.push_back(vt[k]);
        }
        for(int i=y1;i+1<=y2;++i) {            
            vt2.emplace_back(y1,x1,i,x2);
            vt2.emplace_back(i+1,x1,y2,x2);
            dfs(vt2);
            vt2.pop_back();
            vt2.pop_back();
        }
        for(int j=x1;j+1<=x2;++j) {            
            vt2.emplace_back(y1,x1,y2,j);
            vt2.emplace_back(y1,j+1,y2,x2);
            dfs(vt2);
            vt2.pop_back();
            vt2.pop_back();
        }
    }
}

/**
 * @url 
 * @est
 */ 
int main() {
    cin.tie(0);ios::sync_with_stdio(false);
    cin >> H >> W >> T;
    for(int i=0;i<H;++i) {
        for(int j=0;j<W;++j) {
            cin >> vv[i][j];
        }
    }
    vector<tuple<int,int,int,int>> vt;
    vt.emplace_back(0,0,H-1,W-1);
    dfs(vt);
    cout << ans << endl;
    return 0;
}
