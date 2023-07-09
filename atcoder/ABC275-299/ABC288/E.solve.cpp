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
 * @title SparseTable
 * @docs md/data-structure/data-structure/SparseTable.md
 */
template<class Operator> class SparseTable{
public:
    using TypeNode = typename Operator::TypeNode;
    vector<TypeNode> node;
    vector<int> idx;
    size_t depth;
    size_t length;

    SparseTable(const vector<TypeNode>& vec) {
        for(depth = 0;(1<<depth)<=vec.size();++depth);
        length = (1<<depth);
        node.resize(depth*length);
        for(int i = 0; i < vec.size(); ++i) node[i] = vec[i];
        for(int i = 1; i < depth; ++i) for(int j = 0; j + (1<<i) < (1<<depth); ++j) node[i*length+j] = Operator::func_node(node[(i-1)*length+j],node[(i-1)*length+j + (1 << (i-1))]);
        idx.resize(vec.size()+1);
        for(int i = 2; i < vec.size()+1; ++i) idx[i] = idx[i>>1] + 1;
    }

    //[l,r)
    TypeNode get(int l,int r) {
        int bit = idx[r-l];
        return Operator::func_node(node[bit*length+l],node[bit*length+r - (1<<bit)]);
    }
};

template<class T> struct NodeMin {
    using TypeNode = T;
    inline static constexpr TypeNode unitNode = HIGHINF;
    inline static constexpr TypeNode func_node(TypeNode l,TypeNode r){return min(l,r);}
};

/**
 * @url 
 * @est
 */ 
int main() {
    cin.tie(0);ios::sync_with_stdio(false);
    int N,M; cin >> N >> M;
    vector<int64> A(N+1),C(N+1,HIGHINF),X(M);
    for(int i=1;i<=N;++i) cin >> A[i];
    for(int i=1;i<=N;++i) cin >> C[i];
    set<int> st;
    for(int i=0;i<M;++i) {
        int x; cin >> x;
        st.insert(x);
    }

    auto dp = multivector(N+1,N+1,HIGHINF);
    dp[0][0] = 0;
    for(int i=1;i<=N;++i) {
        int flg = st.count(i);
        int64 cc = C[i];
        for(int j=0;j<i;++j) {
            chmin(cc,C[i-j]);
            //買う
            chmin(dp[i][j+1], dp[i-1][j] + cc + A[i]);
            //買わない
            if(!flg) {
                chmin(dp[i][j], dp[i-1][j]);
            }
        }
    }
    cout << (*min_element(ALL(dp[N]))) << endl;
    return 0;
}
