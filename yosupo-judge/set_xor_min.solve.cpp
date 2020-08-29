#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define ALL(obj) (obj).begin(),(obj).end()
#define SPEED cin.tie(0);ios::sync_with_stdio(false);

template<class T> using priority_queue_reverse = priority_queue<T,vector<T>,greater<T>>;

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

template<class Operator, int bit=60> class BinaryTrie{
	using TypeNode = typename Operator::TypeNode; 
public:
	vector<TypeNode> node;
	vector<vector<int>> ch;
	BinaryTrie():node(1),ch(1,vector<int>(2,-1)){}
	void update(long long idx, const TypeNode var) {
		int curr=0;
		stack<int> st;
		for(int i=bit-1; 0 <= i; --i) {
			st.push(curr);
			int f=(idx>>i)&1;
			if(ch[curr][f]==-1) {
				node.push_back(Operator::unit_node);
				ch.push_back(vector<int>(2,-1));
				ch[curr][f] = (int)node.size()-1;
			}
			curr = ch[curr][f];
		}
		node[curr] = Operator::func_merge(node[curr],var);
		while(st.size()) {
			curr = st.top(); st.pop();
			node[curr]=Operator::unit_node;
			if(ch[curr][0]!=-1)	node[curr] = Operator::func_node(node[ch[curr][0]],node[curr]);
			if(ch[curr][1]!=-1)	node[curr] = Operator::func_node(node[curr],node[ch[curr][1]]);
		}
	}
	TypeNode get(long long idx) {
		int curr=0;
		for(int i=bit-1; 0 <= i; --i) {
			int f=(idx>>i)&1;
			if(ch[curr][f]!=-1) curr = ch[curr][f];
			else return Operator::unit_node;
		}
		return node[curr];
	}
	long long min_bitwise_xor(long long x) {
		int curr=0;
		long long y=0;
		for(int i=bit-1; 0 <= i; --i) {
			long long f=(x>>i)&1;
			if(!node[curr]) break;
			if(ch[curr][f]!=-1 && node[ch[curr][f]]) curr = ch[curr][f];
			else curr = ch[curr][f^=1];
			y^=(f<<i);
		}
		return y^x;
	}
};

//一点加算 区間和
template<class T> struct NodeSumPointAdd {
	using TypeNode = T;
	inline static constexpr TypeNode unit_node = 0;
	inline static constexpr TypeNode func_node(TypeNode l,TypeNode r){return l+r;}
	inline static constexpr TypeNode func_merge(TypeNode l,TypeNode r){return l+r;}
};

int main() {
	SPEED
	BinaryTrie<NodeSumPointAdd<int>,30> trie;
	int Q; cin >> Q;
	while (Q--){
		int q; cin >> q;
		long long x; cin >> x;
		if(q==0) {
			long long y=trie.get(x);
			if(!y) trie.update(x,1);
		}
		if(q==1) {
			long long y=trie.get(x);
			if(y) trie.update(x,-1);
		}
		if(q==2) {
			cout << trie.min_bitwise_xor(x) << endl;
		}
	}
		
    return 0;
}
