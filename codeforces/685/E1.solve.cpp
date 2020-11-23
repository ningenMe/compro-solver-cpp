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

/**
 * @url http://codeforces.com/contest/1451/problem/E1
 * @est 500
 */ 
int main() {
    cin.tie(0);ios::sync_with_stdio(false);
    int N; cin >> N;
    vector<int> A(N,-1);
    vector<int> s(3),t(3),u(3);
    {
        cout << "AND 1 2" << endl;
        cin >> s[0];
    }
    {
        cout << "AND 2 3" << endl;
        cin >> s[1];
    }
    {
        cout << "AND 3 1" << endl;
        cin >> s[2];
    }
    {
        cout << "XOR 1 2" << endl;
        cin >> t[0];
    }
    {
        cout << "XOR 2 3" << endl;
        cin >> t[1];
    }
    {
        t[2] = t[0]^t[1];
    }
    for(int i=0;i<3;++i) {
        u[i] = 2*s[i] + t[i];
    }
    int sum = accumulate(ALL(u),0)/2;
    A[0] = sum - u[1];
    A[1] = sum - u[2];
    A[2] = sum - u[0];

    int query = 5;
    for(int i=3; i < N; ++i) {
        int l = i, r = i+1;
        cout << "XOR " << l << " " << r << endl;
        int lr;
        cin >> lr;
        A[i] = lr^A[i-1];
        query++;
    }
    cout << "!";
    for(int i=0;i<N;++i) {
        cout << " " << A[i];
    }
    cout << endl;
    return 0;
}
