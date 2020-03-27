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
    ll A,B,M; cin >> A >> B >> M;
    auto D = Divisor(M);
    string SA(31,'0'),SB(31,'0');
    for(int i = 0; i < A; ++i) SA[i] = '?';
    for(int i = 0; i < B; ++i) SB[i] = '?';
    ll ans = 0;
    if(M >= 100000){
        for(ll m = M; m <= (1LL<<31); m += M) {
            ll cnt = 1;
            for(int i = 0; i < 31; ++i) {
                if(m&(1LL<<i)){
                    if(SA[i] == '0' && SB[i] == '0') cnt *= 0;
                    if(SA[i] == '0' && SB[i] == '?') cnt *= 1;
                    if(SA[i] == '?' && SB[i] == '0') cnt *= 1;
                    if(SA[i] == '?' && SB[i] == '?') cnt *= 2;
                }
                else{
                    if(SA[i] == '0' && SB[i] == '0') cnt *= 1;
                    if(SA[i] == '0' && SB[i] == '?') cnt *= 1;
                    if(SA[i] == '?' && SB[i] == '0') cnt *= 1;
                    if(SA[i] == '?' && SB[i] == '?') cnt *= 2;
                }
            }
            ans += cnt;
        }
    }
    else{
        vector<vector<ll>> dp(31,vector<ll>(M));
        dp[0][0%M]++;
        dp[0][0%M]++;
        dp[0][1%M]++;
        dp[0][1%M]++;

        for(int i = 1; i < 31; ++i) {
            for(int j = 0; j < M; ++j) {
                if(SA[i] == '0' && SB[i] == '0') {
                    dp[i][(j+(0LL<<i))%M] += dp[i-1][j];
                }
                if(SA[i] == '0' && SB[i] == '?') {
                    dp[i][(j+(0LL<<i))%M] += dp[i-1][j];
                    dp[i][(j+(1LL<<i))%M] += dp[i-1][j];
                }
                if(SA[i] == '?' && SB[i] == '0') {
                    dp[i][(j+(0LL<<i))%M] += dp[i-1][j];
                    dp[i][(j+(1LL<<i))%M] += dp[i-1][j];
                }
                if(SA[i] == '?' && SB[i] == '?') {
                    dp[i][(j+(0LL<<i))%M] += dp[i-1][j];
                    dp[i][(j+(0LL<<i))%M] += dp[i-1][j];
                    dp[i][(j+(1LL<<i))%M] += dp[i-1][j];
                    dp[i][(j+(1LL<<i))%M] += dp[i-1][j];
                }
            }
        }
        ans += dp[30][0] - (1LL<<min(A,B));
    }
    cout << ans << endl;
    return 0;
}
