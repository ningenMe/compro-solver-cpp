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
 * @title SegmentTree2D - 非再帰抽象化セグメント木2D
 * @docs md/segment-tree/SegmentTree2D.md
 */
template<class Monoid> class SegmentTree2D {
    using TypeNode = typename Monoid::TypeNode;
    class SegmentTree {
        size_t length;
        vector<TypeNode> node;
    public:
        //unitで初期化
        SegmentTree(const size_t num) {
            for (length = 1; length <= num; length *= 2);
            node.resize(2 * length, Monoid::unit_node);
            for (int i = length - 1; i >= 0; --i) node[i] = Monoid::func_fold(node[(i<<1)+0],node[(i<<1)+1]);
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
        void print() {
            cout << "{";
            for(int i=0; i < length; ++i) cout << fold(i,i+1) << " }"[i+1==length];
            cout << endl;
        }
    };
    size_t height,width;
    vector<SegmentTree> node;
public:
    SegmentTree2D(const size_t h, const size_t w):width(w) {
        for (height = 1; height <= h; height *= 2);
        SegmentTree seg(width);
        node.resize(2 * height, seg);
        for (int i = height - 1; i >= 0; --i) {
            for(int j=0; j < width; ++j) {
                node[i].operate(j, Monoid::func_fold(node[(i<<1)+0].fold(j,j+1),node[(i<<1)+1].fold(j,j+1)));
            }
        }
    }
    //[u,u+1)*[l,l+1) に operate
    void operate(size_t u, size_t l, const TypeNode var) {
        if(u < 0 || height <= u || l < 0 || width <= l) return;
        u += height;
        node[u].operate(l, var);
        while(u >>= 1) node[u].operate(l, Monoid::func_fold(node[(u<<1)+0].fold(l,l+1),node[(u<<1)+1].fold(l,l+1)));
    }
    //[u,d),[l,r)
    TypeNode fold(int u, int d, int l, int r) {
        if(u < 0 || height <= u || d < 0 || height < d || l < 0 || width <= l || r < 0 || width < r) return Monoid::unit_node;
        TypeNode vu = Monoid::unit_node, vd = Monoid::unit_node;
        for(u += height, d += height; u < d; u >>=1, d >>=1) {
            if(u&1) vu = Monoid::func_fold(vu,node[u++].fold(l,r));
            if(d&1) vd = Monoid::func_fold(node[--d].fold(l,r),vd);
        }
        return Monoid::func_fold(vu,vd);
    }
    void print() {
        for(int i=height; i < 2*height; ++i) {
            node[i].print();
        }
    }
};

template<class T> struct MonoidRangeSumPointUpdate {
    using TypeNode = T;
    inline static constexpr TypeNode unit_node = 0;
    inline static constexpr TypeNode func_fold(TypeNode l,TypeNode r){return (l+r);}
    inline static constexpr TypeNode func_operate(TypeNode l,TypeNode r){return r;}
    inline static constexpr bool func_check(TypeNode nodeVal,TypeNode var){return var > nodeVal;}
};
template<class T> struct MonoidRangeMinPointUpdate {
    using TypeNode = T;
    inline static constexpr TypeNode unit_node = {10000,10000,10000};
    inline static constexpr TypeNode func_fold(TypeNode l,TypeNode r){return min(l,r);}
    inline static constexpr TypeNode func_operate(TypeNode l,TypeNode r){return r;}
    inline static constexpr bool func_check(TypeNode nodeVal,TypeNode var){return var > nodeVal;}
};

auto seg_sum = multivector(301,301,0);
SegmentTree2D<MonoidRangeMinPointUpdate<tuple<int,int,int>>> seg_min(300,300);

int N,M;
int ans=0;
set<tuple<int,int,int,int>> st;

//[u,d),[l,r)
void rec(int u, int d, int l, int r) {
    if(st.count({u,d,l,r})) return;
    st.emplace(u,d,l,r);

    auto [mi,i,j] = seg_min.fold(u,d,l,r);
    int su = seg_sum[d][r]-seg_sum[d][l]-seg_sum[u][r]+seg_sum[u][l];

    chmax(ans,su*mi);
    if(u<i) rec(u,i,l,r);
    if(l<j) rec(u,d,l,j);
    if(i+1<d) rec(i+1,d,l,r);
    if(j+1<r) rec(u,d,j+1,r);
}

/**
 * @url 
 * @est
 */ 
int main() {
    cin.tie(0);ios::sync_with_stdio(false);
    read(N),read(M);
    for(int i=0;i<N;++i) {
        for(int j=0;j<M;++j) {
            int a; read(a);
            seg_sum[i+1][j+1]+=a;
            seg_min.operate(i,j,{a,i,j});
        }
    }
    for(int i=0;i<=300;++i) {
        for(int j=1;j<=300;++j) seg_sum[i][j]+=seg_sum[i][j-1];
    }
    for(int j=0;j<=300;++j) {
        for(int i=1;i<=300;++i) seg_sum[i][j]+=seg_sum[i-1][j];
    }

    rec(0,N,0,M);
    cout << ans << endl;

    return 0;
}
