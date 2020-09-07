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
    int N;
    cin >> N;
    vector<ll> X(N),Y(N),P(N),ans(N+1,LOWINF);
    for(int i = 0; i < N; ++i) {
        cin >> X[i] >> Y[i] >> P[i];
    }
    auto vX = multivector(1<<N,N,LOWINF);
    auto vY = multivector(1<<N,N,LOWINF);
    for(int i = 0; i < (1<<N); ++i) {
        for(int j = 0; j < N; ++j) {
            if(i&(1<<j)) {
                vX[i][j]=0;                
                vY[i][j]=0;
                continue;
            }
            chmin(vX[i][j],P[j]*abs(X[j]));
            chmin(vY[i][j],P[j]*abs(Y[j]));
            for(int k = 0; k < N; ++k) {
                if(i&(1<<k)) chmin(vX[i][j],P[j]*abs(X[j]-X[k]));
                if(i&(1<<k)) chmin(vY[i][j],P[j]*abs(Y[j]-Y[k]));
            }
        }
    }
    for(int i = 0; i < (1<<N); ++i) {
        int j = (1<<N)-1;
        j ^= i;
        for(int k=j; 0 <= k; k=(k-1)&j) {
            ll sum=0;
            int bit = i|k;
            int dim = 0;
            for(int l=0; l < N; ++l) dim += bool(bit&(1<<l));
            for(int l=0; l < N; ++l) {
                if(bit&(1<<l)) continue;
                sum += min(vX[i][l],vY[k][l]);
            }
            chmin(ans[dim],sum);
            if(!k) break;
        }
    }
    for(int i = 0; i <= N; ++i) {
        cout << ans[i] << endl;
    }

    return 0;
}
