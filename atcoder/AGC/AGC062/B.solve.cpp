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
 * @title UnionFindTree - Union Find 木
 * @docs md/graph/UnionFindTree.md
 */
class UnionFindTree {
    vector<int> parent,maxi,mini;
    inline int root(int n) {
        return (parent[n]<0?n:parent[n] = root(parent[n]));
    }
public:
    UnionFindTree(const int N = 1) : parent(N,-1),maxi(N),mini(N){
        iota(maxi.begin(),maxi.end(),0);
        iota(mini.begin(),mini.end(),0);
    }
    inline bool connected(const int n, const int m) {
        return root(n) == root(m);
    }
    inline void merge(int n,int m) {
        n = root(n);
        m = root(m);
        if (n == m) return;
        if(parent[n]>parent[m]) swap(n, m);
        parent[n] += parent[m];
        parent[m] = n;
        maxi[n] = std::max(maxi[n],maxi[m]);
        mini[n] = std::min(mini[n],mini[m]);
    }
    inline int min(const int n) {
        return mini[root(n)];
    }
    inline int max(const int n) {
        return maxi[root(n)];
    }
    inline int size(const int n){
        return (-parent[root(n)]);
    }
    inline int operator[](const int n) {
        return root(n);
    }
    inline void print() {
        for(int i = 0; i < parent.size(); ++i) cout << root(i) << " ";
        cout << endl;
    }
};

/*
 * @title DisjointSparseTable
 * @docs md/data-structure/range-query/DisjointSparseTable.md
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
    int64 N,K; cin >> N >> K;
    vector<int64> C(K),P(N);
    for(int i=0;i<K;++i) cin >> C[i];
    for(int i=0;i<N;++i) cin >> P[i], P[i]--;
    auto PP = multivector(N,N,0);
    for(int i=0;i<N;++i) for(int j=i+1;j<N;++j) PP[P[i]][P[j]]=1;

    UnionFindTree uf(N);
    for(int i=N-1; 0 <= i-1; --i) {
        int l = i-1, r=i;
        if(PP[l][r]) uf.merge(l,r);
    }
    map<int64,int64> mp;
    for(int i=0;i<N;++i) mp[uf[i]]=uf.size(i);
    vector<int64> v;
    for(auto p:mp) v.push_back(p.second);

    corner(v.size()<=1,0);

    reverse(ALL(v));
    v.pop_back();
    reverse(ALL(v));
    int64 M = v.size();

    DisjointSparseTable<NodeSum<int64>> dst(v);

    auto dp = multivector(K+1,M+1,M+1,HIGHINF);
    dp[0][0][M]=0;
    for(int i=1;i<=K;++i) {
        for(int j=0;j<=M;++j) {
            for(int k=M; j<=k;--k) {
                //コストを使わない
                chmin(dp[i][j][k], dp[i-1][j][k]);
                if(j+1<=k) chmin(dp[i][j+1][k], dp[i-1][j][k]+dst.fold(j,k)  *C[i-1]);
                if(j<=k-1) chmin(dp[i][j][k-1], dp[i-1][j][k]+dst.fold(k-1,k)*C[i-1]);
            }
        }
    }
    int64 ans = HIGHINF;
    for(int i=0;i<=M;++i) chmin(ans, dp[K][i][i]);
    if(ans >= HIGHINF) ans = -1;
    cout << ans << endl;
    return 0;
}
