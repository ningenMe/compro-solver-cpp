#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define ALL(obj) (obj).begin(),(obj).end()
template<class T> using priority_queue_reverse = priority_queue<T,vector<T>,greater<T>>;

constexpr long long MOD = 1'000'000'000LL + 7;
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
 * @title LazySegmentTree - 非再帰抽象化遅延評価セグメント木
 * @docs md/segment/LazySegmentTree.md
 */
template<class Operator> class LazySegmentTree {
	using TypeNode = typename Operator::TypeNode;          
	using TypeLazy = typename Operator::TypeLazy;
	size_t num;      
	size_t length;                                   
	size_t height;                                   
	vector<TypeNode> node;                           
	vector<TypeLazy> lazy;                           
	vector<pair<size_t,size_t>> range;

	void propagate(int k) {
		if(lazy[k] == Operator::unit_lazy) return;
        node[k] = Operator::func_merge(node[k],lazy[k],range[k].first,range[k].second);
		if(k < length) lazy[2*k+0] = Operator::func_lazy(lazy[2*k+0],lazy[k]);
		if(k < length) lazy[2*k+1] = Operator::func_lazy(lazy[2*k+1],lazy[k]);
		lazy[k] = Operator::unit_lazy;
	}
public:

	//unitで初期化
	LazySegmentTree(const size_t num) : num(num) {
		for (length = 1,height = 0; length <= num; length *= 2, height++);
		node.resize(2 * length, Operator::unit_node);
		lazy.resize(2 * length, Operator::unit_lazy);
		for (int i = 0; i < num; ++i) node[i + length] = Operator::unit_node;
		for (int i = length - 1; i >= 0; --i) node[i] = Operator::func_node(node[(i<<1)+0],node[(i<<1)+1]);
		range.resize(2 * length);
		for (int i = 0; i < length; ++i) range[i+length] = make_pair(i,i+1);
		for (int i = length - 1; i >= 0; --i) range[i] = make_pair(range[(i<<1)+0].first,range[(i<<1)+1].second);
	}

	// //同じinitで初期化
	LazySegmentTree(const size_t num, const TypeNode init) : num(num) {
		for (length = 1,height = 0; length <= num; length *= 2, height++);
		node.resize(2 * length, Operator::unit_node);
		lazy.resize(2 * length, Operator::unit_lazy);
		for (int i = 0; i < num; ++i) node[i + length] = init;
		for (int i = length - 1; i >= 0; --i) node[i] = Operator::func_node(node[(i<<1)+0],node[(i<<1)+1]);
		range.resize(2 * length);
		for (int i = 0; i < length; ++i) range[i+length] = make_pair(i,i+1);
		for (int i = length - 1; i >= 0; --i) range[i] = make_pair(range[(i<<1)+0].first,range[(i<<1)+1].second);
	}

	//vectorで初期化
	LazySegmentTree(const vector<TypeNode>& vec) : num(vec.size()) {
		for (length = 1,height = 0; length <= vec.size(); length *= 2, height++);
		node.resize(2 * length, Operator::unit_node);
		lazy.resize(2 * length, Operator::unit_lazy);
		for (int i = 0; i < vec.size(); ++i) node[i + length] = vec[i];
		for (int i = length - 1; i >= 0; --i) node[i] = Operator::func_node(node[(i<<1)+0],node[(i<<1)+1]);
		range.resize(2 * length);
		for (int i = 0; i < length; ++i) range[i+length] = make_pair(i,i+1);
		for (int i = length - 1; i >= 0; --i) range[i] = make_pair(range[(i<<1)+0].first,range[(i<<1)+1].second);
	}

	//update [a,b)
	void update(int a, int b, TypeLazy x) {
		int l = a + length, r = b + length - 1;
		for (int i = height; 0 < i; --i) propagate(l >> i), propagate(r >> i);
		for(r++; l < r; l >>=1, r >>=1) {
			if(l&1) lazy[l] = Operator::func_lazy(lazy[l],x), propagate(l),l++;
			if(r&1) --r,lazy[r] = Operator::func_lazy(lazy[r],x), propagate(r);
		}
		l = a + length, r = b + length - 1;
		while ((l>>=1),(r>>=1),l) {
            if(lazy[l] == Operator::unit_lazy) node[l] = Operator::func_node(Operator::func_merge(node[(l<<1)+0],lazy[(l<<1)+0],range[(l<<1)+0].first,range[(l<<1)+0].second),Operator::func_merge(node[(l<<1)+1],lazy[(l<<1)+1],range[(l<<1)+1].first,range[(l<<1)+1].second));
            if(lazy[r] == Operator::unit_lazy) node[r] = Operator::func_node(Operator::func_merge(node[(r<<1)+0],lazy[(r<<1)+0],range[(r<<1)+0].first,range[(r<<1)+0].second),Operator::func_merge(node[(r<<1)+1],lazy[(r<<1)+1],range[(r<<1)+1].first,range[(r<<1)+1].second));
  		}
	}

	//get [a,b)
	TypeNode get(int a, int b) {
		int l = a + length, r = b + length - 1;
		for (int i = height; 0 < i; --i) propagate(l >> i), propagate(r >> i);
		TypeNode vl = Operator::unit_node, vr = Operator::unit_node;
		for(r++; l < r; l >>=1, r >>=1) {
            if(l&1) vl = Operator::func_node(vl,Operator::func_merge(node[l],lazy[l],range[l].first,range[l].second)),l++;
            if(r&1) r--,vr = Operator::func_node(Operator::func_merge(node[r],lazy[r],range[r].first,range[r].second),vr);
 		}
		return Operator::func_node(vl,vr);
	}

	//return [0,length]
	int prefix_binary_search(TypeNode var) {
		int l = length, r = 2*length - 1;
		for (int i = height; 0 < i; --i) propagate(l >> i), propagate(r >> i);
		if(!Operator::func_check(node[1],var)) return num;
		TypeNode ret = Operator::unit_node;
		size_t idx = 2;
		for(; idx < 2*length; idx<<=1){
            if(!Operator::func_check(Operator::func_node(ret,Operator::func_merge(node[idx],lazy[idx],range[idx].first,range[idx].second)),var)) {
                ret = Operator::func_node(ret,Operator::func_merge(node[idx],lazy[idx],range[idx].first,range[idx].second));
                idx++;
            }
		}
		return min((idx>>1) - length,num);
	}

	//range[l,r) return [l,r]
	int binary_search(size_t l, size_t r, TypeNode var) {
		if (l < 0 || length <= l || r < 0 || length < r) return -1;
		for (int i = height; 0 < i; --i) propagate((l+length) >> i), propagate((r+length-1) >> i);
		TypeNode ret = Operator::unit_node;
		size_t off = l;
		for(size_t idx = l+length; idx < 2*length && off < r; ){
            if(range[idx].second<=r && !Operator::func_check(Operator::func_node(ret,Operator::func_merge(node[idx],lazy[idx],range[idx].first,range[idx].second)),var)) {
                ret = Operator::func_node(ret,Operator::func_merge(node[idx],lazy[idx],range[idx].first,range[idx].second));
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
		cout << "{ " << get(0,1);
		for(int i = 1; i < length; ++i) cout << ", " << get(i,i+1);
		cout << " }" << endl;
	}
};

//node:最小　lazy:加算
template<class T, class U> struct NodeMinRangeAdd {
	using TypeNode = T;
	using TypeLazy = U;
	inline static constexpr TypeNode unit_node = 1234567;
	inline static constexpr TypeLazy unit_lazy = 1234567;
	inline static constexpr TypeNode func_node(TypeNode l,TypeNode r){return min(l,r);}
	inline static constexpr TypeLazy func_lazy(TypeLazy old_lazy,TypeLazy new_lazy){return min(old_lazy,new_lazy);}
	inline static constexpr TypeNode func_merge(TypeNode node,TypeLazy lazy,int l, int r){return min(node,lazy);}
	// LazySegmentTree<NodeMinRangeAdd<ll,ll>> Seg(N,0);
};


void solve(){
    int N; cin >> N;
    vector<int> a(N);
    for(int i = 0; i < N; ++i) cin >> a[i];
    vector<vector<int>> vv(N+1);
    for(int i = 0; i < N; ++i) {
        vv[a[i]].push_back(i);
    }
    int inf = 1234567;
    LazySegmentTree<NodeMinRangeAdd<int,int>> seg(N+1,inf);
    for(int i = N; 1 <= i; --i) {
        if(vv[i].empty()) continue;
        vv[i].push_back(N);
        int pre = -1;
        int cnt = 1;
        for(int& x:vv[i]) {
            int d = x-pre;
            chmax(cnt,d);
            pre = x;
        }
        seg.update(cnt,N+1,i);
    }
    for(int i=1;i<=N;++i) {
        int ans = seg.get(i,i+1);
        if(ans == inf) ans = -1;
        cout << ans << " ";
    }
    cout << endl;
}

int main() {
    cin.tie(0);ios::sync_with_stdio(false);
    int t; cin >> t;
    while(t--){
        solve();
    }
    return 0;
}
