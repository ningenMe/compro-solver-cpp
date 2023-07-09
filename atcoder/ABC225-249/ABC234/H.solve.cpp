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
 * @title KdTree - 2次元頂点分類木
 * @docs md/geometory/KdTree.md
 */
template<class T> class KdTree{
    struct Point{
        T x,y;
        int idx;
        friend ostream &operator<<(ostream &os, const Point& point) {return os << "{" << point.x << ", " << point.y << ", " << point.idx << "}";}
    };
    struct Node{
        int depth,ch_l,ch_r;
        Point point;
        Node(const Point point,const int depth):point(point),depth(depth),ch_l(-1),ch_r(-1){};
    };
    vector<Node> tree;

    //[l,r)
    void dfs(int depth, int l, int r, vector<Point>& points) {
        if(r-l==1) {
            tree.push_back(Node(points[l],depth));
            return;
        }
        int m = (l+r)/2;
        int root = tree.size();
        if(depth&1) sort(points.begin()+l,points.begin()+r,[&](Point a,Point b){return a.y < b.y;});
        else        sort(points.begin()+l,points.begin()+r,[&](Point a,Point b){return a.x < b.x;});
        tree.push_back(Node(points[m],depth));
        if(l<m) {
            tree[root].ch_l = tree.size();
            dfs(depth+1,l,m,points);
        }
        if(m+1<r) {
            tree[root].ch_r = tree.size();
            dfs(depth+1,m+1,r,points);
        }
    }
    void print(int p) {
        if(p==-1) return;
        print(tree[p].ch_l);
        cout << p << ", " << tree[p].point << ", ";
        print(tree[p].ch_r);
        if(p==0) cout << endl;
    }
public:
    //(x,y)のvector
    KdTree(const vector<pair<T,T>>& arg_points) {
        vector<Point> points(arg_points.size());
        for(int i=0;i<arg_points.size();++i) points[i] = {arg_points[i].first,arg_points[i].second,i};
        dfs(0,0,points.size(),points);
    }
    void print() {
        print(0);
    }
    //x区間[x1,x2],y区間[y1,y2]に囲まれる領域内の数 x1<=x2 && y1 <= y2
    vector<Point> points_in_range(const T& x1,const T& x2,const T& y1,const T& y2) {
        vector<Point> ret;
        stack<int> st; st.push(0);
        while(st.size()) {
            int p=st.top(); st.pop();
            if(x1<=tree[p].point.x&&tree[p].point.x<=x2&&y1<=tree[p].point.y&&tree[p].point.y<=y2) {
                ret.emplace_back(tree[p].point);
            }
            if(tree[p].depth&1) {//y
                if(tree[p].ch_r!=-1 && tree[p].point.y <= y2) st.push(tree[p].ch_r);
                if(tree[p].ch_l!=-1 && y1 <= tree[p].point.y) st.push(tree[p].ch_l);
            }
            else {               //x
                if(tree[p].ch_r!=-1 && tree[p].point.x <= x2) st.push(tree[p].ch_r);
                if(tree[p].ch_l!=-1 && x1 <= tree[p].point.x) st.push(tree[p].ch_l);
            }
        }
        sort(ret.begin(),ret.end(),[&](Point l,Point r){return l.idx < r.idx;});
        return ret;
    }
};

/*
 * @title Distance - 距離
 * @docs md/geometory/Distance.md
 */
template<class T> class Distance{
public:
    //Euclidean distance
    inline static constexpr T euclid(const T& x1, const T& y1, const T& x2, const T& y2) {
        return sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
    }
    //Euclidean distance
    inline static constexpr T euclid_pow2(const T& x1, const T& y1, const T& x2, const T& y2) {
        return (x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2);
    }
    //Chebyshev distance
    inline static constexpr T chebyshev(T x1, T y1, T x2, T y2) {
        return max(abs(x1 - x2),abs(y1 - y2));
    }
    //Manhattan distance
    inline static constexpr T manhattan(T x1, T y1, T x2, T y2) {
        return abs(x1 - x2)+abs(y1 - y2);
    }
    inline static constexpr T between_point_and_line(const T& x,const T& y,const T& x1,const T& y1,const T& x2,const T& y2){
        return abs((y2 - y1)*x+(x1 - x2)*y-(y2-y1)*x1+(x2-x1)*y1)/sqrt((y2 - y1)*(y2 - y1)+(x1 - x2)*(x1 - x2));
    }
};

/**
 * @url 
 * @est
 */ 
int main() {
    cin.tie(0);ios::sync_with_stdio(false);
    int64 N,K; read(N), read(K);
    vector<pair<int64,int64>> vp(N);
    for(int i=0;i<N;++i) {
        int64 x,y; read(x),read(y);
        vp[i]={x,y};
    }
    KdTree<int64> kdt(vp);
    int64 K2 = K*K;
    set<pair<int,int>> st;
    for(int i=0;i<N;++i) {
        auto [x,y] = vp[i];
        auto ps = kdt.points_in_range(x-K,x+K,y-K,y+K);
        for(auto& p: ps) {
            int64 s = p.x, t = p.y;
            int j = p.idx;
            if(i >= j) continue;
            if(Distance<int64>::euclid_pow2(x,y,s,t)<=K2) {
                st.emplace(i+1, j+1);
            }
        }
    }
    cout << st.size() << "\n";
    for(auto& [a,b]: st) {
        cout << a << " " << b << "\n";
    }
    return 0;
}
