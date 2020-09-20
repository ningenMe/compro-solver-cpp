#include <vector>
#include <iostream>
#include <numeric>
#include <algorithm>
#include <stack>
using namespace std;

/*
 * @title StronglyConnectedComponents
 */
class StronglyConnectedComponents{
	int num,is_2sat,half,max_id,cnt;
	vector<vector<int>> edge;
	vector<int> label,order,low;
    stack<size_t> st;
	inline int rev(int i) { return i < half ? i + half : i - half; }
    inline void dfs(int& from) {
        low[from]=order[from]=cnt++;
        st.push(from);
        for(int& to:edge[from]) {
            if(order[to]==-1) {
                dfs(to);
                low[from]=min(low[from],low[to]);
            }
            else {
                low[from]=min(low[from],order[to]);
            }
        }
        if (low[from] == order[from]) {
            while(st.size()) {
                int u = st.top();st.pop();
                order[u] = num;
                label[u] = max_id;
                if (u == from) break;
            }
            max_id++;
        }
    }
public:
	StronglyConnectedComponents(const int n, bool is_2sat=0):num(n),max_id(0),cnt(0),is_2sat(is_2sat){
		if(is_2sat) num<<=1;
		edge.resize(num);
		label.resize(num);
        order.resize(num,-1);
        low.resize(num);
        half=(num>>1);
	}
	inline int operator[](int idx) {
		return label[idx];
	}
	inline void make_edge(const int from,const int to) {
		edge[from].push_back(to);
	}
    //xがflg_xならばyがflg_y
	inline void make_condition(int x, bool flg_x, int y, bool flg_y) {
		if (!flg_x) x = rev(x);
		if (!flg_y) y = rev(y);
		make_edge(x, y);
		make_edge(rev(y), rev(x));
	}
    //is_2sat=1のときに、2satを満たすかを返却する
	inline bool solve(void) {
        for (int i = 0; i < num; i++) if (order[i] == -1) dfs(i);
        for (int& id:label) id = max_id-1-id;
		if(!is_2sat) return true;
		for (int i = 0; i < num; ++i) if (label[i] == label[rev(i)]) return false;
		return true;
	}
    vector<vector<int>> topological_sort(void) {
        vector<vector<int>> ret(max_id);
        for(int i=0;i<num;++i) ret[label[i]].push_back(i);
        return ret;
    }
	int is_true(int i) {
		return label[i] > label[rev(i)];
	}
	void print(void) {
		for(auto id:label) cout << id << " ";
		cout << endl;
	}
};

int main(){
    cin.tie(0);ios::sync_with_stdio(false);
    int N,D; cin >> N >> D;
    StronglyConnectedComponents scc(N,1);
    vector<int> X(2*N);
    for(int i=0;i<N;++i) cin >> X[i] >> X[i+N];
    for(int i=0;i<2*N;++i) {
        for(int j=0;j<2*N;++j) {
            if(i==j||abs(i-j)==N) continue;
            if(abs(X[i]-X[j])<D) scc.make_condition(i%N,(i<N),j%N,!(j<N));
        }
    }
    bool f=scc.solve();
    if(f) {
        cout << "Yes\n";
        for(int i=0;i<N;++i) {
            cout << (scc.is_true(i)?X[i]:X[i+N]) << "\n";
        }
    }
    else{
        cout << "No\n";
    }
    return 0;
}
