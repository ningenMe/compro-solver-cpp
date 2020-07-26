#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
using namespace std;
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
		inline static constexpr TypeNode unit_node = {0,0};
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
		int i;
		//左と傾き比較
		i=lines.lower_bound(line);
		if(i) {
			auto l=lines.get(i-1);
			//傾きが同じものがあるとき、どちらかをerase
			if(l.first==line.first) {
				if(Operator::func_compare(l.second,line.second)) return;
				else lines.erase(l);
			}	
		}
		//右と傾き比較
		i=lines.lower_bound(line);
		if(i!=lines.size()) {
			auto r=lines.get(i);
			//傾きが同じものがあるとき、どちらかをerase
			if(line.first==r.first) {
				if(Operator::func_compare(r.second,line.second)) return;
				else lines.erase(r);
			}	
		}
		//自身が必要か判定
		i=lines.lower_bound(line);
		if(i && i!=lines.size()) {
			auto l=lines.get(i-1);
			auto r=lines.get(i);
			if(!is_required(l,line,r)) return;
		}
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

	void print() {
		lines.print();
	}
};

//最小値クエリ
template<class T> struct ValueMin {
	using TypeValue = T;
	inline static constexpr bool func_compare(TypeValue l,TypeValue r){return l<r;}
};

//最大値クエリ
template<class T> struct ValueMax {
	using TypeValue = T;
	inline static constexpr bool func_compare(TypeValue l,TypeValue r){return l>r;}
};

template <class T>ostream &operator<<(ostream &o, const vector<T>&obj) {o << "{"; for (int i = 0; i < (int)obj.size(); ++i)o << (i > 0 ? ", " : "") << obj[i]; o << "}"; return o;}
template <class T, class U>ostream &operator<<(ostream &o, const pair<T, U>&obj) {o << "{" << obj.first << ", " << obj.second << "}"; return o;}
void print(void) {cout << endl;}
template <class Head> void print(Head&& head) {cout << head;print();}
template <class Head, class... Tail> void print(Head&& head, Tail&&... tail) {cout << head << " ";print(forward<Tail>(tail)...);}

using ll=long long;
int main(){
	int N; cin >> N;
	vector<ll> A(N);
	for(int i = 0; i < N; ++i) cin >> A[i];
	ConvexHullTrick<ValueMin<ll>> cht;
	vector<pair<ll,ll>> vp(N);
	for(ll i = 0; i < N; ++i) vp[i]=make_pair(-2*i,A[i]+i*i);
	random_shuffle(vp.begin(), vp.end());
	for(ll i = 0; i < N; ++i) {
		cht.insert(vp[i]);
	}
	for(ll i = 0; i < N; ++i) cout << i*i+cht.get(i) << endl;
}

