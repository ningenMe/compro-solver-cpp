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

vector<string> f(const int N,map<int,int>& mv,map<int,vector<string>>& mp){
	vector<string> res(N,string(N,'.'));
	int idx=0;
	for(auto e:mv){
		int x=e.first,y=e.second;
		for(int n = 0; n < y; ++n){
			for(int i = 0; i < x; ++i) {
				for(int j = 0; j < x; ++j) {
					res[idx+i][idx+j]=mp[x][i][j];
				}
			}
			idx+=x;
		}
	}
	return res;
}

int main() {
	map<int,vector<string>> mp;
	mp[3]={
		"aa.",
		"..a",
		"..a",
		};
	mp[4]={
		"abcc",
		"abdd",
		"ccab",
		"ddab",
		};
	mp[5]={
		"abbaa",
		"acc.b",
		"b..cb",
		"b..ca",
		"aabba"
		};
	mp[6]={
		"aabbaa",
		"b.a.b.",
		"b.a.b.",
		".a.b.a",
		".a.b.a",
		"bbaabb"
		};
	mp[7]={
		"acc..b.",
		"a..aab.",
		"bb..bcc",
		"..ccb.a",
		"a..aa.a",
		"a....cb",
		".aa..cb"
		};
	map<int,int> mv;
	int N; cin >> N;
	corner(N==2,-1);
	if(N==5){
		mv[5]=1;
	}
	else if(N%3==0){
		mv[3]=N/3;
	}
	else{
		int x,y,z;
		for(int i = 0; i*7 <= N; ++i) {
			for(int j = 0; j*6 + i*7 <= N; ++j) {
				int k = N - j*6 - i*7;
				if(k<0 || k%4) continue;
				k/=4;
				x=i,y=j,z=k;
			}
		}
		mv[7]=x,mv[6]=y,mv[4]=z;
	}
	auto ans=f(N,mv,mp);
	for(int i = 0; i < N; ++i) cout << ans[i] << endl;
    return 0;
}
