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
 * @title RuntimeModInt - 実行時ModInt
 * @docs md/util/RuntimeModInt.md
 */
template<long long& mod> class RuntimeModInt {
public:
    long long x;
    constexpr RuntimeModInt():x(0) {}
    constexpr RuntimeModInt(long long y) : x(y>=0?(y%mod): (mod - (-y)%mod)%mod) {}
    RuntimeModInt &operator+=(const RuntimeModInt &p) {if((x += p.x) >= mod) x -= mod;return *this;}
    RuntimeModInt &operator+=(const long long y) {RuntimeModInt p(y);if((x += p.x) >= mod) x -= mod;return *this;}
    RuntimeModInt &operator+=(const int y) {RuntimeModInt p(y);if((x += p.x) >= mod) x -= mod;return *this;}
    RuntimeModInt &operator-=(const RuntimeModInt &p) {if((x += mod - p.x) >= mod) x -= mod;return *this;}
    RuntimeModInt &operator-=(const long long y) {RuntimeModInt p(y);if((x += mod - p.x) >= mod) x -= mod;return *this;}
    RuntimeModInt &operator-=(const int y) {RuntimeModInt p(y);if((x += mod - p.x) >= mod) x -= mod;return *this;}
    RuntimeModInt &operator*=(const RuntimeModInt &p) {x = (x * p.x % mod);return *this;}
    RuntimeModInt &operator*=(const long long y) {RuntimeModInt p(y);x = (x * p.x % mod);return *this;}
    RuntimeModInt &operator*=(const int y) {RuntimeModInt p(y);x = (x * p.x % mod);return *this;}
    RuntimeModInt &operator^=(const RuntimeModInt &p) {x = (x ^ p.x) % mod;return *this;}
    RuntimeModInt &operator^=(const long long y) {RuntimeModInt p(y);x = (x ^ p.x) % mod;return *this;}
    RuntimeModInt &operator^=(const int y) {RuntimeModInt p(y);x = (x ^ p.x) % mod;return *this;}
    RuntimeModInt &operator/=(const RuntimeModInt &p) {*this *= p.inv();return *this;}
    RuntimeModInt &operator/=(const long long y) {RuntimeModInt p(y);*this *= p.inv();return *this;}
    RuntimeModInt &operator/=(const int y) {RuntimeModInt p(y);*this *= p.inv();return *this;}
    RuntimeModInt operator=(const int y) {RuntimeModInt p(y);*this = p;return *this;}
    RuntimeModInt operator=(const long long y) {RuntimeModInt p(y);*this = p;return *this;}
    RuntimeModInt operator-() const {return RuntimeModInt(-x); }
    RuntimeModInt operator++() {x++;if(x>=mod) x-=mod;return *this;}
    RuntimeModInt operator--() {x--;if(x<0) x+=mod;return *this;}
    RuntimeModInt operator+(const RuntimeModInt &p) const { return RuntimeModInt(*this) += p; }
    RuntimeModInt operator-(const RuntimeModInt &p) const { return RuntimeModInt(*this) -= p; }
    RuntimeModInt operator*(const RuntimeModInt &p) const { return RuntimeModInt(*this) *= p; }
    RuntimeModInt operator/(const RuntimeModInt &p) const { return RuntimeModInt(*this) /= p; }
    RuntimeModInt operator^(const RuntimeModInt &p) const { return RuntimeModInt(*this) ^= p; }
    bool operator==(const RuntimeModInt &p) const { return x == p.x; }
    bool operator!=(const RuntimeModInt &p) const { return x != p.x; }
    RuntimeModInt inv() const {int a=x,b=mod,u=1,v=0,t;while(b > 0) {t = a / b;swap(a -= t * b, b);swap(u -= t * v, v);} return RuntimeModInt(u);}
    RuntimeModInt pow(long long n) const {RuntimeModInt ret(1), mul(x);for(;n > 0;mul *= mul,n >>= 1) if(n & 1) ret *= mul;return ret;}
    friend ostream &operator<<(ostream &os, const RuntimeModInt &p) {return os << p.x;}
    friend istream &operator>>(istream &is, RuntimeModInt &a) {long long t;is >> t;a = RuntimeModInt<mod>(t);return (is);}
};
long long runtime_mod;
// using modint = RuntimeModInt<mod>;

/*
 * @title Matrix - 行列演算
 * @docs md/math/Matrix.md
 */
template <class T, int H, int W = H> class Matrix {
public:
    int h,w;
    array<array<T,W>,H> a;
    Matrix():h(H),w(W){
        // do nothing
    }
    Matrix(const vector<vector<T>>& vec):h(H),w(W) {
        assert(vec.size()==H && vec.front().size()==W);
        for(int i = 0; i < H; ++i) for(int j = 0; j < W; ++j) a[i][j]=vec[i][j];
    }
    static Matrix E() {
        assert(H==W);
        Matrix res = Matrix();
        for(int i = 0; i < H; ++i) res[i][i]=1;
        return res;
    }
    Matrix &operator+=(const Matrix &r) {
        assert(H==r.h&&W==r.w);
        for(int i = 0; i < H; ++i) for(int j = 0; j < W; ++j) a[i][j]+=r[i][j];
        return *this;
    }
    Matrix &operator-=(const Matrix &r) {
        assert(H==r.h&&W==r.w);
        for(int i = 0; i < H; ++i) for(int j = 0; j < W; ++j) a[i][j]-=r[i][j];
        return *this;
    }
    Matrix &operator*=(const Matrix &r) {
        assert(W==r.h);
        Matrix res = Matrix();
        for(int i = 0; i < H; ++i) for(int j = 0; j < r.w; ++j) for(int k = 0; k < W; ++k) res[i][j]+=(a[i][k])*(r[k][j]);
        a.swap(res.a);
        return *this;
    }
    Matrix operator+(const Matrix& r) const {
        return Matrix(*this) += r;
    }
    Matrix operator-(const Matrix& r) const {
        return Matrix(*this) -= r;
    }
    Matrix operator*(const Matrix& r) const {
        return Matrix(*this) *= r;
    }
    inline array<T,W> &operator[](int i) {
        return a[i];
    }
    inline const array<T,W> &operator[](int i) const {
        return a[i];
    }
    Matrix pow(long long K) const {
        assert(H == W);
        Matrix x(*this);
        Matrix res = this->E();
        for (; K > 0; K /= 2) {
            if (K & 1) res *= x;
            x *= x;
        }
        return res;
    }
    T determinant(void) const {
        assert(H==W);
        Matrix x(*this);
        T res = 1;
        for(int i = 0; i < H; i++) {
            int idx = -1;
            for(int j = i; j < W; j++) if(x[j][i] != 0) idx = j;
            if(idx == -1) return 0;
            if(i != idx) {
                res *= -1;
                swap(x[i], x[idx]);
            }
            res *= x[i][i];
            T tmp = x[i][i];
            for(int j = 0; j < W; ++j) x[i][j] /= tmp;
            for(int j = i + 1; j < H; j++) {
                tmp = x[j][i];
                for(int k = 0; k < W; k++) x[j][k] -= x[i][k]*tmp;
            }
        }
        return res;
    }
};

/**
 * @url 
 * @est
 */ 
int main() {
    cin.tie(0);ios::sync_with_stdio(false);
    int64 A,X,M; cin >> A >> X >> M;
    using modint = RuntimeModInt<runtime_mod>;
    runtime_mod = M;
    Matrix<modint,2,2> ma;
    ma[0] = {1,A};
    ma[1] = {0,A};
    ma = ma.pow(X-1);
    cout << ma[0][0]+ma[0][1] << endl;

    return 0;
}
