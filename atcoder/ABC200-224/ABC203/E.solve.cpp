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

/**
 * @url 
 * @est
 */ 
int main() {
    cin.tie(0);ios::sync_with_stdio(false);
    int64 N,M; read(N); read(M);
    vector<int64> X(M),Y(M);
    for(int i=0;i<M;++i) {
        read(X[i]); read(Y[i]);
    }
    map<int64,set<int64>> mporn;
    for(int i=0;i<M;++i) {
        mporn[Y[i]].insert(X[i]);
    }
    queue<pair<int64,int64>> q;
    set<pair<int64,int64>> st;
    q.push({N,0});
    st.insert({N,0});
    
    set<int64> is_ok;
    int64 R = 2*N;
    while(q.size()) {
        auto [y,x] = q.front(); q.pop();
        if(x==R) {
            is_ok.insert(y);
            continue;
        }
        auto ux_itr = mporn[y-1].upper_bound(x);
        auto cx_itr = mporn[y].upper_bound(x);
        auto dx_itr = mporn[y+1].upper_bound(x);
        int64 ux = (ux_itr == mporn[y-1].end() ? R : (*ux_itr)-1);
        int64 cx = (cx_itr == mporn[y].end() ? R : (*cx_itr)-1);
        int64 dx = (dx_itr == mporn[y+1].end() ? R : (*dx_itr)-1);

        //straigt
        {
            int64 ny = y;
            int64 nx = cx;
            if(!st.count({ny,nx})) {
                q.push({ny,nx});
                st.insert({ny,nx});
            }
        }
        if(ux<cx) {
            int64 ny = y;
            int64 nx = ux;
            if(!st.count({ny,nx})) {
                q.push({ny,nx});
                st.insert({ny,nx});
            }
        }
        if(ux+1<cx) {
            int64 ny = y;
            int64 nx = ux+1;
            if(!st.count({ny,nx})) {
                q.push({ny,nx});
                st.insert({ny,nx});
            }
        }
        if(dx<cx) {
            int64 ny = y;
            int64 nx = dx;
            if(!st.count({ny,nx})) {
                q.push({ny,nx});
                st.insert({ny,nx});
            }
        }
        if(dx+1<cx) {
            int64 ny = y;
            int64 nx = dx+1;
            if(!st.count({ny,nx})) {
                q.push({ny,nx});
                st.insert({ny,nx});
            }
        }
        //up
        {
            if(ux==x) {
                int64 ny = y-1;
                int64 nx = x+1;
                if(!st.count({ny,nx})) {
                    q.push({ny,nx});
                    st.insert({ny,nx});
                }
            }
        }
        //down
        {
            if(dx==x) {
                int64 ny = y+1;
                int64 nx = x+1;
                if(!st.count({ny,nx})) {
                    q.push({ny,nx});
                    st.insert({ny,nx});
                }
            }
        }
    }
    cout << is_ok.size() << endl;
    return 0;
}
