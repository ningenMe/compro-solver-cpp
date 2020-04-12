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
template <template <class tmp>  class T, class U> ostream &operator<<(ostream &o, const T<U> &obj) {o << "{"; for (auto itr = obj.begin(); itr != obj.end(); ++itr)o << (itr != obj.begin() ? ", " : "") << *itr; o << "}"; return o;}
void print(void) {cout << endl;}
template <class Head> void print(Head&& head) {cout << head;print();}
template <class Head, class... Tail> void print(Head&& head, Tail&&... tail) {cout << head << " ";print(forward<Tail>(tail)...);}
template <class T> void chmax(T& a, const T b){a=max(a,b);}
template <class T> void chmin(T& a, const T b){a=min(a,b);}
void YN(bool flg) {cout << (flg ? "YES" : "NO") << endl;}
void Yn(bool flg) {cout << (flg ? "Yes" : "No") << endl;}
void yn(bool flg) {cout << (flg ? "yes" : "no") << endl;}


class StronglyConnectedComponents{
    int nodeNum;
    vector<vector<int>> edge,revEdge;

    vector<int> label,visited,order;
    
    void dfs(int curr){
        visited[curr] = 1;
        for(int next:edge[curr]) if(!visited[next]) dfs(next);
        order.push_back(curr);
    }

    void revDfs(int curr,int labelId){
        visited[curr] = 1;
        label[curr] = labelId;
        for(int next:revEdge[curr]) if(!visited[next]) revDfs(next,labelId);
    }

public:

	StronglyConnectedComponents(const int& nodeNum) : 
    nodeNum(nodeNum), edge(nodeNum), revEdge(nodeNum), label(nodeNum), visited(nodeNum) {
        // do nothing        
    }

	int operator[](int idx) {
		return label[idx];
	}

    void makeEdge(const int from,const int to) {
        edge[from].push_back(to);
        revEdge[to].push_back(from);
    }

    void solve(void) {
        for(int i = 0; i < nodeNum; ++i) visited[i] = 0;
        for(int i = 0; i < nodeNum; ++i) if(!visited[i]) dfs(i);
        for(int i = 0; i < nodeNum; ++i) visited[i] = 0;
        reverse(order.begin(),order.end());
        int labelId = 0;
        for(int i:order) if(!visited[i]) revDfs(i,labelId++);
    }

    void print(void) {
        for(auto labelId:label) cout << labelId << " ";
        cout << endl;
    }

};



//Union Find Tree
class UnionFindTree {
public:
	vector<int> parent;
    vector<int> rank;

    UnionFindTree(int N) : parent(N), rank(N,0){
		for (int i = 0; i < N; ++i) parent[i] = i;
	}
 
	int root(int n) {
		return (parent[n] == n ? n : parent[n] = root(parent[n]));
	}

    int same(int n, int m) {
		return root(n) == root(m);
	}
 
	void unite(int n, int m) {
		n = root(n);
		m = root(m);
		if (n == m) return;
		if(rank[n]<rank[m]) {
            parent[n] = m;
        }
        else{
            parent[m] = n;
            if(rank[n] == rank[m]) rank[n]++;
        }
	}
};

//verify https://atcoder.jp/contests/abc097/tasks/arc097_b

int main() {
    int N,M; cin >> N >> M;
    vector<pair<int,int>> edge;
    vector<pair<int,int>> bedge;
    for(int i = 0; i < M; ++i) {
        int a,b; cin >> a >> b;
        a--,b--;
        int c; cin >> c;
        if(c==1){
            bedge.push_back({a,b});
        }
        else{
            edge.push_back({a,b});
        }
    }
    UnionFindTree uf(N);
    for(auto& e:bedge){
        int a = e.first,b = e.second;
        corner(uf.same(a,b),"Yes");
        uf.unite(a,b);
    }
    StronglyConnectedComponents scc(N);
    for(auto& e:edge){
        int a = e.first,b = e.second;
        corner(uf.same(a,b),"Yes");
        scc.makeEdge(uf.root(a),uf.root(b));
    }
    scc.solve();
    vector<int> cnt(N,0);
    for(int i = 0; i < N; ++i) cnt[scc[i]]++;
    for(int i = 0; i < N; ++i) corner(cnt[i] > 1,"Yes");
    cout << "No" << endl; 
    return 0;
}
