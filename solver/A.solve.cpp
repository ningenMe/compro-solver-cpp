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

template<class Monoid> class SplayTreeSequence {
    using TypeNode = typename Monoid::TypeNode;
    using TypeLazy = typename Monoid::TypeLazy;
    struct Node {
    private:
        void build() {left = right = nullptr;size = 1;rev=0;range_lazy = Monoid::unit_lazy;}
    public:
        Node *left, *right, *parent;
        TypeNode value, range_value;
        TypeLazy range_lazy;
        int size,rev;
        Node() : value(Monoid::unit_node), range_value(Monoid::unit_node), parent(parent) {build();}
        Node(const TypeNode v) : value(v),range_value(v) {build();}
        friend ostream &operator<<(ostream &os, const Node* node) {return os << "{" << node->value << ", " << node->size << "}";}
    };
    Node* root;
    int size(Node *node) {return node==nullptr ? 0 : node->size;}
    TypeNode range_value(Node *node) {return node==nullptr ? Monoid::unit_node : node->range_value;}
    Node* update(Node *node) {
        node->size = size(node->left) + size(node->right) + 1;
        node->range_value = Monoid::func_fold(Monoid::func_fold(range_value(node->left),node->value),range_value(node->right));
        return node;
    }
    void propagate(Node *node) {
        if(node==nullptr || (node->range_lazy == Monoid::unit_lazy && node->rev == 0)) return;
        node->range_value = Monoid::func_operate(node->range_value,node->range_lazy,0,node->size);
        node->value = Monoid::func_operate(node->value,node->range_lazy,0,1);
        if(node->left !=nullptr) node->left->range_lazy  = Monoid::func_lazy(node->left->range_lazy,node->range_lazy), node->left->rev ^= node->rev;
        if(node->right!=nullptr) node->right->range_lazy = Monoid::func_lazy(node->right->range_lazy,node->range_lazy), node->right->rev ^= node->rev;
        if(node->rev) swap(node->left,node->right), node->rev = 0;
        node->range_lazy = Monoid::unit_lazy;
    }
    void rotate_left(Node* node){
        Node* parent = node->parent;
        node->parent = parent->parent;
        parent->parent = node;
        if(node->left != nullptr) node->left->parent = parent; 
        parent->right = node->left;
        node->left = parent;
    }
    void rotate_right(Node* node){
        Node* parent = node->parent;
        node->parent = parent->parent;
        parent->parent = node;
        if(node->right != nullptr) node->right->parent = parent; 
        parent->left = node->right;
        node->right = parent;
    }
    void splay(Node* node){
        propagate(node); 
        while(node->parent != nullptr){
            Node* parent = node->parent;
            Node* grand_parent = parent->parent;
            propagate(grand_parent);
            propagate(parent);
            propagate(node);
            if(parent->left == node){
                if(grand_parent == nullptr){ rotate_right(node); }
                else if(grand_parent->left  == parent){ rotate_right(parent); rotate_right(node); }
                else if(grand_parent->right == parent){ rotate_right(parent); rotate_left(node); }
            }
            else{
                if(grand_parent == nullptr){ rotate_left(node); }
                else if(grand_parent->left  == parent){ rotate_left(parent); rotate_right(node); }
                else if(grand_parent->right == parent){ rotate_left(parent); rotate_left(node); }
            }
            update(grand_parent);
            update(parent);
            update(node);
        }
        update(node);
    }
    Node* get_impl(size_t k) {
        Node* node = root;
        while(1) {
            propagate(node);
            if(size(node->left) == k) break;
            if(size(node->left) > k) {
                node = node->left;
            }
            else {
                k -= size(node->left) + 1;
                node = node->right;
            }
        }
        propagate(node);
        splay(node);
        return node;
    }
    void insert_impl(const size_t k, const TypeNode value) {
        Node* node = new Node(value);
        if(k == 0){
            node->right = root;
            if(root != nullptr) root->parent = node;
            root = node;
            propagate(node);
            return;
        }
        if(k == size(root)){
            node->left = root;
            root->parent = node;
            propagate(node);
            return;
        }
        Node* target = get_impl(k);
        node->left = target->left;
        node->right = target;
        root = node;
        target->left->parent = node;
        target->parent = node;
        target->left = nullptr;
        update(target);
        update(node);
    }
    void print_impl() {
        size_t sz = size(root);
        for(int i=0;i<sz;++i) cout << get(i) << (i+1<sz?", ":"");
        cout << endl;
    }
public:
    SplayTreeSequence(): root(nullptr) {}
    TypeNode get(const size_t k) {return get_impl(k)->value; }
    int size() {return size(root); }
    void insert(const size_t k, const TypeNode value) {insert_impl(k,value);}
    void print() {print_impl();}
};

template<class T, class U> struct MonoidRangeSumRangeAdd {
	using TypeNode = T;
	using TypeLazy = U;
	inline static constexpr TypeNode unit_node = 0;
	inline static constexpr TypeLazy unit_lazy = 0;
	inline static constexpr TypeNode func_fold(TypeNode l,TypeNode r){return l+r;}
	inline static constexpr TypeLazy func_lazy(TypeLazy old_lazy,TypeLazy new_lazy){return {new_lazy + old_lazy};}
	inline static constexpr TypeNode func_operate(TypeNode node,TypeLazy lazy,int l, int r){return {node +lazy*(r-l)};}
	inline static constexpr bool func_check(TypeNode nodeVal,TypeNode var){return var <= nodeVal;}
};

/**
 * @url 
 * @est
 */ 
int main() {
    cin.tie(0);ios::sync_with_stdio(false);
    SplayTreeSequence<MonoidRangeSumRangeAdd<int64,int64>> st;
    while(1) {
        int a,b; cin >> a >> b;
        st.insert(a,b);
        st.print();
    }
    return 0;
}
