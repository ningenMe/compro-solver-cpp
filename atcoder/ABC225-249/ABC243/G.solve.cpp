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
 * @title DynamicSegmentTree - 非再帰抽象化動的セグメント木
 * @docs md/segment-tree/DynamicSegmentTree.md
 */
template<class Monoid> class DynamicSegmentTree {
    using TypeNode = typename Monoid::TypeNode;
    using i64 = long long;

    struct Node{
        Node *left, *right;
        TypeNode val;
        Node():left(nullptr),right(nullptr),val(Monoid::unit_node) {}
    };

    TypeNode dfs(i64 l,i64 r,i64 nl,i64 nr,Node* node) {
        if(l <= nl && nr <= r) return node->val;
        if(nr <= l || r <= nl) return Monoid::unit_node;
        TypeNode vl=Monoid::unit_node, vr=Monoid::unit_node;
        i64 m = (nl+nr)>>1;
        if(node->left)  vl = dfs(l,r,nl,m,node->left);
        if(node->right) vr = dfs(l,r,m,nr,node->right);
        return Monoid::func_fold(vl,vr);
    }

    i64 length;
    Node *root;
public:
    //unitで初期化
    DynamicSegmentTree() : length(1) {
        root = new Node();
    }
    //[idx,idx+1)
    void operate(i64 idx, const TypeNode val) {
        if(idx < 0) return;
        for (;length <= idx; length *= 2) {
            Node *new_root = new Node();
            TypeNode val = root->val;
            new_root->left = root;
            root = new_root;
            root->val = val;
        }
        Node* node = root;
        i64 l = 0, r = length, m;
		stack<Node*> st;

        while(r-l>1) {
			st.push(node);
            m = (r+l)>>1;
            if(idx<m) {
                r = m;
                if(!node->left) node->left=new Node();
                node = node->left;
            }
            else {
                l = m;
                if(!node->right) node->right = new Node();
                node = node->right;
            }
        }
        node->val = Monoid::func_operate(node->val,val);
		while(st.size()) {
			node = st.top(); st.pop();
			TypeNode vl=Monoid::unit_node, vr=Monoid::unit_node;
			if(node->left)  vl = node->left->val;
			if(node->right) vr = node->right->val;
			node->val = Monoid::func_fold(vl,vr);
		}
    }

    //[l,r)
    TypeNode fold(i64 l, i64 r) {
        if (l < 0 || length <= l || r < 0) return Monoid::unit_node;
        return dfs(l,r,0,length,root);
    }
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
    DynamicSegmentTree<MonoidRangeSumPointAdd<long long>> dp0,dp1;
    //dp0: iから1に行くまでの経路。iは i=x^2のみ
    //dp1: dp0[i]*((i+1)^2 - (i)^2)
    dp0.operate(1,1);
    dp1.operate(1,(4-1)*1);
    set<int64> st;
    st.insert(1);

    int64 M = 100000;
    //1, 4, 9, 16, 25
    //1, 2, 2, 5, 
    for(int64 x=2; x<=M; ++x) {
        int64 x2 = x*x;
        int64 z2 = (x+1)*(x+1);
        auto itr = st.upper_bound(x);
        itr--;
        int64 y2 = *itr;
        //y2 < x < x^2
        int64 cnt = dp0.fold(y2,y2+1) * (x-y2+1) + dp1.fold(0,y2);
        dp0.operate(x2,cnt);
        dp1.operate(x2,(z2-x2)*cnt);
        st.insert(x2);
    }

    int64 T; read(T);
    while(T--) {
        int64 x2; read(x2);
        int64 x = sqrtl(x2);
        auto itr = st.upper_bound(x);
        itr--;
        int64 y2 = *itr;
        int64 cnt = dp0.fold(y2,y2+1) * (x-y2+1) + dp1.fold(0,y2);
        cout << cnt << "\n";
    }
    return 0;
}
