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
    int N,K; cin >> N >> K;
    vector<string> S(N);
    vector<ll> C(N);
    vector<ll> mp(100*100*100,LOWINF);
    for(int i = 0; i < N; ++i) {
        cin >> S[i] >> C[i];
        S[i] = "." + S[i] + ".";
        int M = S[i].size();
        vector<ll> LJ(M,0),CO(M,0),RI(M,0);
        for(int j = 0; j < M; ++j){
            if(S[i][j]=='J') LJ[j]++;
            if(S[i][j]=='O') CO[j]++;
            if(S[i][j]=='I') RI[j]++;
        }
        for(int j = 1; j < M; ++j){
            LJ[j]+=LJ[j-1];
            CO[j]+=CO[j-1];
            RI[j]+=RI[j-1];
        }
        for(int j = 0; j < M; ++j){
            for(int k = j; k < M; ++k){
                for(int l = k; l < M; ++l){
                    int J = LJ[j];
                    int O = CO[k]-CO[j];
                    int I = RI[l]-RI[k];
                    chmin(mp[J*100*100+O*100+I],C[i]);
                }
            }
        }
    }
    string X = "."+string(K,'J')+string(K,'O')+string(K,'I');
    vector<ll> dp(3*K+1,LOWINF);
    dp[0] = 0;
    for(int i = 1; i <= 3*K; ++i){
        int J = 0, O = 0, I = 0;
        for(int j = 0; j < 80 && i + j <= 3*K; ++j){
            if(X[i+j]=='J') J++;
            if(X[i+j]=='O') O++;
            if(X[i+j]=='I') I++;
            if(mp[J*100*100+O*100+I]!=LOWINF) chmin(dp[i+j],dp[i-1]+mp[J*100*100+O*100+I]);
        }
    }
    if(dp.back()==LOWINF) dp.back()=-1;
    cout << dp.back() << endl;
    return 0;
}
