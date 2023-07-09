#include <vector>
#include <iostream>
#include <cassert>
#include <queue>
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
 * @title LazySplayTreeSequence - 遅延評価SplayTree列
 * @docs md/binary-search-tree/LazySplayTreeSequence.md
 */
template<class Monoid> class LazySplayTreeSequence {
    using TypeNode = typename Monoid::TypeNode;
    using TypeLazy = typename Monoid::TypeLazy;
    struct Node {
    public:
        Node *left, *right;
        TypeNode value, range_value;
        TypeLazy range_lazy;
        int rev;
        int size;
        Node(const TypeNode v) : left(nullptr),right(nullptr),value(v),range_value(v),range_lazy(Monoid::unit_lazy),size(1),rev(0) {}
        friend ostream &operator<<(ostream &os, const Node* node) {return os << "{" << node->value << ", " << node->size << "}";}
    };
    struct TupleNode {
        Node *left, *center, *right;
        TupleNode(Node *left,Node *center,Node *right) : left(left), center(center), right(right) {}
    };
    Node* root;
    inline int size(Node *node) {return node==nullptr ? 0 : node->size;}
    inline TypeNode range_value(Node *node) {return node==nullptr ? Monoid::unit_node : node->range_value;}
    inline void update(Node *node) {
        node->size = 1;
        node->range_value = node->value;
		if(node->left != nullptr) {
            node->size = node->left->size + node->size;
            node->range_value = Monoid::func_fold(node->left->range_value, node->range_value);
        }
		if(node->right != nullptr) {
            node->size = node->size + node->right->size;
            node->range_value = Monoid::func_fold(node->range_value, node->right->range_value);
        }
    }
    inline void propagate(Node *node) {
        if(node==nullptr) return;
        if(node->range_lazy != Monoid::unit_lazy) {
            if(node->left  != nullptr) sync_lazy(node->left, node->range_lazy);
            if(node->right != nullptr) sync_lazy(node->right, node->range_lazy);
            node->range_lazy = Monoid::unit_lazy;
        }
        if(node->rev) {
            if(node->left  != nullptr) sync_rev(node->left);
            if(node->right != nullptr) sync_rev(node->right);
            node->rev = 0;
        }
    }
    inline void sync_lazy(Node *node, const TypeLazy lazy) {
        node->range_lazy = Monoid::func_lazy(node->range_lazy, lazy);
        node->value = Monoid::func_operate(node->value, lazy, 0,1);
        node->range_value = Monoid::func_operate(node->range_value, lazy, 0, node->size);
    }
    inline void sync_rev(Node *node) {
        swap(node->left, node->right);
        node->rev ^= 1;
    }
    inline Node* rotate_left(Node* node){
        Node* right = node->right;
        node->right = right->left;
        right->left = node;
        update(node);
        update(right);
        return right;
    }
    inline Node* rotate_right(Node* node){
        Node* left = node->left;
        node->left = left->right;
        left->right = node;
        update(node);
        update(left);
        return left;
    }

    inline Node* splay(Node* node, size_t k){
        auto p = splay_inner(node, k);
        node = p.first;
        auto last = p.second;
        if(node->left == last) return rotate_right(node);
        else if(node->right == last) return rotate_left(node);
        return node;
    }
    inline pair<Node*,Node*> splay_inner(Node* node, size_t k){
        propagate(node);
        size_t sz_l = size(node->left);
        if(k == sz_l) return {node, node};
        if(k < sz_l) {
            auto p = splay_inner(node->left, k);
            node->left = p.first;
            auto last = p.second;
            update(node);
            if(node->left == last) return {node, last};
            if(node->left->left == last) node = rotate_right(node);
            else node->left = rotate_left(node->left);
            return {rotate_right(node), last};
        }
        else {
            auto p = splay_inner(node->right, k - sz_l - 1);
            node->right = p.first;
            auto last = p.second;
            update(node);
            if(node->right == last) return {node, last};
            if(node->right->right == last) node = rotate_left(node);
            else node->right = rotate_right(node->right);
            return {rotate_left(node), last};
        }
    }

    // 非再帰は遅かった
    // stack<pair<Node*, size_t>> st;
    // inline pair<Node*,Node*> splay_inner2(Node* node, size_t k){
    //     Node* t_node = node;
    //     Node* next = nullptr;
    //     Node* last = nullptr;
    //     while(last == nullptr) {
    //         propagate(t_node);
    //         size_t sz_l = size(t_node->left);
    //         if(k == sz_l) {
    //             next = t_node;
    //             last = t_node;
    //             continue;
    //         }
    //         if(k < sz_l) {
    //             st.emplace(t_node, 1);
    //             t_node = t_node->left;
    //         }
    //         else {
    //             st.emplace(t_node, 0);
    //             t_node = t_node->right;
    //             k = (k - sz_l - 1);
    //         }
    //     }
    //     while(st.size()) {
    //         auto [t_node,is_left] = st.top(); st.pop();
    //         if(is_left) {
    //             t_node->left = next;
    //             update(t_node);
    //             if(t_node->left == last) {
    //                 next = t_node;
    //                 continue;
    //             }
    //             if(t_node->left->left == last) t_node = rotate_right(t_node);
    //             else t_node->left = rotate_left(t_node->left);
    //             next = rotate_right(t_node);
    //         }
    //         else {
    //             t_node->right = next;
    //             update(t_node);
    //             if(t_node->right == last) {
    //                 next = t_node;
    //                 continue;
    //             }
    //             if(t_node->right->right == last) t_node = rotate_left(t_node);
    //             else t_node->right = rotate_right(t_node->right);
    //             next = rotate_left(t_node);
    //         }
    //     }
    //     return {next, last};
    // }

    //    - parent
    //   |
    // left
    //の形でマージ
    Node* merge(Node* left, Node* parent) {
        if(left == nullptr) return parent;
        if(parent == nullptr) return left;
        parent = splay(parent, 0);
        parent->left = left;
        update(parent);
        return parent;
    }
    Node* merge(TupleNode* tuple_node) {
        Node* node = merge(tuple_node->center, tuple_node->right);
        if(tuple_node->left == nullptr) return node;
        tuple_node->left->right = node;
        update(tuple_node->left);
        return tuple_node->left;
    }
    // [0,k),[k,n) でsplit
    pair<Node*,Node*> split(Node* node, size_t k) {
        if(k >= size(node)) return {node, nullptr};
        Node* right = splay(node, k);
        Node* left = right->left;
        right->left = nullptr;
        update(right);
        return {left, right};
    }
    //[0,l),[l,r),[r,n) でsplit
    TupleNode* split(Node* node, size_t l, size_t r) {
        if(!l) {
            auto [center,right] = split(node, r);
            return new TupleNode(nullptr, center, right);
        }
        Node* left = splay(node, l-1);
        auto [center, right] = split(left->right, r-l);
        left->right = nullptr;
        update(left);
        return new TupleNode(left, center, right);
    }
    void insert_impl(const size_t k, const TypeNode value) {
        Node* new_node = new Node(value);
        if(k == size(root)){
            new_node->left = root;
            update(new_node);
            root = new_node;
            return;
        }
        if(k == 0){
            new_node->right = root;
            update(new_node);
            root = new_node;
            return;
        }
        Node* node = splay(root, k);
        new_node->left = node->left;
        node->left = new_node;
        update(new_node);
        update(node);
        root = node;
        return;
    }
    void erase_impl(const size_t k){
        Node* node = splay(root, k);
        root = merge(node->left,node->right);
    }
    TypeNode fold_impl(int l, int r) {
        if (l < 0 || size(root) <= l || r<=0 || r-l <= 0) return Monoid::unit_node;
		TupleNode* tuple_node = split(root,l,r);
        TypeNode res = tuple_node->center->range_value;
        root = merge(tuple_node);
        return res;
    }
    void operate_impl(int l, int r, TypeLazy lazy) {
        if(l < 0 || size(root) <= l || r <= 0 || r-l <= 0) return;
		TupleNode* tuple_node = split(root,l,r);
        sync_lazy(tuple_node->center, lazy);
        root = merge(tuple_node);
    }
    void reverse_impl(int l, int r) {
        if (l < 0 || size(root) <= l || r<=0 || r-l <= 0) return;
		TupleNode* tuple_node = split(root,l,r);
        sync_rev(tuple_node->center);
        root = merge(tuple_node);
    }
    void print_impl() {
        size_t N = size(root);
        for(int i=0;i<N;++i) cout << get(i) << " ";
        cout << endl;
    }
public:
    LazySplayTreeSequence(): root(nullptr) {}
    inline TypeNode get(const size_t k) {root = splay(root , k); return root->value; }
    inline int size() {return size(root); }
    inline void insert(const size_t k, const TypeNode value) {insert_impl(k,value);}
    inline void erase(const size_t k) { erase_impl(k);}
    inline void operate(const int l, const int r, const TypeLazy lazy) {operate_impl(l,r,lazy);}
    inline TypeNode fold(int l, int r) {return fold_impl(l,r); }
    inline void reverse(int l, int r) {reverse_impl(l,r);}
    void print() {print_impl();}
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
    LazySplayTreeSequence<MonoidRangeFoldSumRangeOperateAffine<modint,pair<modint,modint>>> st;
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