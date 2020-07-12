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

/*
 * @title RadixHeapInt
 */
template<class T> class RadixHeapInt{
	using TypeNode = pair<unsigned int, T>;
	array<vector<TypeNode>,33> vq;
	unsigned int size_num;
	TypeNode last;
	inline int bit(int a) {
		return a ? 32 - __builtin_clz(a) : 0;
	}
public:
	RadixHeapInt(T mini) : size_num(0), last(make_pair(0,mini)) {
		// do nothing
	}
	inline bool empty() {
		return size_num == 0;
	}
	inline size_t size(){
		return size_num;
	}
	inline void push(TypeNode x){
		++size_num;
		vq[bit(x.first^last.first)].push_back(x);
	}
	inline void emplace(unsigned int key,T val){
		++size_num;
		vq[bit(key^last.first)].emplace_back(key,val);
	}
	inline TypeNode pop() {
		if(vq[0].empty()) {
			int i = 1;
			while(vq[i].empty()) ++i;
			last = *min_element(vq[i].begin(),vq[i].end());
			for(auto &p : vq[i]) vq[bit(p.first ^ last.first)].push_back(p);
			vq[i].clear();
		}
		--size_num;
		auto res = vq[0].back();
		vq[0].pop_back();
		return res;
	}
};

int main() {
    int H,W,K; cin >> H >> W >> K;
    int sy,sx,gy,gx,dy[4]={-1,1,0,0},dx[4]={0,0,-1,1};
    cin >> sy >> sx >> gy >> gx;
    sy--,sx--,gy--,gx--;
    vector<string> c(H);
    for(int i = 0; i < H; ++i) cin >> c[i];
    vector<vector<pair<int,int>>> cost(H*W,vector<pair<int,int>>(4,{12345678,K}));
    queue<pair<pair<int,int>,int>> pq;
    for(int i = 0; i < 4; ++i) {
        cost[sy*W+sx][i]={0,0};
        pq.push({{0,0},sy*W+sx});
    }
    while(pq.size()) {
        auto p = pq.front();
        pq.pop();
        int w = p.first.first;
        int y=p.second/W;
        int x=p.second%W;
        pair<int,int> v = {12345678,K};
        for(int k = 0; k < 4; ++k) chmin(v,cost[y*W+x][k]);
        if(p.first>v) continue;
        for(int k = 0; k < 4; ++k) {
            for(int i = 1; i <= K; ++i) {
                int s=y+dy[k]*i,t=x+dx[k]*i;
                if(s<0 || H <= s || t < 0 || W <= t) break;
                if(c[s][t]=='@') break;
                pair<int,int> z = {w+1,i};
                if(cost[s*W+t][k] <= z) break;
                cost[s*W+t][k] = z;
                pq.push({z,s*W+t});
            }
        }
    }
    int ans = 12345678;
    for(int i = 0; i < 4; ++i) chmin(ans,cost[gy*W+gx][i].first);
    if(ans==12345678) ans = -1;
    cout << ans << endl;
    return 0;
}
