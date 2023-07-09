#include <bits/stdc++.h>
using namespace std;
using int128 = __int128_t;
using int64 = long long;

#define ALL(obj) (obj).begin(),(obj).end()

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

template<class T> using priority_queue_reverse = priority_queue<T,vector<T>,greater<T>>;

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
 * @title MonoidRangeFoldMinRangeOperateUpdate - fold:区間min, operate:区間更新
 * @docs md/operator/monoid-lazy/MonoidRangeFoldMinRangeOperateUpdate.md
 */
template<class T, class U> struct MonoidRangeFoldMinRangeOperateUpdate {
	using TypeNode = T;
	using TypeLazy = U;
	inline static constexpr TypeNode unit_node = 1000'000'001;
	inline static constexpr TypeLazy unit_lazy = 1000'000'001;
	inline static constexpr TypeNode func_fold(TypeNode l,TypeNode r){return min(l,r);}
	inline static constexpr TypeLazy func_lazy(TypeLazy old_lazy,TypeLazy new_lazy){return new_lazy;}
	inline static constexpr TypeNode func_operate(TypeNode node,TypeLazy lazy,int l, int r){return lazy==unit_lazy?node:lazy;}
	inline static constexpr bool func_check(TypeNode nodeVal,TypeNode var){return var <= nodeVal;}
};

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

    //非再帰は遅かった
    // stack<pair<Node*, size_t>> st;
    // inline Node* splay(Node* node, size_t k){
    //     Node* t_node = node;
    //     Node* last = nullptr;
    //     while(last == nullptr) {
    //         propagate(t_node);
    //         size_t sz_l = size(t_node->left);
    //         if(k == sz_l) {
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
    //             t_node->left = last;
    //             t_node = rotate_right(t_node);
    //         }
    //         else {
    //             t_node->right = last;
    //             t_node = rotate_left(t_node);
    //         }
    //         update(t_node);
    //         last = t_node;
    //     }
    //     return last;
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

/**
 * @url 
 * @est
 */ 
int main() {
    cin.tie(0);ios::sync_with_stdio(false);
    LazySplayTreeSequence<MonoidRangeFoldMinRangeOperateUpdate<int,int>> seq;
    int N,Q; read(N),read(Q);
    for(int i=0;i<N;++i) {
        int a; read(a);
        seq.insert(i,a);
    }
    while(Q--) {
        int x,y,z; 
        read(x),read(y),read(z);
        if(x==0) {
            auto w = seq.get(z);
            seq.erase(z);
            seq.insert(y,w);
        }
        if(x==1) {
            cout << seq.fold(y,z+1) << "\n";
        }
        if(x==2) {
            seq.operate(y,y+1,z);
        }
    }
    return 0; 
}
