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

template<class T> class RectangleOverlapsWeight{
    int H,W;
    vector<tuple<int,int,int,int,T>> query;
    vector<T> grid;
public:
    RectangleOverlapsWeight(int H,int W):H(H),W(W),grid(H*W){
    }
    //[y1,y2)*[x1,x2)の矩形、均質重みw
    void make_query(int y1,int x1,int y2,int x2,T w=1) {
        query.emplace_back(y1,x1,y2,x2,w);
    }
    void solve() {
        for(const auto& q:query) {
            int y1 = std::get<0>(q);
            int x1 = std::get<1>(q);
            int y2 = std::get<2>(q);
            int x2 = std::get<3>(q);
            T   w  = std::get<4>(q);
            grid[y1*W+x1] += w;
            grid[y1*W+x2] -= w;
            grid[y2*W+x1] -= w;
            grid[y2*W+x2] += w;
        }
        for(int y=0;y<H;++y) {
            for(int x=0;x+1<W;++x) {
                grid[y*W+x+1] += grid[y*W+x];
            }
        }
        for(int x=0;x<W;++x) {
            for(int y=0;y+1<H;++y) {
                grid[(y+1)*W+x] += grid[y*W+x];
            }
        }
    }
    T get(int y,int x) {
        return grid[y*W+x];
    }
};

int main() {
    cin.tie(0);ios::sync_with_stdio(false);
    int N; cin >> N;
    int L = 1010;
    RectangleOverlapsWeight<int> rol(L,L);
    while(N--) {
        int x1,y1,x2,y2; cin >> x1 >> y1 >> x2 >> y2;
        rol.make_query(y1,x1,y2,x2,1);
    }
    rol.solve();
    int ans = 0;
    for(int i=0;i<L;++i) for(int j=0;j<L;++j) chmax(ans,rol.get(i,j));
    cout << ans << endl;
    return 0;
}
