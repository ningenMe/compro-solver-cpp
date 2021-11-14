#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define ALL(obj) (obj).begin(),(obj).end()
template<class T> using priority_queue_reverse = priority_queue<T,vector<T>,greater<T>>;

constexpr long long MOD = 1'000'000'000LL + 7; //'
constexpr long long MOD2 = 998244353;
constexpr long long HIGHINF = (long long)1e18;
constexpr long long LOWINF = (long long)1e15;
constexpr long double PI = 3.1415926535897932384626433L;

template <class T> vector<T> multivector(size_t N,T init){return vector<T>(N,init);}
template <class... T> auto multivector(size_t N,T... t){return vector<decltype(multivector(t...))>(N,multivector(t...));}
template <class T> void corner(bool flg, T hoge) {if (flg) {cout << hoge << endl; exit(0);}}
template <class T, class U>ostream &operator<<(ostream &o, const map<T, U>&obj) {o << "{"; for (auto &x : obj) o << " {" << x.first << " : " << x.second << "}" << ","; o << " }"; return o;}
template <class T>ostream &operator<<(ostream &o, const set<T>&obj) {o << "{"; for (auto itr = obj.begin(); itr != obj.end(); ++itr) o << (itr != obj.begin() ? ", " : "") << *itr; o << "}"; return o;}
template <class T>ostream &operator<<(ostream &o, const multiset<T>&obj) {o << "{"; for (auto itr = obj.begin(); itr != obj.end(); ++itr) o << (itr != obj.begin() ? ", " : "") << *itr; o << "}"; return o;}
template <class T>ostream &operator<<(ostream &o, const vector<T>&obj) {o << "{"; for (int i = 0; i < (int)obj.size(); ++i)o << (i > 0 ? ", " : "") << obj[i]; o << "}"; return o;}
template <class T, class U>ostream &operator<<(ostream &o, const pair<T, U>&obj) {o << "{" << obj.first << ", " << obj.second << "}"; return o;}
void print(void) {cout << endl;}
template <class Head> void print(Head&& head) {cout << head;print();}
template <class Head, class... Tail> void print(Head&& head, Tail&&... tail) {cout << head << " ";print(forward<Tail>(tail)...);}
template <class T> void chmax(T& a, const T b){a=max(a,b);}
template <class T> void chmin(T& a, const T b){a=min(a,b);}
vector<string> split(const string &str, const char delemiter) {vector<string> res;stringstream ss(str);string buffer; while( getline(ss, buffer, delemiter) ) res.push_back(buffer); return res;}
int msb(int x) {return x?31-__builtin_clz(x):-1;}
void YN(bool flg) {cout << (flg ? "YES" : "NO") << endl;}
void Yn(bool flg) {cout << (flg ? "Yes" : "No") << endl;}
void yn(bool flg) {cout << (flg ? "yes" : "no") << endl;}

/*
 * @title SegmentTree - 非再帰抽象化セグメント木
 * @docs md/segment/SegmentTree.md
 */
template<class Operator> class SegmentTree {
    using TypeNode = typename Operator::TypeNode; 
    size_t length;
    size_t num;
    vector<TypeNode> node;
    vector<pair<int,int>> range;
    inline void build() {
        for (int i = length - 1; i >= 0; --i) node[i] = Operator::func_node(node[(i<<1)+0],node[(i<<1)+1]);
        range.resize(2 * length);
        for (int i = 0; i < length; ++i) range[i+length] = make_pair(i,i+1);
        for (int i = length - 1; i >= 0; --i) range[i] = make_pair(range[(i<<1)+0].first,range[(i<<1)+1].second);
    }
public:

    //unitで初期化
    SegmentTree(const size_t num): num(num) {
        for (length = 1; length <= num; length *= 2);
        node.resize(2 * length, Operator::unit_node);
        build();
    }

    //vectorで初期化
    SegmentTree(const vector<TypeNode> & vec) : num(vec.size()) {
        for (length = 1; length <= vec.size(); length *= 2);
        node.resize(2 * length, Operator::unit_node);
        for (int i = 0; i < vec.size(); ++i) node[i + length] = vec[i];
        build();
    }
 
    //同じinitで初期化
    SegmentTree(const size_t num, const TypeNode init) : num(num) {
        for (length = 1; length <= num; length *= 2);
        node.resize(2 * length, Operator::unit_node);
        for (int i = 0; i < length; ++i) node[i+length] = init;
        build();
    }
    
    //[idx,idx+1)
    void update(size_t idx, const TypeNode var) {
        if(idx < 0 || length <= idx) return;
        idx += length;
        node[idx] = Operator::func_merge(node[idx],var);
        while(idx >>= 1) node[idx] = Operator::func_node(node[(idx<<1)+0],node[(idx<<1)+1]);
    }

    //[l,r)
    TypeNode get(int l, int r) {
        if (l < 0 || length <= l || r < 0 || length < r) return Operator::unit_node;
        TypeNode vl = Operator::unit_node, vr = Operator::unit_node;
        for(l += length, r += length; l < r; l >>=1, r >>=1) {
            if(l&1) vl = Operator::func_node(vl,node[l++]);
            if(r&1) vr = Operator::func_node(node[--r],vr);
        }
        return Operator::func_node(vl,vr);
    }

    //range[l,r) return [l,r] search max right
    int prefix_binary_search(int l, int r, TypeNode var) {
        assert(0 <= l && l < length && 0 < r && r <= length);
        TypeNode ret = Operator::unit_node;
        size_t off = l;
        for(size_t idx = l+length; idx < 2*length && off < r; ){
            if(range[idx].second<=r && !Operator::func_check(Operator::func_node(ret,node[idx]),var)) {
                ret = Operator::func_node(ret,node[idx]);
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
        TypeNode ret = Operator::unit_node;
        int off = r;
        for(size_t idx = r+length; idx < 2*length && l < off; ){
            if(l < range[idx].first && !Operator::func_check(Operator::func_node(node[idx],ret),var)) {
                ret = Operator::func_node(node[idx],ret);
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
        cout << "{ " << get(0,1);
        for(int i = 1; i < length; ++i) cout << ", " << get(i,i+1);
        cout << " }" << endl;
    }
};

//一点更新 区間最小
template<class T> struct NodeMinPointUpdate {
    using TypeNode = T;
    inline static constexpr TypeNode unit_node = (1LL<<31)-1;
    inline static constexpr TypeNode func_node(TypeNode l,TypeNode r){return min(l,r);}
    inline static constexpr TypeNode func_merge(TypeNode l,TypeNode r){return r;}
    inline static constexpr bool func_check(TypeNode nodeVal,TypeNode var){return var > nodeVal;}
};

/*
 * 区間mex
 * @params A vector
 * @params ranges 半開区間[l,r)のvector 0-indexed
 * @params offset mexの最小値
 * @params ret rangeに対するmexの値
 * @see https://codeforces.com/contest/1436/problem/E
 * @see https://twitter.com/noshi91/status/1279594849826533377?s=20
 */
template<class T> map<pair<int,int>,int> static_range_mex_query(const vector<T>& A, const vector<pair<int,int>>& ranges, T offset = 0) {
    int N = A.size();
    vector<vector<int>> r_to_l(N+1);
    for(int i=0;i<ranges.size();++i) {
        const int& l=ranges[i].first;
        const int& r=ranges[i].second;
        r_to_l[r].push_back(l);
    }
    SegmentTree<NodeMinPointUpdate<int>> seg(offset+N+1,-1);
    for(int i=0;i<offset;++i) seg.update(i,offset+N+1);
    map<pair<int,int>,int> ret;
    for(int r=0;r<N;++r) {
        if(A[r]<=offset+N) seg.update(A[r],r);
        for(int& l:r_to_l[r+1]) {
            ret[{l,r+1}] = seg.prefix_binary_search(offset,offset+N+1,l);
        }
    }
    return ret;
}

int main() {
    cin.tie(0);ios::sync_with_stdio(false);
    int N; cin >> N;
    vector<int> A(N);
    for(int i=0;i<N;++i) cin >> A[i];

    vector<vector<int>> idx(N+2);
    for(int i=1;i<=N+1;++i) idx[i].push_back(-1);
    for(int i=0;i<N;++i) idx[A[i]].push_back(i);
    for(int i=1;i<=N+1;++i) idx[i].push_back(N);

    vector<pair<int,int>> ranges;
    for(int i=1;i<=N;++i) {
        for(int j:idx[i]) {
            if(j<0||N<=j) continue;
            auto itr = lower_bound(ALL(idx[i+1]),j);
            int r = (*itr); --itr;
            int l = (*itr) + 1;
            ranges.emplace_back(l,r);
        }
    }
    auto mex = static_range_mex_query(A,ranges,1);

    set<int> st;
    for(int i=1;i<=N;++i) {
        for(int j:idx[i]) {
            if(j<0||N<=j) continue;
            auto itr = lower_bound(ALL(idx[i+1]),j);
            int r = (*itr); --itr;
            int l = (*itr) + 1;
            int m = mex[{l,r}];
            st.insert(m);
        }
    }

    for(int i=0;i<N;++i) if(A[i]>1) st.insert(1);
    int ans = -1;
    for(int i=1;i<=2*N && ans == -1;++i) {
        if(!st.count(i)) ans = i;
    }
    cout << ans << endl;
    return 0;
}
