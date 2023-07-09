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
template <class T, class U>ostream &operator<<(ostream &o, const pair<T, U>&obj) {o << "{" << obj.first << ", " << obj.second << "}"; return o;}
template <class T, class U>ostream &operator<<(ostream &o, const map<T, U>&obj) {o << "{"; for (auto &x : obj) o << " {" << x.first << " : " << x.second << "}" << ","; o << " }"; return o;}
template <class T>ostream &operator<<(ostream &o, const set<T>&obj) {o << "{"; for (auto itr = obj.begin(); itr != obj.end(); ++itr) o << (itr != obj.begin() ? ", " : "") << *itr; o << "}"; return o;}
template <class T>ostream &operator<<(ostream &o, const multiset<T>&obj) {o << "{"; for (auto itr = obj.begin(); itr != obj.end(); ++itr) o << (itr != obj.begin() ? ", " : "") << *itr; o << "}"; return o;}
template <class T>ostream &operator<<(ostream &o, const vector<T>&obj) {o << "{"; for (int i = 0; i < (int)obj.size(); ++i)o << (i > 0 ? ", " : "") << obj[i]; o << "}"; return o;}
template <class T>ostream &operator<<(ostream &o, const deque<T>&obj) {o << "{"; for (int i = 0; i < (int)obj.size(); ++i)o << (i > 0 ? ", " : "") << obj[i]; o << "}"; return o;}
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
 * @title SegmentTree - 非再帰抽象化セグメント木
 * @docs md/segment-tree/SegmentTree.md
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
 * @title UnionFindTree - Union Find Tree
 * @docs md/union-find-tree/UnionFindTree.md
 */
class UnionFindTree {
    vector<int> parent,maxi,mini;
    inline int root(int n) {
        return (parent[n]<0?n:parent[n] = root(parent[n]));
    }
public:
    UnionFindTree(const int N = 1) : parent(N,-1),maxi(N),mini(N){
        iota(maxi.begin(),maxi.end(),0);
        iota(mini.begin(),mini.end(),0);
    }
    inline bool connected(const int n, const int m) {
        return root(n) == root(m);
    }
    inline void merge(int n,int m) {
        n = root(n);
        m = root(m);
        if (n == m) return;
        if(parent[n]>parent[m]) swap(n, m);
        parent[n] += parent[m];
        parent[m] = n;
        maxi[n] = std::max(maxi[n],maxi[m]);
        mini[n] = std::min(mini[n],mini[m]);
    }
    inline int min(const int n) {
        return mini[root(n)];
    }
    inline int max(const int n) {
        return maxi[root(n)];
    }
    inline int size(const int n){
        return (-parent[root(n)]);
    }
    inline int operator[](const int n) {
        return root(n);
    }
    inline void print() {
        for(int i = 0; i < parent.size(); ++i) cout << root(i) << " ";
        cout << endl;
    }
};

/**
 * @url 
 * @est
 */ 
int main() {
    cin.tie(0);ios::sync_with_stdio(false);
    int N,Q; read(N),read(Q);
    vector<int> L(N,0),R(N,0);
    for(int i=0;i<Q;++i) {
        int l,r; read(l),read(r);
        l--,r--;
        L[l]=1;
        R[r]=1;
    }
    UnionFindTree uf(N);
    for(int i=0;i+1<N;++i) {
        if(R[i] || L[i+1]) continue;
        uf.merge(i,i+1);
    }
    map<int,pair<int,int>> mp;
    for(int i=0;i<N;++i) mp[uf[i]]={uf.min(i),uf.max(i)};
    
    return 0;
}
