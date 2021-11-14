#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define ALL(obj) (obj).begin(),(obj).end()
template<class T> using priority_queue_reverse = priority_queue<T,vector<T>,greater<T>>;

constexpr long long MOD = 1'000'000'000LL + 7; //'
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

/**
 * @url https://atcoder.jp/contests/abc182/tasks/abc182_e 
 * @est 400
 */
int main() {
    cin.tie(0);ios::sync_with_stdio(false);
    int H,W,N,M; cin >> H >> W >> N >> M;
    auto dp1 = multivector(H,W,0);
    auto dp2 = multivector(H,W,0);
    queue<pair<int,int>> q1,q2;
    for(int i=0;i<N;++i) {
        int A,B; cin >> A >> B;
        A--,B--;
        dp1[A][B]=dp2[A][B]=1;
        q1.push({A*W+B,0});
        q1.push({A*W+B,1});
        q2.push({A*W+B,2});
        q2.push({A*W+B,3});
    }
    for(int i=0;i<M;++i) {
        int C,D; cin >> C >> D;
        C--,D--;
        dp1[C][D]=dp2[C][D]=-1;
    }
    while(q1.size()) {
        auto p = q1.front(); q1.pop();
        int y=p.first/W;
        int x=p.first%W;
        int pre = p.second;

        if(pre==0 && y+1 < H && dp1[y+1][x] == 0) {
            dp1[y+1][x]=1;
            q1.push({(y+1)*W+x,pre});
        }
        if(pre==1 && 0 < y && dp1[y-1][x] == 0) {
            dp1[y-1][x]=1;
            q1.push({(y-1)*W+x,pre});
        }
    }
    while(q2.size()) {
        auto p = q2.front(); q2.pop();
        int y=p.first/W;
        int x=p.first%W;
        int pre = p.second;

        if(pre==2 && x+1 < W && dp2[y][x+1] == 0) {
            dp2[y][x+1]=1;
            q2.push({y*W+x+1,pre});
        }
        if(pre==3 && 0 < x && dp2[y][x-1] == 0) {
            dp2[y][x-1]=1;
            q2.push({y*W+x-1,pre});
        }
    }
    int ans = 0;
    for(int i=0;i<H;++i){
        for(int j=0;j<W;++j) {
            if(dp1[i][j]==1||dp2[i][j]==1) ans++;
        }
    }
    cout << ans << endl;
    return 0;
}
