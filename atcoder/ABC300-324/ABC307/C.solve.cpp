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
    int HA,WA;
    read(HA),read(WA);
    vector<string> A(HA);
    for(int i=0;i<HA;++i) read(A[i]);

    int HB,WB;
    read(HB),read(WB);
    vector<string> B(HB);
    for(int i=0;i<HB;++i) read(B[i]);

    int HC,WC;
    read(HC),read(WC);
    vector<string> C(HC);
    for(int i=0;i<HC;++i) read(C[i]);

    int M = 30;
    auto D = multivector(M,M,0);
    auto EA = multivector(M,M,0);
    auto EB = multivector(M,M,0);

    for(int i=0;i<HC;++i) {
        for(int j=0;j<WC;++j) {
            D[10+i][10+j] |= (C[i][j]=='#');
        }
    }
    for(int i=0;i+HA<=M;++i) {
        for(int j=0; j+WA<=M;++j) {
            int flg = 1;
            for(int k=0;k<HA && flg;++k) {
                for(int l=0;l<WA && flg;++l) {
                    if(A[k][l]=='#') {
                        if(D[i+k][j+l] == 0) flg = 0;
                        else continue;
                    }
                }
            }
            EA[i][j]=flg;
        }
    }
    for(int i=0;i+HB<=M;++i) {
        for(int j=0; j+WB<=M;++j) {
            int flg = 1;
            for(int k=0;k<HB && flg;++k) {
                for(int l=0;l<WB && flg;++l) {
                    if(B[k][l]=='#') {
                        if(D[i+k][j+l] == 0) flg = 0;
                        else continue;
                    }
                }
            }
            EB[i][j]=flg;
        }
    }
    for(int i=0;i<M;++i) {
        for(int j=0; j<M;++j) {
            if(!EA[i][j]) continue;
            for(int k=0;k<M;++k) {
                for(int l=0;l<M;++l) {
                    if(!EB[k][l]) continue;
                    auto F = D;
                    for(int m=0;m<HA;++m) {
                        for(int n=0;n<WA;++n) {
                            if(A[m][n]=='#') F[i+m][j+n]=2;
                        }
                    }
                    for(int m=0;m<HB;++m) {
                        for(int n=0;n<WB;++n) {
                            if(B[m][n]=='#') F[k+m][l+n]=2;
                        }
                    }
                    int flg = 1;
                    for(int m=0;m<M && flg;++m) {
                        for(int n=0;n<M && flg;++n) {
                            if(F[m][n]==1) flg=0;
                        }
                    }
                    corner(flg, "Yes");
                }
            }
        }
    }
    cout << "No" << endl;
    return 0;
}
