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
 * @title MonoidRangeSumRangeAdd - [区間和, 区間加算]
 * @docs md/operator/monoid-lazy/MonoidRangeSumRangeAdd.md
 */
template<class T, class U> struct MonoidRangeSumRangeAdd {
	using TypeNode = T;
	using TypeLazy = U;
	inline static constexpr TypeNode unit_node = 0;
	inline static constexpr TypeLazy unit_lazy = 0;
	inline static constexpr TypeNode func_fold(TypeNode l,TypeNode r){return l+r;}
	inline static constexpr TypeLazy func_lazy(TypeLazy old_lazy,TypeLazy new_lazy){return old_lazy+new_lazy;}
	inline static constexpr TypeNode func_operate(TypeNode node,TypeLazy lazy,int l, int r){return node+lazy*(r-l);}
	inline static constexpr bool func_check(TypeNode nodeVal,TypeNode var){return var <= nodeVal;}
};

/**
 * @url 
 * @est
 */ 
int main() {
    cin.tie(0);ios::sync_with_stdio(false);
    int N; cin >> N;
    vector<array<int,4>> yy;
    int L = 100010;
    LazySegmentTree<MonoidRangeSumRangeAdd<int64,int64>> seg(L,0);
    for(int i=0;i<N;++i) {
        int M; cin >> M;
        vector<pair<int,int>> vp(M);
        for(int j=0;j<M;++j) {
            int x,y; cin >> x >> y;
            vp[j] = {x,y};
        }
        vector<array<int,3>> var;
        for(int j=0;j<M;++j) {
            auto [x1,y1]=vp[j];
            auto [x2,y2]=vp[(j+1)%M];
            if(y1!=y2) continue;
            var.push_back({y1,min(x1,x2),max(x1,x2)});
        }
        sort(ALL(var));
        for(auto ar:var) {
            int x1 = ar[1], x2 = ar[2];
            int y = ar[0];
            int c = seg.fold(x1,x2) ? -1 : 1;
            seg.operate(x1,x2,c);
            yy.push_back({y,c,x1,x2});
        }
    }
    int Q; cin >> Q;
    vector<pair<int,int>> query(Q);
    for(int i=0;i<Q;++i) {
        int y,x; cin >> x >> y;
        query[i] = {y,x};
        yy.push_back({y,2,x,x});
    }
    sort(ALL(yy));
    map<pair<int,int>,int> mp;
    for(auto ar:yy) {
        int y = ar[0];
        int c = ar[1];
        int x1 = ar[2];
        int x2 = ar[3];
        if(c==2) {
            mp[{y,x1}] = seg.fold(x1,x1+1);
        }
        else {
            seg.operate(x1,x2,c);
        }
    }
    for(int i=0;i<Q;++i) {
        cout << mp[query[i]] << "\n";
    }    
    return 0;
}
