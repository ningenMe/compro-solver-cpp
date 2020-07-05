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

template<class T> class Combination{
	vector<vector<T>> num;
public:    
    //O(N^2)
    Combination(int N):num(N+1,vector<T>(N+1,0.)){
		num[0][0] = 1;
		for (int n = 1; n <= N; n++) {
			for (int k = 0; k <= n; k++) {
				num[n][k] = (num[n - 1][k]+(k?num[n - 1][k - 1]:0)) / 3;
			}
		}
    } 
	inline T binom(int n, int k) {
		return ((n < 0 || k < 0 || n < k) ? 0 : num[n][k]);
	}
};

int main() {
    int N; cin >> N;
    vector<double> dp(N+1,0);
    vector<int> t(3);
    Combination<double> CP(N);
    for(int n = 2; n <= N; ++n) {
        vector<double> c(n+1,0);
        for(int i = 0; i <= n; ++i) {
            double coe=pow(3,n-i);
            for(int j = 0; i+j <= n; ++j) {
                int k = n - i - j;
                int m;
                if(i==j && j==k && k==i) {
                    m=n;
                }
                else{
                    t[0]=i,t[1]=j,t[2]=k;
                    sort(ALL(t));        
                    int l=0;
                    while(!t[l]) ++l;
                    m=t[l];
                }
                double p = CP.binom(n,i)*CP.binom(n-i,j)*coe;
                c[m] += p;
            }
        }
        dp[n]=1;
        for(int i = 0; i < n; ++i) dp[n]+=c[i]*dp[i];
        dp[n] /= (1-c[n]);
    }
    printf("%.10f",dp[N]);
    return 0;
}
