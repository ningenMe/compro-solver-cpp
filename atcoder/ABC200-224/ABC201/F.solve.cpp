#include <bits/stdc++.h> 
using namespace std; 
using int128  = __int128_t; 
using int64   = long long; 
using int32   = int; 
using uint128 = __uint128_t; 
using uint64  = unsigned long long; 
using uint32  = unsigned int; 

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
template<class T> struct MonoidRangeMinPointUpdate {
    using TypeNode = T;
    inline static constexpr TypeNode unit_node = LOWINF;
    inline static constexpr TypeNode func_fold(TypeNode l,TypeNode r){return min(l,r);}
    inline static constexpr TypeNode func_operate(TypeNode l,TypeNode r){return r;}
    inline static constexpr bool func_check(TypeNode nodeVal,TypeNode var){return var > nodeVal;}
};

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
    vector<int64> P(N),A(N),L(N),R(N);
    for(int i=0;i<N;++i) cin >> P[i], P[i]--;
    for(int i=0;i<N;++i) {
        int64 a,l,r; cin >> a >> l >> r;
        A[i] = a;
        L[i] = min(a,l);
        R[i] = min(a,r);
    }
    DisjointSparseTable<NodeSum<int64>> dstA(A),dstL(L),dstR(R);
    SegmentTree<MonoidRangeMinPointUpdate<int64>> dp(N);
    int64 ans = LOWINF;
    for(int i=0;i<N;++i) {
        int p = P[i];
        int64 cnt = LOWINF;
        chmin(cnt,dstL.fold(0,p));
        chmin(cnt,dstA.fold(0,p) + dp.fold(0,p));
        chmin(ans,cnt + dstR.fold(p+1,N));
        dp.operate(p,cnt - dstA.fold(0,p+1));
    }
    cout << ans << endl;
    return 0; 
} 