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
	int N; cin >> N;
	vector<int> A(N+2,0);
	for(int i = 1; i <= N; ++i) cin >> A[i];
	set<int> st;
	st.insert(0);
	st.insert(N+1);
	vector<pair<int,int>> ord(1);
	for(int i = 1; i <= N; ++i) ord.push_back({A[i],i});
	sort(ALL(ord));
	vector<pair<int,pair<int,int>>> range(N+1);
	for(int i = 1; i <= N; ++i) {
		int x = ord[i].second;
		auto itr = st.lower_bound(x);
		int r = *itr;
		itr--;
		int l = *itr;
		range[i] = {x,{l+1,r-1}};
		st.insert(x);
	}
	const int bucket = 330;
	vector<vector<int>> B(N/bucket+1),R(N/bucket+1),L(N/bucket+1);
	for(int i = 0; i <= N; ++i) {
		B[i/bucket].push_back(A[i]);
	}
	for(int i = 0; i < B.size(); ++i) {
		auto tmpr = B[i],tmpl = B[i];
		set<int> str,stl;
		for(int j = 1; j < tmpr.size(); ++j){
			chmax(tmpr[j],tmpr[j-1]);
		}
		if(tmpl.size()>1)for(int j = tmpl.size()-2; 0 <= j; --j){
			chmax(tmpl[j],tmpl[j+1]);
		}
		for(int e:tmpr){
			str.insert(e);
		}
		for(int e:tmpl){
			stl.insert(e);
		}
		for(auto& e:str){
			R[i].push_back(e);
		}
		for(auto& e:stl){
			L[i].push_back(e);
		}
	}
	ll ans = 0;
	for(int i = 1; i <= N; ++i) {
		int c = range[i].first;
		int l = range[i].second.first;
		int r = range[i].second.second;
		int maxr = A[c];
		int cntr = 0;
		for(int j = 0; j < B.size(); ++j) {
			int bl = j*bucket, br = (j+1)*bucket - 1;
			if(bl <= c && c <= br) for(int k = c; k <= br && k <= r; ++k) {
				if(maxr < A[k]) {
					maxr = A[k];
					cntr++;
				}
			}
		}
		for(int j = 0; j < B.size(); ++j) {
			int bl = j*bucket, br = (j+1)*bucket - 1;
			int m = R[j].size();
			if(c <= bl && br <= r && R[j].size() && maxr < R[j].back()) {
				int k = upper_bound(ALL(R[j]),maxr) - R[j].begin();
				cntr += m-k;
				maxr = R[j].back();
			}
		}
		for(int j = 0; j < B.size(); ++j) {
			int bl = j*bucket, br = (j+1)*bucket - 1;
			if(c < bl && bl <= r && r <= br) for(int k = bl; k <= br && k <= r; ++k) {
				if(maxr < A[k]) {
					maxr = A[k];
					cntr++;
				}
			}
		}

		int maxl = A[c];
		int cntl = 0;
		for(int j = B.size()-1; 0 <= j; --j) {
			int bl = j*bucket, br = (j+1)*bucket - 1;
			if(bl <= c && c <= br) for(int k = c; bl <= k && l <= k; --k) {
				if(maxl < A[k]) {
					maxl = A[k];
					cntl++;
				}
			}
		}
		for(int j = B.size()-1; 0 <= j; --j) {
			int bl = j*bucket, br = (j+1)*bucket - 1;
			int m = L[j].size();
			if(l <= bl && br <= c && L[j].size() && maxl < L[j].back()) {
				int k = upper_bound(ALL(L[j]),maxl) - L[j].begin();
				cntl += m-k;
				maxl = L[j].back();
			}
		}
		for(int j = B.size()-1; 0 <= j; --j) {
			int bl = j*bucket, br = (j+1)*bucket - 1;
			if(br < c && bl <= l && l <= br) for(int k = br; bl <= k && l <= k; --k) {
				if(maxl < A[k]) {
					maxl = A[k];
					cntl++;
				}
			}
		}
		ans += cntl + cntr;
		// print(i,l,c,r,"",cntl,cntr);
		// print(R);
		// print(L);
	}
	cout << ans << endl;
    return 0;
}
