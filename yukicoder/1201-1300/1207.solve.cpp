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
 * @title ModInt
 */
template<long long mod> class ModInt {
public:
	long long x;
	constexpr ModInt():x(0) {
		// do nothing
	}
	constexpr ModInt(long long y) : x(y>=0?(y%mod): (mod - (-y)%mod)%mod) {
		// do nothing
	}
	ModInt &operator+=(const ModInt &p) {
		if((x += p.x) >= mod) x -= mod;
		return *this;
	}
	ModInt &operator+=(const long long y) {
		ModInt p(y);
		if((x += p.x) >= mod) x -= mod;
		return *this;
	}
	ModInt &operator+=(const int y) {
		ModInt p(y);
		if((x += p.x) >= mod) x -= mod;
		return *this;
	}
	ModInt &operator-=(const ModInt &p) {
		if((x += mod - p.x) >= mod) x -= mod;
		return *this;
	}
	ModInt &operator-=(const long long y) {
		ModInt p(y);
		if((x += mod - p.x) >= mod) x -= mod;
		return *this;
	}
	ModInt &operator-=(const int y) {
		ModInt p(y);
		if((x += mod - p.x) >= mod) x -= mod;
		return *this;
	}
	ModInt &operator*=(const ModInt &p) {
		x = (x * p.x % mod);
		return *this;
	}
	ModInt &operator*=(const long long y) {
		ModInt p(y);
		x = (x * p.x % mod);
		return *this;
	}
	ModInt &operator*=(const int y) {
		ModInt p(y);
		x = (x * p.x % mod);
		return *this;
	}
	ModInt &operator^=(const ModInt &p) {
		x = (x ^ p.x) % mod;
		return *this;
	}
	ModInt &operator^=(const long long y) {
		ModInt p(y);
		x = (x ^ p.x) % mod;
		return *this;
	}
	ModInt &operator^=(const int y) {
		ModInt p(y);
		x = (x ^ p.x) % mod;
		return *this;
	}
	ModInt &operator/=(const ModInt &p) {
		*this *= p.inv();
		return *this;
	}
	ModInt &operator/=(const long long y) {
		ModInt p(y);
		*this *= p.inv();
		return *this;
	}
	ModInt &operator/=(const int y) {
		ModInt p(y);
		*this *= p.inv();
		return *this;
	}
	ModInt operator=(const int y) {
		ModInt p(y);
		*this = p;
		return *this;
	}
	ModInt operator=(const long long y) {
		ModInt p(y);
		*this = p;
		return *this;
	}
	ModInt operator-() const { return ModInt(-x); }
	ModInt operator++() { 
		x++;
		if(x>=mod) x-=mod;
		return *this; 
	}
	ModInt operator--() { 
		x--;
		if(x<0) x+=mod;
		return *this; 
	}
	ModInt operator+(const ModInt &p) const { return ModInt(*this) += p; }
	ModInt operator-(const ModInt &p) const { return ModInt(*this) -= p; }
	ModInt operator*(const ModInt &p) const { return ModInt(*this) *= p; }
	ModInt operator/(const ModInt &p) const { return ModInt(*this) /= p; }
	ModInt operator^(const ModInt &p) const { return ModInt(*this) ^= p; }
	bool operator==(const ModInt &p) const { return x == p.x; }
	bool operator!=(const ModInt &p) const { return x != p.x; }
	ModInt inv() const {
		int a = x, b = mod, u = 1, v = 0, t;
		while(b > 0) {
			t = a / b;
			swap(a -= t * b, b);
			swap(u -= t * v, v);
		}
		return ModInt(u);
	}
	ModInt pow(long long n) const {
		ModInt ret(1), mul(x);
		while(n > 0) {
			if(n & 1) ret *= mul;
			mul *= mul;
			n >>= 1;
		}
		return ret;
	}
	friend ostream &operator<<(ostream &os, const ModInt &p) {
		return os << p.x;
	}
	friend istream &operator>>(istream &is, ModInt &a) {
		long long t;
		is >> t;
		a = ModInt<mod>(t);
		return (is);
	}
};
using modint = ModInt<MOD>;

/*
 * @title UnionFindTree
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
 * @title Tree
 * @docs md/graph/Tree.md
 */
template<class Operator> class Tree {
	using TypeDist = typename Operator::TypeDist;
	size_t num;
	size_t ord;
	enum METHODS{
		MAKE_DEPTH,
		MAKE_CHILD,
		MAKE_PARENT,
		MAKE_SIZE,
		MAKE_SUBTREE,
		MAKE_ANCESTOR,
		MAKE_EOULERTOUR,
		MAKE_HEAVY_LIGHT_DECOMPOSITION,
		METHODS_SIZE,
	};
	array<int,METHODS_SIZE> executed_flag;
public:
	vector<vector<pair<size_t,TypeDist>>> edge;
	vector<size_t> depth;
	vector<size_t> order;
	vector<size_t> reorder;
	vector<TypeDist> dist;
	vector<pair<size_t,TypeDist>> parent;
	vector<vector<pair<size_t,TypeDist>>> child;
	vector<array<pair<size_t,TypeDist>,Operator::bit>> ancestor;
	vector<size_t> size;
	vector<vector<size_t>> subtree;
	vector<size_t> head;
	vector<size_t> hldorder;
	vector<size_t> eulertour;
	vector<pair<size_t,size_t>> eulertour_range;
	Tree(const int num):num(num),edge(num),depth(num,-1),order(num),dist(num),executed_flag(){}
	//O(1) anytime
	void make_edge(const int& from, const int& to, const TypeDist w = 1) {
		edge[from].push_back({to,w});
	}
	//O(N) anytime
	void make_depth(const int root) {
		executed_flag[MAKE_DEPTH]++;
		depth[root] = 0;
		dist[root] = Operator::unit_dist;
		ord = 0;
		dfs(root,-1);
		order[ord++] = root;
		reverse_copy(order.begin(),order.end(),back_inserter(reorder));
	}
	//O(N) anytime for forest
	void make_depth(void) {
		executed_flag[MAKE_DEPTH]++;
		ord = 0;
		for(size_t root = 0; root < num; ++root) {
			if(depth[root] != -1) continue;
			depth[root] = 0;
			dist[root] = Operator::unit_dist;
			dfs(root,-1);
			order[ord++] = root;
		}
		reverse_copy(order.begin(),order.end(),back_inserter(reorder));
	}
	//for make_depth
	void dfs(int curr, int prev){
		for(auto& e:edge[curr]){
			int next = e.first;
			if(next==prev) continue;
			depth[next] = depth[curr] + 1;
			dist[next]  = Operator::func_dist(dist[curr],e.second);
			dfs(next,curr);
			order[ord++] = next;
		}
	}
	//for make_eulertour
	void dfs(int from){
		eulertour.push_back(from);
		for(auto& e:child[from]){
			int to = e.first;            
			dfs(to);        
			eulertour.push_back(from);
		}
	}
	//O(N) after make_depth
	void make_parent(const int root = 0) {
		if(executed_flag[MAKE_PARENT]++) return;
		if(!executed_flag[MAKE_DEPTH]) make_depth(root);
		parent.resize(num,make_pair(num,Operator::unit_dist));
		for (size_t i = 0; i < num; ++i) for (auto& e : edge[i]) if (depth[i] > depth[e.first]) parent[i] = e;
	}
	//O(N) after make_depth
	void make_child(const int root = 0) {
		if(executed_flag[MAKE_CHILD]++) return;
		if(!executed_flag[MAKE_DEPTH]) make_depth(root);
		child.resize(num);
		for (size_t i = 0; i < num; ++i) for (auto& e : edge[i]) if (depth[i] < depth[e.first]) child[i].push_back(e);
	}
	//O(NlogN) after make_parent
	void make_ancestor(const int root = 0) {
		if(executed_flag[MAKE_ANCESTOR]++) return;
		if(!executed_flag[MAKE_PARENT]) make_parent(root);
		ancestor.resize(num);
		for (size_t i = 0; i < num; ++i) ancestor[i][0] = (parent[i].first!=num?parent[i]:make_pair(i,Operator::unit_lca));
		for (size_t j = 1; j < Operator::bit; ++j) {
			for (size_t i = 0; i < num; ++i) {
				size_t k = ancestor[i][j - 1].first;
				ancestor[i][j] = Operator::func_lca(ancestor[k][j - 1],ancestor[i][j - 1]);
			}
		}
	}
	//O(logN) after make_ancestor
	//return {lca,lca_dist} l and r must be connected
	pair<size_t,TypeDist> lca(size_t l, size_t r) {
		assert(executed_flag[MAKE_ANCESTOR]);
		if (depth[l] < depth[r]) swap(l, r);
		int diff = depth[l] - depth[r];
		auto ancl = make_pair(l,Operator::unit_lca);
		auto ancr = make_pair(r,Operator::unit_lca);
		for (int j = 0; j < Operator::bit; ++j) {
			if (diff & (1 << j)) {
				ancl = Operator::func_lca(ancestor[ancl.first][j],ancl);
			}
		}
		if(ancl.first==ancr.first) return ancl;
		for (int j = Operator::bit - 1; 0 <= j; --j) {
			if(ancestor[ancl.first][j].first!=ancestor[ancr.first][j].first) {
				ancl = Operator::func_lca(ancestor[ancl.first][j],ancl);
				ancr = Operator::func_lca(ancestor[ancr.first][j],ancr);
			}
		}
		ancl = Operator::func_lca(ancestor[ancl.first][0],ancl);
		ancr = Operator::func_lca(ancestor[ancr.first][0],ancr);
		return Operator::func_lca(ancl,ancr);
	}
	//O(N) anytime
	//pair<diameter,vertex_set>
	pair<TypeDist,vector<int>> diameter(void){
		make_depth(0);
		int root = max_element(dist.begin(), dist.end()) - dist.begin();
		make_depth(root);
		int leaf = max_element(dist.begin(), dist.end()) - dist.begin();
		make_parent();
		TypeDist d = dist[leaf];
		vector<int> v;
		while (leaf != root) {
			v.push_back(leaf);
			leaf = parent[leaf].first;
		}
		v.push_back(root);
		return make_pair(d,v);
	}
	//O(N^2) after make_depth
	void make_subtree(const int root = 0) {
		if(executed_flag[MAKE_SUBTREE]++) return;
		if(!executed_flag[MAKE_DEPTH]) make_depth(root);
		subtree.resize(num);
		for (size_t i = 0; i < num; ++i) subtree[i].push_back(i);
		for (size_t i = 0; i < num; ++i) for (auto& e : edge[order[i]]) if (depth[order[i]] < depth[e.first]) for(auto k: subtree[e.first]) subtree[order[i]].push_back(k);
	}
	//O(N) after make_child
	void make_size(const int root = 0) {
		if(executed_flag[MAKE_SIZE]++) return;
		if(!executed_flag[MAKE_CHILD]) make_child(root);
		size.resize(num,1);
		for (size_t i:order) for (auto e : child[i]) size[i] += size[e.first];
	}
	//(N) after make_depth and make_child
	template<class TypeReroot> vector<TypeReroot> rerooting(vector<TypeReroot> rerootdp,vector<TypeReroot> rerootparent) {
		assert(executed_flag[MAKE_CHILD]);
		for(size_t pa:order) for(auto& e:child[pa]) rerootdp[pa] = Operator::func_reroot(rerootdp[pa],rerootdp[e.first]);
		for(size_t pa:reorder) {
			if(depth[pa]) rerootdp[pa] = Operator::func_reroot(rerootdp[pa],rerootparent[pa]);
			size_t m = child[pa].size();
			for(int j = 0; j < m && depth[pa]; ++j){
				size_t ch = child[pa][j].first;
				rerootparent[ch] = Operator::func_reroot(rerootparent[ch],rerootparent[pa]);
			}
			if(m <= 1) continue;
			vector<TypeReroot> l(m),r(m);
			for(int j = 0; j < m; ++j) {
				size_t ch = child[pa][j].first;
				l[j] = rerootdp[ch];
				r[j] = rerootdp[ch];
			}
			for(int j = 1; j+1 < m; ++j) l[j] = Operator::func_reroot_merge(l[j],l[j-1]);
			for(int j = m-2; 0 <=j; --j) r[j] = Operator::func_reroot_merge(r[j],r[j+1]);
			size_t chl = child[pa].front().first;
			size_t chr = child[pa].back().first;
			rerootparent[chl] = Operator::func_reroot(rerootparent[chl],r[1]);
			rerootparent[chr] = Operator::func_reroot(rerootparent[chr],l[m-2]);
			for(int j = 1; j+1 < m; ++j) {
				size_t ch = child[pa][j].first;
				rerootparent[ch] = Operator::func_reroot(rerootparent[ch],l[j-1]);
				rerootparent[ch] = Operator::func_reroot(rerootparent[ch],r[j+1]);
			}
		}
		return rerootdp;
	}
	//O(N) after make_depth,make_parent,make_child
	void make_heavy_light_decomposition(const int root = 0){
		if(executed_flag[MAKE_HEAVY_LIGHT_DECOMPOSITION]++) return;
		if(!executed_flag[MAKE_SIZE]) make_size(root);
		if(!executed_flag[MAKE_PARENT]) make_parent(root);
		head.resize(num);
		hldorder.resize(num);
		iota(head.begin(),head.end(),0);
		for(size_t& pa:reorder) {
			pair<size_t,size_t> maxi = {0,num};
			for(auto& e:child[pa]) maxi = max(maxi,{size[e.first],e.first});
			if(maxi.first) head[maxi.second] = head[pa];
		}
		stack<size_t> st_head,st_sub;
		size_t cnt = 0;
		for(size_t& root:reorder){
			if(depth[root]) continue;
			st_head.push(root);
			while(st_head.size()){
				size_t h = st_head.top();
				st_head.pop();
				st_sub.push(h);
				while (st_sub.size()){
					size_t pa = st_sub.top();
					st_sub.pop();
					hldorder[pa] = cnt++;
					for(auto& e:child[pa]) {
						if(head[e.first]==head[pa]) st_sub.push(e.first);
						else st_head.push(e.first);
					}
				}				
			}
		}
	}
	//after hld type 0: vertex, 1: edge
	vector<pair<size_t,size_t>> path(size_t u,size_t v,int type = 0) {
		assert(executed_flag[MAKE_HEAVY_LIGHT_DECOMPOSITION]);
		vector<pair<size_t,size_t>> path;
		while(1){
			if(hldorder[u]>hldorder[v]) swap(u,v);
			if(head[u]!=head[v]) {
				path.push_back({hldorder[head[v]],hldorder[v]});
				v=parent[head[v]].first;
			}
			else {
				path.push_back({hldorder[u],hldorder[v]});
				break;
			}
		}
		reverse(path.begin(),path.end());
		if(type) path.front().first++;
		return path;
	}
	size_t hld_lca(size_t u,size_t v){
		assert(executed_flag[MAKE_HEAVY_LIGHT_DECOMPOSITION]);
		while(1){
			if(hldorder[u]>hldorder[v]) swap(u,v);
			if(head[u]==head[v]) return u;
			v=parent[head[v]].first;
		}
	}
	//O(N) after make_child and make_parent
	void make_eulertour(const int root = 0){
		if(executed_flag[MAKE_EOULERTOUR]++) return;
		if(!executed_flag[MAKE_CHILD]) make_child(root);
		if(!executed_flag[MAKE_PARENT]) make_parent(root);
		dfs(reorder.front());
		eulertour_range.resize(num);
		for(int i = 0; i < eulertour.size(); ++i) eulertour_range[eulertour[i]].second = i;
		for(int i = eulertour.size()-1; 0 <= i; --i) eulertour_range[eulertour[i]].first = i;
	}
};
//depth,dist
//https://atcoder.jp/contests/abc126/tasks/abc126_d
//child
//https://atcoder.jp/contests/abc133/tasks/abc133_e
//lca
//https://atcoder.jp/contests/abc014/tasks/abc014_4
//weighted lca
//https://atcoder.jp/contests/code-thanks-festival-2017-open/tasks/code_thanks_festival_2017_h
//https://atcoder.jp/contests/cf16-tournament-round1-open/tasks/asaporo_c
//diameter
//https://atcoder.jp/contests/agc033/tasks/agc033_c
//subtree
//https://atcoder.jp/contests/code-thanks-festival-2018/tasks/code_thanks_festival_2018_f
//rerooting
//https://yukicoder.me/problems/no/922
//size
//https://yukicoder.me/problems/no/872
//eulerTour
//https://yukicoder.me/problems/no/900
//hld
//https://yukicoder.me/problems/no/399
//https://yukicoder.me/problems/no/650
template<class T> struct TreeOperator{
	using TypeDist = T;
	inline static constexpr size_t bit = 20;
	inline static constexpr TypeDist unit_dist = 0;
	inline static constexpr TypeDist unit_lca = 0;
	inline static constexpr TypeDist func_dist(const TypeDist& parent,const TypeDist& w){return parent+w;}
	inline static constexpr pair<size_t,TypeDist> func_lca(const pair<size_t,TypeDist>& l,const pair<size_t,TypeDist>& r){return make_pair(l.first,l.second+r.second);}
	template<class TypeReroot> inline static constexpr TypeReroot func_reroot(const TypeReroot& l,const TypeReroot& r) {
		return {l.first+r.first+r.second,l.second+r.second};
	}
	template<class TypeReroot> inline static constexpr TypeReroot func_reroot_merge(const TypeReroot& l,const TypeReroot& r) {
		return {l.first+r.first,l.second+r.second};
	}
};

/*
 * @title Mod
 */
class Mod{
public:
	//Pow_Mod O(log(n))
	inline static long long pow(long long x, long long n, long long mod) {
		long long res = 1;
		for (x %= mod; n > 0; n >>= 1, (x *= x) %= mod) if (n & 1) (res *= x) %= mod;
		return res;
	}
	//Inv_Mod O(log(mod))
	inline static long long inv(long long x, long long mod){
		return pow(x,mod-2,mod); 
	}
};


int main() {
    cin.tie(0);ios::sync_with_stdio(false);
    ll N,M,X; cin >> N >> M >> X;
    vector<ll> u(M),v(M),w(M);
    for(int i = 0; i < M; ++i) cin >> u[i] >> v[i] >> w[i];
    for(int i = 0; i < M; ++i) u[i]--,v[i]--;
    vector<int> idx(M);
    iota(ALL(idx),0);
    sort(ALL(idx),[&](int l,int r){return w[l]<w[r];});
    UnionFindTree uf(N);
    Tree<TreeOperator<modint>> tree(N);
    for(int i:idx) {
        int l=u[i],r=v[i];
        if(uf.connected(l,r)) continue;
        uf.merge(l,r);
        modint c = Mod::pow(X,w[i],MOD);
        tree.make_edge(l,r,c);
        tree.make_edge(r,l,c);
    }
    tree.make_size(0);
    tree.make_parent();
    modint ans = 0;
    for(int pa:tree.order) {
        if(!tree.depth[pa]) continue;
        modint c = tree.parent[pa].second;
        ll sz = tree.size[pa];
        ans += c * sz * (N-sz);
    }
    cout << ans << endl;
    return 0;
}
