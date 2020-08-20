#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define ALL(obj) (obj).begin(),(obj).end()
template<class T> using priority_queue_reverse = priority_queue<T,vector<T>,greater<T>>;

constexpr long long MOD = 1'000'000'000LL + 7;
constexpr long long MOD2 = 998244353;
constexpr long long HIGHINF = (long long)2e18;
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
    ll N,K; cin >> N >> K;
    vector<int> P(N);
    for(int i = 0; i < N; ++i) cin >> P[i],P[i]--;
    vector<ll> C(N);
    for(int i = 0; i < N; ++i) cin >> C[i];
    vector<pair<ll,ll>> loop(N);
    for(int i = 0; i < N; ++i) {
        vector<pair<ll,ll>> tmp(N,{-1,0});
        int from=i;
        int to;
        tmp[from]={0,0};
        while(1) {
            to = P[from];
            auto tt=tmp[to];
            tmp[to] = {C[to]+tmp[from].first,tmp[from].second+1};
            if(tt.first!=-1) {
                break;
            }
            from=to;
        }
        loop[i]=tmp[i];
    }


    ll ans = -HIGHINF;
    for(int i = 0; i < N; ++i) {
        int from = i;
        ll cost = 0;
        ll cnt = K;
        cnt--;    

        from = P[from];
        cost += C[from];
        chmax(ans,cost);
        
        ll cnt1 = cnt;
        ll cost1 = cost;
        ll from1 = from;
        {
            ll M = loop[from1].second;
            if(loop[from1].first > 0) {
                cost1 += (cnt1 / M) * loop[from1].first;
            }
            cnt1 %= M;
            chmax(ans,cost1);
            
            while(cnt1--) {
                from1 = P[from1];
                cost1 += C[from1];
                chmax(ans,cost1);
            }
        }

        ll cnt2 = cnt;
        ll cost2 = cost;
        ll from2 = from;
        {
            ll M = loop[from2].second;
            chmin(cnt2,M);
            while(cnt2--) {
                from2 = P[from2];
                cost2 += C[from2];
                chmax(ans,cost2);
            }
        }
    }
    cout << ans << endl;
    return 0;
}
