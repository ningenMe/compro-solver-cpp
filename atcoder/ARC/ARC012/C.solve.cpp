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
std::vector<std::string> split(const std::string &str, const char delemiter) {std::vector<std::string> res;std::stringstream ss(str);std::string buffer; while( std::getline(ss, buffer, delemiter) ) res.push_back(buffer); return res;}
int msb(int x) {return x?31-__builtin_clz(x):-1;}
void YN(bool flg) {cout << (flg ? "YES" : "NO") << endl;}
void Yn(bool flg) {cout << (flg ? "Yes" : "No") << endl;}
void yn(bool flg) {cout << (flg ? "yes" : "no") << endl;}

int all_same(const string& S) {
    int flg = 1;
    char c = S.front();
    for(int i = 0; i < S.size(); ++i) if(c!=S[i]) flg=0;
    return flg;
}
int main() {
    int N = 19;
    vector<string> S(N);
    for(int i = 0; i < N; ++i) cin >> S[i];
    int b=0,w=0,flg=1;
    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < N; ++j) {
            if(S[i][j]=='o')b++;
            if(S[i][j]=='x')w++;
        }
    }
    if(b<w || b-w>1) flg=0;
    char last;
    if(b>w) last='o';
    else last='x';
    int ok=0;
    for(int y = 0; y < N; ++y) {
        for(int x = 0; x < N; ++x) {
            if(S[y][x]!=last) continue;
            S[y][x]='.';
            vector<string> VT;
            for(int i = 0; i < N; ++i) {
                for(int j = 0; j < N; ++j) {
                    if(S[i][j]=='.') continue;
                    {
                        string T;
                        for(int l = 0; l < 5 && i+l<N; ++l) T.push_back(S[i+l][j]);
                        if(all_same(T) && T.size()==5) VT.push_back(T);
                    }
                    {
                        string T;
                        for(int l = 0; l < 5 && j+l<N; ++l) T.push_back(S[i][j+l]);
                        if(all_same(T) && T.size()==5) VT.push_back(T);
                    }
                    {
                        string T;
                        for(int l = 0; l < 5 && i+l<N && j+l<N; ++l) T.push_back(S[i+l][j+l]);
                        if(all_same(T) && T.size()==5) VT.push_back(T);
                    }
                    {
                        string T;
                        for(int l = 0; l < 5 && i+l<N && 0<=j-l; ++l) T.push_back(S[i+l][j-l]);
                        if(all_same(T) && T.size()==5) VT.push_back(T);
                    }
                }
            }
            if(VT.empty()) ok=1;
            S[y][x]=last;
        }
    }
    if(!ok) flg = 0;
    if(!b && !w) flg = 1;
    YN(flg);
    return 0;
}
