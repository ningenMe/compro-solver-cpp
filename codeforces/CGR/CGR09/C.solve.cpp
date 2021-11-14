#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;

#define REP(i,n) for(long long i = 0; i < (n); i++)
#define FOR(i, m, n) for(long long i = (m);i < (n); ++i)
#define ALL(obj) (obj).begin(),(obj).end()
#define SPEED cin.tie(0);ios::sync_with_stdio(false);

template<class T> using V = vector<T>;
template<class T, class U> using P = pair<T, U>;
template<class T> using PQ = priority_queue<T>;
template<class T> using PQR = priority_queue<T,vector<T>,greater<T>>;

constexpr long long MOD = (long long)1e9 + 7;
constexpr long long MOD2 = 998244353;
constexpr long long HIGHINF = (long long)1e18;
constexpr long long LOWINF = (long long)1e15;
constexpr long double PI = 3.1415926535897932384626433;

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

template<class T> class SegmentTree {
	size_t length;               //セグメント木の最下段の要素の数(vectorの要素の数を超える2べきの数)
	T init;                      //各ノードの初期値
	vector<T> node;              //ノード
	function<T(T,T)> funcNode;   //node同士の演算
	function<T(T,T)> funcMerge;  //nodeとvarの演算

public:
	//vectorで初期化
	SegmentTree(const vector<T> & vec, const T init, function<T(T,T)> funcNode, function<T(T,T)> funcMerge) : init(init), funcNode(funcNode), funcMerge(funcMerge) {
		for (length = 1; length < vec.size(); length *= 2);
		node.resize(2 * length, init);
		for (int i = 0; i < vec.size(); ++i) node[i + length] = vec[i];
		for (int i = length - 1; i >= 0; --i) node[i] = funcNode(node[(i<<1)+0],node[(i<<1)+1]);
	}
 
	//lengthだけで初期化
	SegmentTree(const size_t num, const T init, function<T(T,T)> funcNode, function<T(T,T)> funcMerge) : init(init), funcNode(funcNode), funcMerge(funcMerge) {
		for (length = 1; length < num; length *= 2);
		node.resize(2 * length, init);
	}
	
	//idx : 0-indexed
	void update(size_t idx, const T var) {
		if(idx < 0 || length <= idx) return;
		idx += length;
		node[idx] = funcMerge(node[idx],var);
		while(idx >>= 1) node[idx] = funcNode(node[(idx<<1)+0],node[(idx<<1)+1]);
	}

	//[l,r)
	T get(int l, int r) {
		if (l < 0 || length <= l || r < 0 || length < r) return init;
		T vl = init, vr = init;
		for(l += length, r += length; l < r; l >>=1, r >>=1) {
			if(l&1) vl = funcNode(vl,node[l++]);
			if(r&1) vr = funcNode(node[--r],vr);
		}
		return funcNode(vl,vr);
	}
 
	void print(){
		cout << "{ " << get(0,1);
		for(int i = 1; i < length; ++i) cout << ", " << get(i,i+1);
		cout << " }" << endl;

		for(int i = 1,j = 1; i < 2*length; ++i) {
			cout << node[i] << " ";
			if(i==((1<<j)-1) && ++j) cout << endl;
		}
	}

};

//GCD
//verify https://atcoder.jp/contests/abc125/tasks/abc125_c

//SUM
//verify https://atcoder.jp/contests/arc077/tasks/arc077_c

//MIN
//verify https://atcoder.jp/contests/bitflyer2018-final-open/tasks/bitflyer2018_final_c

//MAX
//verify https://atcoder.jp/contests/wupc2019/tasks/wupc2019_d

	// //一点加算 + 区間総和
	// function<ll(ll,ll)> funcNode =  [&](ll a,ll b){return a+b;};
	// function<ll(ll,ll)> funcMerge = [&](ll a,ll b){return a+b;};

	// //一点更新 + 区間GCD
	// function<ll(ll,ll)> funcNode =  GCD;
	// function<ll(ll,ll)> funcMerge = [&](ll a,ll b){return b;};

	// //一点更新 + 区間最小
	// function<ll(ll,ll)> funcNode =  [&](ll a,ll b){return min(a,b);};
	// function<ll(ll,ll)> funcMerge = [&](ll a,ll b){return b;};

void f(){
    int N; cin >> N;
    vector<ll> B(N);
    for(int i = 0; i < N; ++i) cin >> B[i];
	using p = pair<ll,int>;

	//一点更新 + 区間最小
	function<p(p,p)> funcMin =  [&](p a,p b){return min(a,b);};
	function<p(p,p)> funcMerge = [&](p a,p b){return b;};
    SegmentTree<p> sMin(N,{LOWINF,-1},funcMin,funcMerge);

    vector<int> L(N,-1),R(N,-1);
    for(int i = 1; i < N; ++i) L[i] = i-1;
    for(int i = 0; i+1<N; ++i) R[i] = i+1;
    for(int i = 0; i < N; ++i) sMin.update(i,{B[i],i});

    vector<ll> ans;
    for(;;){
        p e = sMin.get(0,N);
        ll m = e.first;
        int i = e.second;
        int l = L[i],r = R[i];
        if(l==-1 || r == -1) break;
        p er = sMin.get(r,r+1);
        ll mr = er.first;
        if(m>mr) break;
        ans.push_back(m);
        sMin.update(i,{LOWINF,i});
        if(l!=-1) R[l] = r;
        if(r!=-1) L[r] = l;
    }
    int j = sMin.get(0,N).second;
    while(R[j]!=-1){
        int i = R[j];
        int l = L[i],r = R[i];
        ans.push_back(B[i]);
        if(R[l]=r);
        if(r!=-1) L[r] = l;
    }
    int cnt = 0;
    YN(ans.size()==N-1);

}
int main() {
    SPEED
    int t; cin >> t;
    while(t--){
        f();
    }

    return 0;
}