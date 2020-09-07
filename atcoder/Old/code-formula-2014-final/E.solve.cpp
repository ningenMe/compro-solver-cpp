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
void print(void) {cout << endl;}
template <class Head> void print(Head&& head) {cout << head;print();}
template <class Head, class... Tail> void print(Head&& head, Tail&&... tail) {cout << head << " ";print(forward<Tail>(tail)...);}
template <class T> void chmax(T& a, const T b){a=max(a,b);}
template <class T> void chmin(T& a, const T b){a=min(a,b);}
std::vector<std::string> split(const std::string &str, const char delemiter) {std::vector<std::string> res;std::stringstream ss(str);std::string buffer; while( std::getline(ss, buffer, delemiter) ) res.push_back(buffer); return res;}
void YN(bool flg) {cout << (flg ? "YES" : "NO") << endl;}
void Yn(bool flg) {cout << (flg ? "Yes" : "No") << endl;}
void yn(bool flg) {cout << (flg ? "yes" : "no") << endl;}

string S;
vector<map<int,ll>> dp;
vector<int> v(3,0);
vector<int> w;

ll rec(int l,int r) {
	if(dp[l].count(r)) return dp[l][r];
	if(r-l==1) {
		return 0;
	}
	if(r-l==2) {
		if(S[l]=='a'&&S[l+1]=='b') return 0;
		if(S[l]=='b'&&S[l+1]=='a') return 1;
		return -1;
	}
	int s=r-l;
	int w3=w[s];
	int w1=w3-2,w2=w3-1;
	int v1=v[w1],v2=v[w2];
	{
		ll a=rec(l,l+v1),b=rec(l+v1,r),sl,sr;
		sl=max(4*a,2*b),sr=min(4*(a+1),2*(b+1));
		if(a!=-1&&b!=-1&&sl+1<sr) return dp[l][r]=sl+1;
	}
	{
		ll a=rec(l,l+v2),b=rec(l+v2,r),sl,sr;
		//k:evn
		sl=max(2*a,4*b),sr=min(2*(a+1),4*(b+1));
		if(a!=-1&&b!=-1&&sl<sr) return dp[l][r]=sl;
	}
	return -1;
}

int main() {
	cin >> S;
	corner(S=="b","1 0");
	corner(S=="a","2 0");
	int N=S.size();
	dp.resize(N);
	w.resize(N+1,-1);
	v[1]=v[2]=1;
	for(int i=3;;++i) {
		v.push_back(v[i-1]+v[i-2]);
		w[v.back()]=i;
		if(v.back()>=N) break;
	}
	cout << v.size()-1 << " " << rec(0,N) << endl;
    return 0;
}
