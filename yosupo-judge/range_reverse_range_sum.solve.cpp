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
 * @title MonoidRangeSumRangeAdd - fold:区間和, opearate:区間加算
 * @docs md/operator/monoid-lazy/MonoidRangeSumRangeAdd.md
 */
template<class T, class U> struct MonoidRangeFoldSumRangeOperateAdd {
	using TypeNode = T;
	using TypeLazy = U;
	inline static constexpr TypeNode unit_node = 0;
	inline static constexpr TypeLazy unit_lazy = 0;
	inline static constexpr TypeNode func_fold(TypeNode l,TypeNode r){return l+r;}
	inline static constexpr TypeLazy func_lazy(TypeLazy old_lazy,TypeLazy new_lazy){return old_lazy+new_lazy;}
	inline static constexpr TypeNode func_operate(TypeNode node,TypeLazy lazy,int l, int r){return node+lazy*(r-l);}
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
    inline int size(Node *node) {return node==nullptr ? 0 : node->size;}
    inline TypeNode range_value(Node *node) {return node==nullptr ? Monoid::unit_node : node->range_value;}
    inline void update(Node *node) {
        if(node==nullptr) return;
		if(node->left != nullptr) propagate(node->left);
		if(node->right != nullptr) propagate(node->right);
        node->size = size(node->left) + size(node->right) + 1;
        node->range_value = Monoid::func_fold(Monoid::func_fold(range_value(node->left),node->value),range_value(node->right));
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
    inline void rotate_left(Node* node){
        Node* parent = node->parent;
        if(parent->parent == nullptr) root = node;
        else if (parent->parent->left == parent) parent->parent->left = node;
        else parent->parent->right = node;

        node->parent = parent->parent;
        parent->parent = node;
        if(node->left != nullptr) node->left->parent = parent; 
        parent->right = node->left;
        node->left = parent;
    }
    inline void rotate_right(Node* node){
        Node* parent = node->parent;
        if(parent->parent == nullptr) root = node;
        else if (parent->parent->left == parent) parent->parent->left = node;
        else parent->parent->right = node;

        node->parent = parent->parent;
        parent->parent = node;
        if(node->right != nullptr) node->right->parent = parent; 
        parent->left = node->right;
        node->right = parent;
    }
    inline void splay(Node* node){
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
                else if(grand_parent->right == parent){ rotate_right(node); rotate_left(node); }
            }
            else{
                if(grand_parent == nullptr){ rotate_left(node); }
                else if(grand_parent->left  == parent){ rotate_left(node); rotate_right(node); }
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
        splay(node);
        return node;
    }
    //[l,r)
    Node* get_range_impl(const size_t l, const size_t r) {
        if(r-l==size(root)) return root;
        if(l==0) return get_impl(r)->left;
        if(r==size(root)) return get_impl(l-1)->right;
        Node* target_right = get_impl(r);
        Node* target_left = target_right->left;
        root = target_left;

        target_left->parent = nullptr;
        target_left = get_impl(l-1);
        root=target_right;

        target_right->left=target_left;
        target_left->parent=target_right;
        update(target_right);
        return target_left->right;
    }
    void insert_impl(const size_t k, const TypeNode value) {
        Node* node = new Node(value);
        if(k == 0){
            node->right = root;
            if(root != nullptr) root->parent = node;
            root = node;
            update(node);
            return;
        }
        if(k == size(root)){
            node->left = root;
            root->parent = node;
            root = node;
            update(node);
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
    void erase_impl(const size_t k){
        Node* target = get_impl(k);
        if(k == 0){
            root = target->right;
            if(root != nullptr) root->parent = nullptr;
            return;
        }
        else if(k+1 == size(root)){
            root = target->left;
            if(root != nullptr) root->parent = nullptr;
            return;
        }
        Node* target_left = target->left;
        Node* target_right = target->right;
        target_right->parent = nullptr;
        root = target_right;
        get_impl(0);
        target_right = root;  
        target_right->left = target_left;
        target_left->parent = target_right;
        update(target_right);
    }
    inline TypeNode fold_impl(int l, int r) {
        if (l < 0 || size(root) <= l || r<=0 || r-l <= 0) return Monoid::unit_node;
		Node* node=get_range_impl(l,r);
		propagate(node);
		update(node);
        return range_value(node);
    }
    void operate_impl(int l, int r, TypeLazy lazy) {
        if(l < 0 || size(root) <= l || r <= 0 || r-l <= 0) return;
        Node* node=get_range_impl(l,r);
        node->range_lazy = Monoid::func_lazy(node->range_lazy,lazy);
        splay(node);
    }
    void reverse_impl(int l, int r) {
        if (l < 0 || size(root) <= l || r<=0 || r-l <= 0) return;
        Node* node=get_range_impl(l,r);
        node->rev ^= 1;
        splay(node);
    }
    void print_impl() {
        int M=5;
        vector<vector<Node*>> vv(M);
        vv[0].push_back(root);
        for(int i=0;i+1<M;++i) {
            for(int j=0;j<vv[i].size();++j) {
                auto le = (vv[i][j]==nullptr ? nullptr : vv[i][j]->left);
                auto ri = (vv[i][j]==nullptr ? nullptr : vv[i][j]->right);
                vv[i+1].push_back(le);
                vv[i+1].push_back(ri);
            }
        }
        for(int i=0;i<M;++i) {
            int MM = vv[i].size();
            for(int j=0;j<MM;++j) {
				if(vv[i][j]==nullptr) {
					cout << "{:},";
				}
				else {
					cout << "{" << vv[i][j]->value << ":" << vv[i][j]->range_lazy << "}, ";
				}
            }
            cout << endl;
        }
    }
public:
    LazySplayTreeSequence(): root(nullptr) {}
    inline TypeNode get(const size_t k) {return get_impl(k)->value; }
    inline int size() {return size(root); }
    inline void insert(const size_t k, const TypeNode value) {insert_impl(k,value);}
    inline void erase(const size_t k) { erase_impl(k);}
    inline void operate(const int l, const int r, const TypeLazy lazy) {operate_impl(l,r,lazy);}
    inline TypeNode fold(int l, int r) {return fold_impl(l,r);}
    inline void reverse(int l, int r) {reverse_impl(l,r);}
    void print() {print_impl();}
};

int main(){
    cin.tie(0);ios::sync_with_stdio(false);
    int N,Q; read(N); read(Q);
    LazySplayTreeSequence<MonoidRangeFoldSumRangeOperateAdd<long long,long long>> st;
    for(int i=0;i<N;++i) {
        int a; read(a); st.insert(i,a);
    }
    while(Q--) {
        int q; read(q);
        int l,r; read(l); read(r);
        if(q==0) {
            st.reverse(l,r);
        }
        if(q==1) {
            cout << st.fold(l,r) << "\n";
        }
    }
    return 0;
}