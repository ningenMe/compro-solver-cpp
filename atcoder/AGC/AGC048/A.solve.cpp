#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define ALL(obj) (obj).begin(),(obj).end()
template<class T> using priority_queue_reverse = priority_queue<T,vector<T>,greater<T>>;

constexpr long long MOD = 1'000'000'000LL + 7; //'
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

string ATCODER = "atcoder`";

int f(const string& S,char c) {
    for(int i=0;i<S.size();++i) {
        if(c==S[i]) return i;
    }
    return -1;
}

void solve() {
    string S; cin >> S;
    string T = S;
    sort(ALL(T),greater<>());
    if(ATCODER >= T) {
        cout << -1 << endl;
        return;
    }
    int N = S.size();
    map<char,int> mp;
    for(int i=0;i<26;++i) mp[char('a'+i)]=-1;
    for(int i=N-1; 0 <= i; --i) {
        mp[S[i]]=i;
    }
    int ans = 12345678;
    for(int i=1;i<26;++i) {
        char c = char('a'+i);
        int j = mp[c];
        if(j!=-1) chmin(ans,j);
    }
    string U = S;
    int cnt = 0;
    for(int i=0;i+1<ATCODER.size(); ++i) {
        int flg = 0;
        for(int j=0; j <= i; ++j) {
            int idx = f(U,ATCODER[j]);
            if(idx == -1) {
                flg = 1;
                break;
            }
            cnt += idx-j;
            U = ATCODER.substr(0,j+1) + U.substr(j,idx-j) + U.substr(idx+1,U.size());
            for(int k=j+1;k<U.size();++k) {
                if(ATCODER[j+1]<S[k]) {
                    chmin(ans,cnt+k-(j+1));
                    break;
                }
            }
        }
        if(flg) break;
    }
    cout << ans << endl;
}

int main() {
    cin.tie(0);ios::sync_with_stdio(false);
    int T; cin >> T;
    while(T--){
        solve();
    }
    return 0;
}
