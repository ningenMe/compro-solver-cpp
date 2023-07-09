#include <iostream>
#include <vector>
#include <numeric>
#include <stack>
using namespace std;

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
 * @title DynamicSegmentTree - 非再帰抽象化動的セグメント木
 * @docs md/segment-tree/DynamicSegmentTree.md
 */
template<class Monoid> class DynamicSegmentTree {
    using TypeNode = typename Monoid::TypeNode;
    using i64 = long long;

    struct Node{
        Node *left, *right;
        TypeNode val;
        Node():left(nullptr),right(nullptr),val(Monoid::unit_node) {}
    };

    TypeNode dfs(i64 l,i64 r,i64 nl,i64 nr,Node* node) {
        if(l <= nl && nr <= r) return node->val;
        if(nr <= l || r <= nl) return Monoid::unit_node;
        TypeNode vl=Monoid::unit_node, vr=Monoid::unit_node;
        i64 m = (nl+nr)>>1;
        if(node->left)  vl = dfs(l,r,nl,m,node->left);
        if(node->right) vr = dfs(l,r,m,nr,node->right);
        return Monoid::func_fold(vl,vr);
    }

    i64 length;
    Node *root;
public:
    //unitで初期化
    DynamicSegmentTree() : length(1) {
        root = new Node();
    }
    //[idx,idx+1)
    void operate(i64 idx, const TypeNode val) {
        if(idx < 0) return;
        for (;length <= idx; length *= 2) {
            Node *new_root = new Node();
            TypeNode val = root->val;
            new_root->left = root;
            root = new_root;
            root->val = val;
        }
        Node* node = root;
        i64 l = 0, r = length, m;
		stack<Node*> st;

        while(r-l>1) {
			st.push(node);
            m = (r+l)>>1;
            if(idx<m) {
                r = m;
                if(!node->left) node->left=new Node();
                node = node->left;
            }
            else {
                l = m;
                if(!node->right) node->right = new Node();
                node = node->right;
            }
        }
        node->val = Monoid::func_operate(node->val,val);
		while(st.size()) {
			node = st.top(); st.pop();
			TypeNode vl=Monoid::unit_node, vr=Monoid::unit_node;
			if(node->left)  vl = node->left->val;
			if(node->right) vr = node->right->val;
			node->val = Monoid::func_fold(vl,vr);
		}
    }

    //[l,r)
    TypeNode fold(i64 l, i64 r) {
        if (l < 0 || length <= l || r < 0) return Monoid::unit_node;
        return dfs(l,r,0,length,root);
    }
};

/*
 * @title MonoidRangeCompositePointUpdate - [区間一次関数, 点更新]
 * @docs md/operator/monoid/MonoidRangeCompositePointUpdate.md
 */
template<class T> struct MonoidRangeCompositePointUpdate {
    using TypeNode = T;
    inline static constexpr TypeNode unit_node = make_pair(1,0);
    inline static constexpr TypeNode func_fold(TypeNode l,TypeNode r){return {r.first*l.first,r.first*l.second+r.second};}
    inline static constexpr TypeNode func_operate(TypeNode l,TypeNode r){return r;}
    inline static constexpr bool func_check(TypeNode nodeVal,TypeNode var){return var == nodeVal;}
};

using Mint = ModInt<MOD_998244353>;

int main(){
	cin.tie(0);ios::sync_with_stdio(false);
    int N,Q; 
	read(N), read(Q);
    DynamicSegmentTree<MonoidRangeCompositePointUpdate<pair<Mint,Mint>>> seg;
    for(int i = 0; i < N; ++i) {
		int a,b; read(a), read(b);
		seg.operate(i,{a,b});
    }
    while(Q--){
        long long q,l,r,x; 
		read(q),read(l),read(r),read(x);
        if(q) {
			auto p = seg.fold(l,r);
			cout << p.first*x+p.second << "\n";
		}
        else seg.operate(l,{r,x});
    }
}

