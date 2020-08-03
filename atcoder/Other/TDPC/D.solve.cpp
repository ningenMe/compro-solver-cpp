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

auto dp=multivector(101,60,60,60,(double)(-1));

double rec(int n,int p2,int p3, int p5) {
    if(dp[n][p2][p3][p5]>=0) return dp[n][p2][p3][p5];
    if(n==0) return dp[n][p2][p3][p5]=0;
    double sum=0;
    //1
    sum += rec(n-1,p2,p3,p5) / 6;
    //2
    sum += rec(n-1,max(p2-1,0),p3,p5) / 6;
    //3
    sum += rec(n-1,p2,max(p3-1,0),p5) / 6;
    //4
    sum += rec(n-1,max(p2-2,0),p3,p5) / 6;
    //5
    sum += rec(n-1,p2,p3,max(p5-1,0)) / 6;
    //6
    sum += rec(n-1,max(p2-1,0),max(p3-1,0),p5) / 6;
    return dp[n][p2][p3][p5]=sum;
}

int main() {
    int N; cin >> N;
    ll D; cin >> D;
    int p2=0,p3=0,p5=0;
    while(!(D%2)){
        D/=2;
        p2++;
    }
    while(!(D%3)){
        D/=3;
        p3++;
    }
    while(!(D%5)){
        D/=5;
        p5++;
    }
    corner(D!=1,0.);
    dp[0][0][0][0]=1;
    printf("%.10f",rec(N,p2,p3,p5));
    return 0;
}
