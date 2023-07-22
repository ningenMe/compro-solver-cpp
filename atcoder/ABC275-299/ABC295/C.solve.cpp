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

template<class T> class StaticRangePairQuery {
    vector<int> compressed;
    vector<vector<size_t>> sqrt_bucket_count;
    vector<vector<int>> acc;
    size_t length,bucket_size,val_size;
    vector<size_t> tmp;
public:
    StaticRangePairQuery(const vector<T>& ar, T pre=-1) : compressed(ar.size()) {
        length = ar.size();
        bucket_size = sqrt(length) + 1;
        //zarts
        {
            vector<pair<T,size_t>> ord(length);
            for(size_t i=0;i<length;++i) ord[i]={ar[i],i};
            sort(ord.begin(),ord.end());
            int inc=-1;
            for(size_t i=0;i<length;++i) {
                if(pre < ord[i].first) inc++;
                compressed[ord[i].second] = inc;
                pre = ord[i].first;
            }
            val_size = inc + 1;
            tmp.resize(val_size);
        }
        //sqrt bucket
        {
            sqrt_bucket_count.resize(bucket_size+1,vector<size_t>(bucket_size+1));
            for(size_t l = 0; l < length; l += bucket_size) {
                for(size_t i = 0; i < val_size; ++i) tmp[i]=0;

                size_t bl = l/bucket_size;
                for(size_t r = l; r < length; ++r) {
                    int val=compressed[r];
                    tmp[val]++;
                    if(tmp[val]==2) {
                        tmp[val]=0;
                        size_t br = r/bucket_size + 1;
                        sqrt_bucket_count[bl][br]++;
                    }
                }
                for(size_t r = l+bucket_size; r < length; r += bucket_size) {
                    size_t br = r/bucket_size + 1;
                    sqrt_bucket_count[bl][br] += sqrt_bucket_count[bl][br-1];
                }
            }
            //queryで使い回すから0にしておく
            for(size_t i = 0; i < val_size; ++i) tmp[i]=0;
        }
        
        //acc
        {
            acc.resize(val_size, vector<int>(bucket_size+1, 0));
            for(size_t i = 0; i < length; ++i) acc[compressed[i]][i/bucket_size + 1]++;
            for(size_t i = 0; i < val_size; ++i) {
                for(size_t j = 0; j+1 < bucket_size+1; ++j) acc[i][j+1] += acc[i][j];
            }
        }
    }
    //[l,r) におけるA[i]のペアの数
    int get(int l, int r) {
        stack<size_t> st;
        int res = 0;

        //naive
        if(r - l <= bucket_size) {
            for(int i = l; i < r; ++i) {
                size_t val = compressed[i];
                st.push(val);
                tmp[val]++;
                if(tmp[val]==2) {
                    tmp[val]=0;
                    res++;
                }
            }
            while(st.size()) {
                auto val = st.top(); st.pop();
                tmp[val]=0;
            }
            return res;
        }

        int bl = l/bucket_size + !!(l%bucket_size), br = r/bucket_size;

        int ml = bl * bucket_size, mr = br * bucket_size;
        ml = min(ml,r); mr = max(l,mr);
        res += sqrt_bucket_count[bl][br];    

        //左側の探索
        for(int i = l; i < ml; ++i) {
            size_t val = compressed[i];
            st.push(val);
            tmp[val]++;
            if(tmp[val]==2) {
                tmp[val]=0;
                res++;
            }
        }
        //右側の探索
        for(int i = mr; i < r; ++i) {
            size_t val = compressed[i];
            st.push(val);
            tmp[val]++;
            if(tmp[val]==2) {
                tmp[val]=0;
                res++;
            }
        }
        //1個余ってるものと、[ml,mr) で探索
        while(st.size()) {
            auto val = st.top(); st.pop();
            if(tmp[val]==0) continue;
            tmp[val]=0;
            int cnt = acc[val][br] - acc[val][bl];
            //合計が奇数だったら1個余ってるからインクリメント
            if(cnt&1) res++;
        }

        return res;
    }
};

/**
 * @url 
 * @est
 */ 
int main() {
    cin.tie(0);ios::sync_with_stdio(false);
    int N; read(N);
    vector<int> A(N);
    for(int i=0;i<N;++i) read(A[i]);
    StaticRangePairQuery<int> srpq(A);
    cout << srpq.get(0,N) << endl;
    return 0;
}
