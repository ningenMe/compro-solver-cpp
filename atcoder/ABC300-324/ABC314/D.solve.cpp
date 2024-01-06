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
    inline static void read(char &x) {string tmp; read_string(tmp); x=tmp[0];}
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
 * @title DualSegmentTree - 非再帰抽象化双対セグメント木
 * @docs md/segment-tree/DualSegmentTree.md
 */
template<class Monoid> class DualSegmentTree {
    using TypeNode = typename Monoid::TypeNode;
    using TypeLazy = typename Monoid::TypeLazy;
    size_t length;
    size_t height;
    vector<TypeNode> node;
    vector<TypeLazy> lazy;

    void propagate(int k) {
        if(lazy[k] == Monoid::unit_lazy) return;
        if(k >=length) node[k-length] = Monoid::func_operate(node[k-length],lazy[k],k-length,k-length+1);
        if(k < length) lazy[2*k+0] = Monoid::func_lazy(lazy[2*k+0],lazy[k]);
        if(k < length) lazy[2*k+1] = Monoid::func_lazy(lazy[2*k+1],lazy[k]);
        lazy[k] = Monoid::unit_lazy;
    }
    void build(const size_t num) {
        for (length = 1,height = 0; length <= num; length *= 2, height++);
        node.resize(1 * length, Monoid::unit_node);
        lazy.resize(2 * length, Monoid::unit_lazy);
    }

public:

    //unitで初期化
    DualSegmentTree(const size_t num) {
        build(num);
    }
    // //同じinitで初期化
    DualSegmentTree(const size_t num, const TypeNode init) {
        build(num);
        for (int i = 0; i < num; ++i) node[i] = init;
    }
    //vectorで初期化
    DualSegmentTree(const vector<TypeNode>& vec) {
        build(vec.size());
        for (int i = 0; i < vec.size(); ++i) node[i] = vec[i];
    }

    //operate [a,b)
    void operate(int a, int b, TypeLazy x) {
        int l = a + length, r = b + length - 1;
        for (int i = height; 0 < i; --i) propagate(l >> i), propagate(r >> i);
        for(r++; l < r; l >>=1, r >>=1) {
            if(l&1) lazy[l] = Monoid::func_lazy(lazy[l],x), propagate(l),l++;
            if(r&1) --r,lazy[r] = Monoid::func_lazy(lazy[r],x), propagate(r);
        }
    }

    //fold [a,a+1)
    TypeNode fold(int a) {
        int l = a + length;
        for (int i = height; 0 <= i; --i) propagate(l >> i);
        return node[a];
    }

    void print(){
        // cout << "lazy" << endl;
        // for(int i = 1,j = 1; i < 2*length; ++i) {
        //     cout << lazy[i] << " ";
        //     if(i==((1<<j)-1) && ++j) cout << endl;
        // }
        cout << "vector" << endl;
        cout << "{ " << fold(0);
        for(int i = 1; i < length; ++i) cout << ", " << fold(i);
        cout << " }" << endl;
    }
};

/*
 * @title MonoidRangeFoldMinRangeOperateAdd - fold:区間min, operate:区間加算
 * @docs md/operator/monoid-lazy/MonoidRangeFoldMinRangeOperateAdd.md
 */
template<class T, class U> struct MonoidRangeFoldVoidRangeOperateUpdate {
    using TypeNode = T;
    using TypeLazy = U;
    inline static constexpr TypeNode unit_node = {26, -1};
    inline static constexpr TypeLazy unit_lazy = {26, -1};
    inline static constexpr TypeNode func_fold(TypeNode l,TypeNode r){return {26, -1};}
    inline static constexpr TypeLazy func_lazy(TypeLazy old_lazy,TypeLazy new_lazy){
        if(new_lazy.first == 26) {
            return {old_lazy.first, new_lazy.second};
        }
        else {
            return new_lazy;
        }
    }
    inline static constexpr TypeNode func_operate(TypeNode node,TypeLazy lazy,int l, int r){
        if(lazy.first == 26) {
            return {node.first, lazy.second};
        }
        else {
            return lazy;
        }
    }
};

using P = pair<int,int>;
P trans(char c) {
    if(0 <= c-'a' && c-'a'<26) {
        return {c-'a',0};
    }
    else {
        return {c-'A',1};
    }
}

/**
 * @url 
 * @est
 */ 
int main() {
    cin.tie(0);ios::sync_with_stdio(false);
    
    int N; read(N);
    DualSegmentTree<MonoidRangeFoldVoidRangeOperateUpdate<P,P>> seg(N);
    string S; read(S);
    for(int i=0;i<N;++i) {
        char c = S[i];
        seg.operate(i,i+1,trans(c));
    }
    int Q; read(Q);
    while(Q--) {
        int t,x; read(t),read(x);
        char c; read(c);
        x--;
        if(t==1) {
            seg.operate(x,x+1,trans(c));
        }
        if(t==2) {
            seg.operate(0,N,{26,0});
        }
        if(t==3) {
            seg.operate(0,N,{26,1});
        }
    }
    for(int i=0;i<N;++i) {
        auto [d,flg] = seg.fold(i);
        char c = char((flg ? 'A':'a') + d);
        cout << c;
    }
    cout << "\n";
    return 0;
}
