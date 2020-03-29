#include <bits/stdc++.h>
using namespace std;
using ll = long long;
 
template<class Operator> class SegmentTree {
	Operator Op;                            
	using typeNode = decltype(Op.unitNode); 
	size_t length;
	size_t num;
	vector<typeNode> node;
	vector<pair<size_t,size_t>> range;
public:

	//unitで初期化
	SegmentTree(const size_t num): num(num) {
		for (length = 1; length < num; length *= 2);
		node.resize(2 * length, Op.unitNode);
		range.resize(2 * length);
		for (int i = 0; i < length; ++i) range[i+length] = make_pair(i,i+1);
		for (int i = length - 1; i >= 0; --i) range[i] = make_pair(range[(i<<1)+0].first,range[(i<<1)+1].second);
	}

	//vectorで初期化
	SegmentTree(const vector<typeNode> & vec) : num(vec.size()) {
		for (length = 1; length < vec.size(); length *= 2);
		node.resize(2 * length, Op.unitNode);
		for (int i = 0; i < vec.size(); ++i) node[i + length] = vec[i];
		for (int i = length - 1; i >= 0; --i) node[i] = Op.funcNode(node[(i<<1)+0],node[(i<<1)+1]);
		range.resize(2 * length);
		for (int i = 0; i < length; ++i) range[i+length] = make_pair(i,i+1);
		for (int i = length - 1; i >= 0; --i) range[i] = make_pair(range[(i<<1)+0].first,range[(i<<1)+1].second);
	}
 
	//同じinitで初期化
	SegmentTree(const size_t num, const typeNode init) : num(num) {
		for (length = 1; length < num; length *= 2);
		node.resize(2 * length, init);
		range.resize(2 * length);
		for (int i = 0; i < length; ++i) range[i+length] = make_pair(i,i+1);
		for (int i = length - 1; i >= 0; --i) range[i] = make_pair(range[(i<<1)+0].first,range[(i<<1)+1].second);
	}
	
	//[idx,idx+1)
	void update(size_t idx, const typeNode var) {
		if(idx < 0 || length <= idx) return;
		idx += length;
		node[idx] = Op.funcMerge(node[idx],var);
		while(idx >>= 1) node[idx] = Op.funcNode(node[(idx<<1)+0],node[(idx<<1)+1]);
	}

	//[l,r)
	typeNode get(int l, int r) {
		if (l < 0 || length <= l || r < 0 || length < r) return Op.unitNode;
		typeNode vl = Op.unitNode, vr = Op.unitNode;
		for(l += length, r += length; l < r; l >>=1, r >>=1) {
			if(l&1) vl = Op.funcNode(vl,node[l++]);
			if(r&1) vr = Op.funcNode(node[--r],vr);
		}
		return Op.funcNode(vl,vr);
	}

	//return [0,length]
	int PrefixBinarySearch(typeNode var) {
		if(!Op.funcCheck(node[1],var)) return num;
		typeNode ret = Op.unitNode;
		size_t idx = 2;
		for(; idx < 2*length; idx<<=1){
			if(!Op.funcCheck(Op.funcNode(ret,node[idx]),var)) {
				ret = Op.funcNode(ret,node[idx]);
				idx++;
			}
		}
		return min((idx>>1) - length,num);
	}

	//range[l,r) return [l,r]
	int BinarySearch(size_t l, size_t r, typeNode var) {
		if (l < 0 || length <= l || r < 0 || length < r) return -1;
		typeNode ret = Op.unitNode;
		size_t off = l;
		for(size_t idx = l+length; idx < 2*length && off < r; ){
			if(range[idx].second<=r && !Op.funcCheck(Op.funcNode(ret,node[idx]),var)) {
				ret = Op.funcNode(ret,node[idx]);
				off = range[idx++].second;
				if(!(idx&1)) idx >>= 1;			
			}
			else{
				idx <<=1;
			}
		}
		return off;
	}

	void print(){
		cout << "{ " << get(0,1);
		for(int i = 1; i < length; ++i) cout << ", " << get(i,i+1);
		cout << " }" << endl;

		// for(int i = 1,j = 1; i < 2*length; ++i) {
		// 	cout << node[i] << " ";
		// 	if(i==((1<<j)-1) && ++j) cout << endl;
		// }
	}

};

template<class typeNode> struct nodeUpdateRangeOr {
	typeNode unitNode = 0;
	typeNode funcNode(typeNode l,typeNode r){return (l|r);}
	typeNode funcMerge(typeNode l,typeNode r){return r;}
};

//Digit Sum
long long DigitSum(long long N, long long K) {
    long long sum = 0;
    for (; N > 0; N /= K) sum += N % K;
    return sum;
}

int main() {
    int N; cin >> N;
    string S; cin >> S;
    SegmentTree<nodeUpdateRangeOr<ll>> seg(N);
    for(int i = 0; i < N; ++i){
        int c = S[i]-'a';
        seg.update(i,1<<c);
    }
    int Q; cin >> Q;
    for(int i = 0; i < Q; ++i){
        int q; cin >> q;
        if(q==1){
            int a;
            char d;
            cin >> a >> d;
            int b = d-'a';
            a--;
            seg.update(a,1<<b);
        }
        else{
            int l,r; cin >> l >> r;
            l--;
            cout << DigitSum(seg.get(l,r),2) << endl;
        }
    }


    return 0;
}
