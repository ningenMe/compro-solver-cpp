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
    ll N,K; cin >> N >> K;
    vector<ll> A(N+1,0);
    for(int i = N; 1 <= i; --i) {
        string S;
        cin >> S;
        for(int j = 0; j < 7; ++j) if(S[j]=='1') A[i] |= (1<<j);
    }
    vector<string> s = {"1110111", "0010010", "1011101", "1011011", "0111010", "1101011", "1101111", "1010010", "1111111", "1111011" };
    vector<ll> mp(10,0);
    for(int i = 0; i < 10; ++i) {
        for(int j = 0; j < 7; ++j) if(s[i][j]=='1') mp[i] |= (1<<j);
    }
    auto dp = multivector(N+1,K+1,10,-1);
    dp[0][0][0] = 0;
    for(int i = 1; i <= N; ++i) {
        for(int k = 0; k < 10; ++k) {
            if( (A[i] | mp[k]) != mp[k] ) continue;
            int cost = 0;
            for(int j = 0; j < 7; ++j) if((A[i]&(1<<j)) != (mp[k]&(1<<j))) cost++;
            for(int j = 0; j <= K; ++j) {
                if(j - cost < 0) continue;
                for(int l = 0; l < 10; ++l) {
                    if(dp[i-1][j-cost][l] != -1) chmax(dp[i][j][k],l);
                }
            }
        }
    }
    string ans = "";
    int rest = K;
    int d = -1;
    for(int k = 0; k < 10; ++k) if(dp[N][rest][k]!=-1) d = k;
    for(int i = N; 1 <= i; --i) {
        if(d == -1) {
            ans = "-1";
            break;
        }
        ans.push_back(char(d+'0'));
        int cost = 0;
        for(int j = 0; j < 7; ++j) if((A[i]&(1<<j)) != (mp[d]&(1<<j))) cost++;
        d = dp[i][rest][d];
        rest -= cost;
    }
    cout << ans << endl;
    

    return 0;
}