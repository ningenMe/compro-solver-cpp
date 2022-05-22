#include <bits/stdc++.h>
using namespace std;
using int128 = __int128_t;
using int64 = long long;

#define ALL(obj) (obj).begin(),(obj).end()
template<class T> using priority_queue_reverse = priority_queue<T,vector<T>,greater<T>>;

constexpr int64 MOD = 1'000'000'000LL + 7; //'
constexpr int64 MOD2 = 998244353;
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
 * @title DisjointSparseTable
 * @docs md/data-structure/data-structure/DisjointSparseTable.md
 */
template<class Operator> class DisjointSparseTable{
public:
    using TypeNode = typename Operator::TypeNode;
    size_t depth;
    size_t length;
    vector<TypeNode> node;
    vector<size_t> msb;

    DisjointSparseTable(const vector<TypeNode>& vec) {
        for(depth = 0;(1<<depth)<=vec.size();++depth);
        length = (1<<depth);

        //msb
        msb.resize(length,0);
        for(int i = 0; i < length; ++i) for(int j = 0; j < depth; ++j) if(i>>j) msb[i] = j;

        //init value
        node.resize(depth*length,Operator::unit_node);
        for(int i = 0; i < vec.size(); ++i) node[i] = vec[i];

        for(int i = 1; i < depth; ++i) {
            for(int r = (1<<i),l = r-1; r < length; r += (2<<i),l = r-1){
                //init accumulate
                node[i*length+l] = node[l];
                node[i*length+r] = node[r];
                //accumulate
                for(int k = 1; k < (1<<i); ++k) {
                    node[i*length+l-k] = Operator::func_fold(node[i*length+l-k+1],node[l-k]);
                    node[i*length+r+k] = Operator::func_fold(node[i*length+r+k-1],node[r+k]);
                }
            }
        }
    }

    //[l,r)
    TypeNode fold(int l,int r) {
        r--;
        return (l>r||l<0||length<=r) ? Operator::unit_node: (l==r ? node[l] : Operator::func_fold(node[msb[l^r]*length+l],node[msb[l^r]*length+r]));
    }
};

//sum
template<class T> struct NodeSum {
    using TypeNode = T;
    inline static constexpr TypeNode unit_node = 0;
    inline static constexpr TypeNode func_fold(TypeNode l,TypeNode r){return l+r;}
};

/**
 * @url 
 * @est
 */ 
int main() {
    cin.tie(0);ios::sync_with_stdio(false);
    int N; cin >> N;
    int M = 3*100000;
    vector<int64> A(M,0);
    for(int i=0;i<N;++i) {
        int a; cin >> a;
        A[a]++;
    }
    DisjointSparseTable<NodeSum<int64>> dst(A);
    int64 ans = 0;
    for(int i=1;i+1<M;++i) {
        ans += dst.fold(0,i)*A[i]*dst.fold(i+1,M);
    }
    cout << ans << endl;
    return 0;
}
