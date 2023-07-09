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
 * @title RangeIntegerFrequencyQuerySqrtTree - integer専用区間freq
 * @docs md/segment-tree/RangeIntegerFrequencyQuerySqrtTree.md
 */
template<unsigned int bit_length=20> class RangeIntegerFrequencyQuerySqrtTree {
    using u64 = unsigned long long;
    class SimpleBinaryTrie {
        struct Node {
            Node *left, *right;
            u64 size;
            Node(): size(0) {left=right=nullptr;}
        };
        Node* root;
        size_t size(Node* node) const {return (node==nullptr ? 0 : node->size);}
        bool empty(Node* node) const {return size(node) == 0;}
        void print(Node* node,u64 i, u64 val) {
            if(i == bit_length) {
                cout << "{" << val << ":" << size(node) << "} ";
                return;
            }
            if(node->left != nullptr) {
                print(node->left, i+1, val);
            }
            if(node->right != nullptr) {
                print(node->right, i+1, (val | (1UL<<(bit_length-1-i))) );
            }
        }
    public:
        SimpleBinaryTrie(): root(new Node()) {}
        void insert(const u64 val) {
            Node* curr = root; stack<Node*> st;
            for(u64 i=0; i < bit_length; ++i) {
                u64 j = ((val>>(bit_length-1-i)) & 1UL);
                st.push(curr);
                if(j) {
                    if(curr->right != nullptr) { curr = curr->right;}
                    else {
                        Node* next = new Node();
                        curr->right = next;
                        curr = next;
                    }
                }
                else {
                    if(curr->left != nullptr) curr = curr->left;
                    else {
                        Node* next = new Node();
                        curr->left = next;
                        curr = next;
                    }
                }
            }
            curr->size += 1;
            while(st.size()) {
                auto node=st.top(); st.pop();
                node->size = size(node->left) + size(node->right);
            }
        }
        void erase(const u64 val) {
            Node* curr = root; stack<Node*> st;
            for(u64 i=0; i < bit_length; ++i) {
                u64 j = ((val>>(bit_length-1-i)) & 1UL);
                st.push(curr);
                if(j) {
                    if(curr->right != nullptr) curr = curr->right;
                    else return;
                }
                else {
                    if(curr->left != nullptr) curr = curr->left;
                    else return;
                }
            }
            if(empty(curr)) return;
            curr->size -= 1;
            while(st.size()) {
                auto node=st.top(); st.pop();
                node->size = size(node->left) + size(node->right);
            }
        }
        size_t size() const {return size(root);}
        bool empty() const {return empty(root);}
        u64 kth_smallest(u64 k) const {
            Node* curr = root; u64 val=0;
            for(u64 i=0; i < bit_length; ++i) {
                u64 j = 1UL << (bit_length-1-i);
                u64 sz_l = size(curr->left);
                if(k<sz_l) curr = curr->left;
                else {
                    val |= j;
                    k -= sz_l;
                    curr = curr->right;
                }
            }
            return val;
        }
        size_t lower_bound(const u64 val) const {
            Node* curr = root;
            u64 k=0;
            for(u64 i=0; i < bit_length; ++i) {
                u64 j = ((val>>(bit_length-1-i)) & 1UL);
                if(j) {
                    k+=size(curr->left);
                    if(curr->right != nullptr) curr = curr->right;
                    else break;
                }
                else {
                    if(curr->left != nullptr) curr = curr->left;
                    else break;
                }
            }
            return k;
        }
        size_t count(const u64 val) const {
            Node* curr = root;
            for(u64 i=0; i < bit_length; ++i) {
                u64 j = ((val>>(bit_length-1-i)) & 1);
                if(j) {
                    if(curr->right != nullptr) curr = curr->right;
                    else return 0;
                }
                else {
                    if(curr->left != nullptr) curr = curr->left;
                    else return 0;
                }
            }
            return size(curr);
        }
        void print() {
            cout << "{"; print(root,0,0); cout << "} ";
        }
    };
    size_t length;
    size_t bucket_size;
    vector<SimpleBinaryTrie> node0;
    vector<u64> node1;
    inline static constexpr u64 inf = 1UL << bit_length;
    void insert_impl(size_t idx, const u64 val) {
        if(idx < 0 || length <= idx) return;
        node0[idx/bucket_size].insert(val);
        node1[idx]=val;
    }
    void erase_impl(size_t idx) {
        if(idx < 0 || length <= idx) return;
        if(node1[idx]==inf) return;
        u64 val = node1[idx];
        node0[idx/bucket_size].erase(val);
        node1[idx]=inf;
    }
    int range_freq_upper_impl(int l, int r, const u64 upper) const {
        if (l < 0 || length <= l || r < 0 || length < r) return 0;

        int ret=0;
        if(r-l <= bucket_size) {
            for(int i=l; i<r; ++i) ret += (node1[i] < upper);
            return ret;         
        }
        int bl0 = l / bucket_size + !!(l%bucket_size), br0 = r / bucket_size;
        int bl1 = bl0 * bucket_size, br1 = br0 * bucket_size;

        for(int i=l; i < min(bl1,r); ++i) ret += (node1[i] < upper);
        for(int i=bl0; i < br0; ++i) ret += node0[i].lower_bound(upper);
        for(int i=max(br1,l); i < r; ++i) ret += (node1[i] < upper);

        return ret;
    }
    int range_freq_impl(int l, int r, const u64 val) const {
        if (l < 0 || length <= l || r < 0 || length < r) return 0;
        int ret=0;
        if(r-l <= bucket_size) {
            for(int i=l; i<r; ++i) ret += (node1[i] == val);
            return ret;         
        }
        int bl0 = l / bucket_size + !!(l%bucket_size), br0 = r / bucket_size;
        int bl1 = bl0 * bucket_size, br1 = br0 * bucket_size;

        for(int i=l; i < min(bl1,r); ++i) ret += (node1[i] == val);
        for(int i=bl0; i < br0; ++i) ret += node0[i].count(val);
        for(int i=max(br1,l); i < r; ++i) ret += (node1[i] == val);

        return ret;
    }
public:
    RangeIntegerFrequencyQuerySqrtTree(const u64 length): length(length), node1(length,inf) {
        bucket_size = 5*sqrt(length);
        if(!bucket_size) bucket_size=1;
        node0.resize(length / bucket_size + 1);
    }
    //idx番目の要素をupdate
    void update(const size_t idx, const u64 val) { erase_impl(idx); insert_impl(idx, val);}
    //idx番目の要素をerase
    void erase(const size_t idx) { erase_impl(idx); }
    //[l,r) range freq of val (val < upper)
    int range_freq_upper(const int l, const int r, const u64 upper) const {return range_freq_upper_impl(l,r,upper);}
    //[l,r) range freq of val (lower <= val < upper)
    int range_freq_lower_upper(const int l, const int r, const u64 lower, const u64 upper) const { return range_freq_upper_impl(l,r,upper) - range_freq_upper_impl(l,r,lower);}
    //[l,r) range freq of val
    int range_freq(const int l, const int r, const u64 val) const {return range_freq_impl(l,r,val);}
    void print() { 
        cout << length << " " << bucket_size << endl;
        for(int i= 0; i < length / bucket_size + 1; ++i) node0[i].print();
        cout << endl;
        for(int i= 0; i < length; ++i) cout << node1[i] << " \n"[i==length-1];
        cout << endl;
    }
};

template<class T, unsigned int bit_length=20> class RangeSetQuerySqrtTree {
    using size_t = unsigned int;
    RangeIntegerFrequencyQuerySqrtTree<bit_length> tree;
    unordered_map<T,set<size_t>> mp;
    vector<T> ar;
    size_t length;
    size_t range_set_size_impl(const int l, const int r) const {
        if (l < 0 || length <= l || r < 0 || length < r) return 0;
        return (r-l) - tree.range_freq_upper(l,r,r);
    }
    void update_impl(const size_t idx, const T next) {
        T prev = ar[idx];
        //更新前の1つ左に影響があるか確認
        {
            auto itr_r = mp[prev].lower_bound(idx);
            //左が存在するなら影響あり
            if(itr_r != mp[prev].begin()) {
                auto itr_l=itr_r;
                itr_l--;
                itr_r++;
                if(itr_r==mp[prev].end()) tree.erase((*itr_l));
                else tree.update((*itr_l),(*itr_r));
            }
            mp[prev].erase(idx);
        }
        //更新後の1つ左に影響があるか確認
        {
            mp[next].insert(idx);
            auto itr_r = mp[next].upper_bound(idx);
            if(itr_r==mp[next].end()) tree.erase(idx);
            else tree.update(idx,(*itr_r));

            //左が存在するなら影響あり
            auto itr_l = mp[next].lower_bound(idx);
            if(itr_l != mp[next].begin()) {
                itr_l--;
                tree.update((*itr_l),idx);
            }
        }
        ar[idx] = next;
    }
public:
    RangeSetQuerySqrtTree(const vector<T> & vec):ar(vec),tree(vec.size()) {
        length = vec.size();
        for(size_t i = 0; i<length; ++i) mp[ar[i]].insert(i);
        for(auto& [_,st]: mp) {
            size_t l=length,r=length; //このl,rは閉区間 [l,r]
            for(size_t idx: st) {
                r=idx;
                if(l<length && r<length) tree.update(l,r);
                l=r; 
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
    RangeSetQuerySqrtTree<int> rsqt(A);
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
