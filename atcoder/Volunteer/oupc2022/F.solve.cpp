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
    UnionFindTree(int N = 1) : parent(N,-1),maxi(N),mini(N){
        iota(maxi.begin(),maxi.end(),0);
        iota(mini.begin(),mini.end(),0);
    }
    inline bool connected(int n, int m) {
        return root(n) == root(m);
    }
    inline void merge(int n, int m) {
        n = root(n);
        m = root(m);
        if (n == m) return;
        if(parent[n]>parent[m]) swap(n, m);
        parent[n] += parent[m];
        parent[m] = n;
        maxi[n] = std::max(maxi[n],maxi[m]);
        mini[n] = std::min(mini[n],mini[m]);
    }
    inline int min(int n) {
        return mini[root(n)];
    }
    inline int max(int n) {
        return maxi[root(n)];
    }
    inline int size(int n){
        return (-parent[root(n)]);
    }
    inline int operator[](int n) {
        return root(n);
    }
    inline void print() {
        for(int i = 0; i < parent.size(); ++i) cout << root(i) << " ";
        cout << endl;
    }
};

/*
 * @title LazySegmentTree - 非再帰抽象化遅延評価セグメント木
 * @docs md/data-structure/segment-tree/LazySegmentTree.md
 */
template<class Monoid> class LazySegmentTree {
    using TypeNode = typename Monoid::TypeNode;
    using TypeLazy = typename Monoid::TypeLazy;
    size_t num;
    size_t length;
    size_t height;
    vector<TypeNode> node;
    vector<TypeLazy> lazy;
    vector<pair<size_t,size_t>> range;

    void propagate(int k) {
        if(lazy[k] == Monoid::unit_lazy) return;
        node[k] = Monoid::func_operate(node[k],lazy[k],range[k].first,range[k].second);
        if(k < length) lazy[2*k+0] = Monoid::func_lazy(lazy[2*k+0],lazy[k]);
        if(k < length) lazy[2*k+1] = Monoid::func_lazy(lazy[2*k+1],lazy[k]);
        lazy[k] = Monoid::unit_lazy;
    }

    void build() {
        for (int i = length - 1; i >= 0; --i) node[i] = Monoid::func_fold(node[(i<<1)+0],node[(i<<1)+1]);
        range.resize(2 * length);
        for (int i = 0; i < length; ++i) range[i+length] = make_pair(i,i+1);
        for (int i = length - 1; i >= 0; --i) range[i] = make_pair(range[(i<<1)+0].first,range[(i<<1)+1].second);
    }
public:

    //unitで初期化
    LazySegmentTree(const size_t num) : num(num) {
        for (length = 1,height = 0; length <= num; length *= 2, height++);
        node.resize(2 * length, Monoid::unit_node);
        lazy.resize(2 * length, Monoid::unit_lazy);
        for (int i = 0; i < num; ++i) node[i + length] = Monoid::unit_node;
        build();
    }

    // //同じinitで初期化
    LazySegmentTree(const size_t num, const TypeNode init) : num(num) {
        for (length = 1,height = 0; length <= num; length *= 2, height++);
        node.resize(2 * length, Monoid::unit_node);
        lazy.resize(2 * length, Monoid::unit_lazy);
        for (int i = 0; i < num; ++i) node[i + length] = init;
        build();
    }

    //vectorで初期化
    LazySegmentTree(const vector<TypeNode>& vec) : num(vec.size()) {
        for (length = 1,height = 0; length <= vec.size(); length *= 2, height++);
        node.resize(2 * length, Monoid::unit_node);
        lazy.resize(2 * length, Monoid::unit_lazy);
        for (int i = 0; i < vec.size(); ++i) node[i + length] = vec[i];
        build();
    }

    //operate [a,b)
    void operate(int a, int b, TypeLazy x) {
        int l = a + length, r = b + length - 1;
        for (int i = height; 0 < i; --i) propagate(l >> i), propagate(r >> i);
        for(r++; l < r; l >>=1, r >>=1) {
            if(l&1) lazy[l] = Monoid::func_lazy(lazy[l],x), propagate(l),l++;
            if(r&1) --r,lazy[r] = Monoid::func_lazy(lazy[r],x), propagate(r);
        }
        l = a + length, r = b + length - 1;
        while ((l>>=1),(r>>=1),l) {
            if(lazy[l] == Monoid::unit_lazy) node[l] = Monoid::func_fold(Monoid::func_operate(node[(l<<1)+0],lazy[(l<<1)+0],range[(l<<1)+0].first,range[(l<<1)+0].second),Monoid::func_operate(node[(l<<1)+1],lazy[(l<<1)+1],range[(l<<1)+1].first,range[(l<<1)+1].second));
            if(lazy[r] == Monoid::unit_lazy) node[r] = Monoid::func_fold(Monoid::func_operate(node[(r<<1)+0],lazy[(r<<1)+0],range[(r<<1)+0].first,range[(r<<1)+0].second),Monoid::func_operate(node[(r<<1)+1],lazy[(r<<1)+1],range[(r<<1)+1].first,range[(r<<1)+1].second));
        }
    }

    //fold [a,b)
    TypeNode fold(int a, int b) {
        int l = a + length, r = b + length - 1;
        for (int i = height; 0 < i; --i) propagate(l >> i), propagate(r >> i);
        TypeNode vl = Monoid::unit_node, vr = Monoid::unit_node;
        for(r++; l < r; l >>=1, r >>=1) {
            if(l&1) vl = Monoid::func_fold(vl,Monoid::func_operate(node[l],lazy[l],range[l].first,range[l].second)),l++;
            if(r&1) r--,vr = Monoid::func_fold(Monoid::func_operate(node[r],lazy[r],range[r].first,range[r].second),vr);
        }
        return Monoid::func_fold(vl,vr);
    }

    //return [0,length]
    int prefix_binary_search(TypeNode var) {
        int l = length, r = 2*length - 1;
        for (int i = height; 0 < i; --i) propagate(l >> i), propagate(r >> i);
        if(!Monoid::func_check(node[1],var)) return num;
        TypeNode ret = Monoid::unit_node;
        size_t idx = 2;
        for(; idx < 2*length; idx<<=1){
            if(!Monoid::func_check(Monoid::func_fold(ret,Monoid::func_operate(node[idx],lazy[idx],range[idx].first,range[idx].second)),var)) {
                ret = Monoid::func_fold(ret,Monoid::func_operate(node[idx],lazy[idx],range[idx].first,range[idx].second));
                idx++;
            }
        }
        return min((idx>>1) - length,num);
    }

    //range[l,r) return [l,r]
    int binary_search(size_t l, size_t r, TypeNode var) {
        if (l < 0 || length <= l || r < 0 || length < r) return -1;
        for (int i = height; 0 < i; --i) propagate((l+length) >> i), propagate((r+length-1) >> i);
        TypeNode ret = Monoid::unit_node;
        size_t off = l;
        for(size_t idx = l+length; idx < 2*length && off < r; ){
            if(range[idx].second<=r && !Monoid::func_check(Monoid::func_fold(ret,Monoid::func_operate(node[idx],lazy[idx],range[idx].first,range[idx].second)),var)) {
                ret = Monoid::func_fold(ret,Monoid::func_operate(node[idx],lazy[idx],range[idx].first,range[idx].second));
                off = range[idx++].second;
                if(!(idx&1)) idx >>= 1;
            }
            else{
                idx <<=1;
            }
        }
        return off;
    }

    void print(){
        // cout << "node" << endl;
        // for(int i = 1,j = 1; i < 2*length; ++i) {
        // 	cout << node[i] << " ";
        // 	if(i==((1<<j)-1) && ++j) cout << endl;
        // }
        // cout << "lazy" << endl;
        // for(int i = 1,j = 1; i < 2*length; ++i) {
        // 	cout << lazy[i] << " ";
        // 	if(i==((1<<j)-1) && ++j) cout << endl;
        // }
        cout << "vector" << endl;
        cout << "{ " << fold(0,1);
        for(int i = 1; i < length; ++i) cout << ", " << fold(i,i+1);
        cout << " }" << endl;
    }
};

/*
 * @title MonoidRangeSumRangeUpdate - [区間max, 区間更新]
 * @docs md/operator/monoid-lazy/MonoidRangeSumRangeUpdate.md
 */
template<class T, class U> struct MonoidRangeMaxRangeUpdate {
	using TypeNode = T;
	using TypeLazy = U;
	inline static constexpr TypeNode unit_node = 0;
	inline static constexpr TypeLazy unit_lazy = -1;
	inline static constexpr TypeNode func_fold(TypeNode l,TypeNode r){return max(l,r);}
	inline static constexpr TypeLazy func_lazy(TypeLazy old_lazy,TypeLazy new_lazy){return new_lazy;}
	inline static constexpr TypeNode func_operate(TypeNode node,TypeLazy lazy,int l, int r){return lazy!=-1?lazy:node;}
	inline static constexpr bool func_check(TypeNode nodeVal,TypeNode var){return var <= nodeVal;}
};

int main() {
    cin.tie(0);ios::sync_with_stdio(false);
    int64 N,Q; cin >> N >> Q;
    vector<int64> T(N);
    for(int i=0;i<N;++i) cin >> T[i];
    vector<int64> S(Q);
    for(int i=0;i<Q;++i) cin >> S[i],S[i]--;
    UnionFindTree uf(Q);
    for(int i=0;i+1<Q;++i) if(S[i]==S[i+1]) uf.merge(i,i+1);
    vector<set<pair<int,int>>> vst(N);
    for(int i=0;i<Q;++i) vst[S[i]].insert({uf.min(i),uf.max(i)});
    LazySegmentTree<MonoidRangeMaxRangeUpdate<int,int>> seg(Q,2);

    int ans = 0;
    for(int i=N-1; 0<=i; --i) {
        auto st = vst[i];
        for(auto p:st) {
            int l = p.first;
            int r = ++p.second;
            for(; l < r; ++l) {
                if(seg.fold(l,l+1) == 1) continue;
                break;
            }
            for(; l + T[i] <= r; l += T[i]) {
                seg.operate(l,l+T[i],1);
                ans += 1;
            }
            seg.operate(l, r, 1LL);
            if(l == r) {
                //do nothing
            }
            else if(seg.fold(l,l+T[i]) == 1 || r==Q) {
                ans += 1;
            }            
            else {
                ans += 2;
            }
        }
    }
    cout << ans << endl;

    return 0;
}
