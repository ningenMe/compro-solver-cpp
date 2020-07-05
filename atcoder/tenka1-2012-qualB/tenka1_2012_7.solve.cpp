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

int main() {
    int N; cin >> N;
    vector<pair<int,int>> vp(N);
    for(int i = 0; i < N; ++i){
        string S,T; cin >> S >> T;
        int s = stoi(S.substr(0,2))*60+stoi(S.substr(3,2));
        int t = stoi(T.substr(0,2))*60+stoi(T.substr(3,2));
        vp[i]={s,t};
    }
    int M = 24*60;
    auto mc = multivector(N,N,1);
    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < N; ++j) {
            int ok=1;
            for(int k = 0; k < M; ++k) {
                int flgi=0,flgj=0;
                flgi |= (vp[i].first<=k && k < vp[i].second);
                flgi |= (vp[i].first<=k+M && k+M < vp[i].second);
                flgj |= (vp[j].first<=k && k < vp[j].second);
                flgj |= (vp[j].first<=k+M && k+M < vp[j].second);
                if(flgi && flgj) ok=0;
            }
            if(ok) mc[i][j]=0;
        }
    }
    vector<int> dp(1<<N,N);
    for(int i = 1; i < (1<<N); ++i) {
        int ok = 1;
        for(int j = 0; j < N; ++j) {
            for(int k = j+1; k < N; ++k) {
                if(!(i&(1<<j))) continue;
                if(!(i&(1<<k))) continue;
                if(mc[j][k]) ok = 0;
            }
        }        
        if(ok) {
            dp[i]=1;
        }
        for(int j=i;0<j;j=((j-1)&i)) {
            int k = i-j;
            chmin(dp[i],dp[j]+dp[k]);
        }
    }
    cout << dp.back() << endl;
    return 0;
}
