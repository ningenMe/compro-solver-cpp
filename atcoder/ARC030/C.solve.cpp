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
void YN(bool flg) {cout << (flg ? "YES" : "NO") << endl;}
void Yn(bool flg) {cout << (flg ? "Yes" : "No") << endl;}
void yn(bool flg) {cout << (flg ? "yes" : "no") << endl;}

/*
 * @title StronglyConnectedComponents
 */
class StronglyConnectedComponents{
	int num,is_2sat,half;
	vector<vector<int>> edge,redge;

	vector<int> label,visited,order;

	inline void dfs(int curr){
		visited[curr] = 1;
		for(int next:edge[curr]) if(!visited[next]) dfs(next);
		order.push_back(curr);
	}

	inline void rdfs(int curr,int id){
		visited[curr] = 1;
		label[curr] = id;
		for(int next:redge[curr]) if(!visited[next]) rdfs(next,id);
	}
	inline int rev(int i) { return i < half ? i + half : i - half; }
public:
    int compress_num;
	vector<vector<int>> compress_edge;
	StronglyConnectedComponents(const int n, bool is_2sat=0):num(n),is_2sat(is_2sat){
		if(is_2sat) num*=2;
		edge.resize(num);
		redge.resize(num);
		label.resize(num);
		visited.resize(num);
		half=num/2;
	}
	inline int operator[](int idx) {
		return label[idx];
	}
	inline void make_edge(const int from,const int to) {
		edge[from].push_back(to);
		redge[to].push_back(from);
	}
	inline void make_condition(int x, bool flg_x, int y, bool flg_y) {
		if (!flg_x) x = rev(x);
		if (!flg_y) y = rev(y);
		make_edge(x, y);
		make_edge(rev(y), rev(x));
	}
	inline int solve(void) {
		for(int i = 0; i < num; ++i) visited[i] = 0;
		for(int i = 0; i < num; ++i) if(!visited[i]) dfs(i);
		for(int i = 0; i < num; ++i) visited[i] = 0;
		reverse(order.begin(),order.end());
		int id = 0;
		for(int i:order) if(!visited[i]) rdfs(i,id++);
        compress_num = id;
		if(!is_2sat) return true;
		for (int i = 0; i < num; ++i) if (label[i] == label[rev(i)]) return false;
		return true;
	}
    inline void make_compress_edge(void){
        compress_edge.resize(compress_num);
        for(int i = 0; i < num; ++i) for(int j:edge[i]) if(label[i]!=label[j]) compress_edge[label[i]].push_back(label[j]);
        for(int i = 0; i < compress_num; ++i) {
            sort(compress_edge[i].begin(), compress_edge[i].end());
            compress_edge[i].erase( unique(compress_edge[i].begin(), compress_edge[i].end()), compress_edge[i].end() );
        }
    }
	int is_true(int i) {
		return label[i] > label[rev(i)];
	}
	void print(void) {
		for(auto id:label) cout << id << " ";
		cout << endl;
	}

};

int main() {
    int N,M,K; cin >> N >> M >> K;
    string S;
    for(int i = 0; i < N; ++i) {
        char c;
        cin >> c;
        S.push_back(c);
    }
    StronglyConnectedComponents scc(N);
    while(M--) {
        int a,b; cin >> a >> b;
        a--,b--;
        scc.make_edge(a,b);
    }
    scc.solve();
    M = scc.compress_num;
    scc.make_compress_edge();
    vector<string> vs(M);
    for(int i = 0; i < N; ++i) vs[scc[i]].push_back(S[i]);
    for(int i = 0; i < M; ++i) sort(ALL(vs[i]));
    auto dp = multivector(N+1,N+1,string(""));
    for(int i = 0; i < M; ++i) for(int j = 1; j <= vs[i].size(); ++j) dp[i][j]=vs[i].substr(0,j);
    vector<int> dim(M,0);
    for(int i = 0; i < M; ++i) for(int j:scc.compress_edge[i]) dim[j]++;
    queue<int> q;
    for(int i = 0; i < M; ++i) if(!dim[i]) q.push(i);
    while(q.size()) {
        int from = q.front();
        q.pop();
        for(int to:scc.compress_edge[from]) {
            for(int j = 1; j <= N; ++j) {
                if(dp[from][j]=="") break;
                chmin(dp[to][j],dp[from][j]);
                string tmp="";
                for(int k = 1; k <= vs[to].size(); ++k) {
                    tmp.push_back(vs[to][k-1]);
                    if(dp[to][j+k]=="") dp[to][j+k]=dp[from][j]+tmp;
                    else chmin(dp[to][j+k],dp[from][j]+tmp);
                }
            }
            dim[to]--;
            if(dim[to]) continue;
            q.push(to);
        }
    }
    string ans = "-1";
    for(int i = 0; i < M; ++i) {
        if(dp[i][K]=="") continue;
        if(ans=="-1") ans = dp[i][K];
        else chmin(ans,dp[i][K]);
    }
    cout << ans << endl;
    return 0;
}
