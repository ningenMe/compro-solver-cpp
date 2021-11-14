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
void YN(bool flg) {cout << (flg ? "YES" : "NO") << endl;}
void Yn(bool flg) {cout << (flg ? "Yes" : "No") << endl;}
void yn(bool flg) {cout << (flg ? "yes" : "no") << endl;}

//Union Find Tree
class UnionFindTreeSize {
public:
	vector<int> parent;
    vector<int> maxidx;
    vector<int> minidx;

    UnionFindTreeSize(int N = 1) : parent(N,-1),maxidx(N),minidx(N){
        iota(maxidx.begin(),maxidx.end(),0);
        iota(minidx.begin(),minidx.end(),0);
	}
 
	int root(int n) {
        return (parent[n]<0?n:parent[n] = root(parent[n]));
	}

    bool same(int n, int m) {
		return root(n) == root(m);
	}

    int mini(int n) {
        return minidx[root(n)];
    }

    int maxi(int n) {
        return maxidx[root(n)];
    }
 
	void unite(int n, int m) {
		n = root(n);
		m = root(m);
		if (n == m) return;
		if(parent[n]>parent[m]) swap(n, m);
        parent[n] += parent[m];
        parent[m] = n;
        maxidx[n] = max(maxidx[n],maxidx[m]);
        minidx[n] = min(minidx[n],minidx[m]);
	}

    int size(int n){
        return (-parent[root(n)]);
    }

    void print() {
        for(int i = 0; i < parent.size(); ++i) cout << root(i) << " ";
        cout << endl;
    }
};

int main() {
    SPEED
    int N,M; cin >> N >> M;
    vector<ll> A(M),B(M),C(M),T(M);
    for(int i = 0; i < M; ++i) cin >> A[i] >> B[i] >> C[i] >> T[i];
    double ok = 1e9, ng = 0, md;
    for(int n=0;n<500;++n) {
        md=(ok+ng)/2;
        PQR<pair<double,int>> pq;
        for(int i=0;i<M;++i) {
            pq.push({C[i]-T[i]*md,i});
        }

        double cs=0,ts=0;
        UnionFindTreeSize uf(N);
        while(pq.size()) {
            auto p = pq.top(); pq.pop();
            int i=p.second;
            if(p.first<=0) {
                uf.unite(A[i],B[i]);
                cs += C[i];
                ts += T[i];
            }
            else {
                if(!uf.same(A[i],B[i])) {
                    uf.unite(A[i],B[i]);
                    cs += C[i];
                    ts += T[i];
                }
            }
        }
        (cs <= ts * md ? ok : ng) = md;
    }
    printf("%.10f",ok);
    return 0;
}
