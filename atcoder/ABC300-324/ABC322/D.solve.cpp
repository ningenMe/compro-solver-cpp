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

vector<string> rotate(const vector<string>& vs) {
    int M = vs.size();
    vector<string> res(M, string(M,'.'));
    for(int i=0;i<M;++i) {
        for(int j=0;j<M;++j) {
            res[i][j] = vs[M-1-j][i];
        }
    }
    return res;
}

bool is_ok(const vector<string>& vs0, const vector<string>& vs1, const vector<string>& vs2) {
    int M = vs0.size();
    vector<string> vs(3*M, string(3*M,'.'));

    // print();
    // for(int i=0;i<M;++i) print(vs0[i]);
    // print();
    // for(int i=0;i<M;++i) print(vs1[i]);
    // print();
    // for(int i=0;i<M;++i) print(vs2[i]);
    // print();

    for(int y0=1; y0+M<3*M; ++y0) {
        for(int x0=1; x0+M<3*M; ++x0) {
            for(int y1=1; y1+M<3*M; ++y1) {
                for(int x1=1; x1+M<3*M; ++x1) {
                    for(int y2=1; y2+M<3*M; ++y2) {
                        for(int x2=1; x2+M<3*M; ++x2) {
                            auto res = vs;

                            int flg = true;
                            for(int i=0;i<M && flg;++i) {
                                for(int j=0;j<M && flg;++j) {
                                    if(vs0[i][j] == '#') {
                                        if(res[i+y0][j+x0] == '#') flg = false;
                                        if(!(M <= i+y0 && i+y0 < 2*M && M <= j+x0 && j+x0 < 2*M)) flg = false;
                                        res[i+y0][j+x0] = vs0[i][j];
                                    }
                                }
                            }
                            if(!flg) continue;

                            for(int i=0;i<M && flg;++i) {
                                for(int j=0;j<M && flg;++j) {
                                    if(vs1[i][j] == '#') {
                                        if(res[i+y1][j+x1] == '#') flg = false;
                                        if(!(M <= i+y1 && i+y1 < 2*M && M <= j+x1 && j+x1 < 2*M)) flg = false;
                                        res[i+y1][j+x1] = vs1[i][j];
                                    }
                                }
                            }
                            if(!flg) continue;

                            for(int i=0;i<M && flg;++i) {
                                for(int j=0;j<M && flg;++j) {
                                    if(vs2[i][j] == '#') {
                                        if(res[i+y2][j+x2] == '#') flg = false;
                                        if(!(M <= i+y2 && i+y2 < 2*M && M <= j+x2 && j+x2 < 2*M)) flg = false;
                                        res[i+y2][j+x2] = vs2[i][j];
                                    }
                                }
                            }
                            if(!flg) continue;

                            for(int i=M;i<2*M && flg;++i) {
                                for(int j=M;j<2*M && flg;++j) {
                                    if(res[i][j] == '.') flg = false;
                                }
                            }

                            if(flg) return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}

/**
 * @url 
 * @est
 */ 
int main() {
    cin.tie(0);ios::sync_with_stdio(false);
    int N = 3;
    int M = 4;
    auto vvs = multivector(N,M,string(""));
    for(int i=0;i<N;++i) {
        for(int j=0;j<M;++j) {
            read(vvs[i][j]);
        }
    }

    int flg = false;

    for(int rot0 = 0; rot0 < 4; ++rot0) {
        for(int rot1 = 0; rot1 < 4; ++rot1) {
            for(int rot2 = 0; rot2 < 4; ++rot2) {
                auto a0 = vvs[0];
                auto a1 = vvs[1];
                auto a2 = vvs[2];
                for(int i=0;i<rot0;++i) a0 = rotate(a0);
                for(int i=0;i<rot1;++i) a1 = rotate(a1);
                for(int i=0;i<rot2;++i) a2 = rotate(a2);
                if(is_ok(a0,a1,a2)) flg = true;
            }
        }
    }
    Yn(flg);
    return 0;
}
