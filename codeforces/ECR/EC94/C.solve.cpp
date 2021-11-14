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
void YN(bool flg) {cout << (flg ? "YES" : "NO") << endl;}
void Yn(bool flg) {cout << (flg ? "Yes" : "No") << endl;}
void yn(bool flg) {cout << (flg ? "yes" : "no") << endl;}

void solve(){
    string S; cin >> S;
    int N = S.size();
    string T(N,'2');
    int X; cin >> X;
    for(int i = 0; i < N; ++i) {
        if(0<=i-X) break;
        if(i+X>=N) continue;
        if(T[i+X]=='2' || T[i+X]==S[i]) {
            T[i+X] = S[i];
        }
        else{
            cout << -1 << endl;
            return;
        }
    }
    for(int i = N-1; 0 <= i; --i) {
        if(i+X<N) break;
        if(i-X<0) continue;
        if(T[i-X]=='2' || T[i-X]==S[i]) {
            T[i-X] = S[i];
        }
        else{
            cout << -1 << endl;
            return;
        }
    }
    for(int i = 0; i < N; ++i) {
        if(i+X<N) continue;
        if(0<=i-X) continue;
        if(S[i]=='1') {
            cout << -1 << endl;
            return;
        }
    }
    for(int i = X; i + X < N; ++i) {
        if(S[i]=='0') {
            if(T[i-X]=='1' || T[i+X]=='1') {
                cout << -1 << endl;
                return;
            }
            T[i-X] = '0';
            T[i+X] = '0';
        }
        else{
            if(T[i-X]=='0' && T[i+X]=='0') {
                cout << -1 << endl;
                return;
            }
            if(T[i-X]=='0') {
                T[i+X] = '1';
            }
            else{
                T[i-X] = '1';
            }
        }
    }
    for(int i = 0; i < N; ++i) if(T[i]=='2') T[i]='1';
    cout << T << endl;
}

int main() {
    int T; cin >> T;
    while(T--){
        solve();
    }
    return 0;
}
