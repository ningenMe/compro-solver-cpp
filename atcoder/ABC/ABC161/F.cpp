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

vector<long long> NBase(long long X,long long N) {
    assert(abs(N)>1);
    vector<long long> res;
    while(1) {
        long long b = (X%abs(N)+abs(N)) % abs(N);
        res.push_back(b);
        (X -= b) /= N;
        if(X==0) break;
    }
    return res;
}

//divisor O(sqrt(N))
set<long long> Divisor(long long N) {
    set<long long> ret;
    for (long long i = 1; i*i <= N; ++i) {
        if (N%i == 0) {
            ret.insert(i);
            ret.insert(N / i);
        }
    }
    return ret;
}

//verify https://atcoder.jp/contests/abc112/tasks/abc112_d

int main() {
	ll N; cin >> N;
	ll ans = 0;
	auto D = Divisor(N);
	set<ll> st;
	for(ll i:D) {
		if(i==1) continue;
		auto B = NBase(N,i);
		int flg = 0;
		for(auto e:B){
			if(e==0) continue;
			if(e==1) {
				flg = 1;
			}
			else break;
		}
		if(flg) st.insert(i);
	}
	D = Divisor(N-1);
	for(ll i:D) {
		if(i==1) continue;
		auto B = NBase(N,i);
		int flg = 0;
		for(auto e:B){
			if(e==0) continue;
			if(e==1) {
				flg = 1;
			}
			else break;
		}
		if(flg) st.insert(i);
	}
	cout << st.size() << endl;
    return 0;
}
