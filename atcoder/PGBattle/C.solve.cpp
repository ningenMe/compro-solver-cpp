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

int main() {
    cin.tie(0);ios::sync_with_stdio(false);
    int H,W; cin >> H >> W;
    int sy,sx,gy,gx; cin >> sy >> sx >> gy >> gx;
    int inf = 12345678;

    vector<string> grid(H+2);
    grid[0]=string(W+2,'#');
    for(int i=1;i<=H;++i) {
        string S; cin >> S;
        grid[i]="#"+S+"#";
    }
    grid[H+1]=string(W+2,'#');

    int L = W+2;
    auto dp = multivector((H+2)*L,4,inf);
    //0:up,1:right,2:down,3:left
    dp[sy*L+sx][0]=0;
    queue<pair<int,int>> q;
    q.push({sy*L+sx,0});

    while(q.size()) {
        auto from    =q.front(); q.pop();
        int from_y   =from.first/L;
        int from_x   =from.first%L;
        int from_type=from.second;

        int to_y=-1,to_x=-1,to_type=-1;
        //上
        if(from_type==0) {
            //0:up,1:right,2:down,3:left
            //3->0->1->2の順
            if     (grid[from_y][from_x-1]=='.') to_y=from_y,to_x=from_x-1,to_type=3;
            else if(grid[from_y-1][from_x]=='.') to_y=from_y-1,to_x=from_x,to_type=0;
            else if(grid[from_y][from_x+1]=='.') to_y=from_y,to_x=from_x+1,to_type=1;
            else if(grid[from_y+1][from_x]=='.') to_y=from_y+1,to_x=from_x,to_type=2;
            if(to_y!=-1&&to_x!=-1&&to_type!=-1&&dp[to_y*L+to_x][to_type]==inf) {
                dp[to_y*L+to_x][to_type]=dp[from_y*L+from_x][from_type]+1;
                q.push({to_y*L+to_x,to_type});
            }
        }
        //左
        if(from_type==3) {
            //0:up,1:right,2:down,3:left
            //2->3->0->1の順
            if     (grid[from_y+1][from_x]=='.') to_y=from_y+1,to_x=from_x,to_type=2;
            else if(grid[from_y][from_x-1]=='.') to_y=from_y,to_x=from_x-1,to_type=3;
            else if(grid[from_y-1][from_x]=='.') to_y=from_y-1,to_x=from_x,to_type=0;
            else if(grid[from_y][from_x+1]=='.') to_y=from_y,to_x=from_x+1,to_type=1;

            if(to_y!=-1&&to_x!=-1&&to_type!=-1&&dp[to_y*L+to_x][to_type]==inf) {
                dp[to_y*L+to_x][to_type]=dp[from_y*L+from_x][from_type]+1;
                q.push({to_y*L+to_x,to_type});
            }
        }
        //右
        if(from_type==1) {
            //0:up,1:right,2:down,3:left
            //0->1->2->3の順
            if     (grid[from_y-1][from_x]=='.') to_y=from_y-1,to_x=from_x,to_type=0;
            else if(grid[from_y][from_x+1]=='.') to_y=from_y,to_x=from_x+1,to_type=1;
            else if(grid[from_y+1][from_x]=='.') to_y=from_y+1,to_x=from_x,to_type=2;
            else if(grid[from_y][from_x-1]=='.') to_y=from_y,to_x=from_x-1,to_type=3;

            if(to_y!=-1&&to_x!=-1&&to_type!=-1&&dp[to_y*L+to_x][to_type]==inf) {
                dp[to_y*L+to_x][to_type]=dp[from_y*L+from_x][from_type]+1;
                q.push({to_y*L+to_x,to_type});
            }
        }
        //下
        if(from_type==2) {
            //0:up,1:right,2:down,3:left
            //1->2->3->0の順
            if     (grid[from_y][from_x+1]=='.') to_y=from_y,to_x=from_x+1,to_type=1;
            else if(grid[from_y+1][from_x]=='.') to_y=from_y+1,to_x=from_x,to_type=2;
            else if(grid[from_y][from_x-1]=='.') to_y=from_y,to_x=from_x-1,to_type=3;
            else if(grid[from_y-1][from_x]=='.') to_y=from_y-1,to_x=from_x,to_type=0;

            if(to_y!=-1&&to_x!=-1&&to_type!=-1&&dp[to_y*L+to_x][to_type]==inf) {
                dp[to_y*L+to_x][to_type]=dp[from_y*L+from_x][from_type]+1;
                q.push({to_y*L+to_x,to_type});
            }
        }
    }
    int ans = inf;
    for(int i=0;i<4;++i) chmin(ans,dp[gy*L+gx][i]);
    if(ans==inf) ans = -1;
    cout << ans << endl;
    return 0;
}
