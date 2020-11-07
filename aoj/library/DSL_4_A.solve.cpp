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

template<class T> class Zarts{
    vector<T> value;
    map<T,int> key;
    size_t sz;
public:
    vector<T> compressed;
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

int main() {
    cin.tie(0);ios::sync_with_stdio(false);
    int N; cin >> N;
    vector<ll> x(N*2),y(N*2);
    for(int i=0;i<N;++i) {
        cin >> x[i*2+0];
        cin >> y[i*2+0];
        cin >> x[i*2+1];
        cin >> y[i*2+1];
    }
    Zarts<ll> Zx(x),Zy(y);
    auto grid = multivector(Zy.size(),Zx.size(),0LL);
    for(int i=0;i<N;++i) {
        ll x1=Zx.compressed[i*2+0],y1=Zy.compressed[i*2+0],x2=Zx.compressed[i*2+1],y2=Zy.compressed[i*2+1];
        grid[y1][x1]++;
        grid[y1][x2]--;
        grid[y2][x1]--;
        grid[y2][x2]++;
    }    
    for(int i=0;i<Zy.size();++i) {
        for(int j=1;j<Zx.size();++j) {
            grid[i][j] += grid[i][j-1];
        }
    }
    for(int j=0;j<Zx.size();++j) {
        for(int i=1;i<Zy.size();++i) {
            grid[i][j] += grid[i-1][j];
        }
    }
    ll ans = 0;
    for(int i=0;i+1<Zy.size();++i) {
        for(int j=0;j+1<Zx.size();++j) {
            if(grid[i][j]) ans += (Zy.get_value(i+1)-Zy.get_value(i))*(Zx.get_value(j+1)-Zx.get_value(j));
        }
    }
    cout << ans << endl;
    return 0;
}
