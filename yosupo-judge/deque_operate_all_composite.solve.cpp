#include <bits/stdc++.h>
using namespace std;
using int128 = __int128_t;
using int64 = long long;

#define ALL(obj) (obj).begin(),(obj).end()
template <class T, class U>ostream &operator<<(ostream &o, const pair<T, U>&obj) {o << "{" << obj.first << ", " << obj.second << "}"; return o;}

/*
 * @title FastIO
 * @docs md/util/FastIO.md
 */
class FastIO{
private:
    inline static constexpr int ch_0='0';
    inline static constexpr int ch_9='9';
    inline static constexpr int ch_n='-';
    inline static constexpr int ch_s=' ';
    inline static constexpr int ch_l='\n';
    inline static void endline_skip(char& ch) {
        while(ch==ch_l) ch=getchar();
    }
    template<typename T> inline static void read_integer(T &x) {
        int neg=0; char ch; x=0;
        ch=getchar();
        endline_skip(ch);
        if(ch==ch_n) neg=1,ch=getchar();
        for(;(ch_0 <= ch && ch <= ch_9); ch = getchar()) x = x*10 + (ch-ch_0);
        if(neg) x*=-1;
    }
    template<typename T> inline static void read_unsigned_integer(T &x) {
        char ch; x=0;
        ch=getchar();
        endline_skip(ch);
        for(;(ch_0 <= ch && ch <= ch_9); ch = getchar()) x = x*10 + (ch-ch_0);
    }
    inline static void read_string(string &x) {
        char ch; x="";
        ch=getchar();
        endline_skip(ch);
        for(;(ch != ch_s && ch!=ch_l); ch = getchar()) x.push_back(ch);
    }
    inline static char ar[40];
    inline static char *ch_ar;
    template<typename T> inline static void write_integer(T x) {
        ch_ar=ar;
        if(x< 0) putchar(ch_n), x=-x;
        if(x==0) putchar(ch_0);
        for(;x;x/=10) *ch_ar++=(ch_0+x%10);
        while(ch_ar--!=ar) putchar(*ch_ar);
    }
public:
    inline static void read(int &x) {read_integer<int>(x);}
    inline static void read(long long &x) {read_integer<long long>(x);}
    inline static void read(unsigned int &x) {read_unsigned_integer<unsigned int>(x);}
    inline static void read(unsigned long long &x) {read_unsigned_integer<unsigned long long>(x);}
    inline static void read(string &x) {read_string(x);}
    inline static void read(__int128_t &x) {read_integer<__int128_t>(x);}
    inline static void write(__int128_t x) {write_integer<__int128_t>(x);}
    inline static void write(char x) {putchar(x);}
};
#define read(arg) FastIO::read(arg)
#define write(arg) FastIO::write(arg)

/*
 * @title ModInt
 * @docs md/util/ModInt.md
 */
template<long long mod> class ModInt {
public:
    long long x;
    constexpr ModInt():x(0) {}
    constexpr ModInt(long long y) : x(y>=0?(y%mod): (mod - (-y)%mod)%mod) {}
    constexpr ModInt &operator+=(const ModInt &p) {if((x += p.x) >= mod) x -= mod;return *this;}
    constexpr ModInt &operator+=(const long long y) {ModInt p(y);if((x += p.x) >= mod) x -= mod;return *this;}
    constexpr ModInt &operator+=(const int y) {ModInt p(y);if((x += p.x) >= mod) x -= mod;return *this;}
    constexpr ModInt &operator-=(const ModInt &p) {if((x += mod - p.x) >= mod) x -= mod;return *this;}
    constexpr ModInt &operator-=(const long long y) {ModInt p(y);if((x += mod - p.x) >= mod) x -= mod;return *this;}
    constexpr ModInt &operator-=(const int y) {ModInt p(y);if((x += mod - p.x) >= mod) x -= mod;return *this;}
    constexpr ModInt &operator*=(const ModInt &p) {x = (x * p.x % mod);return *this;}
    constexpr ModInt &operator*=(const long long y) {ModInt p(y);x = (x * p.x % mod);return *this;}
    constexpr ModInt &operator*=(const int y) {ModInt p(y);x = (x * p.x % mod);return *this;}
    constexpr ModInt &operator^=(const ModInt &p) {x = (x ^ p.x) % mod;return *this;}
    constexpr ModInt &operator^=(const long long y) {ModInt p(y);x = (x ^ p.x) % mod;return *this;}
    constexpr ModInt &operator^=(const int y) {ModInt p(y);x = (x ^ p.x) % mod;return *this;}
    constexpr ModInt &operator/=(const ModInt &p) {*this *= p.inv();return *this;}
    constexpr ModInt &operator/=(const long long y) {ModInt p(y);*this *= p.inv();return *this;}
    constexpr ModInt &operator/=(const int y) {ModInt p(y);*this *= p.inv();return *this;}
    constexpr ModInt operator=(const int y) {ModInt p(y);*this = p;return *this;}
    constexpr ModInt operator=(const long long y) {ModInt p(y);*this = p;return *this;}
    constexpr ModInt operator-() const {return ModInt(-x); }
    constexpr ModInt operator++() {x++;if(x>=mod) x-=mod;return *this;}
    constexpr ModInt operator--() {x--;if(x<0) x+=mod;return *this;}
    constexpr ModInt operator+(const ModInt &p) const { return ModInt(*this) += p; }
    constexpr ModInt operator-(const ModInt &p) const { return ModInt(*this) -= p; }
    constexpr ModInt operator*(const ModInt &p) const { return ModInt(*this) *= p; }
    constexpr ModInt operator/(const ModInt &p) const { return ModInt(*this) /= p; }
    constexpr ModInt operator^(const ModInt &p) const { return ModInt(*this) ^= p; }
    constexpr bool operator==(const ModInt &p) const { return x == p.x; }
    constexpr bool operator!=(const ModInt &p) const { return x != p.x; }
    // ModInt inv() const {int a=x,b=mod,u=1,v=0,t;while(b > 0) {t = a / b;swap(a -= t * b, b);swap(u -= t * v, v);} return ModInt(u);}
    constexpr ModInt inv() const {int a=x,b=mod,u=1,v=0,t=0,tmp=0;while(b > 0) {t = a / b;a-=t*b;tmp=a;a=b;b=tmp;u-=t*v;tmp=u;u=v;v=tmp;} return ModInt(u);}
    constexpr ModInt pow(long long n) const {ModInt ret(1), mul(x);for(;n > 0;mul *= mul,n >>= 1) if(n & 1) ret *= mul;return ret;}
    friend ostream &operator<<(ostream &os, const ModInt &p) {return os << p.x;}
    friend istream &operator>>(istream &is, ModInt &a) {long long t;is >> t;a = ModInt<mod>(t);return (is);}
};
constexpr long long MOD_998244353 = 998244353;
constexpr long long MOD_1000000007 = 1'000'000'000LL + 7; //'

/*
 * @title SwagDeque
 * @docs md/data-structure/Swag.md
 */
template<class Operator> class SwagDeque{
public:
    using TypeNode = typename Operator::TypeNode;
    stack<pair<TypeNode,TypeNode>> pre,suf;
    stack<TypeNode> tmp;

    SwagDeque() {
        // do nothing
    }
    TypeNode fold() {
        TypeNode res = Operator::unit_node;
        if(pre.size()) res = Operator::func_node(pre.top().second,res);
        if(suf.size()) res = Operator::func_node(res,suf.top().second);
        return res;
    }
    void push_back(const TypeNode val) {
        TypeNode acc = val;
        if(suf.size()) acc = Operator::func_node(suf.top().second,val);
        suf.emplace(val,acc);
    }
    void push_front(const TypeNode val) {
        TypeNode acc = val;
        if(pre.size()) acc = Operator::func_node(val,pre.top().second);
        pre.emplace(val,acc);
    }
    void pop_back() {
        if(suf.empty()) {
            while(pre.size()>tmp.size()+1) {
                tmp.push(pre.top().first); pre.pop();
            }
            {
                TypeNode acc = Operator::unit_node;
                while(pre.size()) {
                    auto [val,_] = pre.top(); pre.pop();
                    acc = Operator::func_node(acc,val);
                    suf.emplace(val,acc);
                }
            }
            {
                TypeNode acc = Operator::unit_node;
                while(tmp.size()) {
                    TypeNode val = tmp.top(); tmp.pop();
                    acc = Operator::func_node(val,acc);
                    pre.emplace(val,acc);
                }
            }
        }
        suf.pop();
    }
    void pop_front() {
        if(pre.empty()) {
            while(suf.size()>tmp.size()+1) {
                tmp.push(suf.top().first); suf.pop();
            }
            {
                TypeNode acc = Operator::unit_node;
                while(suf.size()) {
                    auto [val,_] = suf.top(); suf.pop();
                    acc = Operator::func_node(val,acc);
                    pre.emplace(val,acc);
                }
            }
            {
                TypeNode acc = Operator::unit_node;
                while(tmp.size()) {
                    TypeNode val = tmp.top(); tmp.pop();
                    acc = Operator::func_node(acc,val);
                    suf.emplace(val,acc);
                }
            }
        }
        pre.pop();
    }
    size_t size() const {
        return pre.size()+suf.size();
    }
    bool empty() const {
        return pre.empty() && suf.empty();
    }
    void print() {
        stack<pair<TypeNode,TypeNode>> ls,rs;
        vector<pair<TypeNode,TypeNode>> lv,rv;
        while(pre.size()) {
            auto p=pre.top(); pre.pop();
            lv.push_back(p);
            ls.push(p);
        }
        while(suf.size()) {
            rs.emplace(suf.top()); suf.pop();
        }
        while(ls.size()) {
            pre.push(ls.top()); ls.pop();
        }
        while(rs.size()) {
            auto p=rs.top(); rs.pop();
            rv.push_back(p);
            suf.push(p);
        }
        cout << "{";
        for(int i=0;i<lv.size();++i) {
            cout << "{" << lv[i].first << ":" << lv[i].second << "} ";
        }
        cout << "} , {";
        for(int i=0;i<rv.size();++i) {
            cout << "{" << rv[i].first << ":" << rv[i].second << "} ";
        }
        cout << "}" << endl;
    }
};

template<class T> struct NodeGcd {
    using TypeNode = T;
    inline static constexpr TypeNode unit_node = 0;
    inline static constexpr TypeNode func_node(TypeNode l,TypeNode r){return r?func_node(r,l%r):l;}
};

template<class T> struct NodeComposite {
    using TypeNode = T;
    inline static constexpr TypeNode unit_node = {1,0};
    inline static constexpr TypeNode func_node(TypeNode l,TypeNode r){return {l.first*r.first, r.first*l.second+r.second};}
};

/**
 * @url 
 * @est
 */ 
int main() {
    cin.tie(0);ios::sync_with_stdio(false);
    int Q; read(Q);
    using modint = ModInt<MOD_998244353>;
    SwagDeque<NodeComposite<pair<modint,modint>>> swag;
    while(Q--) {
        long long q; read(q);
        if(q==0) {
            int a,b; read(a); read(b);
            swag.push_front({a,b});
        }
        if(q==1) {
            int a,b; read(a); read(b);
            swag.push_back({a,b});
        }
        if(q==2) {
            swag.pop_front();
        }
        if(q==3) {
            swag.pop_back();
        }
        if(q==4) {
            long long x; read(x);
            auto [a,b] = swag.fold();
            cout << a*x+b << "\n";
        }
    }

    return 0;
}
