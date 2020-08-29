#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define ALL(obj) (obj).begin(),(obj).end()
template<class T> using priority_queue_reverse = priority_queue<T,vector<T>,greater<T>>;

constexpr long long MOD = 1'000'000'000LL + 7;
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
vector<string> split(const string &str, const char delemiter) {vector<string> res;stringstream ss(str);string buffer; while( getline(ss, buffer, delemiter) ) res.push_back(buffer); return res;}
int msb(int x) {return x?31-__builtin_clz(x):-1;}
void YN(bool flg) {cout << (flg ? "YES" : "NO") << endl;}
void Yn(bool flg) {cout << (flg ? "Yes" : "No") << endl;}
void yn(bool flg) {cout << (flg ? "yes" : "no") << endl;}

ll calc(const vector<int>& A, int bit) {
    int N = A.size();
    auto dp = multivector(N,4,LOWINF);
    int l = (bool)(bit&(1<<1));
    int r = (bool)(bit&(1<<0));
    dp[1][bit]=0;
    if(l!=A[0]) dp[1][bit]++; 
    if(r!=A[1]) dp[1][bit]++;

    for(int i = 2; i < N; ++i) {
        // LL:00 -> 01
        chmin(dp[i][1],dp[i-1][0]+(A[i]!=1));

        // LR:01 -> 10
        chmin(dp[i][2],dp[i-1][1]+(A[i]!=0));
        // LR:01 -> 11
        chmin(dp[i][3],dp[i-1][1]+(A[i]!=1));

        // RL:10 -> 00
        chmin(dp[i][0],dp[i-1][2]+(A[i]!=0));
        // RL:10 -> 01
        chmin(dp[i][1],dp[i-1][2]+(A[i]!=1));

        // RR:11 -> 10
        chmin(dp[i][2],dp[i-1][3]+(A[i]!=0));
    }
    ll cnt = LOWINF;
    if(bit==0) {
        //LR,RR
        chmin(cnt,dp[N-1][1]);
        chmin(cnt,dp[N-1][3]);
    }
    if(bit==1) {
        //LR,RR
        chmin(cnt,dp[N-1][1]);
        chmin(cnt,dp[N-1][2]);
        chmin(cnt,dp[N-1][3]);
    }
    if(bit==2) {
        //LR,RR
        chmin(cnt,dp[N-1][0]);
        chmin(cnt,dp[N-1][1]);
        chmin(cnt,dp[N-1][2]);
    }
    if(bit==3) {
        chmin(cnt,dp[N-1][0]);
        chmin(cnt,dp[N-1][2]);
    }
    return cnt;
}

void solve(){
	int N; cin >> N;
    string S; cin >> S;
    vector<int> A(N);
    for(int i = 0; i < N; ++i) A[i]=(S[i]=='L'?0:1);
    ll ans = LOWINF;
    for(int i = 0; i < (1<<2); ++i) chmin(ans,calc(A,i));
    cout << ans << endl;
}

int main() {
    cin.tie(0);ios::sync_with_stdio(false);
	int T; cin >> T;
	while(T--) {
		solve();
	}
    return 0;
}
