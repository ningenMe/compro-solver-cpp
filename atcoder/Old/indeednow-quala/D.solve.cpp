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
    SPEED
    int H,W; 
    cin >> H >> W;
    vector<int> a(H*W),b(H*W);
    vector<pair<int,int>> p(H*W);
    for(int i = 0; i < H; ++i) {
        for(int j = 0; j < W; ++j) {
            cin >> a[i*W+j];
            b[i*W+j]=(i*W+j+1)%(H*W);
            p[b[i*W+j]]={i,j};
        }
    }
    map<vector<int>,int> dp;
    PQR<pair<int,vector<int>>> q;
    int init_cost=0;
    for(int i = 0; i < H; ++i) {
        for(int j = 0; j < W; ++j) {
            if(a[i*W+j])init_cost+=abs(p[a[i*W+j]].first-i)+abs(p[a[i*W+j]].second-j);
        }
    }
    dp[a]=0;
    q.push({init_cost,a});
    while (q.size()){
        auto v = q.top().second;
        q.pop();
        if(v==b) break;
        int cost = dp[v];
        int from = min_element(ALL(v))-v.begin();
        int to;
        int y = from/W, x = from%W;
        if(y+1<H) {
            to=(y+1)*W+x;
            swap(v[from],v[to]);
            if(!dp.count(v) || dp[v]>cost+1) {
                dp[v]=cost+1;
                int acost=0;
                for(int i = 0; i < H; ++i) {
                    for(int j = 0; j < W; ++j) {
                        if(v[i*W+j])acost+=abs(p[v[i*W+j]].first-i)+abs(p[v[i*W+j]].second-j);
                    }
                }
                q.push({acost+cost+1,v});
            }
            swap(v[from],v[to]);
        }
        if(0<=y-1) {
            to=(y-1)*W+x;
            swap(v[from],v[to]);
            if(!dp.count(v) || dp[v]>cost+1) {
                dp[v]=cost+1;
                int acost=0;
                for(int i = 0; i < H; ++i) {
                    for(int j = 0; j < W; ++j) {
                        if(v[i*W+j])acost+=abs(p[v[i*W+j]].first-i)+abs(p[v[i*W+j]].second-j);
                    }
                }
                q.push({acost+cost+1,v});
            }
            swap(v[from],v[to]);
        }
        if(x+1<W) {
            to=y*W+x+1;
            swap(v[from],v[to]);
            if(!dp.count(v) || dp[v]>cost+1) {
                dp[v]=cost+1;
                int acost=0;
                for(int i = 0; i < H; ++i) {
                    for(int j = 0; j < W; ++j) {
                        if(v[i*W+j])acost+=abs(p[v[i*W+j]].first-i)+abs(p[v[i*W+j]].second-j);
                    }
                }
                q.push({acost+cost+1,v});
            }
            swap(v[from],v[to]);
        }
        if(0<=x-1) {
            to=y*W+x-1;
            swap(v[from],v[to]);
            if(!dp.count(v) || dp[v]>cost+1) {
                dp[v]=cost+1;
                int acost=0;
                for(int i = 0; i < H; ++i) {
                    for(int j = 0; j < W; ++j) {
                        if(v[i*W+j])acost+=abs(p[v[i*W+j]].first-i)+abs(p[v[i*W+j]].second-j);
                    }
                }
                q.push({acost+cost+1,v});
            }
            swap(v[from],v[to]);
        }
    }
    cout << dp[b] << endl;   

    return 0;
}
