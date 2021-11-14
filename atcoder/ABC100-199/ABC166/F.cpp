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
	SPEED
	int N,A,B,C; cin >> N >> A >> B >> C;
	vector<string> S(N);
	for(int i = 0; i < N; ++i) {
		cin >> S[i];
	}
	auto dp = multivector(N+1,3,3,3,0);
	auto pr = multivector(N+1,3,3,3,4,0);
	dp[0][min(A,2)][min(B,2)][min(C,2)]=1;
	for(int i = 0; i < N; ++i) {
		for(int a = 0; a < 3; ++a) {
			for(int b = 0; b < 3; ++b) {
				for(int c = 0; c < 3; ++c) {
					if(!dp[i][a][b][c]) continue;
					if(S[i]=="AB"){
						if(a) {
							dp[i+1][a-1][min(b+1,2)][c]=1;
							pr[i+1][a-1][min(b+1,2)][c]={a,b,c,1};
						}
						if(b) {
							dp[i+1][min(a+1,2)][b-1][c]=1;
							pr[i+1][min(a+1,2)][b-1][c]={a,b,c,0};
						}
					}
					if(S[i]=="AC"){
						if(a) {
							dp[i+1][a-1][b][min(c+1,2)]=1;
							pr[i+1][a-1][b][min(c+1,2)]={a,b,c,2};
						}
						if(c) {
							dp[i+1][min(a+1,2)][b][c-1]=1;
							pr[i+1][min(a+1,2)][b][c-1]={a,b,c,0};
						}
					}
					if(S[i]=="BC"){
						if(b) {
							dp[i+1][a][b-1][min(c+1,2)]=1;
							pr[i+1][a][b-1][min(c+1,2)]={a,b,c,2};
						}
						if(c) {
							dp[i+1][a][min(b+1,2)][c-1]=1;
							pr[i+1][a][min(b+1,2)][c-1]={a,b,c,1};
						}
					}
				}
			}
		}
	}
	int s=-1,t=-1,u=-1;
	{
		for(int a = 0; a < 3; ++a) {
			for(int b = 0; b < 3; ++b) {
				for(int c = 0; c < 3; ++c) {
					if(dp[N][a][b][c]) {
						s=a,t=b,u=c;
					}
				}
			}
		}
	}
	corner(s==-1,"No");
	string ans = "";
	for(int i = N; 0 < i; --i) {
		auto& v = pr[i][s][t][u];
		ans.push_back(char(v[3]+'A'));
		s=v[0],t=v[1],u=v[2];
	}
	reverse(ALL(ans));
	cout << "Yes" << endl;
	for(int i = 0; i < N; ++i) {
		cout << ans[i] << endl;
	}

    return 0;
}
