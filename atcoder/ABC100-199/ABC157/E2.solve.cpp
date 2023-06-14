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
    inline static void read_char(char &x) {
        char ch;
        ch=getchar();
        endline_skip(ch);
        for(;(ch != ch_s && ch!=ch_l); ch = getchar()) x=ch;
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
    inline static void read(char &x) {read_char(x);}
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
 * @title RangeFrequencyQueryTree - 区間freqTree
 * @docs md/segment-tree/RangeFrequencyQueryTree.md
 */
template<class T> class RangeFrequencyQueryTree {
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
        inline T get_root() const {return root->value;}
    };
    size_t length;
    vector<BinarySearchTreeSet<T>> node;
    void insert_impl(size_t idx, const T var) {
        if(idx < 0 || length <= idx) return;
        idx += length;
        node[idx].insert(var);
        while(idx >>= 1) node[idx].insert(var);
    }
    void erase_impl(size_t idx) {
        if(idx < 0 || length <= idx) return;
        idx += length;
        if(node[idx].empty()) return;
        T val = node[idx].get_root();
        node[idx].erase(val);
        while(idx >>= 1) node[idx].erase(val);
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
    RangeFrequencyQueryTree(const size_t num) {
        for (length = 1; length <= num; length *= 2);
        node.resize(2 * length, BinarySearchTreeSet<T>());
    }
    RangeFrequencyQueryTree(const vector<T> & vec) {
        for (length = 1; length <= vec.size(); length *= 2);
        node.resize(2 * length, BinarySearchTreeSet<T>());
        for (int i=0; i < vec.size(); ++i) {
            insert_impl(i, vec[i]);
        }
    }
    //idx番目の要素をupdate
    void update(const size_t idx, const T var) { erase_impl(idx); insert_impl(idx, var);}
    //[l,r) range freq of val (val < upper)
    int range_freq_upper(const int l, const int r, const T upper) const {return range_freq_upper_impl(l,r,upper);}
    //[l,r) range freq of val (lower <= val < upper)
    int range_freq_lower_upper(const int l, const int r, const T lower, const T upper) const {return range_freq_upper_impl(l,r,upper) - range_freq_upper_impl(l,r,lower);}
    //[l,r) range freq of val
    int range_freq(const int l, const int r, const T val) const {return range_freq_impl(l,r,val);}
};

template<class T> class RangeSetQueryTree {
    using size_t = unsigned int;
    RangeFrequencyQueryTree<size_t> tree;
    unordered_map<T,set<size_t>> mp;
    vector<T> ar;
    size_t length;
    size_t range_set_size_impl(const int l, const int r) const {
        if (l < 0 || length <= l || r < 0 || length < r) return 0;
        return (r-l) - tree.range_freq_upper(l,r,r);
    }
    void update_impl(const size_t idx, const T next) {
        T prev = ar[idx];
        queue<pair<size_t,size_t>> q;
        //更新前の1つ左に影響があるか確認
        {
            auto itr_l = mp[prev].find(idx);
            auto itr_r = mp[prev].upper_bound(idx);
            if(itr_l != mp[prev].begin()) {
                --itr_l;
                q.emplace((*itr_l),(*itr_r));
            }
            mp[prev].erase(idx);
        }
        {
            if(mp[next].size()==0) mp[next].insert(length);
            auto itr_r = mp[next].upper_bound(idx);
            q.emplace(idx,(*itr_r));
            //更新後の1つ左に影響があるか確認
            if(itr_r != mp[next].begin()) {
                --itr_r;
                q.emplace((*itr_r),idx);
            }
            mp[next].insert(idx);
        }
        ar[idx] = next;
        while(q.size()) {
            auto [l,r]=q.front(); q.pop();
            tree.update(l,r);
        }
    }
public:
    RangeSetQueryTree(const vector<T> & vec):ar(vec),tree(vec.size()) {
        length = vec.size();
        for(size_t i = 0; i<length; ++i) mp[ar[i]].insert(i);
        for(auto& [_,st]: mp) {
            st.insert(length);
            int cnt=0;
            size_t l=length,r=length; //このl,rは閉区間 [l,r]
            for(size_t idx: st) {
                r=idx;
                if(cnt) {
                    tree.update(l,r);
                }
                l=r;
                cnt++;
            }
        }
    }
    //idx番目の要素をupdate
    void update(const size_t idx, const T val) { update_impl(idx,val); }
    //[l,r) range set size 
    size_t range_set_size(const int l, const int r) const {return range_set_size_impl(l,r);}
};

/**
 * @url 
 * @est
 */ 
int main() {
    cin.tie(0);ios::sync_with_stdio(false);
    int N; read(N);
    string S; read(S);
    vector<int> A(N);
    for(int i=0;i<N;++i) {
        A[i]=S[i]-'a';
    }
    RangeSetQueryTree<int> rsqt(A);
    int Q; read(Q);
    while(Q--) {
        int q; read(q);
        if(q==1) {
            int i; char c;
            read(i); read(c);
            --i;
            rsqt.update(i,c-'a');
        }
        if(q==2) {
            int l,r; read(l); read(r); --l;
            cout << rsqt.range_set_size(l,r) << "\n";
        }
    }

    return 0;
}
