#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define ALL(obj) (obj).begin(),(obj).end()
#define SPEED cin.tie(0);ios::sync_with_stdio(false);

template<class T> using PQ = priority_queue<T>;
template<class T> using PQR = priority_queue<T,vector<T>,greater<T>>;

constexpr long long MOD = (long long)1e9 + 7;
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
template <template <class tmp>  class T, class U> ostream &operator<<(ostream &o, const T<U> &obj) {o << "{"; for (auto itr = obj.begin(); itr != obj.end(); ++itr)o << (itr != obj.begin() ? ", " : "") << *itr; o << "}"; return o;}
void print(void) {cout << endl;}
template <class Head> void print(Head&& head) {cout << head;print();}
template <class Head, class... Tail> void print(Head&& head, Tail&&... tail) {cout << head << " ";print(forward<Tail>(tail)...);}
template <class T> void chmax(T& a, const T b){a=max(a,b);}
template <class T> void chmin(T& a, const T b){a=min(a,b);}
void YN(bool flg) {cout << (flg ? "YES" : "NO") << endl;}
void Yn(bool flg) {cout << (flg ? "Yes" : "No") << endl;}
void yn(bool flg) {cout << (flg ? "yes" : "no") << endl;}

template<class Operator> class SegmentTree {
	Operator Op;                            
	using typeNode = decltype(Op.unitNode); 
	size_t length;
	size_t num;
	vector<typeNode> node;
	vector<pair<size_t,size_t>> range;
public:

	//unitで初期化
	SegmentTree(const size_t num): num(num) {
		for (length = 1; length < num; length *= 2);
		node.resize(2 * length, Op.unitNode);
		range.resize(2 * length);
		for (int i = 0; i < length; ++i) range[i+length] = make_pair(i,i+1);
		for (int i = length - 1; i >= 0; --i) range[i] = make_pair(range[(i<<1)+0].first,range[(i<<1)+1].second);
	}

	//vectorで初期化
	SegmentTree(const vector<typeNode> & vec) : num(vec.size()) {
		for (length = 1; length < vec.size(); length *= 2);
		node.resize(2 * length, Op.unitNode);
		for (int i = 0; i < vec.size(); ++i) node[i + length] = vec[i];
		for (int i = length - 1; i >= 0; --i) node[i] = Op.funcNode(node[(i<<1)+0],node[(i<<1)+1]);
		range.resize(2 * length);
		for (int i = 0; i < length; ++i) range[i+length] = make_pair(i,i+1);
		for (int i = length - 1; i >= 0; --i) range[i] = make_pair(range[(i<<1)+0].first,range[(i<<1)+1].second);
	}
 
	//同じinitで初期化
	SegmentTree(const size_t num, const typeNode init) : num(num) {
		for (length = 1; length < num; length *= 2);
		node.resize(2 * length, init);
		range.resize(2 * length);
		for (int i = 0; i < length; ++i) range[i+length] = make_pair(i,i+1);
		for (int i = length - 1; i >= 0; --i) range[i] = make_pair(range[(i<<1)+0].first,range[(i<<1)+1].second);
	}
	
	//[idx,idx+1)
	void update(size_t idx, const typeNode var) {
		if(idx < 0 || length <= idx) return;
		idx += length;
		node[idx] = Op.funcMerge(node[idx],var);
		while(idx >>= 1) node[idx] = Op.funcNode(node[(idx<<1)+0],node[(idx<<1)+1]);
	}

	//[l,r)
	typeNode get(int l, int r) {
		if (l < 0 || length <= l || r < 0 || length < r) return Op.unitNode;
		typeNode vl = Op.unitNode, vr = Op.unitNode;
		for(l += length, r += length; l < r; l >>=1, r >>=1) {
			if(l&1) vl = Op.funcNode(vl,node[l++]);
			if(r&1) vr = Op.funcNode(node[--r],vr);
		}
		return Op.funcNode(vl,vr);
	}

	//return [0,length]
	int PrefixBinarySearch(typeNode var) {
		if(!Op.funcCheck(node[1],var)) return num;
		typeNode ret = Op.unitNode;
		size_t idx = 2;
		for(; idx < 2*length; idx<<=1){
			if(!Op.funcCheck(Op.funcNode(ret,node[idx]),var)) {
				ret = Op.funcNode(ret,node[idx]);
				idx++;
			}
		}
		return min((idx>>1) - length,num);
	}

	//range[l,r) return [l,r]
	int BinarySearch(size_t l, size_t r, typeNode var) {
		if (l < 0 || length <= l || r < 0 || length < r) return -1;
		typeNode ret = Op.unitNode;
		size_t off = l;
		for(size_t idx = l+length; idx < 2*length && off < r; ){
			if(range[idx].second<=r && !Op.funcCheck(Op.funcNode(ret,node[idx]),var)) {
				ret = Op.funcNode(ret,node[idx]);
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
		cout << "{ " << get(0,1);
		for(int i = 1; i < length; ++i) cout << ", " << get(i,i+1);
		cout << " }" << endl;

		// for(int i = 1,j = 1; i < 2*length; ++i) {
		// 	cout << node[i] << " ";
		// 	if(i==((1<<j)-1) && ++j) cout << endl;
		// }
	}

};

//一点加算 区間最大
template<class typeNode> struct nodeMaxPointAdd {
	typeNode unitNode = 0;
	typeNode funcNode(typeNode l,typeNode r){return max(l,r);}
	typeNode funcMerge(typeNode l,typeNode r){return l+r;}
};

//一点加算 区間総和
template<class typeNode> struct nodeSumPointAdd {
	typeNode unitNode = 0;
	typeNode funcNode(typeNode l,typeNode r){return l+r;}
	typeNode funcMerge(typeNode l,typeNode r){return l+r;}
	// Binary Search for first index at where funcCheck is true
	bool funcCheck(typeNode nodeVal,typeNode var){return var <= nodeVal;}
};

//一点更新 区間最小
template<class typeNode> struct nodeMinPointUpdate {
	typeNode unitNode = (1LL<<31)-1;
	typeNode funcNode(typeNode l,typeNode r){return min(l,r);}
	typeNode funcMerge(typeNode l,typeNode r){return r;}
};

//一点更新 区間GCD
template<class typeNode> struct nodeGCDPointUpdate {
	typeNode unitNode = 0;
	typeNode funcNode(typeNode l,typeNode r){return ((r == 0) ? l : funcNode(r, l % r));}
	typeNode funcMerge(typeNode l,typeNode r){return r;}
	// Binary Search for first index at where funcCheck is true
	bool funcCheck(typeNode nodeVal,typeNode var){return var == nodeVal;}
};

//Union Find Tree
class UnionFindTreeSize {
public:
	vector<int> parent;

    UnionFindTreeSize(int N = 1) : parent(N,-1){
	}
 
	int root(int n) {
        return (parent[n]<0?n:parent[n] = root(parent[n]));
	}

    bool same(int n, int m) {
		return root(n) == root(m);
	}
 
	void unite(int n, int m) {
		n = root(n);
		m = root(m);
		if (n == m) return;
		if(parent[n]>parent[m]) swap(n, m);
        parent[n] += parent[m];
        parent[m] = n;
	}

    int size(int n){
        return (-parent[root(n)]);
    }
};


//verify 

int main() {
    int N,K; cin >> N >> K;
    vector<ll> A(N);
    for(int i = 0; i < N; ++i) cin >> A[i];
    sort(ALL(A));
    UnionFindTreeSize uf(N);
    for(int i = 0; i+1 < N; ++i) if(A[i]==A[i+1])uf.unite(i,i+1);
    for(int i = 0; i < N; ++i) corner(uf.size(i) >= K,0);

    SegmentTree<nodeSumPointAdd<ll>> Seg(A);
    ll ans = LOWINF;
    vector<ll> L(N),R(N);
    L[0] = 0;
    for(int i = 1; i < N; ++i) {
        ll sum = Seg.get(0,i+1);
        ll X = A[i];
        L[i] = X*(i+1) - sum;
        if(K<=(i+1)) chmin(ans,L[i]-(i+1-K));
    }
    for(int i = N-1; 0 <= i; --i) {
        ll sum = Seg.get(i,N);
        ll X = A[i];
        R[i] = sum - X*(N-i);
        if(K<=(N-i)) chmin(ans,R[i]-(N-i-K));
    }
    for(int i = 0; i < N; ++i) {
        ll sum = L[i] + R[i];
        chmin(ans,sum - (N-K));
    }
    cout << ans << endl;
    return 0;
}
