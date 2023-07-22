#include <bits/stdc++.h>
using namespace std;
using int128 = __int128_t;
using int64 = long long;

#define ALL(obj) (obj).begin(),(obj).end()

/*
 * @title FastIO
 * @docs md/util/FastIO.md
 */
class FastIO{
private:
    inline static constexpr int ch_0='0';
    inline static constexpr int ch_9='9';
    inline static constexpr int ch_n='-';
    inline static constexpr int ch_s=' ';
    inline static constexpr int ch_l='\n';
    inline static void endline_skip(char& ch) {
        while(ch==ch_l) ch=getchar();
    }
    template<typename T> inline static void read_integer(T &x) {
        int neg=0; char ch; x=0;
        ch=getchar();
        endline_skip(ch);
        if(ch==ch_n) neg=1,ch=getchar();
        for(;(ch_0 <= ch && ch <= ch_9); ch = getchar()) x = x*10 + (ch-ch_0);
        if(neg) x*=-1;
    }
    template<typename T> inline static void read_unsigned_integer(T &x) {
        char ch; x=0;
        ch=getchar();
        endline_skip(ch);
        for(;(ch_0 <= ch && ch <= ch_9); ch = getchar()) x = x*10 + (ch-ch_0);
    }
    inline static void read_string(string &x) {
        char ch; x="";
        ch=getchar();
        endline_skip(ch);
        for(;(ch != ch_s && ch!=ch_l); ch = getchar()) x.push_back(ch);
    }
    inline static char ar[40];
    inline static char *ch_ar;
    template<typename T> inline static void write_integer(T x) {
        ch_ar=ar;
        if(x< 0) putchar(ch_n), x=-x;
        if(x==0) putchar(ch_0);
        for(;x;x/=10) *ch_ar++=(ch_0+x%10);
        while(ch_ar--!=ar) putchar(*ch_ar);
    }
public:
    inline static void read(int &x) {read_integer<int>(x);}
    inline static void read(long long &x) {read_integer<long long>(x);}
    inline static void read(unsigned int &x) {read_unsigned_integer<unsigned int>(x);}
    inline static void read(unsigned long long &x) {read_unsigned_integer<unsigned long long>(x);}
    inline static void read(string &x) {read_string(x);}
    inline static void read(__int128_t &x) {read_integer<__int128_t>(x);}
    inline static void write(__int128_t x) {write_integer<__int128_t>(x);}
    inline static void write(char x) {putchar(x);}
};
#define read(arg) FastIO::read(arg)
#define write(arg) FastIO::write(arg)

template<class T> using priority_queue_reverse = priority_queue<T,vector<T>,greater<T>>;

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
 * @title DinicMaxFlow - Dinicフロー
 * @docs md/graph/Dinic.md
 */
template <class TypeFlow> class DinicMaxFlow {
	struct Edge {
		size_t to, rev;
		TypeFlow cap;
	};
	vector<vector<Edge>> edge;
	vector<int> level, iter;
    TypeFlow inf_flow;

	inline void bfs(const size_t start) {
		for (int i = 0; i < level.size(); ++i) level[i] = -1;
		queue<size_t> q;
		level[start] = 0;
		q.push(start);
		while (q.size()) {
			auto from = q.front();
			q.pop();
			for (auto& e : edge[from]) {
				if (e.cap > 0 && level[e.to] < 0) {
					level[e.to] = level[from] + 1;
					q.push(e.to);
				}
			}
		}
	}

	inline TypeFlow dfs(size_t from, size_t goal, TypeFlow flow) {
		if (from == goal) return flow;
		for (int& i = iter[from]; i < edge[from].size(); ++i) {
            //TODO 参照が効いてなくて冗長
			auto& e = edge[from][i];
			if (e.cap <= 0 || level[from] >= level[e.to]) continue;
			TypeFlow dflow = dfs(e.to, goal, min(flow, e.cap));
			if (dflow <= 0) continue;
			e.cap -= dflow;
			edge[e.to][e.rev].cap += dflow;
			return dflow;
		}
		return 0;
	}

public:
	DinicMaxFlow(const size_t N) : edge(N), level(N), iter(N), inf_flow(0) {
		// do nothing
	}

	inline void make_edge(const size_t from,const size_t to, TypeFlow cap) {
		edge[from].push_back({ to, edge[to].size(), cap });
		edge[to].push_back({ from, edge[from].size() - 1, 0});
        inf_flow += cap;
	}

	inline TypeFlow flow(const size_t start,const size_t goal) {
		TypeFlow max_flow = 0;
		while (1) {
			bfs(start);
			if (level[goal] < 0) return max_flow;
			for (int i = 0; i < iter.size(); ++i) iter[i] = 0;
			TypeFlow flow;
			while ((flow = dfs(start, goal, inf_flow))>0) max_flow += flow;
		}
	}
};

//verify https://atcoder.jp/contests/arc085/tasks/arc085_c

/**
 * @url 
 * @est
 */ 
int main() {
    cin.tie(0);ios::sync_with_stdio(false);
    int H,W; read(H),read(W);
    vector<vector<int64>> grid(H,vector<int64>(W));
    for(int i=0;i<H;++i) for(int j=0;j<W;++j) read(grid[i][j]);    
    vector<int64> R(H),C(W);
    for(int i=0;i<H;++i) read(R[i]);
    for(int j=0;j<W;++j) read(C[j]);    

    //行/列に対して「植える」:0, 「植えない」:1 ,と割り当てる
    //加えて、問題の性質的にi行目に関してはフローを流す前に貪欲に選んでしまう
    //そうすることで、辺の数が2乗オーダーから落ちる
    DinicMaxFlow<int64> di(H+W+2);
    int S = H+W, G = H+W+1;

    int64 ans = 0;
    for(int i=0;i<H;++i) {
        //i行目を全部植えたときのコストを計算
        int64 cost = 0;
        for(int j=0;j<W;++j) cost += grid[i][j];        
        //差分が正のとき
        if(R[i]-cost >= 0) ans += R[i]-cost;
        //差分が負のとき→ iが0のとき|cost-R[i]|失う
        else di.make_edge(i,G,abs(R[i]-cost));
    }
    for(int j=0;j<W;++j) {
        //j列目を全部植えたときのコスト
        int64 cost = C[j];
        //jが0のとき|cost|得る
        ans += cost, di.make_edge(S,j+H,cost);
    }
    for(int i=0;i<H;++i) for(int j=0;j<W;++j) {
        //iが1,jが0のとき、grid[i][j]失う
        di.make_edge(j+H,i,grid[i][j]);
    }
    cout << ans - di.flow(S,G) << endl;
    return 0;
}
