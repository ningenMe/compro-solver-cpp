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

const int MAX_M = 101;
using Ar = array<int,MAX_M>;
ostream &operator<<(ostream &o, const Ar&obj) {o << "{"; for (int i = 0; i < (int)obj.size(); ++i)o << (i > 0 ? ", " : "") << obj[i]; o << "}"; return o;}


/*
 * @title MonoidRangeSumPointAdd - [区間和, 一点加算]
 * @docs md/operator/monoid/MonoidRangeSumPointAdd.md
 */
template<class T> struct MonoidRangeSumPointAdd {
    using TypeNode = T;
    inline static constexpr TypeNode unit_node = {-1,Ar{}};
    inline static constexpr TypeNode func_fold(TypeNode l,TypeNode r){
        if(l.first==-1) return r;
        if(r.first==-1) return l;
        for(int i=0;i<r.second.size();++i) r.second[i]=l.second[r.second[i]];
        return {r.first,r.second};
    }
};

/*
 * @title SegmentTree - 非再帰抽象化セグメント木
 * @docs md/data-structure/segment-tree/SegmentTree.md
 */
template<class Monoid> class SegmentTree {
    using TypeNode = typename Monoid::TypeNode;
    size_t length;
    size_t num;
    vector<TypeNode> node;
    vector<pair<int,int>> range;
    inline void build() {
        for (int i = length - 1; i >= 0; --i) node[i] = Monoid::func_fold(node[(i<<1)+0],node[(i<<1)+1]);
        range.resize(2 * length);
        for (int i = 0; i < length; ++i) range[i+length] = make_pair(i,i+1);
        for (int i = length - 1; i >= 0; --i) range[i] = make_pair(range[(i<<1)+0].first,range[(i<<1)+1].second);
    }
public:

    //unitで初期化
    SegmentTree(const size_t num): num(num) {
        for (length = 1; length <= num; length *= 2);
        node.resize(2 * length, Monoid::unit_node);
        build();
    }

    //vectorで初期化
    SegmentTree(const vector<TypeNode> & vec) : num(vec.size()) {
        for (length = 1; length <= vec.size(); length *= 2);
        node.resize(2 * length, Monoid::unit_node);
        for (int i = 0; i < vec.size(); ++i) node[i + length] = vec[i];
        build();
    }

    //同じinitで初期化
    SegmentTree(const size_t num, const TypeNode init) : num(num) {
        for (length = 1; length <= num; length *= 2);
        node.resize(2 * length, Monoid::unit_node);
        for (int i = 0; i < length; ++i) node[i+length] = init;
        build();
    }

    //[idx,idx+1)
    void operate(size_t idx, const TypeNode var) {
        if(idx < 0 || length <= idx) return;
        idx += length;
        node[idx] = Monoid::func_operate(node[idx],var);
        while(idx >>= 1) node[idx] = Monoid::func_fold(node[(idx<<1)+0],node[(idx<<1)+1]);
    }

    //[l,r)
    TypeNode fold(int l, int r) {
        if (l < 0 || length <= l || r < 0 || length < r) return Monoid::unit_node;
        TypeNode vl = Monoid::unit_node, vr = Monoid::unit_node;
        for(l += length, r += length; l < r; l >>=1, r >>=1) {
            if(l&1) vl = Monoid::func_fold(vl,node[l++]);
            if(r&1) vr = Monoid::func_fold(node[--r],vr);
        }
        return Monoid::func_fold(vl,vr);
    }

    //range[l,r) return [l,r] search max right
    int prefix_binary_search(int l, int r, TypeNode var) {
        assert(0 <= l && l < length && 0 < r && r <= length);
        TypeNode ret = Monoid::unit_node;
        size_t off = l;
        for(size_t idx = l+length; idx < 2*length && off < r; ){
            if(range[idx].second<=r && !Monoid::func_check(Monoid::func_fold(ret,node[idx]),var)) {
                ret = Monoid::func_fold(ret,node[idx]);
                off = range[idx++].second;
                if(!(idx&1)) idx >>= 1;
            }
            else{
                idx <<=1;
            }
        }
        return off;
    }

    //range(l,r] return [l,r] search max left
    int suffix_binary_search(const int l, const int r, const TypeNode var) {
        assert(-1 <= l && l < (int)length-1 && 0 <= r && r < length);
        TypeNode ret = Monoid::unit_node;
        int off = r;
        for(size_t idx = r+length; idx < 2*length && l < off; ){
            if(l < range[idx].first && !Monoid::func_check(Monoid::func_fold(node[idx],ret),var)) {
                ret = Monoid::func_fold(node[idx],ret);
                off = range[idx--].first-1;
                if(idx&1) idx >>= 1;
            }
            else{
                idx = (idx<<1)+1;
            }
        }
        return off;
    }

    void print(){
        // cout << "node" << endl;
        // for(int i = 1,j = 1; i < 2*length; ++i) {
        // 	cout << node[i] << " ";
        // 	if(i==((1<<j)-1) && ++j) cout << endl;
        // }
        cout << "vector" << endl;
        cout << "{ " << fold(0,1);
        for(int i = 1; i < length; ++i) cout << ", " << fold(i,i+1);
        cout << " }" << endl;
    }
};

/*
 * @title MonoidRangeCompositePointUpdate - [区間一次関数, 点更新]
 * @docs md/operator/monoid/MonoidRangeCompositePointUpdate.md
 */
template<class T> struct MonoidRangeCompositePointUpdate {
    using TypeNode = T;
    inline static constexpr TypeNode unit_node = {-1,Ar{}};
    inline static constexpr TypeNode func_fold(TypeNode l,TypeNode r){
        if(l.first==-1) return r;
        if(r.first==-1) return l;
        for(int i=0;i<r.second.size();++i) r.second[i]=l.second[r.second[i]];
        return {r.first,r.second};
    }
    inline static constexpr TypeNode func_operate(TypeNode l,TypeNode r){return r;}
    inline static constexpr bool func_check(TypeNode nodeVal,TypeNode var){return var == nodeVal;}
};

/**
 * @url 
 * @est
 */ 
int main() {
    cin.tie(0);ios::sync_with_stdio(false);
    int64 N,M; cin >> N >> M;
    vector<RandomizedBinarySearchTree<MonoidRangeSumPointAdd<pair<int64,Ar>>>> vst(N);
    SegmentTree<MonoidRangeCompositePointUpdate<pair<int64,Ar>>> seg(N);

    int Q; cin >> Q;
    while(Q--) {
        int q; cin >> q;
        if(q==1) {
            int64 s,p,a,b;
            cin >> s >> p >> a >> b;
            s--;
            Ar ar;
            for(int i=0;i<MAX_M;++i) ar[i]=i;
            for(int i=a;i<b;++i) ar[i]=i+1;
            ar[b]=a;

            vst[s].insert({p, ar});
            auto zv = vst[s].fold(0,vst[s].size());
            seg.operate(s,zv);
        }
        if(q==2) {
            int64 x,y; cin >> x >> y;
            x--;y--;
            auto xv = vst[x].fold(0,vst[x].size());
            auto yv = vst[y].fold(0,vst[y].size());
            swap(vst[x],vst[y]);
            seg.operate(y,xv);
            seg.operate(x,yv);
        }
        if(q==3) {
            int64 l,r; cin >> l >> r;
            l--;
            auto [flg,br] = seg.fold(l,r);
            Ar ar;
            for(int i=0;i<MAX_M;++i) ar[i]=i;
            for(int i=0;i<MAX_M;++i) {
                if(flg==-1) br[i]=i;
                else br[i]=ar[br[i]];
            }
            for(int i=1;i<=M;++i) cout << br[i] << (i==M?"":" ");
            cout << endl;
        }
    }

    

    return 0;
}
