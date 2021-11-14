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
 * @title SparseTable
 */
template<class Operator> class SparseTable{
public:
	using TypeNode = typename Operator::TypeNode;
	vector<TypeNode> node;
	vector<int> idx;
	size_t depth;
	size_t length;

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

template<class T> struct NodeMin {
	using TypeNode = T;
	inline static constexpr TypeNode unitNode = {10000,-1};
	inline static constexpr TypeNode func_node(TypeNode l,TypeNode r){return min(l,r);}
};

int main() {
    int T; cin >> T;
    while(T--){
        int N; cin >> N;
        vector<pair<int,int>> A(N);
        for(int i = 0; i < N; ++i) {
            int a;
            cin >> a;
            A[i]={a,i};
        }
        SparseTable<NodeMin<pair<int,int>>> st(A); 
        int l=-1,c=-1,r=-1;
        for(int i = 1; i+1 < N; ++i) {
            auto ml=st.get(0,i);
            auto mr=st.get(i+1,N);
            if(ml.first<A[i].first && A[i].first>mr.first){
                l=ml.second;
                c=i;
                r=mr.second;
            }
        }
        if(c==-1) cout << "NO" << endl;
        else{
            cout << "YES" << endl;
            cout << l+1 << " " << c+1 << " " << r+1 << endl;
        }

    }    
    return 0;
}
