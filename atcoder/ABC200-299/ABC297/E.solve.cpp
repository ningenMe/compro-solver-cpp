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
 * @title RandomizedBinarySearchTree - 平衡二分探索木
 * @docs md/data-structure/binary-search-tree/RandomizedBinarySearchTree.md
 */
template<class Monoid> class RandomizedBinarySearchTree {
    using TypeNode = typename Monoid::TypeNode;
    unsigned int x = 123456789, y = 362436069, z = 521288629, w = 88675123;
    unsigned int xor_shift() {
        unsigned int t = (x ^ (x << 11)); x = y; y = z; z = w;
        return (w = (w ^ (w >> 19)) ^ (t ^ (t >> 8)));
    }
    struct Node {
    private:
        void build() {left = right = nullptr;size = 1;}
    public:
        Node *left, *right;
        TypeNode value, range_value;
        int size;
        Node() : value(Monoid::unit_node), range_value(Monoid::unit_node) {build();}
        Node(TypeNode v) : value(v), range_value(v) {build();}
        friend ostream &operator<<(ostream &os, const Node* node) {return os << "{" << node->value << ", " << node->range_value << ", " << node->size << "}";}
    };
    Node* root;
    inline int size(Node *node) {return node==nullptr ? 0 : node->size;}
    inline TypeNode range_value(Node *node) {return node==nullptr ? Monoid::unit_node : node->range_value;}
    inline TypeNode get(Node *node, size_t k) {
        if (node==nullptr) return Monoid::unit_node;
        if (k == size(node->left)) return node->value;
        if (k < size(node->left)) return get(node->left, k);
        else return get(node->right, k-1 - size(node->left));
    }
    inline Node* update(Node *node) {
        node->size = size(node->left) + size(node->right) + 1;
        node->range_value = Monoid::func_fold(Monoid::func_fold(range_value(node->left),node->value),range_value(node->right));
        return node;
    }
    inline Node* merge_impl(Node *left, Node *right) {
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
        if (k <= size(node->left)) {
            pair<Node*, Node*> sub = split_impl(node->left, k);
            node->left = sub.second;
            return make_pair(sub.first, update(node));
        }
        else {
            pair<Node*, Node*> sub = split_impl(node->right, k - 1 - size(node->left));
            node->right = sub.first;
            return make_pair(update(node), sub.second);
        }
    }
    inline TypeNode fold_impl(Node *node, int l, int r) {
        if (l < 0 || size(node) <= l || r<=0 || r-l <= 0) return Monoid::unit_node;
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
    inline int lower_bound(Node *node, TypeNode value) {
        if (node==nullptr) return 0;
        if (value <= node->value) return lower_bound(node->left, value);
        else return size(node->left) + lower_bound(node->right, value) + 1;
    }
    inline int upper_bound(Node *node, TypeNode value) {
        if (node==nullptr) return 0;
        if (value < node->value) return upper_bound(node->left, value);
        else return size(node->left) + upper_bound(node->right, value) + 1;
    }
    inline void insert_impl(const TypeNode value) {
        pair<Node*, Node*> sub = split_impl(this->root, lower_bound(this->root,value));
        this->root = this->merge_impl(this->merge_impl(sub.first, new Node(value)), sub.second);
    }
    inline void erase_impl(const TypeNode value) {
        int k1 = lower_bound(value), k2 = upper_bound(value);
        if(k1==k2) return;
        auto sub = split_impl(this->root,k1);
        this->root = merge_impl(sub.first, split_impl(sub.second, 1).second);
    }
public:
    RandomizedBinarySearchTree() : root(nullptr) {}
    inline int size() {return size(this->root);}
    inline int empty(void) {return bool(size()==0);}
    inline Node* merge(Node *left, Node *right) {return merge_impl(left,right);}
    inline pair<Node*, Node*> split(int k) {return split_impl(this->root,k);}
    inline void insert(const TypeNode value) {insert_impl(value);}
    inline void erase(const TypeNode value) {erase_impl(value);}
    inline TypeNode get(size_t k) {return get(this->root, k);}
    inline TypeNode fold(int l, int r) {return fold_impl(this->root,l,r);}
    inline int lower_bound(TypeNode value) {return lower_bound(this->root,value);}
    inline int upper_bound(TypeNode value) {return upper_bound(this->root,value);}
    inline int count(TypeNode value) {return upper_bound(value) - lower_bound(value);}
    void print() {int m = size(this->root); for(int i=0;i<m;++i) cout << get(i) << " \n"[i==m-1];}
};

/*
 * @title MonoidRangeSumPointAdd - [区間和, 一点加算]
 * @docs md/operator/monoid/MonoidRangeSumPointAdd.md
 */
template<class T> struct MonoidRangeSumPointAdd {
    using TypeNode = T;
    inline static constexpr TypeNode unit_node = 0;
    inline static constexpr TypeNode func_fold(TypeNode l,TypeNode r){return l+r;}
    inline static constexpr TypeNode func_operate(TypeNode l,TypeNode r){return l+r;}
    inline static constexpr bool func_check(TypeNode nodeVal,TypeNode var){return var == nodeVal;}
};

/**
 * @url 
 * @est
 */ 
int main() {
    cin.tie(0);ios::sync_with_stdio(false);
    int64 N,K; cin >> N >> K;
    vector<int64> A(N); 
    for(int i=0;i<N;++i) cin >> A[i];
    sort(ALL(A));
    RandomizedBinarySearchTree<MonoidRangeSumPointAdd<int64>> st;
    priority_queue_reverse<int64> pq;
    pq.push(0);
    st.insert(0);

    while(pq.size()) {
        auto from = pq.top();
        pq.pop();

        for(int64 diff: A) {
            auto to = diff + from;
            if(st.count(to) > 0) continue;
            if(st.size() <= K || st.get(K) > to) {
                st.insert(to);
                pq.push(to);
            }
        }
    }
    cout << st.get(K) << endl;
    return 0;
}
