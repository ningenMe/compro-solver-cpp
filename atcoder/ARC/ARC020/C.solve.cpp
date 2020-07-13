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

//Matrix_Repeated_Multiplication_Mod O((N^3)(logK))
vector<vector<long long>> Matrix_Repeated_Multiplication_Mod(vector<vector<long long>> mat, long long K, long long mod) {
    int N = mat.size();
    vector<vector<long long>> res(N, vector<long long>(N)), tmp(N, vector<long long>(N));

    for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) res[i][j] = (i == j);
    for (; K > 0; K /= 2) {
        if (K & 1) {
            for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) tmp[i][j] = 0;
            for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) for (int k = 0; k < N; ++k) (tmp[i][j] += (mat[i][k] * res[k][j]) % mod) %= mod;
            res = tmp;
        }
        for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) tmp[i][j] = 0;
        for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) for (int k = 0; k < N; ++k) (tmp[i][j] += (mat[i][k] * mat[k][j]) % mod) %= mod;
        mat = tmp;
    }
    return res;
}

//Pow_Mod O(log(n))
long long PowMod(long long x, long long n, long long mod) {
    long long res = 1;
    x %= mod;
    for (; n > 0; n >>= 1, (x *= x) %= mod) if (n & 1) (res *= x) %= mod;
    return res;
}

int main() {
    int N; cin >> N;
    vector<ll> A(N),L(N);
    for(int i = 0; i < N; ++i) cin >> A[i] >> L[i];
    ll B; cin >> B;
    ll base=1;
    auto mat=multivector(2,2,0LL);
    mat[0]={1,0};
    mat[1]={0,0};
    ll ans = 0;
    for(int i = N-1; 0 <= i; --i) {
        ll M=to_string(A[i]).size();
        auto X=mat;
        X[0][1]=X[1][1]=PowMod(10,M,B);
        X=Matrix_Repeated_Multiplication_Mod(X,L[i]-1,B);
        ll S = (X[0][0]+X[0][1])%B;
        ll T = (X[1][0]+X[1][1])%B;
        (T *= PowMod(10,M,B)) %= B;
        (S *= A[i]) %= B;
        (S *= base) %= B;
        (ans += S) %= B;
        (base *= T) %= B;
    }
    cout << ans << endl;
    return 0;
}
