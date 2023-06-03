#include <vector>
#include <iostream>
#include <cassert>
#include <queue>

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
 * @title LazyRandomizedBinarySearchTreeSequence - 遅延評価ランダム平衡二分探索木列
 * @docs md/binary-search-tree/LazyRandomizedBinarySearchTreeSequence.md
 */
template<class Monoid> class LazyRandomizedBinarySearchTreeSequence {
    using TypeNode = typename Monoid::TypeNode;
    using TypeLazy = typename Monoid::TypeLazy;
    unsigned int x = 123456789, y = 362436069, z = 521288629, w = 88675123;
    unsigned int xor_shift() {
        unsigned int t = (x ^ (x << 11)); x = y; y = z; z = w;
        return (w = (w ^ (w >> 19)) ^ (t ^ (t >> 8)));
    }
    struct Node {
    private:
        void build() {left = right = nullptr;size = 1; rev=0; range_lazy = Monoid::unit_lazy;}
    public:
        Node *left, *right;
        TypeNode value, range_value;
        TypeLazy range_lazy;
        int size,rev;
        Node() : value(Monoid::unit_node), range_value(Monoid::unit_node) {build();}
        Node(TypeNode v) : value(v), range_value(v) {build();}
        friend ostream &operator<<(ostream &os, const Node* node) {return os << "{" << node->value << ", " << node->range_value << ", " << node->range_lazy << ", " << node->size << "}";}
    };
    Node* root;
    inline int size(Node *node) {return node==nullptr ? 0 : node->size;}
    inline TypeNode range_value(Node *node) {return node==nullptr ? Monoid::unit_node : node->range_value;}
    inline TypeNode get(Node *node, size_t k) {
        if (node==nullptr) return Monoid::unit_node;
        propagate(node);
        if (k == size(node->left)) return node->value;
        if (k < size(node->left)) return get(node->left, k);
        else return get(node->right, k-1 - size(node->left));
    }
    inline Node* update(Node *node) {
        node->size = size(node->left) + size(node->right) + 1;
        node->range_value = Monoid::func_fold(Monoid::func_fold(range_value(node->left),node->value),range_value(node->right));
        return node;
    }
    inline void propagate(Node *node) {
        if(node==nullptr || (node->range_lazy == Monoid::unit_lazy && node->rev == 0)) return;
        node->range_value = Monoid::func_operate(node->range_value,node->range_lazy,0,node->size);
        node->value = Monoid::func_operate(node->value,node->range_lazy,0,1);
        if(node->left !=nullptr) node->left->range_lazy  = Monoid::func_lazy(node->left->range_lazy,node->range_lazy), node->left->rev ^= node->rev;
        if(node->right!=nullptr) node->right->range_lazy = Monoid::func_lazy(node->right->range_lazy,node->range_lazy), node->right->rev ^= node->rev;
        if(node->rev) swap(node->left,node->right), node->rev = 0;
        node->range_lazy = Monoid::unit_lazy;
    }
    inline Node* merge_impl(Node *left, Node *right) {
        propagate(left);
        propagate(right);
        if (left==nullptr)  return right;
        if (right==nullptr) return left;
        if (xor_shift() % (left->size + right->size) < left->size) {
            left->right = merge_impl(left->right, right);
            return update(left);
        }
        else {
            right->left = merge_impl(left, right->left);
            return update(right);
        }
    }
    inline pair<Node*, Node*> split_impl(Node* node, int k) {
        if (node==nullptr) return make_pair(nullptr, nullptr);
        propagate(node);
        if (k <= size(node->left)) {
            propagate(node->right);
            pair<Node*, Node*> sub = split_impl(node->left, k);
            node->left = sub.second;
            return make_pair(sub.first, update(node));
        }
        else {
            propagate(node->left);
            pair<Node*, Node*> sub = split_impl(node->right, k - 1 - size(node->left));
            node->right = sub.first;
            return make_pair(update(node), sub.second);
        }
    }
    inline TypeNode fold_impl(Node *node, int l, int r) {
        if (l < 0 || size(node) <= l || r<=0 || r-l <= 0) return Monoid::unit_node;
        propagate(node);
        if (l == 0 && r == size(node)) return range_value(node);
        TypeNode value = Monoid::unit_node;
        int sl = size(node->left);
        if(sl > l) value = Monoid::func_fold(value,fold_impl(node->left,l,min(sl,r)));
        l = max(l-sl,0), r -= sl;
        if(l == 0 && r > 0) value = Monoid::func_fold(value,node->value);
        l = max(l-1,0), r -= 1;
        if(l >= 0 && r > l) value = Monoid::func_fold(value,fold_impl(node->right,l,r));
        return value;
    }
    inline void operate_impl(Node *node, int l, int r, TypeLazy lazy) {
        if(l < 0 || size(node) <= l || r <= 0 || r-l <= 0) return;
        if (l == 0 && r == size(node)) {
            node->range_lazy = Monoid::func_lazy(node->range_lazy,lazy);
            propagate(node);
            return;
        }
        int sl = size(node->left);
        propagate(node->left);
        propagate(node->right);
        if(sl > l) operate_impl(node->left,l,min(sl,r),lazy);
        l = max(l-sl,0), r -= sl;
        if(l == 0 && r > 0) node->value = Monoid::func_operate(node->value,lazy,0,1);
        l = max(l-1,0), r -= 1;
        if(l >= 0 && r > l) operate_impl(node->right,l,r,lazy);
        update(node);
    }
    inline void reverse_impl(int l, int r) {
        if(l < 0 || size(root) <= l || r <= 0 || r-l <= 0) return;
        pair<Node*,Node*> tmp1 = split_impl(this->root,l);
        pair<Node*,Node*> tmp2 = split_impl(tmp1.second,r-l);
        Node* nl = tmp1.first;
        Node* nc = tmp2.first;
        Node* nr = tmp2.second;
        nc->rev ^= 1;
        this->root = merge_impl(merge_impl(nl,nc),nr);
    }
    inline void insert_impl(const size_t k, const TypeNode value) {
        pair<Node*, Node*> sub = split_impl(this->root, k);
        this->root = this->merge_impl(this->merge_impl(sub.first, new Node(value)), sub.second);
    }
    inline void erase_impl(const size_t k) {
        if(size(this->root) <= k) return;
        auto sub = split_impl(this->root,k);
        this->root = merge_impl(sub.first, split_impl(sub.second, 1).second);
    }
public:
    LazyRandomizedBinarySearchTreeSequence() : root(nullptr) {}
    inline int size() {return size(this->root);}
    inline int empty(void) {return bool(size()==0);}
    inline Node* merge(Node *left, Node *right) {return merge_impl(left,right);}
    inline pair<Node*, Node*> split(int k) {return split_impl(this->root,k);}
    inline void insert(const size_t k, const TypeNode value) {insert_impl(k,value);}
    inline void erase(const size_t k) {erase_impl(k);}
    inline TypeNode get(size_t k) {return get(this->root, k);}
    inline void operate(const int l, const int r, const TypeLazy lazy) {propagate(this->root); operate_impl(this->root,l,r,lazy);}
    inline TypeNode fold(int l, int r) {return fold_impl(this->root,l,r);}
    inline void reverse(int l, int r) {reverse_impl(l,r);}
    void print() {int m = size(this->root); for(int i=0;i<m;++i) cout << get(i) << " \n"[i==m-1];}
};

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
 * @title MonoidRangeFoldSumRangeOperateAffine - fold:区間和, operate:区間アフィン変換
 * @docs md/operator/monoid-lazy/MonoidRangeSumRangeAffine.md
 */
template<class T, class U> struct MonoidRangeFoldSumRangeOperateAffine {
	using TypeNode = T;
	using TypeLazy = U;
	inline static constexpr TypeNode unit_node = 0;
	inline static constexpr TypeLazy unit_lazy = {1,0};
	inline static constexpr TypeNode func_fold(TypeNode l,TypeNode r){return l+r;}
	inline static constexpr TypeLazy func_lazy(TypeLazy old_lazy,TypeLazy new_lazy){return {new_lazy.first*old_lazy.first,new_lazy.first*old_lazy.second+new_lazy.second};}
	inline static constexpr TypeNode func_operate(TypeNode node,TypeLazy lazy,int l, int r){return {node*lazy.first+lazy.second*(r-l)};}
	inline static constexpr bool func_check(TypeNode nodeVal,TypeNode var){return var <= nodeVal;}
};
using modint = ModInt<MOD_998244353>;

int main(){
    cin.tie(0);ios::sync_with_stdio(false);
    int N,Q; read(N); read(Q);
    LazyRandomizedBinarySearchTreeSequence<MonoidRangeFoldSumRangeOperateAffine<modint,pair<modint,modint>>> st;
    for(int i=0;i<N;++i) {
        int a; read(a); st.insert(i,a);
    }
    while(Q--) {
        int q; read(q);
        if(q==0) {
            int i,x; read(i); read(x);
            st.insert(i,x);
        }
        if(q==1) {
            int i; read(i);
            st.erase(i);
        }
		if(q==2) {
			int l,r; read(l); read(r);
			st.reverse(l,r);
		}
		if(q==3) {
			int l,r,b,c; read(l); read(r); read(b); read(c);
			st.operate(l,r,{b,c});
		}
        if(q==4) {
            int l,r; read(l); read(r);
            cout << st.fold(l,r) << "\n";
        }
    }
    return 0;
}