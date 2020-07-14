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
		if(!is_2sat) return true;
		for (int i = 0; i < num; ++i) if (label[i] == label[rev(i)]) return false;
		return true;
	}
	int is_true(int i) {
		return label[i] > label[rev(i)];
	}
	void print(void) {
		for(auto id:label) cout << id << " ";
		cout << endl;
	}

};


//重みなし有向グラフの最小閉路を求めるクラス
class MinimumDirectedClosedCircuit {
	vector<vector<int>> edge,redge;  
	vector<int> dist;
	size_t N;
public:
	MinimumDirectedClosedCircuit(size_t N) : N(N),edge(N),redge(N),dist(N) {
		//do nothing
	}
	void make_edge(int from,int to){
		edge[from].push_back(to);
		redge[to].push_back(from);
	}
	//rootを含む最小閉路の集合を返す O(N) 閉路がないときは空集合
	vector<int> solve(int root,int inf = 123456789){
		int mini = inf;
		int last = -1;
		for(int i = 0; i < N; ++i) dist[i] = -1;
		queue<int> q;
		q.push(root);
		dist[root] = 0;
		while (q.size()) {
			int curr = q.front();
			q.pop();
			for(int next:edge[curr]){
				if(next == root && mini > dist[curr]+1) mini = dist[curr]+1,last = curr;
				if(dist[next]==-1) {
					dist[next] = dist[curr] + 1;
					q.push(next);
				}
			}
		}
		vector<int> res;
		if(last != -1){
			res.push_back(last);
			int curr = last;
			while(curr != root){
				for(int next:redge[curr]){
					if(dist[next]+1==dist[curr]) {
						res.push_back(next);
						curr = next;
						break;
					}
				}
			}
			reverse(res.begin(),res.end());
		}
		return res;
	}
};

int main() {
    SPEED
    int N,M; cin >> N >> M;
    StronglyConnectedComponents scc(N);
    MinimumDirectedClosedCircuit dcc(N);
    map<pair<int,int>,int> mp;
    for(int i = 0; i < M; ++i) {
        int u,v; cin >> u >> v;
        scc.make_edge(u,v);
        dcc.make_edge(u,v);
        mp[{u,v}]=i;
    }
    scc.solve();
    vector<int> cnt(N,0);
    for(int i = 0; i < N; ++i) cnt[scc[i]]++;
    corner(*max_element(ALL(cnt))==1,-1);
    int label=max_element(ALL(cnt))-cnt.begin();
    int root;
    for(int i = 0; i < N; ++i) if(scc[i]==label) root=i;
    auto ans = dcc.solve(root);
    int L = ans.size();
    cout << L << endl;
    for(int i = 0; i < L; ++i) cout << mp[{ans[i],ans[(i+1)%L]}] << endl;
    return 0;
}
