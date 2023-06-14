#include <bits/stdc++.h>
using namespace std;
using int128 = __int128_t;
using int64 = long long;

#define ALL(obj) (obj).begin(),(obj).end()

/*
 * @title FastIO
 * @docs md/util/FastIO.md
 */
class FastIO{
private:
    inline static constexpr int ch_0='0';
    inline static constexpr int ch_9='9';
    inline static constexpr int ch_n='-';
    inline static constexpr int ch_s=' ';
    inline static constexpr int ch_l='\n';
    inline static void endline_skip(char& ch) {
        while(ch==ch_l) ch=getchar();
    }
    template<typename T> inline static void read_integer(T &x) {
        int neg=0; char ch; x=0;
        ch=getchar();
        endline_skip(ch);
        if(ch==ch_n) neg=1,ch=getchar();
        for(;(ch_0 <= ch && ch <= ch_9); ch = getchar()) x = x*10 + (ch-ch_0);
        if(neg) x*=-1;
    }
    template<typename T> inline static void read_unsigned_integer(T &x) {
        char ch; x=0;
        ch=getchar();
        endline_skip(ch);
        for(;(ch_0 <= ch && ch <= ch_9); ch = getchar()) x = x*10 + (ch-ch_0);
    }
    inline static void read_string(string &x) {
        char ch; x="";
        ch=getchar();
        endline_skip(ch);
        for(;(ch != ch_s && ch!=ch_l); ch = getchar()) x.push_back(ch);
    }
    inline static char ar[40];
    inline static char *ch_ar;
    template<typename T> inline static void write_integer(T x) {
        ch_ar=ar;
        if(x< 0) putchar(ch_n), x=-x;
        if(x==0) putchar(ch_0);
        for(;x;x/=10) *ch_ar++=(ch_0+x%10);
        while(ch_ar--!=ar) putchar(*ch_ar);
    }
public:
    inline static void read(int &x) {read_integer<int>(x);}
    inline static void read(long long &x) {read_integer<long long>(x);}
    inline static void read(unsigned int &x) {read_unsigned_integer<unsigned int>(x);}
    inline static void read(unsigned long long &x) {read_unsigned_integer<unsigned long long>(x);}
    inline static void read(string &x) {read_string(x);}
    inline static void read(__int128_t &x) {read_integer<__int128_t>(x);}
    inline static void write(__int128_t x) {write_integer<__int128_t>(x);}
    inline static void write(char x) {putchar(x);}
};
#define read(arg) FastIO::read(arg)
#define write(arg) FastIO::write(arg)

template<class T> using priority_queue_reverse = priority_queue<T,vector<T>,greater<T>>;

constexpr int64 HIGHINF = 1'000'000'000'000'000'000LL;
constexpr int64 LOWINF = 1'000'000'000'000'000LL; //'
constexpr long double PI = 3.1415926535897932384626433L;

template <class T> vector<T> multivector(size_t N,T init){return vector<T>(N,init);}
template <class... T> auto multivector(size_t N,T... t){return vector<decltype(multivector(t...))>(N,multivector(t...));}
template <class T> void corner(bool flg, T hoge) {if (flg) {cout << hoge << endl; exit(0);}}
template <class T, class U>ostream &operator<<(ostream &o, const map<T, U>&obj) {o << "{"; for (auto &x : obj) o << " {" << x.first << " : " << x.second << "}" << ","; o << " }"; return o;}
template <class T>ostream &operator<<(ostream &o, const set<T>&obj) {o << "{"; for (auto itr = obj.begin(); itr != obj.end(); ++itr) o << (itr != obj.begin() ? ", " : "") << *itr; o << "}"; return o;}
template <class T>ostream &operator<<(ostream &o, const multiset<T>&obj) {o << "{"; for (auto itr = obj.begin(); itr != obj.end(); ++itr) o << (itr != obj.begin() ? ", " : "") << *itr; o << "}"; return o;}
template <class T>ostream &operator<<(ostream &o, const vector<T>&obj) {o << "{"; for (int i = 0; i < (int)obj.size(); ++i)o << (i > 0 ? ", " : "") << obj[i]; o << "}"; return o;}
template <class T>ostream &operator<<(ostream &o, const deque<T>&obj) {o << "{"; for (int i = 0; i < (int)obj.size(); ++i)o << (i > 0 ? ", " : "") << obj[i]; o << "}"; return o;}
template <class T, class U>ostream &operator<<(ostream &o, const pair<T, U>&obj) {o << "{" << obj.first << ", " << obj.second << "}"; return o;}
void print(void) {cout << endl;}
template <class Head> void print(Head&& head) {cout << head;print();}
template <class Head, class... Tail> void print(Head&& head, Tail&&... tail) {cout << head << " ";print(forward<Tail>(tail)...);}
template <class T> void chmax(T& a, const T b){a=max(a,b);}
template <class T> void chmin(T& a, const T b){a=min(a,b);}
vector<string> split(const string &str, const char delemiter) {vector<string> res;stringstream ss(str);string buffer; while( getline(ss, buffer, delemiter) ) res.push_back(buffer); return res;}
inline constexpr int msb(int x) {return x?31-__builtin_clz(x):-1;}
inline constexpr int64 ceil_div(const int64 a,const int64 b) {return (a+(b-1))/b;}// return ceil(a/b)
void YN(bool flg) {cout << (flg ? "YES" : "NO") << endl;}
void Yn(bool flg) {cout << (flg ? "Yes" : "No") << endl;}
void yn(bool flg) {cout << (flg ? "yes" : "no") << endl;}

/*
 * @title ModInt
 * @docs md/util/ModInt.md
 */
template<long long mod> class ModInt {
public:
    long long x;
    constexpr ModInt():x(0) {}
    constexpr ModInt(long long y) : x(y>=0?(y%mod): (mod - (-y)%mod)%mod) {}
    constexpr ModInt &operator+=(const ModInt &p) {if((x += p.x) >= mod) x -= mod;return *this;}
    constexpr ModInt &operator+=(const long long y) {ModInt p(y);if((x += p.x) >= mod) x -= mod;return *this;}
    constexpr ModInt &operator+=(const int y) {ModInt p(y);if((x += p.x) >= mod) x -= mod;return *this;}
    constexpr ModInt &operator-=(const ModInt &p) {if((x += mod - p.x) >= mod) x -= mod;return *this;}
    constexpr ModInt &operator-=(const long long y) {ModInt p(y);if((x += mod - p.x) >= mod) x -= mod;return *this;}
    constexpr ModInt &operator-=(const int y) {ModInt p(y);if((x += mod - p.x) >= mod) x -= mod;return *this;}
    constexpr ModInt &operator*=(const ModInt &p) {x = (x * p.x % mod);return *this;}
    constexpr ModInt &operator*=(const long long y) {ModInt p(y);x = (x * p.x % mod);return *this;}
    constexpr ModInt &operator*=(const int y) {ModInt p(y);x = (x * p.x % mod);return *this;}
    constexpr ModInt &operator^=(const ModInt &p) {x = (x ^ p.x) % mod;return *this;}
    constexpr ModInt &operator^=(const long long y) {ModInt p(y);x = (x ^ p.x) % mod;return *this;}
    constexpr ModInt &operator^=(const int y) {ModInt p(y);x = (x ^ p.x) % mod;return *this;}
    constexpr ModInt &operator/=(const ModInt &p) {*this *= p.inv();return *this;}
    constexpr ModInt &operator/=(const long long y) {ModInt p(y);*this *= p.inv();return *this;}
    constexpr ModInt &operator/=(const int y) {ModInt p(y);*this *= p.inv();return *this;}
    constexpr ModInt operator=(const int y) {ModInt p(y);*this = p;return *this;}
    constexpr ModInt operator=(const long long y) {ModInt p(y);*this = p;return *this;}
    constexpr ModInt operator-() const {return ModInt(-x); }
    constexpr ModInt operator++() {x++;if(x>=mod) x-=mod;return *this;}
    constexpr ModInt operator--() {x--;if(x<0) x+=mod;return *this;}
    constexpr ModInt operator+(const ModInt &p) const { return ModInt(*this) += p; }
    constexpr ModInt operator-(const ModInt &p) const { return ModInt(*this) -= p; }
    constexpr ModInt operator*(const ModInt &p) const { return ModInt(*this) *= p; }
    constexpr ModInt operator/(const ModInt &p) const { return ModInt(*this) /= p; }
    constexpr ModInt operator^(const ModInt &p) const { return ModInt(*this) ^= p; }
    constexpr bool operator==(const ModInt &p) const { return x == p.x; }
    constexpr bool operator!=(const ModInt &p) const { return x != p.x; }
    // ModInt inv() const {int a=x,b=mod,u=1,v=0,t;while(b > 0) {t = a / b;swap(a -= t * b, b);swap(u -= t * v, v);} return ModInt(u);}
    constexpr ModInt inv() const {int a=x,b=mod,u=1,v=0,t=0,tmp=0;while(b > 0) {t = a / b;a-=t*b;tmp=a;a=b;b=tmp;u-=t*v;tmp=u;u=v;v=tmp;} return ModInt(u);}
    constexpr ModInt pow(long long n) const {ModInt ret(1), mul(x);for(;n > 0;mul *= mul,n >>= 1) if(n & 1) ret *= mul;return ret;}
    friend ostream &operator<<(ostream &os, const ModInt &p) {return os << p.x;}
    friend istream &operator>>(istream &is, ModInt &a) {long long t;is >> t;a = ModInt<mod>(t);return (is);}
};
constexpr long long MOD_998244353 = 998244353;
constexpr long long MOD_1000000007 = 1'000'000'000LL + 7; //'

/*
 * @title UnionFindTree - Union Find 木
 * @docs md/graph/UnionFindTree.md
 */
class UnionFindTree {
    vector<int> parent,maxi,mini;
    inline int root(int n) {
        return (parent[n]<0?n:parent[n] = root(parent[n]));
    }
public:
    UnionFindTree(const int N = 1) : parent(N,-1),maxi(N),mini(N){
        iota(maxi.begin(),maxi.end(),0);
        iota(mini.begin(),mini.end(),0);
    }
    inline bool connected(const int n, const int m) {
        return root(n) == root(m);
    }
    inline void merge(int n,int m) {
        n = root(n);
        m = root(m);
        if (n == m) return;
        if(parent[n]>parent[m]) swap(n, m);
        parent[n] += parent[m];
        parent[m] = n;
        maxi[n] = std::max(maxi[n],maxi[m]);
        mini[n] = std::min(mini[n],mini[m]);
    }
    inline int min(const int n) {
        return mini[root(n)];
    }
    inline int max(const int n) {
        return maxi[root(n)];
    }
    inline int size(const int n){
        return (-parent[root(n)]);
    }
    inline int operator[](const int n) {
        return root(n);
    }
    inline void print() {
        for(int i = 0; i < parent.size(); ++i) cout << root(i) << " ";
        cout << endl;
    }
};

/*
 * @title KdTree - 2次元頂点分類木
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

class XorShift{
	unsigned int x,y,z,w;
public:
	XorShift():x(123456789),y(362436069),z(521288629),w(88675123){}
	unsigned int rand() {
		unsigned int t = (x ^ (x << 11)); x = y; y = z; z = w;
		return (w = (w ^ (w >> 19)) ^ (t ^ (t >> 8)));
	}
};

int64 calc_value(const vector<int>& P, const vector<int>& B, const vector<int64>& W, int n, int K) {
    if (n < K) {
        return 1000'000LL * double(n+1) / K;
    }
    else {
        int64 S = 0;
        for(int64 p: P) S += p*p;
        for(int i=0;i<B.size(); ++i) if(B[i]) S += W[i];
        return 1000'000LL * (1LL + 100'000'000.0 / (S + 10'000'000LL));
    }
}

/**
 * @url 
 * @est
 */ 
int main() {
    cin.tie(0);ios::sync_with_stdio(false);
    int64 N,M,K; read(N); read(M); read(K);
    vector<int64> X(N),Y(N),U(M),V(M),W(M);
    for(int i=0;i<N;++i) read(X[i]), read(Y[i]);
    for(int i=0;i<M;++i) {
        read(U[i]), read(V[i]), read(W[i]);
        U[i]--;
        V[i]--;
    }
    vector<pair<int64,int64>> vp(K);
    for(int i=0;i<K;++i) {
        int64 a,b; read(a), read(b);
        vp[i]={a,b};
    }
    KdTree<int64> tree(vp);

    vector<int> ans_P;
    vector<int> ans_B;
    int64 ans_value=0;

    vector<int> idx_base(N);
    iota(ALL(idx_base),0);
    
    std::random_device seed_gen;
    std::mt19937 engine(seed_gen());
    XorShift xs;
    const int MAX_P = 5000;
    const int MAIN_P = 3500;

    chrono::system_clock::time_point start, end;
	double diff,max_diff = 1900;//ms
    start = chrono::system_clock::now();

    int num_mini = 40;
    int num_main = 100;
    int num_maxi = 100;

    while(1) {

        //-------------------------------------
 		end = chrono::system_clock::now();
		diff = (chrono::duration_cast<chrono::microseconds>(end - start).count() / 1000.0);
		if(diff > max_diff) break;
        //-------------------------------------
        unsigned int rn_num = xs.rand();
        int num = 0;
        if(rn_num % 10 == 0) {
            num = rn_num % (num_maxi - num_mini + 1) + num_mini;
        }
        else {
            num = rn_num % (num_main - num_mini + 1) + num_mini;
        }

        //初期化
        vector<int> P(N,0);
        vector<int> B(M,0);
        set<int> st;
        vector<set<int>> vst(N);
        int64 cost = 0;

        auto idx=idx_base;
        //シャッフル。
        std::shuffle(idx.begin(), idx.end(), engine);
        //prefix num頂点を採用する
        for(int i=0;i<num;++i) P[idx[i]]=1;

        //N頂点の最小全域木を作る
        UnionFindTree uf(N);
        priority_queue_reverse<pair<int64,int>> pq;
        for(int i=0; i<M; ++i) {
            //u[i],v[i]が採用されてないならコストを100かける
            int64 coe=1;
            if(!P[U[i]]) coe *= 100;
            if(!P[V[i]]) coe *= 100;
            pq.push({coe*W[i], i});
        }
        while(pq.size()) {
            auto [_,i]=pq.top(); pq.pop();
            if(uf.connected(U[i],V[i])) continue;
            uf.merge(U[i],V[i]);
            B[i]=1;
            cost += W[i];
        }


        //頂点が決まってるので、強度を決める。
        for(int i=0;i<num;++i) {
            int j = idx[i];
            int64 x = X[j];
            int64 y = Y[j];
            for(int p_try=0;p_try<100;++p_try) {
                unsigned int rn = xs.rand();
                int p = rn%MAIN_P;
                int64 x1 = x - p/2;
                int64 x2 = x + p/2;
                int64 y1 = y - p/2;
                int64 y2 = y + p/2;
                auto points = tree.points_in_range(x1,x2,y1,y2);

                //どれぐらい得する?
                int cnt=0;
                for(auto& point: points) {
                    if(st.count(point.idx)) continue;
                    if(vst[j].count(point.idx)) continue;
                    cnt++;
                }
                if(!((cnt > vst[j].size()) || (cnt == vst[j].size() && p<P[j]))) {
                    continue;
                }
                set<int> tmp_st;
                for(auto& point: points) {
                    vst[j]=tmp_st;
                }
                P[j]=p;
            }
            for(int z: vst[j]) {
                st.insert(z);
            }
        }
        for(int i=0;i<num;++i) {
            int j = idx[i];
            int64 x = X[j];
            int64 y = Y[j];
            for(int p_try=0;p_try<5;++p_try) {
                unsigned int rn = xs.rand();
                int p = rn%MAX_P;
                int64 x1 = x - p/2;
                int64 x2 = x + p/2;
                int64 y1 = y - p/2;
                int64 y2 = y + p/2;
                auto points = tree.points_in_range(x1,x2,y1,y2);

                //どれぐらい得する?
                int cnt=0;
                for(auto& point: points) {
                    if(st.count(point.idx)) continue;
                    cnt++;
                }
                if(cnt == 0) {
                    continue;
                }
                set<int> tmp_st;
                for(auto& point: points) {
                    vst[j]=tmp_st;
                }
                P[j]=p;
            }
            for(int z: vst[j]) {
                st.insert(z);
            }
        }


        //最小全域木である必要はないので、無駄な葉を削除する
        vector<vector<int>> edge(N);
        vector<int> deg(N,0);
        for(int i=0;i<M;++i) {
            if(!B[i]) continue;
            edge[U[i]].push_back(i);
            edge[V[i]].push_back(i);
            deg[U[i]]++;deg[V[i]]++;
        }
        queue<int> q;
        for(int i=1;i<N;++i) if(deg[i]==1 && P[i]<=1) q.push(i);
        while(q.size()) {
            auto leaf = q.front(); q.pop();
            if(leaf==0) continue;
            for(int i: edge[leaf]) {
                int u=U[i],v=V[i];
                B[i]=0;
                deg[u]--; deg[v]--;
                if(deg[u]==1 && P[u]<=1) q.push(u);
                if(deg[v]==1 && P[v]<=1) q.push(v);
            }
        }

        int64 tmp_value = calc_value(P,B,W,st.size(),K);

        if(tmp_value > ans_value) {
            ans_value = tmp_value;
            ans_P = P;
            ans_B = B;
        }

    }
    for(int i=0;i<N;++i) cout << ans_P[i] << " \n"[i==N-1];
    for(int i=0;i<M;++i) cout << ans_B[i] << " \n"[i==M-1];

    return 0;
}
