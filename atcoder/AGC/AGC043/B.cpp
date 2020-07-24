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

template<class T> class Combination{
	vector<vector<T>> num;
public:    
    //O(N^2)
    Combination(int N):num(N+1,vector<T>(N+1,(T)0)){
		num[0][0] = 1;
		for (int n = 1; n <= N; n++) {
			for (int k = 0; k <= n; k++) {
				num[n][k] = (num[n - 1][k]+(k?num[n - 1][k - 1]:0));
			}
		}
    } 
	inline T binom(int n, int k) {
		return ((n < 0 || k < 0 || n < k) ? 0 : num[n][k]);
	}
    //nCk mod p (p is prime & p <= N)
    inline T lucas(int n, int k, long long p) {
        long long res=1;
        for(;n||k;n/=p,k/=p) (res *= num[n%p][k%p]) %= p;
        return res;
    }
};
//https://atcoder.jp/contests/dwango2015-prelims/tasks/dwango2015_prelims_3

int main() {
    SPEED
    int N; cin >> N;
    string S; cin >> S;
    vector<int> A(N),tmp;
    for(int i = 0; i < N; ++i) A[i] = S[i]-'0';
    vector<vector<int>> c(4,vector<int>(4));
    for(int i = 0; i < 4; ++i) for(int j = 0; j < 4; ++j) c[i][j] = abs(i-j);
    {
        vector<int> tmp;
        for(int i = 0; i+1 < A.size(); ++i){
            tmp.push_back(c[A[i]][A[i+1]]);
        }
        A = tmp;
    }
    Combination<int> CM(3);
    corner(A.size()==1,A.front());
    {
        N = A.size();
        int ans=0;
        for(int i = 0; i < N; ++i) {
            ans ^= (A[i]%2)*CM.lucas(N-1,i,2);
        }
        corner(ans,ans);
    }
    {
        corner(find(A.begin(),A.end(),1)!=A.end(),0);
    }
    {
        N = A.size();
        int ans=0;
        for(int i = 0; i < N; ++i) {
            ans ^= A[i]*CM.lucas(N-1,i,2);
        }
        cout << ans << endl;
    }

    return 0;
}
