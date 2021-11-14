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

vector<pair<char,long long>> Rarts(string S){
	char ch = S[0];
	int cnt = 1;
	vector<pair<char,long long>> res;
 	for(int i = 1; i < S.size(); ++i){
		 if(S[i]==ch) {
			 cnt++;
		 }
		 else{
			 res.push_back({ch,cnt});
			 ch = S[i];
			 cnt = 1;
		 }
	}
	res.push_back({ch,cnt});
	return res;
}

//verify https://atcoder.jp/contests/agc039/tasks/agc039_a

void solve(){
    int N,K; cin >> N >> K;
    string S; cin >> S;
    auto R = Rarts(S);
    priority_queue_reverse<pair<int,int>> pq;
    int idx=R.front().second;
    for(int i=1;i+1<R.size();++i) {
        if(R[i].first!='W') {
            pq.push({R[i].second,idx});
        }
        idx += R[i].second;
    }
    while(pq.size()) {
        auto p = pq.top(); pq.pop();
        if(p.first > K) continue;
        K -= p.first; 
        for(int i=0; i < p.first; ++i) {
            S[i+p.second]='W';
        }
    }
    for(int i=1;i<N && K;++i) {
        if(S[i-1]=='W' && S[i]=='L') {
            K--;
            S[i]='W';
        }
    }
    for(int i=N-2; 0<=i && K;--i) {
        if(S[i]=='L' && S[i+1]=='W') {
            K--;
            S[i]='W';
        }
    }
    for(int i=0;i<N && K;++i) {
        if(S[i]=='L') {
            K--;
            S[i]='W';
        }
    }
    char pre='L';
    int ans = 0;
    for(int i=0;i<N;++i) {
        if(S[i]=='W') {
            if(pre=='W') ans+=2;
            else ans += 1;
        }
        pre=S[i];
    }
    cout << ans << endl;
}
int main() {
    cin.tie(0);ios::sync_with_stdio(false);
    int t; cin >> t;
    while(t--){
        solve();
    }
    return 0;
}
