#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define ALL(obj) (obj).begin(),(obj).end()
template<class T> using priority_queue_reverse = priority_queue<T,vector<T>,greater<T>>;

constexpr long long MOD = 1'000'000'000LL + 7;
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

int main() {
    cin.tie(0);ios::sync_with_stdio(false);
    int N; cin >> N;
    vector<int> L(N),R(N);
    for(int i=0;i<N;++i) cin >> L[i] >> R[i];
    int F = 0;
    vector<vector<int>> LtoR(2*N+1),RtoL(2*N+1);
    for(int i=0;i<N;++i) {
        if(L[i]==-1&&R[i]==-1) {
            F++;
            continue;
        }
        if(L[i]==-1) {
            RtoL[R[i]].push_back(i);
            continue;
        }
        if(R[i]==-1) {
            LtoR[L[i]].push_back(i);
            continue;
        }
        LtoR[L[i]].push_back(i);
        RtoL[R[i]].push_back(i);
    }
    int inf = 1234567;
    vector<int> dp(2*N+1,inf);
    dp[0]=0;
    for(int l=1;l<2*N;++l) {
        int s = l-1;
        if(dp[s]==inf) continue;

        for(int r=l+1;r<=2*N;++r) {
            int d = r - l;
            int g = r + d - 1;
            if(2*N < g) continue;

            //s to g
            int flg = 1;
            int sum = 0;
            for(int i=l; i < r; ++i) {
                int j=i+d;
                if(RtoL[i].size() || LtoR[j].size()) {
                    flg = 0;
                    break;
                }
                if(LtoR[i].size()>2 || RtoL[j].size()>2) {
                    flg = 0;
                    break;
                }
                if(LtoR[i].size()==1 && RtoL[j].size()==1) {
                    if(LtoR[i].front() != RtoL[j].front()) {
                        flg = 0;
                        break;
                    }
                    else {
                        continue;                        
                    }
                }
                if(LtoR[i].empty() && RtoL[j].empty()) {
                    sum++;
                    continue;
                }
                if(LtoR[i].size() == 1) {
                    int k = LtoR[i].front();
                    if(R[k]==-1 || R[k]==j) {
                        continue;
                    }
                    else {
                        flg = 0;
                        break;
                    }
                }
                if(RtoL[j].size() == 1) {
                    int k = RtoL[j].front();
                    if(L[k]==-1 || L[k]==i) {
                        continue;
                    }
                    else {
                        flg = 0;
                        break;
                    }
                }
            }
            if(flg) chmin(dp[g],dp[s]+sum);
        }
    }
    int ans = dp[2*N];
    Yn(ans <= F); 
    return 0;
}
