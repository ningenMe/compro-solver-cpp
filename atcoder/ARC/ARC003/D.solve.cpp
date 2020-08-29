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

class XorShift{
	unsigned int x,y,z,w;
public:
	XorShift():x(123456789),y(362436069),z(521288629),w(88675123){}
	unsigned int rand() {
		unsigned int t = (x ^ (x << 11)); x = y; y = z; z = w;
		return (w = (w ^ (w >> 19)) ^ (t ^ (t >> 8)));
	}
};

inline bool is_ok(const vector<int>& perm,const vector<int>& is_invalid) {
	int is_ok=1,N=perm.size();
	for(int i = 0; i<N; ++i) {
		int x=perm[i],y = perm[(i+1)%N];
		if(is_invalid[x*N+y]) is_ok=0;
	}
	return is_ok;
}

XorShift xor_shift;

int simulation(const int N,const int K,const vector<int>& is_invalid) {
	vector<int> perm(N);
	iota(ALL(perm),0);
	for(int i = 0; i < K; ++i) {
		int x=xor_shift.rand()%N;
		int y=xor_shift.rand()%N;
		while(x==y) y=xor_shift.rand()%N;
		swap(perm[x],perm[y]);
	}
	return is_ok(perm,is_invalid);
}

int main() {
	int N,M,K; cin >> N >> M >> K;
	auto is_invalid = multivector(N*N,0);
	for(int i = 0; i < M; ++i) {
		int a,b; cin >> a >> b;
		is_invalid[a*N+b]=is_invalid[b*N+a]=1;
	}
	double sum=0,cnt=0;
    chrono::system_clock::time_point start, end;
	double diff,max_diff = 0.3*1000;//ms
    start = chrono::system_clock::now();
	while(1) {

		//ここに処理を書く
		//-------------------------------------

		sum+=1,cnt+=simulation(N,K,is_invalid);

		//-------------------------------------

		end = chrono::system_clock::now();
		diff = (chrono::duration_cast<chrono::microseconds>(end - start).count() / 1000.0);
		if(diff > max_diff) break;
	}
	printf("%.10f\n",cnt/sum);
    return 0;
}
