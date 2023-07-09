#include <bits/stdc++.h>
using namespace std;
using int128 = __int128_t;
using int64 = long long;

#define ALL(obj) (obj).begin(),(obj).end()
template<class T> using priority_queue_reverse = priority_queue<T,vector<T>,greater<T>>;

constexpr int64 MOD = 1'000'000'000LL + 7; //'
constexpr int64 MOD2 = 998244353;
constexpr int64 HIGHINF = 1'000'000'000'000'000'000LL;
constexpr int64 LOWINF = 1'000'000'000'000'000LL; //'
constexpr long double PI = 3.1415926535897932384626433L;

template <class T> vector<T> multivector(size_t N,T init){return vector<T>(N,init);}
template <class... T> auto multivector(size_t N,T... t){return vector<decltype(multivector(t...))>(N,multivector(t...));}
template <class T> void corner(bool flg, T hoge) {if (flg) {cout << hoge << endl; exit(0);}}
template <class T, class U>ostream &operator<<(ostream &o, const map<T, U>&obj) {o << "{"; for (auto &x : obj) o << " {" << x.first << " : " << x.second << "}" << ","; o << " }"; return o;}
template <class T>ostream &operator<<(ostream &o, const set<T>&obj) {o << "{"; for (auto itr = obj.begin(); itr != obj.end(); ++itr) o << (itr != obj.begin() ? ", " : "") << *itr; o << "}"; return o;}
template <class T>ostream &operator<<(ostream &o, const multiset<T>&obj) {o << "{"; for (auto itr = obj.begin(); itr != obj.end(); ++itr) o << (itr != obj.begin() ? ", " : "") << *itr; o << "}"; return o;}
template <class T>ostream &operator<<(ostream &o, const vector<T>&obj) {o << "{"; for (int i = 0; i < (int)obj.size(); ++i)o << (i > 0 ? ", " : "") << obj[i]; o << "}"; return o;}
template <class T>ostream &operator<<(ostream &o, const deque<T>&obj) {o << "{"; for (int i = 0; i < (int)obj.size(); ++i)o << (i > 0 ? ", " : "") << obj[i]; o << "}"; return o;}
template <class T, class U>ostream &operator<<(ostream &o, const pair<T, U>&obj) {o << "{" << obj.first << ", " << obj.second << "}"; return o;}
void print(void) {cout << endl;}
template <class Head> void print(Head&& head) {cout << head;print();}
template <class Head, class... Tail> void print(Head&& head, Tail&&... tail) {cout << head << " ";print(forward<Tail>(tail)...);}
template <class T> void chmax(T& a, const T b){a=max(a,b);}
template <class T> void chmin(T& a, const T b){a=min(a,b);}
vector<string> split(const string &str, const char delemiter) {vector<string> res;stringstream ss(str);string buffer; while( getline(ss, buffer, delemiter) ) res.push_back(buffer); return res;}
inline constexpr int msb(int x) {return x?31-__builtin_clz(x):-1;}
inline constexpr int64 ceil_div(const int64 a,const int64 b) {return (a+(b-1))/b;}// return ceil(a/b)
void YN(bool flg) {cout << (flg ? "YES" : "NO") << endl;}
void Yn(bool flg) {cout << (flg ? "Yes" : "No") << endl;}
void yn(bool flg) {cout << (flg ? "yes" : "no") << endl;}

/*
 * @title NBase - N進数
 * @docs md/util/NBase.md
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

/**
 * @url 
 * @est
 */ 
int main() {
    cin.tie(0);ios::sync_with_stdio(false);
    int H,W,T; cin >> H >> W >> T;
    vector<string> vs(H);
    for(int i=0;i<H;++i) cin >> vs[i];
    vector<int> b;
    map<int,int> mp;
    for(int i=0;i<H;++i) {
        for(int j=0;j<W;++j) {
            if(vs[i][j]=='S') {
                mp[i*W+j]=b.size();
                b.push_back(i*W+j);
            }
        }
    }
    for(int i=0;i<H;++i) {
        for(int j=0;j<W;++j) {
            if(vs[i][j]=='o') {
                mp[i*W+j]=b.size();
                b.push_back(i*W+j);
            }
        }
    }
    for(int i=0;i<H;++i) {
        for(int j=0;j<W;++j) {
            if(vs[i][j]=='G') {
                mp[i*W+j]=b.size();
                b.push_back(i*W+j);
            }
        }
    }
    int M = b.size();
    auto dist = multivector(M,M,0LL);
    int dy[4] = {-1,1,0,0};
    int dx[4] = {0,0,-1,1};

    for(int n=0;n<M;++n) {
        int s = b[n];
        int sy=s/W, sx=s%W;
        queue<pair<int,int>> q;
        auto dp = multivector(H,W,-1LL);
        q.push({sy,sx});
        dp[sy][sx]=0;
        while(q.size()) {
            auto [y,x]=q.front(); q.pop();
            for(int i=0;i<4;++i) {
                int ny = y+dy[i];
                int nx = x+dx[i];
                if(!(0<=ny && ny<H)) continue;
                if(!(0<=nx && nx<W)) continue;
                if(vs[ny][nx]=='#') continue;
                if(dp[ny][nx]!=-1) continue;
                q.push({ny,nx});
                dp[ny][nx]=dp[y][x]+1;
            }
        }
        for(int j=0;j<M;++j) {
            int g = b[j];
            int gy=g/W, gx=g%W;
            dist[n][j] = dp[gy][gx];
        }
    }
    auto dp2 = multivector(1<<M,M,LOWINF);
    dp2[(1<<0)][0]=0;
    for(int i=1;i<(1LL<<M);++i) {
        for(int j=0;j<M;++j) {
            if(!(i & (1LL<<j))) continue;
            for(int k=0;k<M;++k) {
                if(i & (1LL<<k)) continue;
                if(dist[j][k]!=-1) chmin(dp2[i ^ (1<<k)][k], dp2[i][j] + dist[j][k]);
            }
        }
    }
    int64 ans = -1;
    for(int i=0;i<(1<<M);++i) {
        if(dp2[i][M-1] <= T) chmax(ans, NBase::digit_sum(i,2)-2);
    }
    cout << ans << endl;
    return 0;
}
