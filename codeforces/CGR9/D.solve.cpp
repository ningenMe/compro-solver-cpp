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
void YN(bool flg) {cout << (flg ? "YES" : "NO") << endl;}
void Yn(bool flg) {cout << (flg ? "Yes" : "No") << endl;}
void yn(bool flg) {cout << (flg ? "yes" : "no") << endl;}

int mex(const vector<int>& A){
    set<int> st;
    for(int j:A) st.insert(j);
    for(int j = 0; j <= A.size()+1; ++j) {
        if(st.count(j)) continue;
        else {
            return j;
        }
    }
}
int main() {
    int t; cin >> t;
    while(t--){
        int N; cin >> N;
        vector<int> A(N);
        for(int i = 0; i < N; ++i) cin >> A[i];
        vector<int> ans;
		while(1) {
			int m = mex(A);
			while(m!=N) {
				A[m]=m;
				ans.push_back(m);
				m = mex(A);
			}
			int flg = 1;
			for(int i = 0; i+1 < N; ++i) {
				if(A[i]>A[i+1]) flg = 0;
			}
			if(flg) break;
			int x;
			for(int i = 0; i < N; ++i) {
				if(A[i]!=i) {
					x = i;
					break;
				}
			}
			for(int i = 0; i < N; ++i) {
				if(A[i]==x) {
					x = i;
					break;
				}
			}
			A[x]=m;
			ans.push_back(x);
		}
        cout << ans.size() << endl;
        for(int i = 0; i < ans.size(); ++i) cout << ans[i]+1 << " ";
        cout << endl;
    }
    return 0;
}
