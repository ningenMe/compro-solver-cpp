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

/*
 * @title ConvexHullTrickMonotone
 */
template<class Operator> class ConvexHullTrickMonotone {
private:
	using TypeValue = typename Operator::TypeValue;

	//front->backに向かって傾きがa1<a2<...<aN
	deque<pair<TypeValue,TypeValue>> lines;

	//3直線に関してline2が必要か確認 (このとき a1 < a2 < a3が必要=dequeの順そのまま)
	inline int is_required(const pair<TypeValue,TypeValue>& line1, const pair<TypeValue,TypeValue>& line2, const pair<TypeValue,TypeValue>& line3) {
		return Operator::func_compare((line2.second-line3.second)*(line2.first-line1.first),(line1.second-line2.second)*(line3.first-line2.first));
	}

	//y=ax+bの値
	inline TypeValue y(const pair<TypeValue,TypeValue> line, TypeValue x) {
		return line.first * x + line.second;
	}

	inline void insert_back(const pair<TypeValue,TypeValue> line){
		//傾きが同じとき
		if(lines.size() && lines.back().first == line.first){
			if(Operator::func_compare(lines.back().second,line.second)) return;
			else lines.pop_back();
		}
		//不必要な直線を取り除く
		while (lines.size() > 1 && !is_required(lines[(int)lines.size()-2], lines[(int)lines.size()-1],line)) lines.pop_back();
		//backにinsert
		lines.push_back(line);
	}
	inline void insert_front(const pair<TypeValue,TypeValue> line){
		//傾きが同じとき
		if(lines.size() && lines.front().first == line.first){
			if(Operator::func_compare(lines.front().second,line.second)) return;
			else lines.pop_front();
		}
		//不必要な直線を取り除く
		while (lines.size() > 1 && !is_required(line, lines[0], lines[1])) lines.pop_front();
		//frontにinsert
		lines.push_front(line);
	}
public:
	ConvexHullTrickMonotone() {
		// do nothing
	} 
	void insert(const TypeValue a, const TypeValue b) {
		insert({a,b});
	}
	//傾きの大きさが常に最大or最小になるようにinsertする
	void insert(const pair<TypeValue,TypeValue> line) {
		if(lines.empty() || line.first <= lines.front().first) insert_front(line);
		else if(lines.back().first <= line.first) insert_back(line);
		else assert(false);
	}
	//O(log(N))
	TypeValue get(TypeValue x) {
		if(lines.empty()) return Operator::unit_value;
		int ng = -1, ok = (int)lines.size()-1, md;
		while (ok - ng > 1) {
			md = (ok + ng) >> 1;
			( Operator::func_compare(y(lines[md],x),y(lines[md+1],x)) ?ok:ng)=md;
		}
		return y(lines[ok],x);
	}
	//O(log(N))
	pair<TypeValue,TypeValue> get_line(TypeValue x) {
		if(lines.empty()) return {0,Operator::unit_value};
		int ng = -1, ok = (int)lines.size()-1, md;
		while (ok - ng > 1) {
			md = (ok + ng) >> 1;
			( Operator::func_compare(y(lines[md],x),y(lines.get[md+1],x)) ?ok:ng)=md;
		}
		return lines[ok];
	}
};

//最小値クエリ
template<class T> struct ValueMin {
	using TypeValue = T;
	inline static constexpr TypeValue unit_value = 3e18;
	inline static constexpr bool func_compare(TypeValue l,TypeValue r){return l<r;}
};
//傾きの大きさが常に最大or最小になるようにinsertする

//最大値クエリ
template<class T> struct ValueMax {
	using TypeValue = T;
	inline static constexpr TypeValue unit_value = -3e18;
	inline static constexpr bool func_compare(TypeValue l,TypeValue r){return l>r;}
};
//傾きの大きさが常に最大or最小になるようにinsertする

int main() {
	ll N,A,B,W; cin >> N >> A >> B >> W;
	vector<ll> D(N+2,0);
	for(int i = 1; i <= N; ++i) cin >> D[i];
	// dp[i]=min{j:[0,i)}-> dp[j]+B*k*(k+1)/2-k*A+D[i] (k=i-j-1)
	//                   -> dp[j]+B*(i-j-1)*(i-j)/2-(i-j-1)*A+D[i]
	//                   -> dp[j]+B/2*(i*i-2*i*j+j*j-i+j)-A*(i-j-1)+D[i]
	//                   -> (-B*j)*i  +  dp[j]+B/2*(j*j+j)+A*j  +  B/2*(i*i-i)-A*(i-1)+D[i] 
	vector<ll> dp(N+2,LOWINF);
	dp[0]=W;
	ConvexHullTrickMonotone<ValueMin<ll>> cht;
	cht.insert(0,dp[0]);
	for(ll i=1;i<=N+1;++i){
		dp[i]=cht.get(i)+B*(i*i-i)/2-A*(i-1)+D[i];
		cht.insert(-B*i,dp[i]+B*(i*i+i)/2+A*i);
	}
	cout << dp[N+1] << endl;
    return 0;
}
