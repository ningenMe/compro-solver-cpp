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

int main() {
    int sz=-1;

    {
        ll base=1;
        for(int i=0; i<10;++i){
            cout << "? " << base << endl;
            char c; cin >> c;
            if(c=='N') {
                sz=i;
                break;
            } 
            base *= 10;
        }
    }

    if(sz==-1) {
        ll base=9,base10=1;
        for(int i=0; i<10;++i){
            cout << "? " << base << endl;
            char c; cin >> c;
            if(c=='Y') {
                cout << "! " << base10 << endl;
                return 0;
            }
            base *= 10;
            base += 9;
            base10 *= 10;
        }        
    }

    if(sz == 1) {
        ll base=10;
        for(int i=1; i<10;++i){
            cout << "? " << base*i << endl;
            char c; cin >> c;
            if(c=='Y') {
                cout << "! " << i << endl;
                return 0;
            }
        }        
    }

    ll pre=0;
    {
        for(int i=sz; 2<=i;--i){
            ll base = 1;
            for(int j=0;j+2<i;++j) base *= 10;
            ll ok=0,ng=10,md;
            while(ng-ok>1) {
                md = (ok+ng)/2;
                ll cnt = pre/10 + base*md;
                cout << "? " << cnt << endl;
                char c; cin >> c;
                (c=='Y'?ok:ng)=md;
            }
            pre += base*10*ok;
        }        
    }

    {
        ll base=10;
        for(int i=0; i<10;++i){
            ll cnt = pre*10 + base*i;
            cout << "? " << cnt << endl;
            char c; cin >> c;
            if(c=='Y') {
                cout << "! " << pre+i << endl;
                return 0;
            }
        }        
    }

    return 0;
}
