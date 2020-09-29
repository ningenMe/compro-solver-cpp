#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define ALL(obj) (obj).begin(),(obj).end()
template<class T> using priority_queue_reverse = priority_queue<T,vector<T>,greater<T>>;

constexpr long long MOD = 1'000'000'000LL + 7;
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

/*
 * @title Distance - 距離
 * @docs md/geometory/Distance.md
 */
template<class T> class Distance{
public:
    //Euclidean distance
    inline static constexpr T euclid(const T& x1, const T& y1, const T& x2, const T& y2) {
        return sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
    }
    //Chebyshev distance
    inline static constexpr T chebyshev(T x1, T y1, T x2, T y2) {
        return max(abs(x1 - x2),abs(y1 - y2));
    }
    //Manhattan distance
    inline static constexpr T manhattan(T x1, T y1, T x2, T y2) {
        return abs(x1 - x2)+abs(y1 - y2);
    }
    inline static constexpr T between_point_and_line(const T& x,const T& y,const T& x1,const T& y1,const T& x2,const T& y2){
        return abs((y2 - y1)*x+(x1 - x2)*y-(y2-y1)*x1+(x2-x1)*y1)/sqrt((y2 - y1)*(y2 - y1)+(x1 - x2)*(x1 - x2));
    }
};

int main() {
    cin.tie(0);ios::sync_with_stdio(false);
    int N,W,H; cin >> N >> W >> H;
    vector<int> x(N),y(N);
    for(int i=0;i<N;++i) cin >> x[i] >> y[i];
    using D = Distance<double>;
    int ans = 0;
    double eps = 1e-7;
    for(int i=0;i<N;++i) {
        for(int j=0;j<N;++j) {
            if(i==j) continue;
            for(int k=0;k<N;++k) {
                if(i==k||j==k) continue;
                for(int l=0;l<N;++l) {
                    if(i==l||j==l|k==l) continue;
                    double d1 = D::euclid(x[i],y[i],x[j],y[j]);
                    double d2 = D::euclid(x[k],y[k],x[l],y[l]);
                    if(x[i]-d1<-eps || W+eps<x[i]+d1 || y[i]-d1<-eps || H+eps<y[i]+d1) continue;
                    if(x[k]-d2<-eps || W+eps<x[k]+d2 || y[k]-d2<-eps || H+eps<y[k]+d2) continue;
                    double d3 = D::euclid(x[i],y[i],x[k],y[k]);
                    if(d1 < d3 + d2 + eps) continue;
                    ans++;
                }
            }
        }
    }
    cout << ans << endl;
    return 0;
}
