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

/*
 * @title NBase
 */
class NBase{
public:
	inline static vector<long long> translate(long long X,long long N) {
		assert(abs(N)>1);
		vector<long long> res;
		while(1) {
			long long b = (X%abs(N)+abs(N)) % abs(N);
			res.push_back(b);
			(X -= b) /= N;
			if(X==0) break;
		}
		return res;
	}
	//Digit Sum
	inline static constexpr long long digit_sum(long long N, long long K) {
		long long sum = 0;
		for (; N > 0; N /= K) sum += N % K;
		return sum;
	}
};

int main() {
    int N,A,B,C; cin >> N >> A >> B;
    C=A^B;
    corner(NBase::digit_sum(C,2)%2==0,"NO");
    vector<vector<int>> vv(N+1);
    vv[0]={0};
    for(int i=1;i<=N;++i) {
        int M=vv[i-1].size();
        for(int j=0;j<M;++j) vv[i].push_back(2*vv[i-1][j]);
        for(int j=M-1;0<=j;--j) vv[i].push_back(2*vv[i-1][j]+1);
    }
    vector<int> bf(N),af;
    for(int i = 0; i < N; ++i) bf[i]=((C>>i)&1);
    af = bf;
    sort(ALL(af));
    vector<int> idx(N,-1);
    for(int i=0; i<N; ++i) {
        for(int j=0;j<N;++j) {
            if(idx[j]!=-1)continue;
            if(af[i]!=bf[j]) continue;
            idx[j]=i;
            break;
        }
    }
    int pre=0,rev=0;
    vector<int> cnt;
    for(int i=N-1;0<=i;--i) {
        int last = 0;
        if(!af[i] || i==0) last = 1;
        if(rev) {
            reverse(ALL(vv[i+last]));
            for(int x:vv[i+last]) cnt.push_back(pre + x);
            reverse(ALL(vv[i+last]));
        }
        else{
            for(int x:vv[i+last]) cnt.push_back(pre + x);
        }
        if(last) break;
        pre += (1<<i);
        rev ^= 1;
    }
    
    vector<int> ans;
    for(int& x:cnt) {
        int y = 0;
        for(int i = 0; i < N; ++i) {
            int j=idx[i];
            int b=((x>>j)&1);
            y ^= (b<<i);
        }
        ans.push_back(y);
    }

    for(int& x:ans) {
        x ^= A;
    }
    cout << "YES" << endl;
    for(int i = 0; i < ans.size(); ++i) {
        cout << (i?" ":"") << ans[i];
    }
    cout << endl;
    return 0;
}
