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

//Digit Sum
inline long long DigitSum(long long N, long long K) {
    long long sum = 0;
    for (; N > 0; N /= K) sum += N % K;
    return sum;
}

int main() {
    SPEED
    string S; cin >> S;
    int K; cin >> K;
    ll ans = HIGHINF;
    for(int i = 1; i < (1<<10); ++i) {
        if(DigitSum(i,2)>K) continue;
        int maxi = -1, mini = 10;
        for(int j = 0; j < 10; ++j) if(i & (1<<j)) maxi = j;
        for(int j = 9; 0 <= j; --j) if(i & (1<<j)) mini = j;
        for(int j = 0; j < S.size(); ++j) {
            string T;
            int flg = 0;
            for(int k = 0; k < j; ++k) {
                if( !(i & (1<<(S[k]-'0'))) ) flg = 1;
                T.push_back(S[k]);
            }
            if(flg) break;

            for(int k = 0; k <10; ++k) {
                if( !(k==0 && j==0) && !(i & (1<<k)) ) continue;
                string U = T;
                U.push_back(char(k+'0'));
                int c = S[j]-'0';
                if(c== k) while(U.size() < S.size()) U.push_back(char(k+'0'));
                if(c > k) while(U.size() < S.size()) U.push_back(char(maxi+'0'));
                if(c < k) while(U.size() < S.size()) U.push_back(char(mini+'0'));
                ll a = stoll(S);
                ll b = stoll(U);
                chmin(ans,abs(a-b));
            }
        }
    }
    cout << ans << endl;
    return 0;
}
