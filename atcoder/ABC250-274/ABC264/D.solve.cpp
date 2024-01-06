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
 * @title BinaryIndexedTree - BIT
 * @docs md/binary-indexed-tree/BinaryIndexedTree.md
 */
template<class Abel> class BinaryIndexedTree {
    using TypeNode = typename Abel::TypeNode;
    size_t length;
    size_t num;
    vector<TypeNode> node;
public:

    //[0,N) constructed, inplace [0,1) + [1,N+1)
    //you can ignore inplace offset
    BinaryIndexedTree(const size_t num) : num(num) {
        for (length = 1; length < num; length *= 2);
        node.resize(length+1, Abel::unit_node);
    }

    //[idx,idx+1) operate
    void operate(size_t idx, TypeNode var) {
        assert(0 <= idx && idx < length);
        for (++idx; idx <= length; idx += idx & -idx) node[idx] = Abel::func_fold(node[idx],var);
    }

    //[0,idx) fold
    TypeNode fold(size_t idx) {
        TypeNode ret = Abel::unit_node;
        for (idx = min(length,idx); idx > 0; idx -= idx & -idx) ret = Abel::func_fold(ret,node[idx]);
        return ret;
    }

    //return [0,length]
    int binary_search(TypeNode var) {
        if(!Abel::func_check(node.back(),var)) return num;
        TypeNode ret = Abel::unit_node;
        size_t off = 0;
        for(size_t idx = length; idx; idx >>= 1){
            if(off + idx <= length && !Abel::func_check(Abel::func_fold(ret,node[off+idx]),var)) {
                off += idx;
                ret = Abel::func_fold(ret,node[off]);
            }
        }
        return min(off,num);
    }

    void print() {
        cout << "{ " << fold(1);
        for(int i = 1; i < length; ++i) cout << ", " << fold(i+1);
        cout << " }" << endl;
    }
};

/*
 * @title AbelPrefixSumPointAdd
 * @docs md/operator/abel/AbelPrefixSumPointAdd.md
 */
template<class T> struct AbelPrefixSumPointAdd {
    using TypeNode = T;
    inline static constexpr TypeNode unit_node = 0;
    inline static constexpr TypeNode func_fold(const TypeNode& l,const TypeNode& r){return l+r;}
    inline static constexpr TypeNode func_fold_inv(const TypeNode& l,const TypeNode& r){return l-r;}
};

/*
 * @title StaticRangeInversionQuery - 静的区間転倒数クエリ
 * @docs md/static-range-query/StaticRangeInversionQuery.md
 */
template<class T> class StaticRangeInversionQuery {
    vector<size_t> compressed;
    vector<long long> prefix_inv;
    vector<long long> suffix_inv;
    vector<vector<long long>> sqrt_bucket_freq;
    vector<long long> sqrt_bucket_inv;
    vector<vector<size_t>> sqrt_bucket_sort_index;
    vector<long long> sqrt_bucket_size;
    size_t N,B,M;
public:
    StaticRangeInversionQuery(const vector<T>& ar, T pre=-1)
            : compressed(ar.size()),prefix_inv(ar.size()),suffix_inv(ar.size()) {
        N = ar.size();
        B = sqrt(N) + 1; // bucket size
        M = N / B + 1;   // bucket num
        //zarts
        {
            vector<pair<T,size_t>> ord(N);
            for(size_t i=0;i<N;++i) ord[i]={ar[i],i};
            sort(ord.begin(),ord.end());
            size_t inc=0;
            for(size_t i=0;i<N;++i) {
                if(pre < ord[i].first) inc++;
                compressed[ord[i].second] = inc;
                pre = ord[i].first;
            }
        }
        //freq
        {
            sqrt_bucket_freq.resize(M);
            vector<long long> freq(N+1,0);
            for(size_t i=0;i<M;++i) {
                size_t l = i*B, r = min((i+1)*B,N);
                for(size_t j=l;j<r;++j) freq[compressed[j]]++;
                sqrt_bucket_freq[i] = freq;
                for(size_t j=1;j<=N;++j) sqrt_bucket_freq[i][j]+=sqrt_bucket_freq[i][j-1];
            }
        }
        //prefix,suffix inv
        {
            BinaryIndexedTree<AbelPrefixSumPointAdd<long long>> bit(N+1);
            for(size_t i=0;i<M;++i) {
                int l = i*B, r = min((i+1)*B,N);
                //prefix
                {
                    long long inv = 0;
                    for(size_t j=l;j<r;++j) {
                        inv += bit.fold(N+1)-bit.fold(compressed[j]+1);
                        prefix_inv[j]=inv;
                        bit.operate(compressed[j],1);
                    }
                    for(size_t j=l;j<r;++j) {
                        bit.operate(compressed[j],-1);
                    }
                }
                //suffix
                {
                    long long inv = 0;
                    for(int j=r-1;l<=j;--j) {
                        inv += bit.fold(compressed[j]);
                        suffix_inv[j]=inv;
                        bit.operate(compressed[j],1);
                    }
                    for(size_t j=l;j<r;++j) {
                        bit.operate(compressed[j],-1);
                    }
                }
            }
        }
        //sqrt bucket inv
        {
            sqrt_bucket_inv.resize(M*M,0);
            for(size_t i=0;i<M;++i) {
                size_t l = i*B, r = min((i+1)*B,N);
                if(l<r) sqrt_bucket_inv[i*M+i] = prefix_inv[r-1];
            }
            for(size_t k=1;k<M;++k) {
                for(size_t i=0;i+k<M;++i) {
                    sqrt_bucket_inv[i*M+i+k] += sqrt_bucket_inv[i*M+i]+sqrt_bucket_inv[(i+1)*M+i+k];
                    size_t l = i*B, r = min((i+1)*B,N);
                    for(size_t j=l;j<r;++j) {
                        size_t& c = compressed[j];
                        sqrt_bucket_inv[i*M+i+k] += (sqrt_bucket_freq[i+k][c-1]-sqrt_bucket_freq[i][c-1]);
                    }
                }
            }
        }
        //sort
        {
            sqrt_bucket_sort_index.resize(M);
            sqrt_bucket_size.resize(M,0);
            size_t sz = 0;
            for(size_t i=0;i<M;++i) {
                int l = i*B, r = min((i+1)*B,N);
                sz += max(0,(r-l));
                sqrt_bucket_size[i] = sz;
                if(r-l<1) continue;
                sqrt_bucket_sort_index[i].resize(r-l);
                for(size_t j=l;j<r;++j) sqrt_bucket_sort_index[i][j-l]=j;
                sort(sqrt_bucket_sort_index[i].begin(),sqrt_bucket_sort_index[i].end(),
                     [&](size_t l,size_t r){return compressed[l]==compressed[r]?l<r:compressed[l]<compressed[r];});
            }
        }
    }
    //query [l,r)
    //return {freq,mode} ({頻度,元の配列における値})
    long long fold(int l, int r) {
        int bl = l/B + 1, br = (r-1)/B - 1;
        long long inv = 0;
        //同じbucketにl,rがあるとき
        if(bl > br + 1) {
            inv += prefix_inv[r-1];
            if(l%B) inv -= prefix_inv[l-1];
            long long sum = 0;
            for(size_t i: sqrt_bucket_sort_index[l/B]) {
                if(r <= i) continue;
                if(l <= i) sum++;
                else inv -= sum;
            }
        }
        else {
            inv += sqrt_bucket_inv[bl*M+br];
            inv += suffix_inv[l];
            inv += prefix_inv[r-1];
            size_t ml = bl*B;
            for(size_t i=l;i<ml;++i) {
                size_t& c = compressed[i];
                inv += sqrt_bucket_freq[br][c-1]-sqrt_bucket_freq[bl-1][c-1];
            }
            size_t mr = (br+1)*B;
            for(size_t i=mr;i<r;++i) {
                size_t& c = compressed[i];
                inv += (sqrt_bucket_size[br]-sqrt_bucket_freq[br][c])-(sqrt_bucket_size[bl-1]-sqrt_bucket_freq[bl-1][c]);
            }
            int ir = 0, nr = sqrt_bucket_sort_index[br+1].size();
            long long sum = 0;
            for(auto& xl:sqrt_bucket_sort_index[bl-1]) {
                if(xl < l) continue;
                for(;ir<nr;++ir) {
                    auto& xr = sqrt_bucket_sort_index[br+1][ir];
                    if(xr >= r) continue;
                    if(compressed[xl] > compressed[xr]) sum++;
                    else break;
                }
                inv += sum;
            }
        }
        return inv;
    }
};

/**
 * @url 
 * @est
 */ 
int main() {
    cin.tie(0);ios::sync_with_stdio(false);
    string S;
    read(S);
    string T="atcoder";
    map<char,int> mp;
    for(int i=0;i<T.size();++i) {
        mp[T[i]]=i;
    }
    vector<int> v(S.size());
    for(int i=0;i<S.size();++i) {
        v[i]=mp[S[i]];
    }
    StaticRangeInversionQuery<int> sriq(v);
    cout << sriq.fold(0,S.size()) << endl;

    return 0;
}
