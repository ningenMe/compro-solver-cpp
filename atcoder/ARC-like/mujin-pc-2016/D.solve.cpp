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

inline tuple<int,int,int,int,int> calc(const string& S,int a=0,int b=0,int c=0,int d=0,int e=0) {
    for(auto& ch:S) {
        if(ch=='?') {
            c++;
            if(e && d < c) {
                e--;
                d++;
            }
        }
        if(ch=='(') {
            e++;
        }
        if(ch==')') {
            if(e) e--;
            else if(d) d--;
            else if(c>b) b++;
            else a++;
        }
    }
    return {a,b,c,d,e};
}

int main() {
    int N; cin >> N;
    string S; cin >> S;
    int B = sqrt(N)+1;
    vector<tuple<int,int,int,int,int>> acc(B+1);
    for(int i = 0; i+B <= N; i += B) {
        acc[i/B] = calc(S.substr(i,B));
    }
    
    int Q; cin >> Q;
    for(int q=0; q<Q; ++q) {
        int l,r,u=0,v=0; cin >> l >> r;
        l--;
        int a=0,b=0,c=0,d=0,e=0,flg=1;
        for(int i = l; i < r; ++i) {
            tuple<int,int,int,int,int> tp;
            if(i%B==0 && i+B <= r) tp = acc[i/B],i+=B-1;
            else tp = {S[i]==')',0,S[i]=='?',0,S[i]=='('};

            {                
                int s = get<0>(tp);
                int t = get<1>(tp);
                int u = get<2>(tp);
                int v = get<3>(tp);
                int w = get<4>(tp);
                // print(l,r,i,"base",a,b,c,d,e);
                // print(l,r,i,"diff",s,t,u,v,w);
                {
                    int m;
                    m = min(e,s);
                    s -= m;
                    e -= m;
                    m = min(d,s);
                    s -= m;
                    d -= m;
                    m = min(c,s);
                    s -= m;
                    c -= m;
                    if(s) {
                        flg=0;
                        break;
                    }
                }
                {
                    int m;
                    m = min(e,t);
                    t -= m;
                    e -= m;
                    m = min(d,t);
                    t -= m;
                    d -= m;
                    m = min(c,t);
                    t -= m;
                    c -= m;
                    m = min(u,t);
                    t -= m;
                    u -= m;
                    if(t) {
                        flg=0;
                        break;
                    }
                }
                {
                    e += v;
                    int m = min(e,u);
                    e -= m;
                    d += m;
                    c += u;
                }
                {
                    e += w;
                }
                // print(l,r,i,"aftr",a,b,c,d,e);
            }
        }
        {
            if(e) flg=0;
            else {
                int m = min(d,c);
                d -= m;
                c -= m;
                if(d) flg=0;
                if(c%2) flg=0;
            }
        }
        Yn(flg);
    }
    return 0;
}
