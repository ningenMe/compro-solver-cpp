#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
using namespace std;
using ll = long long;

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
		if (node==nullptr) return Operator::unit_node;
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
	void print(Node *node) {
		if (node==nullptr) return;
		print(node->left);
		cout << node->val << " ";
		print(node->right);
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
	inline int empty(void) {
		return bool(size()==0);
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
	void print() {
		cout << "{";
		print(this->root);
		cout << "}" << endl;
	}
};
//https://atcoder.jp/contests/abc154/tasks/abc154_c
//https://atcoder.jp/contests/arc033/tasks/arc033_3
//https://atcoder.jp/contests/m-solutions2020/tasks/m_solutions2020_c
//https://yukicoder.me/problems/no/919
//https://yukicoder.me/problems/no/649
//https://yukicoder.me/problems/no/822

/*
 * @title ConvexHullTrick
 */
template<class Operator> class ConvexHullTrick {
private:
	using TypeValue = typename Operator::TypeValue;
	struct NodePair {
		using TypeNode = pair<TypeValue,TypeValue>;
		inline static constexpr TypeNode unit_node = {0,Operator::unit_value};
		inline static constexpr TypeNode func_node(TypeNode l,TypeNode c,TypeNode r){return {0,0};}
	};
	Rbst<NodePair> lines;

	//3直線に関してline2が必要か確認 (このとき a1 < a2 < a3が必要=rbstの順そのまま)
	inline int is_required(const pair<TypeValue,TypeValue>& line1, const pair<TypeValue,TypeValue>& line2, const pair<TypeValue,TypeValue>& line3) {
		return Operator::func_compare((line2.second-line3.second)*(line2.first-line1.first),(line1.second-line2.second)*(line3.first-line2.first));
	}
	
	//y=ax+bの値
	inline TypeValue y(const pair<TypeValue,TypeValue> line, TypeValue x) {
		return line.first * x + line.second;
	}

public:
	ConvexHullTrick() {
		// do nothing
	} 

	//ax+bを追加
	void insert(const TypeValue a, const TypeValue b) {
		insert({a,b});
	}
	//ax+bを追加 armortized O(log(N))
	void insert(const pair<TypeValue,TypeValue> line) {
		int i,flg=1;
		i=lines.lower_bound(line);
		auto l=lines.get(i-1);
		auto r=lines.get(i);
		//lと傾きが同じなら、どちらかをerase
		if(flg && l.second!=Operator::unit_value && l.first==line.first) {
			if(Operator::func_compare(l.second,line.second)) return;
			else lines.erase(l),flg=0;
		}	
		//rと傾きが同じなら、どちらかをerase
		if(flg && r.second!=Operator::unit_value && line.first==r.first) {
			if(Operator::func_compare(r.second,line.second)) return;
			else lines.erase(r),flg=0;
		}	
		//自身が必要か判定
		if(flg && l.second!=Operator::unit_value && r.second!=Operator::unit_value && !is_required(l,line,r)) return;
		//傾きが小さい側の不必要な直線を取り除く
		for(i=lines.lower_bound(line);i>=2&&!is_required(lines.get(i-2), lines.get(i-1), line);i=lines.lower_bound(line)) lines.erase(lines.get(i-1));
		//傾きが大きい側の不必要な直線を取り除く
		for(i=lines.lower_bound(line);i+1<lines.size()&&!is_required(line,lines.get(i),lines.get(i+1));i=lines.lower_bound(line)) lines.erase(lines.get(i));
		lines.insert(line);
	}
	
	//O(log(N)^2)
	TypeValue get(TypeValue x) {
		int ng = -1, ok = (int)lines.size()-1, md;
		while (ok - ng > 1) {
			md = (ok + ng) >> 1;
			( Operator::func_compare(y(lines.get(md),x),y(lines.get(md+1),x)) ?ok:ng)=md;
		}
		return y(lines.get(ok),x);
	}

	//O(log(N)^2)
	pair<TypeValue,TypeValue> get_line(TypeValue x) {
		int ng = -1, ok = (int)lines.size()-1, md;
		while (ok - ng > 1) {
			md = (ok + ng) >> 1;
			( Operator::func_compare(y(lines.get(md),x),y(lines.get(md+1),x)) ?ok:ng)=md;
		}
		return lines.get(ok);
	}

	void print() {
		lines.print();
	}
};

//最小値クエリ
template<class T> struct ValueMin {
	using TypeValue = T;
	inline static constexpr TypeValue unit_value = 3e18;
	inline static constexpr bool func_compare(TypeValue l,TypeValue r){return l<r;}
};

//最大値クエリ
template<class T> struct ValueMax {
	using TypeValue = T;
	inline static constexpr TypeValue unit_value = -3e18;
	inline static constexpr bool func_compare(TypeValue l,TypeValue r){return l>r;}
};


/*
 * @title ConvexHullTrickSegmentTree
 */
template<class Operator> class ConvexHullTrickSegmentTree {
	using TypeValue = typename Operator::TypeValue;
	using TypeNode = pair<TypeValue,TypeValue>;
	size_t length;
	size_t num;
	vector<ConvexHullTrick<Operator>> node;
public:
	inline constexpr TypeValue y(const TypeNode p, TypeValue x) {
		return p.first*x+p.second;
	}
	ConvexHullTrickSegmentTree(const size_t num): num(num) {
		for (length = 1; length <= num; length *= 2);
		node.resize(2 * length);
	}
	//[idx,idx+1) insert{ax+b}
	void update(size_t idx, const TypeValue a, const TypeValue b) {
		if(idx < 0 || length <= idx) return;
		for(idx+=length;idx;idx >>= 1) node[idx].insert(a,b);
	}
	//[l,r)
	TypeValue get(int l, int r, TypeValue x) {
		if (l < 0 || length <= l || r < 0 || length < r) return Operator::unit_value;
		TypeValue vl =  Operator::unit_value, vr = Operator::unit_value;
		for(l += length, r += length; l < r; l >>=1, r >>=1) {
			if(l&1) {
				auto tl=node[l++].get(x);                
				vl = (Operator::func_compare(vl,tl)?vl:tl);
			}
			if(r&1) {
				auto tr=node[--r].get(x);                
				vr = (Operator::func_compare(tr,vr)?tr:vr);
			}
		}
		return (Operator::func_compare(vl,vr)?vl:vr);
	}
	//[l,r)
	TypeNode get_line(int l, int r, TypeValue x) {
		if (l < 0 || length <= l || r < 0 || length < r) return {0,Operator::unit_value};
		TypeNode vl = {0,Operator::unit_value}, vr = {0,Operator::unit_value};
		for(l += length, r += length; l < r; l >>=1, r >>=1) {
			if(l&1) {
				auto tl=node[l++].get_line(x);                
				vl = (Operator::func_compare(y(vl,x),y(tl,x))?vl:tl);
			}
			if(r&1) {
				auto tr=node[--r].get_line(x);                
				vr = (Operator::func_compare(y(tr,x),y(vr,x))?tr:vr);
			}
		}
		return (Operator::func_compare(y(vl,x),y(vr,x))?vl:vr);
	}
	void print(){
		cout << "node" << endl;
		for(int i = 1,j = 1; i < 2*length; ++i) {
			node[i].print();
			if(i==((1<<j)-1) && ++j) cout << endl;
		}    
	}
};
//https://atcoder.jp/contests/wupc2019/tasks/wupc2019_i

template <class T> void chmin(T& a, const T b){a=min(a,b);}

int main(void){
    cin.tie(0);ios::sync_with_stdio(false);
    ll N; cin >> N;
    //区間[l,r)にある直線群の中で、あるxに対して最小値を取る直線を取得するセグメント木
	int M=100002;
    ConvexHullTrickSegmentTree<ValueMin<ll>> chtsegmin(M);
    vector<ll> O(N),C(N),D(N),X(N),P(N);
    vector<vector<int>> idx(M);
	for(int i = 0; i < N; ++i) {
		ll o,c,d,x;
		cin >> o >> c >> d >> x;
        if(c==-1) c=M-1;
        O[i]=o,C[i]=c,D[i]=d,X[i]=x;
        idx[o].push_back(i);
	}
	for(int i = 0; i < M; ++i) {
        for(int j:idx[i]){
            ll o,c,d,x;
            o=O[j],c=C[j],d=D[j],x=X[j];
            //p_i <= min((-2d_j)*d_i+(p_j+d_j^2) + d_i^2, x_i);
            ll p = chtsegmin.get(o-1,M,d)+d*d;
            chmin(p,x);
            P[j]=p;
        }
        for(int j:idx[i]){
            ll o,c,d,x,p;
            o=O[j],c=C[j],d=D[j],x=X[j],p=P[j];
            ll a = -2*d;
            ll b = p+d*d;
            chtsegmin.update(c,a,b);
        }
 	}
    for(auto& e:P) cout << e << endl;
	return 0;
}