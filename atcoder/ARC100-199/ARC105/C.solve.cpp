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


/*
 * @title SparseTable
 * @docs md/segment/SparseTable.md
 */
template<class Operator> class SparseTable{
public:
	using TypeNode = typename Operator::TypeNode;
	vector<TypeNode> node;
	vector<int> idx;
	size_t depth;
	size_t length;

	SparseTable(void) {

	}

	SparseTable(const vector<TypeNode>& vec) {
		for(depth = 0;(1<<depth)<=vec.size();++depth);
		length = (1<<depth);
		node.resize(depth*length);
		for(int i = 0; i < vec.size(); ++i) node[i] = vec[i];
		for(int i = 1; i < depth; ++i) for(int j = 0; j + (1<<i) < (1<<depth); ++j) node[i*length+j] = Operator::func_node(node[(i-1)*length+j],node[(i-1)*length+j + (1 << (i-1))]);
		idx.resize(vec.size()+1);
		for(int i = 2; i < vec.size()+1; ++i) idx[i] = idx[i>>1] + 1;
	}

	//[l,r)
	TypeNode get(int l,int r) {
		int bit = idx[r-l];
		return Operator::func_node(node[bit*length+l],node[bit*length+r - (1<<bit)]);
	}
};

template<class T> struct NodeMax {
	using TypeNode = T;
	inline static constexpr TypeNode unitNode = 0;
	inline static constexpr TypeNode func_node(TypeNode l,TypeNode r){return max(l,r);}
};

int N,M; 
vector<ll> W,X,V;
SparseTable<NodeMax<ll>> spt;

ll ans = LOWINF;

ll check_dist(const vector<int>& idx,const vector<ll>& dist,int n) {
    int K = idx.size();
    ll d = 0;
    ll len_sum = 0, weight_sum = W[n];
    for(int i=K-1; 0 <= i; --i) {
        weight_sum += W[idx[i]];
        int j = lower_bound(ALL(V),weight_sum)-V.begin();
        ll maxi_len;
        if(j) {
            maxi_len = spt.get(0,j);
        }
        else {
            maxi_len = 0;
        }

        if(maxi_len > len_sum) {
            chmax(d,maxi_len-len_sum);
        }
        len_sum += dist[i];
    }
    return d;
}

void dfs(vector<int>& idx,vector<ll>& dist, set<int>& st) {

    
    if(idx.size()==N) {
        chmin(ans,accumulate(ALL(dist),0LL));
        return;
    }

    for(int i=0;i<N;++i) {
        if(st.count(i)) continue;

        ll d = check_dist(idx,dist,i);

        idx.push_back(i);
        dist.push_back(d);
        st.insert(i);

        dfs(idx,dist,st);

        idx.pop_back();
        dist.pop_back();
        st.erase(i);
    }

}

/**
 * @url https://atcoder.jp/contests/arc105/tasks/arc105_c
 * @est 500
 */ 
int main() {
    cin.tie(0);ios::sync_with_stdio(false);
    cin >> N >> M;
    W.resize(N);
    X.resize(M);
    V.resize(M);
    for(int i=0;i<N;++i) cin >> W[i];
    for(int i=0;i<M;++i) cin >> X[i] >> V[i];

    vector<pair<ll,ll>> ord(M);
    for(int i=0;i<M; ++i) ord[i] = {V[i],X[i]};
    sort(ALL(ord));
    for(int i=0;i<M; ++i) V[i]=ord[i].first,X[i]=ord[i].second;



    spt = SparseTable<NodeMax<ll>>(X);

    corner(*max_element(ALL(W)) > *min_element(ALL(V)),-1);


    for(int i=0;i<N;++i) {
        vector<int> idx = {i};
        vector<ll> dist = {0};
        set<int> st;
        st.insert(i);
        dfs(idx,dist,st);
    }
    cout << ans << endl;
    return 0;
}
