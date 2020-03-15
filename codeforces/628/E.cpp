#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
 
#define ALL(obj) (obj).begin(),(obj).end()
#define SPEED cin.tie(0);ios::sync_with_stdio(false);
 
template<class T> using PQ = priority_queue<T>;
template<class T> using PQR = priority_queue<T,vector<T>,greater<T>>;
 
constexpr long long MOD = (long long)1e9 + 7;
constexpr long long MOD2 = 998244353;
constexpr long long HIGHINF = (long long)1e18;
constexpr long long LOWINF = (long long)1e15;
constexpr long double PI = 3.1415926535897932384626433;
 
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


//Prime Factorization O(sqrt(N))
vector<pair<long long,long long>> PrimeFactorization(long long N) {
    vector<pair<long long,long long>> ret;
    if (N == 1) return ret;
    for (long long i = 2,M = N; i*i <= M; ++i) {
        if (N%i == 0) {
            long long cnt = 0;
            while (N%i == 0) N /= i, cnt++;
            ret.push_back({i,cnt});
        }
    }
    if (N != 1) ret.push_back({N,1});
    return ret;
}

//重みなし無効グラフの最小閉路を求めるクラス
class MinimumUndirectedClosedCircuit {
	vector<vector<int>> edge;
	vector<int> dist;
	size_t N;
public:
	MinimumUndirectedClosedCircuit(size_t N) : N(N),edge(N),dist(N) {
		//do nothing
	}
	void makeEdge(int from,int to){
		edge[from].push_back(to);
	}
	//rootを含む最小閉路の長さを返す O(N) 閉路がないときは空集合
	vector<int> solve(int root,int inf = 123456789){
		int mini = inf;
		for(int i = 0; i < N; ++i) dist[i] = -1;
		queue<pair<int,int>> q;
		q.push({root,-1});
		dist[root] = 0;
		pair<int,int> last = make_pair(-1,-1);
		while (q.size()) {
			int curr = q.front().first;
			int prev = q.front().second;
			q.pop();
			for(int next:edge[curr]){
				if(next==prev) continue;
				if(dist[next]==-1) {
					dist[next] = dist[curr] + 1;
					q.push({next,curr});
				}
				else{
					if(mini > dist[curr]+dist[next]+1){
						mini = dist[curr]+dist[next]+1;
						last = make_pair(curr,next);
					}
				}
			}
		}
		vector<int> idxl,idxr,res;
		if(last != make_pair(-1,-1)){
			queue<int> l;
			stack<int> r;
			int curr;
            curr = last.first;
            while(curr != root){
				l.push(curr);
                for(int next:edge[curr]){
                    if(dist[next]+1==dist[curr]) {
						curr = next;
                        break;
                    }
                }
            }
            curr = last.second;
            while(curr != root){
				r.push(curr);
                for(int next:edge[curr]){
                    if(dist[next]+1==dist[curr]) {
						curr = next;
                        break;
                    }
                }
            }
			while (l.size()) {
				res.push_back(l.front());
				l.pop();
			}
			res.push_back(root);			
			while (r.size()) {
				res.push_back(r.top());
				r.pop();
			}
		}
		return res;
	}
};

int main() {
	SPEED
	int N; cin >> N;
	vector<ll> A(N);
	for(int i = 0; i < N; ++i) cin >> A[i];
	vector<vector<pair<ll,ll>>> B(N);

	for(int i = 0; i < N; ++i) {
		B[i] = PrimeFactorization(A[i]);
		int flg = 1;
		for(auto p:B[i]){
			if(p.second%2) flg = 0;
		}
		corner(flg,1);
	}
	map<ll,int> mp;
	mp[1];
	vector<pair<int,int>> tmp;
	for(auto v:B) {
		if(v.size()==1){
			mp[v[0].first]++;
			corner(mp[v[0].first]>=2,2);
			tmp.push_back({v[0].first,1});
		}
		if(v.size()==2){
			if(v[0].second%2 && v[1].second%2) {
				mp[v[0].first];
				mp[v[1].first];
				tmp.push_back({v[0].first,v[1].first});
			}
			else{
				if(v[0].second%2) {
					mp[v[0].first]++;
					corner(mp[v[0].first]>=2,2);
					tmp.push_back({v[0].first,1});
				}
				if(v[1].second%2) {
					mp[v[1].first]++;
					corner(mp[v[1].first]>=2,2);
					tmp.push_back({v[1].first,1});
				}
			}
		}
	}
	int M=0;
	vector<int> val;
	for(auto& e:mp) {
		val.push_back(e.first);
		e.second=M++;
	}
	MinimumUndirectedClosedCircuit mucc(M);
	for(auto& e:tmp) {
		mucc.makeEdge(mp[e.first],mp[e.second]);
		mucc.makeEdge(mp[e.second],mp[e.first]);
	}
	int ans = 1234567;
	for(int i = 0; i < M; ++i) {
		if(val[i] > 1000) continue;
		auto v = mucc.solve(i);
		if(v.empty()) continue;
		chmin(ans,(int)v.size());
	}
	if(ans==1234567) ans = -1;
	cout << ans << endl;
    return 0;
}
