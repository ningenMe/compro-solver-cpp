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

template<class Operator> class ConvexHullTrick {
private:
    using TypeValue = typename Operator::TypeValue;
    deque<pair<TypeValue,TypeValue>> lines;

	//cが必要かどうか判定する
    inline int isRequired(const pair<TypeValue,TypeValue>& l, const pair<TypeValue,TypeValue>& c, const pair<TypeValue,TypeValue>& r) {
        return (c.first - l.first) * (r.second - c.second) >= (c.second - l.second) * (r.first - c.first);
    }
    
	//k番目のax+bの値
    inline TypeValue value(int k, TypeValue x) {
        return lines[k].first * x + lines[k].second;
    }

public:
	ConvexHullTrick() {
		// do nothing
	} 

	//傾きの大きさが単調な順にax+bを追加
	void insert(TypeValue a, TypeValue b) {
		//insertの必要がないとき
        if(lines.size() && lines.back().first == a && lines.back().second <= b) return;
		// 直前の直線の傾きが同じ　かつ　それが必要ないとき
		if(lines.size() && lines.back().first == a && lines.back().second > b ) lines.pop_back();
		//不必要な直線を取り除く
		while (lines.size() > 1 && isRequired(lines[lines.size()-2], lines[lines.size()-1], {a,b})) lines.pop_back();
		lines.push_back({a,b});
    }
    
    TypeValue get(TypeValue x) {
        int ng = -1, ok = (int)lines.size()-1, md;
        while (ok - ng > 1) {
            md = (ok + ng) >> 1;
            ( Operator::func_compare(value(md, x),value(md + 1, x)) ?ok:ng)=md;
        }
        return value(ok, x);
    }
    
    // クエリの単調性も成り立つ場合 (x が単調増加)
    TypeValue getMonotone(TypeValue x) {
        while (lines.size() >= 2 && value(0, x) >= value(1, x)) lines.pop_front();
        return lines[0].first * x + lines[0].second;
    }

};

//最小値クエリ
template<class T> struct ValueMin {
	using TypeValue = T;
	inline static constexpr bool func_compare(TypeValue l,TypeValue r){return l<r;}
};
//傾きがa1>=a2>=a3...となるようにinsertする

//最大値クエリ
template<class T> struct ValueMax {
	using TypeValue = T;
	inline static constexpr bool func_compare(TypeValue l,TypeValue r){return l>r;}
};
//傾きがa1<=a2<=a3...となるようにinsertする

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
	ConvexHullTrick<ValueMin<ll>> cht;
	cht.insert(0,dp[0]);
	for(ll i=1;i<=N+1;++i){
		dp[i]=cht.getMonotone(i)+B*(i*i-i)/2-A*(i-1)+D[i];
		cht.insert(-B*i,dp[i]+B*(i*i+i)/2+A*i);
	}
	cout << dp[N+1] << endl;
    return 0;
}
