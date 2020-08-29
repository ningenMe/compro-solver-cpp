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

class RollingHash {
private:
    long long base1,base2;
    long long mod1,mod2;
    vector<long long> hash1,hash2,pow1,pow2;
 
public: 
    RollingHash(const string& S) : base1(1007), base2(2009), mod1(1000000007), mod2(1000000009) {
        int N = S.size();
        hash1.resize(N+1,0);
        hash2.resize(N+1,0);
        pow1.resize(N+1,1);
        pow2.resize(N+1,1);
 
        for(int i=1; i<=N; ++i) {
            hash1[i] = ((hash1[i-1]+S[i-1]) * base1) % mod1;
            hash2[i] = ((hash2[i-1]+S[i-1]) * base2) % mod2;
            pow1[i] = (pow1[i-1] * base1) % mod1;
            pow2[i] = (pow2[i-1] * base2) % mod2;
        }
    }

	//[l,r)
    pair<long long, long long> get(int l,int r) {
        long long t1 = ((hash1[r] - hash1[l] * pow1[r-l]) % mod1 + mod1) % mod1;
        long long t2 = ((hash2[r] - hash2[l] * pow2[r-l]) % mod2 + mod2) % mod2;
        return {t1,t2};
    }
};

//verify
//https://atcoder.jp/contests/abc141/tasks/abc141_e

int main() {
    SPEED
    int N; cin >> N;
    vector<pair<int,string>> vp(N);
    for(int i = 0; i < N; ++i) {
        string s; cin >> s;
        int m = s.size();
        vp[i] = {m,s};
    }
    sort(ALL(vp));
    string U="";
    for(int i = 0; i < N; ++i) {
        U += vp[i].second;
    }

    RollingHash rh(U);
    map<pair<ll,ll>,vector<int>> mp;
    vector<ll> d(26,0);

    ll ans=0;
    vector<int> c(26,0);
    int sum=0;
    for(int i = 0; i < N; ++i) {
        string& s = vp[i].second;
        int m = s.size();
        for(int j = 0; j < 26; ++j) {
            c[j]=0;
        }
        for(int j = 0; j < m; ++j) {
            c[s[j]-'a']++;
        }
        if(m!=1){
            for(int j=0;j<26;++j) {
                if(!c[j]) continue;
                ans += d[j];
            }            
        }
        for(int j = m-1; 0 <= j; --j) {
            int l=sum+j,r=sum+m;
            c[s[j]-'a']--;
            auto p=rh.get(l,r);
            if(!mp.count(p)) continue;
            auto v=mp[p];
            for(int k=0;k<26;++k) {
                if(!c[k]) continue;
                if(v[k]) ans++;
            }
        }
        if(m==1) {
            d[s[0]-'a']++;
        }
        else{
            auto p = rh.get(sum+1,sum+m);
            if(!mp.count(p)) mp[p].resize(26,0);
            mp[p][s[0]-'a']++;
        }
        sum+=m;
    }
    cout << ans << endl;
    return 0;
}
