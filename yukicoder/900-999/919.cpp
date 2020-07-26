#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;

#define REP(i,n) for(long long i = 0; i < (n); i++)
#define FOR(i, m, n) for(long long i = (m);i < (n); ++i)
#define ALL(obj) (obj).begin(),(obj).end()
#define SPEED cin.tie(0);ios::sync_with_stdio(false);

template<class T> using V = vector<T>;
template<class T, class U> using P = pair<T, U>;
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
 * @title Rbst
 */
template<class Operator> class Rbst {
	using TypeNode = typename Operator::TypeNode;
	unsigned int x = 123456789, y = 362436069, z = 521288629, w = 88675123;
    unsigned int xor_shift() {
        unsigned int t = (x ^ (x << 11)); x = y; y = z; z = w;
        return (w = (w ^ (w >> 19)) ^ (t ^ (t >> 8)));
    }
    struct Node {
        Node *left, *right;
        TypeNode val;
        int size;
        TypeNode sum;

        Node() : val(Operator::unit_node), size(1), sum(Operator::unit_node) {
            left = right = nullptr;
        }
        Node(TypeNode v) : val(v), size(1), sum(v) {
            left = right = nullptr;
        }
    };
    Node* root;
    inline int size(Node *node) {
        return node==nullptr ? 0 : node->size;
    }
    inline TypeNode sum(Node *node) {
        return node==nullptr ? Operator::unit_node : node->sum;
    }
    inline Node* update(Node *node) {
        node->size = size(node->left) + size(node->right) + 1;
        node->sum = Operator::func_node(sum(node->left),sum(node->right),node->val);
        return node;
    }
    inline TypeNode get(Node *node, int k) {
        if (node==nullptr) return -1;
        if (k == size(node->left)) return node->val;
        if (k < size(node->left)) return get(node->left, k);
        else return get(node->right, k-1 - size(node->left));
    }
    inline int lower_bound(Node *node, TypeNode val) {
        if (node==nullptr) return 0;
        if (val <= node->val) return lower_bound(node->left, val);
        else return size(node->left) + lower_bound(node->right, val) + 1;
    }
    inline int upper_bound(Node *node, TypeNode val) {
        if (node==nullptr) return 0;
        if (val >= node->val) return size(node->left) + upper_bound(node->right, val) + 1;
        else return upper_bound(node->left, val);
    }
	Node* merge(Node *left, Node *right) {
        if (left==nullptr)  return right;
		if (right==nullptr) return left;
        if (xor_shift() % (left->size + right->size) < left->size) {
            left->right = merge(left->right, right);
            return update(left);
        }
        else {
            right->left = merge(left, right->left);
            return update(right);
        }
    }
	pair<Node*, Node*> split(Node* node, int k) {
        if (node==nullptr) return make_pair(node, node);
        if (k <= size(node->left)) {
            pair<Node*, Node*> sub = split(node->left, k);
            node->left = sub.second;
            return make_pair(sub.first, update(node));
        }
        else {
            pair<Node*, Node*> sub = split(node->right, k-1 - size(node->left));
            node->right = sub.first;
            return make_pair(update(node), sub.second);
        }
    }
	Rbst(Node* node):root(node){}
public:
    Rbst() : root(nullptr) {}
    inline int size() {
        return size(this->root);
    }
    inline TypeNode sum() {
        return sum(this->root);
    }
    inline int lower_bound(TypeNode val) {
        return lower_bound(this->root, val);
    }

    inline int upper_bound(TypeNode val) {
        return upper_bound(this->root, val);
    }
    inline int count(TypeNode val) {
        return upper_bound(val) - lower_bound(val);
    }
    inline TypeNode get(int k) {
        return get(this->root, k);
    }
    inline TypeNode get_median() {
		//奇数の時N/2
        return get(this->root, (size()-1)/2);
    }
    void merge(Rbst another) {
        root = merge(this->root, another.root);
    }
    void insert(const TypeNode val) {
        pair<Node*, Node*> sub = split(this->root, this->lower_bound(val));
        this->root = this->merge(this->merge(sub.first, new Node(val)), sub.second);
    }
    void erase(const TypeNode val) {
        if (!this->count(val)) return;
        pair<Node*, Node*> sub = this->split(this->root, this->lower_bound(val));
        this->root = this->merge(sub.first, this->split(sub.second, 1).second);
    }
};
//https://atcoder.jp/contests/abc154/tasks/abc154_c
//https://atcoder.jp/contests/arc033/tasks/arc033_3
//https://atcoder.jp/contests/m-solutions2020/tasks/m_solutions2020_c

template<class T> struct NodeSum {
	using TypeNode = T;
	inline static constexpr TypeNode unit_node = 0;
	inline static constexpr TypeNode func_node(TypeNode l,TypeNode c,TypeNode r){return l+c+r;}
};

template<class T> class Mo{
    unordered_map<long long,int> mp;
    long long N;
    int bucket;
    vector<pair<int,int>> range;
	vector<int> idx;
public:

    Mo(int N, const vector<pair<int,int>>& range) : N(N),range(range),idx(range.size()),bucket(sqrt(N)) {
        iota(idx.begin(),idx.end(),0);
        sort(idx.begin(),idx.end(),[&](int a, int b){
            auto  al = range[a].first/bucket;
            auto  ar = range[a].second;
            auto  bl = range[b].first/bucket;
            auto  br = range[b].second;
            return (al != bl) ? (al < bl) : ((al%2)?(ar > br):(ar < br));
        });
    }
    
    //参照でvectorを渡したりすると良い
    void solve(const vector<int>& A, Rbst<NodeSum<long long>>& med){
        int l = 0, r = 0;
        for(int& i:idx){
            auto& xl = range[i].first;
            auto& xr = range[i].second;
            
            //左端を広げる
            while(xl < l){
                l--;
                med.insert(A[l]);
            }
            //右端を広げる
            while(r < xr){
                r++;
                med.insert(A[r]);
            }
            //左端を狭める
            while(l < xl){
				med.erase(A[l]);
                l++;
            }
            //右端を狭める
            while(xr < r){
				med.erase(A[r]);
                r--;
            }
            mp[xl*N+xr] = med.get_median();
        }
    }

    T& operator [] (pair<int,int> p) {
        return mp[p.first*N+p.second];
    }
};

int main() {
    cin.tie(0);ios::sync_with_stdio(false);
	int N; cin >> N;
    vector<int> A(N);
	for(int i = 0; i < N; ++i) cin >> A[i];

	//クエリ区間を列挙、調和級数なのでO(N*logN)
	vector<pair<int,int>> range;
	for(int n = 1; n <= N; ++n) {
		int M = N/n;
		for(int i = 0;     i+n <= N; i+=n) range.push_back({i,i+n-1});
		for(int i = N-M*n; i+n <= N; i+=n) range.push_back({i,i+n-1});
	}

	
	//Moで中央値列挙　O(N*sqrt(N)*(logN)^2)
    Mo<int> mo(N,range);
    Rbst<NodeSum<long long>> med;
    med.insert(A[0]);
    mo.solve(A,med);

	long long ans = 0;
	int cnt = 0;
	//区間長決め打ち全探索O(N*logN)
	for(long long n = 1; n <= N; ++n) {
		int M = N/n;
		vector<long long> lSum(M,0),rSum(M,0);
		vector<pair<int, int>> lRange(M),rRange(M);
		//区間取得 O(M)
		for(int i = 0; i < M; ++i) {
			lRange[i] = range[cnt + i];
			lSum[i]   = n*mo[lRange[i]];
			rRange[i] = range[cnt + i + M];
			rSum[i]   = n*mo[rRange[i]];
		}
		//累積和 O(M)
		for(int i = 1;    i < M; ++i) lSum[i]  += lSum[i-1];
		for(int i = M-2; 0 <= i; --i) rSum[i]  += rSum[i+1];
		//累積max O(M)
		for(int i = 1;    i < M; ++i) chmax(lSum[i],lSum[i-1]);
		for(int i = M-2; 0 <= i; --i) chmax(rSum[i],rSum[i+1]);

		chmax(ans,lSum[M-1]);
		chmax(ans,rSum[0]);

		//尺取りしながら左右決め打ち全探索 O(M)
		int j = 0;
		for(int i = 0; i < M; ++i) {
			while(j < M && lRange[i].second >= rRange[j].first) j++;
			if(j<M && lRange[i].second < rRange[j].first) {
				chmax(ans,lSum[i]+rSum[j]);
			}
		}
		cnt += 2*M;
	}
	cout << ans << endl;

    return 0;
}
