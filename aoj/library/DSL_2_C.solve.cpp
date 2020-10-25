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
 * @title KdTree
 * @docs md/geometory/KdTree.md
 */
template<class T> class KdTree{
    struct Point{
        T x,y;
        int idx;
        friend ostream &operator<<(ostream &os, const Point& point) {return os << "{" << point.x << ", " << point.y << ", " << point.idx << "}";}
    };
    struct Node{
        int depth,ch_l,ch_r;
        Point point;
        Node(const Point point,const int depth):point(point),depth(depth),ch_l(-1),ch_r(-1){};
    };
    vector<Node> tree;

    //[l,r)
    void dfs(int depth, int l, int r, vector<Point>& points) {
        if(r-l==1) {
            tree.push_back(Node(points[l],depth));
            return;
        }
        int m = (l+r)/2;
        int root = tree.size();
        if(depth&1) sort(points.begin()+l,points.begin()+r,[&](Point a,Point b){return a.y < b.y;});
        else        sort(points.begin()+l,points.begin()+r,[&](Point a,Point b){return a.x < b.x;});
        tree.push_back(Node(points[m],depth));
        if(l<m) {
            tree[root].ch_l = tree.size();
            dfs(depth+1,l,m,points);
        }
        if(m+1<r) {
            tree[root].ch_r = tree.size();
            dfs(depth+1,m+1,r,points);
        }
    }
    void print(int p) {
        if(p==-1) return;
        print(tree[p].ch_l);
        cout << p << ", " << tree[p].point << ", ";
        print(tree[p].ch_r);
        if(p==0) cout << endl;
    }
public:
    //(x,y)のvector
    KdTree(const vector<pair<T,T>>& arg_points) {
        vector<Point> points(arg_points.size());
        for(int i=0;i<arg_points.size();++i) points[i] = {arg_points[i].first,arg_points[i].second,i};
        dfs(0,0,points.size(),points);
    }
    void print() {
        print(0);
    }
    //x区間[x1,x2],y区間[y1,y2]に囲まれる領域内の数 x1<=x2 && y1 <= y2
    vector<Point> points_in_range(const T& x1,const T& x2,const T& y1,const T& y2) {
        vector<Point> ret;
        stack<int> st; st.push(0);
        while(st.size()) {
            int p=st.top(); st.pop();
            if(x1<=tree[p].point.x&&tree[p].point.x<=x2&&y1<=tree[p].point.y&&tree[p].point.y<=y2) {
                ret.emplace_back(tree[p].point);
            }
            if(tree[p].depth&1) {//y
                if(tree[p].ch_r!=-1 && tree[p].point.y <= y2) st.push(tree[p].ch_r);
                if(tree[p].ch_l!=-1 && y1 <= tree[p].point.y) st.push(tree[p].ch_l);
            }
            else {               //x
                if(tree[p].ch_r!=-1 && tree[p].point.x <= x2) st.push(tree[p].ch_r);
                if(tree[p].ch_l!=-1 && x1 <= tree[p].point.x) st.push(tree[p].ch_l);
            }
        }
        sort(ret.begin(),ret.end(),[&](Point l,Point r){return l.idx < r.idx;});
        return ret;
    }
};

int main() {
    int N; 
    scanf("%d",&N);
    vector<pair<int,int>> points(N);
    for(int i=0;i<N;++i) {
        int x,y;
        scanf("%d%d",&x,&y);
        points[i]={x,y};
    }
    KdTree<int> kdtree(points);
    int Q;
    scanf("%d",&Q);
    while(Q--) {
        int x1,x2,y1,y2;
        scanf("%d%d%d%d",&x1,&x2,&y1,&y2);
        auto v = kdtree.points_in_range(x1,x2,y1,y2);
        for(auto& e:v) cout << e.idx << "\n";
        cout << "\n";
    }
    return 0;
}
