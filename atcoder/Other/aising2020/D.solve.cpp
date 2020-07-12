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
    ll N; cin >> N;
    string S; cin >> S;
    reverse(ALL(S));
    vector<ll> A(N);
    for(int i = 0; i < N; ++i) {
        A[i]=S[i]-'0';
    }
    int cnt = 0;
    ll sum0 = accumulate(ALL(A),0LL)+1;
    ll sum1 = accumulate(ALL(A),0LL)-1;
    ll num0=0,num1=0;
    vector<ll> base0(N+1,1),base1(N+1,1);
    for(int i = 0; i < N; ++i) {
        num0 += A[i]*base0[i];
        num0 %= sum0;
        base0[i+1] = 2*base0[i];
        base0[i+1] %= sum0; 
        
        if(sum1>0) {
            num1 += A[i]*base1[i];
            num1 %= sum1;
            base1[i+1] = 2*base1[i];
            base1[i+1] %= sum1; 
        }
    }
    vector<ll> ans(N);
    for(int n = 0; n < N; ++n) {
        ll sum = 0;
        ll num = 0;
        if(A[n]) {
            sum = sum1;
            if(sum==0) {
                ans[n]=0;
                continue;
            }
            num = num1;
            num += sum-(base1[n])%sum;
            num %= sum;
        }
        else{
            sum=sum0;
            num = num0;
            num += base0[n];
            num %= sum;
        }
        ans[n]++;
        while(1) {
            sum = NBase::digit_sum(num,2);
            if(!sum) break;
            num %= sum;
            ans[n]++;
        }
    }
    for(int i = N-1; 0 <= i; --i) {
        cout << ans[i] << endl;
    }
    return 0;
}
