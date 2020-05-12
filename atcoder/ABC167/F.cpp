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

int main() {
	int N; cin >> N;
	PQ<pair<ll,pair<ll,ll>>> pq0;
	PQ<pair<ll,pair<ll,ll>>> pq1;
	PQR<pair<ll,pair<ll,ll>>> pq2;
	PQR<pair<ll,pair<ll,ll>>> pq3;
	for(int i = 0; i < N; ++i) {
		string S; cin >> S;
		int cnt = 0,mini = 0;
		for(int i = 0; i < S.size(); ++i) {
			if(S[i]=='(') cnt++;
			else cnt--;
			chmin(mini,cnt);
		}
		if(mini==0) {
			pq0.push({mini,{mini,cnt}});
		}
		else if(cnt>0) {
			pq1.push({mini,{mini,cnt}});
		}
		else if(mini<cnt) {
			pq2.push({mini,{mini,cnt}});
		}
		else {
			pq3.push({mini,{mini,cnt}});
		}
	}
	int sum = 0;
	while(pq0.size()){
		auto p = pq0.top();
		pq0.pop();
		int mini = p.second.first;
		int cnt = p.second.second;
		corner(sum+mini<0,"No");
		sum += cnt;
		corner(sum<0,"No");
	}
	while(pq1.size()){
		auto p = pq1.top();
		pq1.pop();
		int mini = p.second.first;
		int cnt = p.second.second;
		corner(sum+mini<0,"No");
		sum += cnt;
		corner(sum<0,"No");
	}
	while(pq2.size()){
		auto p = pq2.top();
		pq2.pop();
		int mini = p.second.first;
		int cnt = p.second.second;
		corner(sum+mini<0,"No");
		sum += cnt;
		corner(sum<0,"No");
	}
	while(pq3.size()){
		auto p = pq3.top();
		pq3.pop();
		int mini = p.second.first;
		int cnt = p.second.second;
		corner(sum+mini<0,"No");
		sum += cnt;
		corner(sum<0,"No");
	}


	corner(sum!=0,"No");
	cout << "Yes" << endl;
    return 0;
}
