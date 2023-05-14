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
 * @title Zarts - 座標圧縮
 * @docs md/util/Zarts.md
 */
template<class T> class Zarts{
    vector<T> value;
    map<T,int> key;
    size_t sz;
public:
    vector<int> compressed;
    Zarts(const vector<T> & ar, int light_flag = 0, T pre=-1) : compressed(ar.size()) {
        if(!light_flag) {
            for (auto &e : ar) key[e];
            int cnt=0;
            for (auto &e : key) e.second = cnt++;
            for (int i=0;i<ar.size();++i) compressed[i]=key[ar[i]];
            value.resize(key.size());
            for (auto &e : key) value[e.second] = e.first;
            sz = cnt;
        }
        else {
            vector<pair<int,int>> ord(ar.size());
            for(int i=0;i<ar.size();++i) ord[i]={ar[i],i};
            sort(ord.begin(),ord.end());
            int cnt=-1;
            for(int i=0;i<ar.size();++i) {
                if(pre < ord[i].first) cnt++;
                compressed[ord[i].second] = cnt;
                pre = ord[i].first;
            }
            sz = cnt+1;
        }
    }
    T get_value(int key) {
        return value[key];
    }
    int get_key(T value) {
        assert(key.count(value));
        return key[value];
    }
    size_t size() {
        return sz;
    }
};

/*
 * @title SegmentTree - 非再帰抽象化セグメント木
 * @docs md/data-structure/segment-tree/SegmentTree.md
 */
template<class Monoid> class SegmentTree {
    using TypeNode = typename Monoid::TypeNode;
    size_t length;
    size_t num;
    vector<TypeNode> node;
    vector<pair<int,int>> range;
    inline void build() {
        for (int i = length - 1; i >= 0; --i) node[i] = Monoid::func_fold(node[(i<<1)+0],node[(i<<1)+1]);
        range.resize(2 * length);
        for (int i = 0; i < length; ++i) range[i+length] = make_pair(i,i+1);
        for (int i = length - 1; i >= 0; --i) range[i] = make_pair(range[(i<<1)+0].first,range[(i<<1)+1].second);
    }
public:

    //unitで初期化
    SegmentTree(const size_t num): num(num) {
        for (length = 1; length <= num; length *= 2);
        node.resize(2 * length, Monoid::unit_node);
        build();
    }

    //vectorで初期化
    SegmentTree(const vector<TypeNode> & vec) : num(vec.size()) {
        for (length = 1; length <= vec.size(); length *= 2);
        node.resize(2 * length, Monoid::unit_node);
        for (int i = 0; i < vec.size(); ++i) node[i + length] = vec[i];
        build();
    }

    //同じinitで初期化
    SegmentTree(const size_t num, const TypeNode init) : num(num) {
        for (length = 1; length <= num; length *= 2);
        node.resize(2 * length, Monoid::unit_node);
        for (int i = 0; i < length; ++i) node[i+length] = init;
        build();
    }

    //[idx,idx+1)
    void operate(size_t idx, const TypeNode var) {
        if(idx < 0 || length <= idx) return;
        idx += length;
        node[idx] = Monoid::func_operate(node[idx],var);
        while(idx >>= 1) node[idx] = Monoid::func_fold(node[(idx<<1)+0],node[(idx<<1)+1]);
    }

    //[l,r)
    TypeNode fold(int l, int r) {
        if (l < 0 || length <= l || r < 0 || length < r) return Monoid::unit_node;
        TypeNode vl = Monoid::unit_node, vr = Monoid::unit_node;
        for(l += length, r += length; l < r; l >>=1, r >>=1) {
            if(l&1) vl = Monoid::func_fold(vl,node[l++]);
            if(r&1) vr = Monoid::func_fold(node[--r],vr);
        }
        return Monoid::func_fold(vl,vr);
    }

    //range[l,r) return [l,r] search max right
    int prefix_binary_search(int l, int r, TypeNode var) {
        assert(0 <= l && l < length && 0 < r && r <= length);
        TypeNode ret = Monoid::unit_node;
        size_t off = l;
        for(size_t idx = l+length; idx < 2*length && off < r; ){
            if(range[idx].second<=r && !Monoid::func_check(Monoid::func_fold(ret,node[idx]),var)) {
                ret = Monoid::func_fold(ret,node[idx]);
                off = range[idx++].second;
                if(!(idx&1)) idx >>= 1;
            }
            else{
                idx <<=1;
            }
        }
        return off;
    }

    //range(l,r] return [l,r] search max left
    int suffix_binary_search(const int l, const int r, const TypeNode var) {
        assert(-1 <= l && l < (int)length-1 && 0 <= r && r < length);
        TypeNode ret = Monoid::unit_node;
        int off = r;
        for(size_t idx = r+length; idx < 2*length && l < off; ){
            if(l < range[idx].first && !Monoid::func_check(Monoid::func_fold(node[idx],ret),var)) {
                ret = Monoid::func_fold(node[idx],ret);
                off = range[idx--].first-1;
                if(idx&1) idx >>= 1;
            }
            else{
                idx = (idx<<1)+1;
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
        cout << "vector" << endl;
        cout << "{ " << fold(0,1);
        for(int i = 1; i < length; ++i) cout << ", " << fold(i,i+1);
        cout << " }" << endl;
    }
};

/*
 * @title MonoidRangeMinPointUpdate - [区間min, 点更新]
 * @docs md/operator/monoid/MonoidRangeMinPointUpdate.md
 */
template<class T> struct MonoidRangeMaxPointAdd {
    using TypeNode = T;
    inline static constexpr TypeNode unit_node = 0;
    inline static constexpr TypeNode func_fold(TypeNode l,TypeNode r){return max(l,r);}
    inline static constexpr TypeNode func_operate(TypeNode l,TypeNode r){return l+r;}
    inline static constexpr bool func_check(TypeNode nodeVal,TypeNode var){return var > nodeVal;}
};

/**
 * @url 
 * @est
 */ 
int main() {
    cin.tie(0);ios::sync_with_stdio(false);
    int N; cin >> N;
    vector<int64> Y(N),X(N),C(N);
    for(int i=0;i<N;++i) cin >> Y[i] >> X[i] >> C[i];
    Zarts ZY(Y),ZX(X);
    SegmentTree<MonoidRangeMaxPointAdd<int64>> seg(N,0);
    for(int i=0;i<N;++i) {
        seg.operate(ZY.compressed[i],C[i]);
    }
    vector<vector<int>> vv(N);
    for(int i=0;i<N;++i) {
        vv[ZX.compressed[i]].push_back(i);
    }
    vector<int64> sum(N,0);
    for(int i=0;i<N;++i) {
        sum[ZX.compressed[i]]+=C[i];
    }
    int64 ans = 0;
    for(int x=0;x<N;++x) {
        int64 ss = sum[x];
        for(int i:vv[x]) {
            int y = ZY.compressed[i];
            seg.operate(y,-C[i]);
        }
        chmax(ans,ss + seg.fold(0,N));
        for(int i:vv[x]) {
            int y = ZY.compressed[i];
            seg.operate(y,C[i]);
        }
    }
    cout << ans << endl;
    return 0;
}
