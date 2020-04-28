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

int MillerRabin(const long long N, int challenge = 10) {
	if (N <= 1) return 0;
	if (N == 2) return 1;
	long long M = N - 1,cnt = 0;;
	for (; M % 2 == 0; M /= 2,cnt++);
	mt19937 mt(time(NULL));
	vector<long long> v;
    for(int i = 0; i < challenge; ++i) v.push_back(uniform_int_distribution<long long>(2, N - 1)(mt));
	for (long long a:v) {
        long long r = 1;
		for (long long K = M; K > 0; K >>= 1, (a *= a) %= N) if (K & 1) (r *= a) %= N;
		if (r == 1) continue;
		for (int i = 1; i < cnt && r != N - 1; i++) (r *= r) %= N;
		if (r != N - 1) return 0;
	}
	return 1;
}

int main() {
    int Y,X; cin >> Y >> X;
    int S=Y,T=X,prt=0;
    corner(Y==2||X==2,"Second");
    corner(MillerRabin(S)&&MillerRabin(T),"Second");
    if(MillerRabin(S)){
        S++;
        X++;
        prt++;
    }
    if(MillerRabin(T)){
        T++;
        Y++;
        prt++;
    }
    while(!MillerRabin(S)) S++;
    while(!MillerRabin(T)) T++;
    cout << ((S-Y+T-X+prt)%2?"First":"Second") << endl;
    return 0;
}
