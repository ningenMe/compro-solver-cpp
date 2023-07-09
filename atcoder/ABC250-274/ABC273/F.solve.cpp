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

/*
 * @title Zarts - 座標圧縮
 * @docs md/util/Zarts.md
 */
template<class T> class Zarts{
    vector<T> value;
    map<T,int> key;
    size_t sz;
public:
    vector<int> compressed;
    Zarts(const vector<T> & ar, int light_flag = 0, T pre=-1) : compressed(ar.size()) {
        if(!light_flag) {
            for (auto &e : ar) key[e];
            int cnt=0;
            for (auto &e : key) e.second = cnt++;
            for (int i=0;i<ar.size();++i) compressed[i]=key[ar[i]];
            value.resize(key.size());
            for (auto &e : key) value[e.second] = e.first;
            sz = cnt;
        }
        else {
            vector<pair<int,int>> ord(ar.size());
            for(int i=0;i<ar.size();++i) ord[i]={ar[i],i};
            sort(ord.begin(),ord.end());
            int cnt=-1;
            for(int i=0;i<ar.size();++i) {
                if(pre < ord[i].first) cnt++;
                compressed[ord[i].second] = cnt;
                pre = ord[i].first;
            }
            sz = cnt+1;
        }
    }
    T get_value(int key) {
        return value[key];
    }
    int get_key(T value) {
        assert(key.count(value));
        return key[value];
    }
    size_t size() {
        return sz;
    }
};

/**
 * @url 
 * @est
 */ 
int main() {
    cin.tie(0);ios::sync_with_stdio(false);
    int64 N, X; cin >> N >> X;
    vector<int64> Y(N),Z(N);
    for(int i=0;i<N;++i) cin >> Y[i];
    for(int i=0;i<N;++i) cin >> Z[i];
    vector<int64> v;
    v.push_back(0);
    v.push_back(X);
    for(int i=0;i<N;++i) v.push_back(Y[i]);
    for(int i=0;i<N;++i) v.push_back(Z[i]);

    Zarts z(v,0,-LOWINF);
    int64 M = z.size();
    vector<int> isKabe(M,0);
    for(int i=0;i<N;++i) isKabe[z.get_key(Y[i])] = 1;

    map<int64,int> W;
    for(int i=0;i<N;++i) W[Y[i]]=i;
    vector<int> hammerIndex(M,-1);
    for(int i=0;i<N;++i) {
        hammerIndex[z.get_key(Y[i])] = z.get_key(Z[W[Y[i]]]);
    }

    auto dp = multivector(M,M,2,HIGHINF);
    int s = z.get_key(0);
    
    queue<pair<int64,tuple<int,int,int>>> pq;
    dp[s][s][0] = dp[s][s][1] = 0;
    pq.push({0,{s,s,0}});
    while(pq.size()) {
        auto [pre_cost, p] = pq.front(); pq.pop();
        auto [l,r,d] = p;
        if(dp[l][r][d] < pre_cost) continue;

        int64 xc = (d == 0 ? z.get_value(l) : z.get_value(r));
        if(r+1<M) {
            int64 xr = z.get_value(r+1);
            int flg = 1;
            if (isKabe[r+1]) flg &= (l <= hammerIndex[r+1] && hammerIndex[r+1] <= r+1);
            if (flg && dp[l][r+1][1] > dp[l][r][d] + xr - xc) {
                dp[l][r+1][1] = dp[l][r][d] + xr - xc;
                pq.push({dp[l][r+1][1], {l,r+1,1}});
            }
        }
        if(0<=l-1) {
            int64 xl = z.get_value(l-1);
            int flg = 1;
            if (isKabe[l-1]) flg &= (l-1 <= hammerIndex[l-1] && hammerIndex[l-1] <= r);
            if (flg && dp[l-1][r][0] > dp[l][r][d] + xc - xl) {
                dp[l-1][r][0] = dp[l][r][d] + xc - xl;
                pq.push({dp[l-1][r][0], {l-1,r,0}});
            }
        }
    }
    int g = z.get_key(X);
    int64 ans = HIGHINF;
    for(int i=0;i<M;++i) chmin(ans,dp[i][g][0]);
    for(int i=0;i<M;++i) chmin(ans,dp[i][g][1]);
    for(int i=0;i<M;++i) chmin(ans,dp[g][i][0]);
    for(int i=0;i<M;++i) chmin(ans,dp[g][i][1]);
    if(ans == HIGHINF) ans = -1;
    cout << ans << endl;
    return 0;
}
