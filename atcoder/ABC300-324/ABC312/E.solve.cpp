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

template<class T> class IntersectRectangle {
    class BinaryIndexedTree {
        size_t length; vector<T> node;
    public:
        BinaryIndexedTree(const size_t num) { for (length = 1; length < num; length *= 2); node.resize(length+1, 0);}
        void operate(size_t idx, T val) { for (++idx; idx <= length; idx += idx & -idx) node[idx] += val; }
        T fold(size_t idx) { T res = 0; for (idx = min(length,idx); idx > 0; idx -= idx & -idx) res += node[idx]; return res;}
        void clear() {for(size_t i = 0; i <= length; ++i) node[i] = 0;}
    };
    size_t N;
    vector<int> count;
    void build(vector<T> vl, vector<T> vr, vector<T> vd, vector<T> vu) {
        N = vl.size();
        assert(vr.size() == N);
        assert(vd.size() == N);
        assert(vu.size() == N);
        for(size_t i = 0; i < N; ++i) {
            assert(vl[i] < vr[i] && vd[i] < vu[i]);
        }
        //x,yそれぞれで座圧
        vector<T> sorted_x(2*N),sorted_y(2*N);
        for(size_t i=0;i<N;++i) {
            sorted_x[2*i+0]=vl[i];
            sorted_x[2*i+1]=vr[i];
            sorted_y[2*i+0]=vd[i];
            sorted_y[2*i+1]=vu[i];
        }
        sort(sorted_x.begin(), sorted_x.end());
        sort(sorted_y.begin(), sorted_y.end());
        vector<size_t> zl(N),zr(N),zd(N),zu(N);
        for(size_t i=0;i<N;++i) {
            zl[i] = lower_bound(sorted_x.begin(), sorted_x.end(), vl[i]) - sorted_x.begin();
            zr[i] = lower_bound(sorted_x.begin(), sorted_x.end(), vr[i]) - sorted_x.begin();
            zd[i] = lower_bound(sorted_y.begin(), sorted_y.end(), vd[i]) - sorted_y.begin();
            zu[i] = lower_bound(sorted_y.begin(), sorted_y.end(), vu[i]) - sorted_y.begin();
        }
        //   |  | 
        // --|--|--
        //   | s| 
        // --|--|--
        //   |  |
        // 領域sに対して、sと共有領域を持たないものを包除原理で数える {左|右|上|下} - {左上|左下|右上|右下}
        count.resize(N,0);
        BinaryIndexedTree bit(2*N);
        {
            for(size_t i=0;i<N;++i) bit.operate(zr[i]-1,1);
            for(size_t i=0;i<N;++i) count[i] += bit.fold(zl[i]);
            bit.clear();
            for(size_t i=0;i<N;++i) bit.operate(zl[i],1);
            for(size_t i=0;i<N;++i) count[i] += N-bit.fold(zr[i]);
            bit.clear();
            for(size_t i=0;i<N;++i) bit.operate(zu[i]-1,1);
            for(size_t i=0;i<N;++i) count[i] += bit.fold(zd[i]);
            bit.clear();
            for(size_t i=0;i<N;++i) bit.operate(zd[i],1);
            for(size_t i=0;i<N;++i) count[i] += N-bit.fold(zu[i]);
            bit.clear();
        }
        vector<tuple<size_t,int,size_t>> sorted_zx;
        BinaryIndexedTree bit_u(2*N),bit_d(2*N);
        {
            for(size_t i=0;i<N;++i) sorted_zx.emplace_back(zl[i],1,i), sorted_zx.emplace_back(zr[i],0,i);
            sort(sorted_zx.begin(), sorted_zx.end());
        }
        {
            for(size_t j=0;j<2*N;++j) {
                auto [_,lr,i] = sorted_zx[j];
                if(lr == 1) {
                    count[i] -= bit_u.fold(zd[i]);
                    count[i] -= bit_d.fold(2*N)-bit_d.fold(zu[i]);
                }
                if(lr == 0) {
                    bit_d.operate(zd[i],1);
                    bit_u.operate(zu[i]-1,1);
                }
            }
            bit_d.clear();
            bit_u.clear();
            for(size_t j=2*N-1;;--j) {
                auto [_,lr,i] = sorted_zx[j];
                if(lr == 1) {
                    bit_d.operate(zd[i],1);
                    bit_u.operate(zu[i]-1,1);
                }
                if(lr == 0) {
                    count[i] -= bit_u.fold(zd[i]);
                    count[i] -= bit_d.fold(2*N)-bit_d.fold(zu[i]);
                }
                if(j==0) break;
            }
        }
    }
public:
    //[l,r) x [d,u) の長方形の集合
    IntersectRectangle(const vector<array<T,4>>& l_r_d_u){
        size_t N = l_r_d_u.size();
        vector<T> vl(N),vr(N),vd(N),vu(N);
        for(size_t i = 0; i < N; ++i) {
            auto [a,b,c,d]=l_r_d_u[i];
            vl[i]=a,vr[i]=b,vd[i]=c,vu[i]=d;
        }
        build(vl,vr,vd,vu);
    }
    IntersectRectangle(const vector<T>& vl, const vector<T>& vr, const vector<T>& vd, const vector<T>& vu) {
        build(vl,vr,vd,vu);
    }
    size_t size() { return N; }
    int get(const size_t i) { return N-1-count[i]; }
};

/**
 * @url 
 * @est
 */ 
int main() {
    cin.tie(0);ios::sync_with_stdio(false);
    int N;
    read(N);
    unordered_map<int, vector<tuple<int,int,int,int,size_t> >> z_xy, x_yz, y_zx;
    for(int i=0;i<N;++i) {
        int x1,y1,z1,x2,y2,z2;
        read(x1),read(y1),read(z1),read(x2),read(y2),read(z2);
        z_xy[z1].emplace_back(x1,x2,y1,y2,i);
        z_xy[z2].emplace_back(x1,x2,y1,y2,i);
        y_zx[y1].emplace_back(z1,z2,x1,x2,i);
        y_zx[y2].emplace_back(z1,z2,x1,x2,i);
        x_yz[x1].emplace_back(y1,y2,z1,z2,i);
        x_yz[x2].emplace_back(y1,y2,z1,z2,i);
    }
    vector<int> ans(N,0);
    for(auto& [_,vt]: z_xy) {
        size_t M = vt.size();
        vector<int> vl(M),vr(M),vd(M),vu(M),idx(M);
        for(int i=0;i<M;++i) {
            auto [l,r,d,u,j] = vt[i];
            vl[i]=l,vr[i]=r,vd[i]=d,vu[i]=u;
            idx[i]=j;
        }
        IntersectRectangle<int> ir(vl,vr,vd,vu);
        for(int i=0;i<M;++i) {
            int j = idx[i];
            ans[j] += ir.get(i);
        }
    }
    for(auto& [_,vt]: y_zx) {
        size_t M = vt.size();
        vector<int> vl(M),vr(M),vd(M),vu(M),idx(M);
        for(int i=0;i<M;++i) {
            auto [l,r,d,u,j] = vt[i];
            vl[i]=l,vr[i]=r,vd[i]=d,vu[i]=u;
            idx[i]=j;
        }
        IntersectRectangle<int> ir(vl,vr,vd,vu);
        for(int i=0;i<M;++i) {
            auto [l,r,d,u,j] = vt[i];
            ans[j] += ir.get(i);
        }
    }
    for(auto& [_,vt]: x_yz) {
        size_t M = vt.size();
        vector<int> vl(M),vr(M),vd(M),vu(M),idx(M);
        for(int i=0;i<M;++i) {
            auto [l,r,d,u,j] = vt[i];
            vl[i]=l,vr[i]=r,vd[i]=d,vu[i]=u;
            idx[i]=j;
        }
        IntersectRectangle<int> ir(vl,vr,vd,vu);
        for(int i=0;i<M;++i) {
            int j = idx[i];
            ans[j] += ir.get(i);
        }
    }
    for(int i=0;i<N;++i) cout << ans[i] << "\n";
    return 0;
}
