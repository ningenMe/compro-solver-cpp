#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

/*
 * @title DynamicSegmentTree - 非再帰抽象化動的セグメント木
 * @docs md/segment-tree/DynamicSegmentTree.md
 */
template<class Monoid> class DynamicSegmentTree {
    using TypeNode = typename Monoid::TypeNode;
    using i64 = long long;

    struct Node{
        Node *left, *right;
        TypeNode val;
        Node():left(nullptr),right(nullptr),val(Monoid::unit_node) {}
    };

    TypeNode dfs(i64 l,i64 r,i64 nl,i64 nr,Node* node) {
        if(l <= nl && nr <= r) return node->val;
        if(nr <= l || r <= nl) return Monoid::unit_node;
        TypeNode vl=Monoid::unit_node, vr=Monoid::unit_node;
        i64 m = (nl+nr)>>1;
        if(node->left)  vl = dfs(l,r,nl,m,node->left);
        if(node->right) vr = dfs(l,r,m,nr,node->right);
        return Monoid::func_fold(vl,vr);
    }

    i64 length;
    Node *root;
public:

    //unitで初期化
    DynamicSegmentTree() : length(1) {
        root = new Node();
    }

    //[idx,idx+1)
    void operate(i64 idx, const TypeNode var) {
        if(idx < 0) return;
        for (;length <= idx; length *= 2) {
            Node *new_root = new Node();
            TypeNode val = root->val;
            new_root->left = root;
            root = new_root;
            root->val = val;
        }

        Node *node = root;
        node->val = Monoid::func_operate(node->val,var);

        i64 l = 0, r = length, m;
        while(r-l>1) {
            m = (r+l)>>1;
            if(idx<m) {
                r = m;
                if(!node->left) node->left=new Node();
                node = node->left;
            }
            else {
                l = m;
                if(!node->right) node->right = new Node();
                node = node->right;
            }
            node->val = Monoid::func_operate(node->val,var);
        }
    }

    //[l,r)
    TypeNode fold(i64 l, i64 r) {
        if (l < 0 || length <= l || r < 0) return Monoid::unit_node;
        return dfs(l,r,0,length,root);
    }
};

/*
 * @title MonoidRangeSumPointAdd - [区間和, 一点加算]
 * @docs md/operator/monoid/MonoidRangeSumPointAdd.md
 */
template<class T> struct MonoidRangeSumPointAdd {
    using TypeNode = T;
    inline static constexpr TypeNode unit_node = 0;
    inline static constexpr TypeNode func_fold(TypeNode l,TypeNode r){return l+r;}
    inline static constexpr TypeNode func_operate(TypeNode l,TypeNode r){return l+r;}
    inline static constexpr bool func_check(TypeNode nodeVal,TypeNode var){return var == nodeVal;}
};

int main(){
	cin.tie(0);ios::sync_with_stdio(false);
    int N,Q; cin >> N >> Q;
	DynamicSegmentTree<MonoidRangeSumPointAdd<long long>> seg;
    for(int i = 0; i < N; ++i) {
		int a; cin >> a;
		seg.operate(i,a);
    }
    
    while(Q--){
        long long q,l,r; cin >> q >> l >> r;
        if(q) cout << seg.fold(l,r) << "\n";
        else seg.operate(l,r);
    }
}

