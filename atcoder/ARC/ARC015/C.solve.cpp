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
template <class T> int chmax(T& a, const T b){if(a<b){a=b;return 1;}else return 0;}
template <class T> int chmin(T& a, const T b){if(a>b){a=b;return 1;}else return 0;}
std::vector<std::string> split(const std::string &str, const char delemiter) {std::vector<std::string> res;std::stringstream ss(str);std::string buffer; while( std::getline(ss, buffer, delemiter) ) res.push_back(buffer); return res;}
int msb(int x) {return x?31-__builtin_clz(x):-1;}
void YN(bool flg) {cout << (flg ? "YES" : "NO") << endl;}
void Yn(bool flg) {cout << (flg ? "Yes" : "No") << endl;}
void yn(bool flg) {cout << (flg ? "yes" : "no") << endl;}

int main() {
    int N; cin >> N;
    map<string,int> mp;
    vector<string> a(N),b(N);
    vector<ll> c(N);
    for(int i = 0; i < N; ++i) {
        cin >> a[i] >> c[i] >> b[i];
        mp[a[i]];mp[b[i]];
    }
    vector<string> s;
    int M=0;
    for(auto& e:mp) {
        e.second=M++;
        s.push_back(e.first);
    }
    vector<vector<pair<int,long double>>> edge(M);
    for(int i = 0; i < N; ++i) {
        int from=mp[a[i]];
        int to=mp[b[i]];
        long double w = c[i];
        long double r = 1;
        edge[from].push_back({to,w});
        edge[to].push_back({from,r/w});
    }
    long double ans = 0.;
    int l,r;
    for(int i = 0; i < M; ++i) {
        queue<int> q;
        vector<long double> dp(M,0.);
        dp[i]=1.0;
        q.push(i);
        while(q.size()){
            int from = q.front();
            if(chmax(ans,dp[from])) l=i,r=from;                
            q.pop();
            for(auto& e:edge[from]){
                int to=e.first;
                if(dp[to]>0) continue;
                dp[to]=dp[from]*e.second;
                q.push(to);
            }
        }        
    }
    string t="1"+s[l]+"="+to_string((ll)(ans+0.1))+s[r];
    print(t);
    return 0;
}
