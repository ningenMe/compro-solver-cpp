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
	string A,B,C,D; cin >> A >> B;
	for(int i = 0; i < A.size(); ++i) {
		if(A[i]!=B[i]) {
			C.push_back(A[i]);
			D.push_back(B[i]);
		}
	}
	int flg = 0;
	for(int i = 0; i < A.size(); ++i) {
		for(int j = i+1; j < A.size(); ++j)
		if(A[i]==B[i] && A[j]==B[j] && A[i]==A[j]) {
			flg = 1;
		}
	}
	int M = C.size();
	corner(M>6,"NO");
	for(int i = 0; i < M; ++i) {
		for(int j = i+1; j < M; ++j) {
			for(int k = 0; k < M; ++k) {
				for(int l = k+1; l < M; ++l) {
					for(int m = 0; m < M; ++m) {
						for(int n = m+1; n < M; ++n) {
							string E = C;
							swap(E[i],E[j]);
							swap(E[k],E[l]);
							swap(E[m],E[n]);
							corner(E==D,"YES");
						}
					}
				}
			}
		}
	}
	if(flg){
		for(int k = 0; k < M; ++k) {
			for(int l = k+1; l < M; ++l) {
				for(int m = 0; m < M; ++m) {
					for(int n = m+1; n < M; ++n) {
						string E = C;
						swap(E[k],E[l]);
						swap(E[m],E[n]);
						corner(E==D,"YES");
					}
				}
			}
		}
		for(int m = 0; m < M; ++m) {
			for(int n = m+1; n < M; ++n) {
				string E = C;
				swap(E[m],E[n]);
				corner(E==D,"YES");
			}
		}
		corner(A==B,"YES");
	}
	cout << "NO" << endl;
    return 0;
}
