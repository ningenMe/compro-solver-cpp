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

/*
 * @title RangeFrequencyQuery - 区間freq
 * @docs md/segment-tree/RangeFrequencyQuery.md
 */
template<class T> class RangeFrequencyQuery {
    template<class U> class BinarySearchTreeSet {
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
            U value;
            int size;
            Node() {build();}
            Node(U v) : value(v) {build();}
            friend ostream &operator<<(ostream &os, const Node* node) {return os << "{" << node->value << ", " << node->range_value << ", " << node->size << "}";}
        };
        Node* root;
        inline int size(Node *node) const {return node==nullptr ? 0 : node->size;}
        inline Node* update(Node *node) {
            node->size = size(node->left) + size(node->right) + 1;
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
        inline int lower_bound(Node *node, U value) const {
            if (node==nullptr) return 0;
            if (value <= node->value) return lower_bound(node->left, value);
            else return size(node->left) + lower_bound(node->right, value) + 1;
        }
        inline int upper_bound(Node *node, U value) const {
            if (node==nullptr) return 0;
            if (value < node->value) return upper_bound(node->left, value);
            else return size(node->left) + upper_bound(node->right, value) + 1;
        }
        inline void insert_impl(const U value) {
            pair<Node*, Node*> sub = split_impl(this->root, lower_bound(this->root,value));
            this->root = this->merge_impl(this->merge_impl(sub.first, new Node(value)), sub.second);
        }
        inline void erase_impl(const U value) {
            int k1 = lower_bound(value), k2 = upper_bound(value);
            if(k1==k2) return;
            auto sub = split_impl(this->root,k1);
            this->root = merge_impl(sub.first, split_impl(sub.second, 1).second);
        }
    public:
        BinarySearchTreeSet() : root(nullptr) {}
        inline int size() {return size(this->root);}
        inline int empty(void) {return bool(size()==0);}
        inline Node* merge(Node *left, Node *right) {return merge_impl(left,right);}
        inline pair<Node*, Node*> split(int k) {return split_impl(this->root,k);}
        inline void insert(const U value) {insert_impl(value);}
        inline void erase(const U value) {erase_impl(value);}
        inline int lower_bound(U value) const {return lower_bound(this->root,value);}
        inline int upper_bound(U value) const {return upper_bound(this->root,value);}
        inline int count(U value) const {return upper_bound(value) - lower_bound(value);}
    };
    size_t length;
    size_t num;
    vector<BinarySearchTreeSet<T>> node;
    void insert_impl(size_t idx, const T var) {
        if(idx < 0 || length <= idx) return;
        idx += length;
        node[idx].insert(var);
        while(idx >>= 1) node[idx].insert(var);
    }
    void erase_impl(size_t idx, const T var) {
        if(idx < 0 || length <= idx) return;
        idx += length;
        node[idx].erase(var);
        while(idx >>= 1) node[idx].erase(var);
    }
    int range_freq_upper_impl(int l, int r, const T upper) const {
        if (l < 0 || length <= l || r < 0 || length < r) return 0;
        int ret=0;
        for(l += length, r += length; l < r; l >>=1, r >>=1) {
            if(l&1) ret += node[l++].lower_bound(upper);
            if(r&1) ret += node[--r].lower_bound(upper);
        }
        return ret;
    }
    int range_freq_impl(int l, int r, const T val) const {
        if (l < 0 || length <= l || r < 0 || length < r) return 0;
        int ret=0;
        for(l += length, r += length; l < r; l >>=1, r >>=1) {
            if(l&1) ret += node[l++].count(val);
            if(r&1) ret += node[--r].count(val);
        }
        return ret;
    }
public:
    //unitで初期化
    RangeFrequencyQuery(const vector<T> & vec) {
        for (length = 1; length <= vec.size(); length *= 2);
        node.resize(2 * length, BinarySearchTreeSet<T>());
        for (int i=0; i < vec.size(); ++i) {
            insert(i, vec[i]);
        }
    }
    //idx番目の要素にinsert
    void insert(const size_t idx, const T var) { insert_impl(idx, var);}
    //idx番目の要素にdelete
    void erase(size_t idx, const T var) { erase_impl(idx, var);}
    //[l,r) range freq of val (val < upper)
    int range_freq_upper(const int l, const int r, const T upper) const {return range_freq_upper_impl(l,r,upper);}
    //[l,r) range freq of val (lower <= val < upper)
    int range_freq_lower_upper(const int l, const int r, const T lower, const T upper) const {return range_freq_upper_impl(l,r,upper) - range_freq_upper_impl(l,r,lower);}
    //[l,r) range freq of val
    int range_freq(const int l, const int r, const T val) const {return range_freq_impl(l,r,val);}
};

/**
 * @url 
 * @est
 */ 
int main() {
    cin.tie(0);ios::sync_with_stdio(false);
    int N,Q; read(N); read(Q);
    vector<int64> A(N);
    for(int i=0;i<N;++i) read(A[i]);
    RangeFrequencyQuery<int64> rfq(A);
    while(Q--) {
        int l,r,x;
        read(l); read(r); read(x);
        cout << rfq.range_freq(l,r,x) << "\n";
    }
    
    return 0;
}