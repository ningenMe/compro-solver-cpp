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

// O(N)
vector<int> ZAlgorithm(const string& str) {
	int N = str.size();
	vector<int> res(N);
	for(int i = 1, j = 0; i < N; i++) {
		if(i + res[i - j] < j + res[j]) {
			res[i] = res[i - j];
		} 
		else {
			int k = max(0, j + res[j] - i);
			while(i + k < N && str[k] == str[i + k]) ++k;
			res[j = i] = k;
		}
	}
	res[0] = N;
	return res;
}

int main() {
    cin.tie(0);ios::sync_with_stdio(false);
    string S; cin >> S;
    auto LtoR = ZAlgorithm(S);
    reverse(ALL(S));
    auto RtoL = ZAlgorithm(S);
    reverse(ALL(RtoL));
    int N = S.size();
    ll ans = 0;
    for(int l=2;l+2<N;++l) {
        int r=l+1;
        if(LtoR[r]+RtoL[l] < N-r) continue;
        if(!LtoR[r] || !RtoL[l]) continue;
        int mini = max((N-r)-RtoL[l],1);
        {
            int sc = N-(r+mini);
            int flg = 1;
            if(flg && r+mini>=N) flg = 0;
            if(flg && sc < 1) flg = 0;
            if(flg && LtoR[r]<mini) flg = 0;
            if(flg && RtoL[l]<sc) flg = 0;
            if(flg && mini>=r-sc) flg = 0;
            if(!flg) continue;
        }

        int ok=mini,ng=N,md;
        while(ng-ok>1) {
            md = (ok+ng)/2;
            int flg = 1;
            int sc = N-(r+md);
            //A=[0,md)
            //B=[md,r-sc)
            //C=[r-sc,r)
            //A=[r,r+md)
            //C=[r+md,N)
            if(flg && r+md>=N) flg = 0;
            if(flg && sc < 1) flg = 0;
            if(flg && LtoR[r]<md) flg = 0;
            if(flg && RtoL[l]<sc) flg = 0;
            if(flg && md>=r-sc) flg = 0;
            (flg?ok:ng)=md;
        }
        ans += (ll)(ok-mini+1);
    }
    cout << ans << endl;
    return 0;
}
