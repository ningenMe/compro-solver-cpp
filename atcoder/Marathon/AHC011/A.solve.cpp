#include <bits/stdc++.h>
using namespace std;
using int128 = __int128_t;
using int64 = long long;

#define ALL(obj) (obj).begin(),(obj).end()
template<class T> using priority_queue_reverse = priority_queue<T,vector<T>,greater<T>>;

constexpr int64 MOD = 1'000'000'000LL + 7; //'
constexpr int64 MOD2 = 998244353;
constexpr int64 HIGHINF = 1'000'000'000'000'000'000LL;
constexpr int64 LOWINF = 1'000'000'000'000'000LL; //'
constexpr long double PI = 3.1415926535897932384626433L;

template <class T> vector<T> multivector(size_t N,T init){return vector<T>(N,init);}
template <class... T> auto multivector(size_t N,T... t){return vector<decltype(multivector(t...))>(N,multivector(t...));}
template <class T> void corner(bool flg, T hoge) {if (flg) {cout << hoge << endl; exit(0);}}
template <class T, class U>ostream &operator<<(ostream &o, const map<T, U>&obj) {o << "{"; for (auto &x : obj) o << " {" << x.first << " : " << x.second << "}" << ","; o << " }"; return o;}
template <class T, class U>ostream &operator<<(ostream &o, const unordered_map<T, U>&obj) {o << "{"; for (auto &x : obj) o << " {" << x.first << " : " << x.second << "}" << ","; o << " }"; return o;}
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
 * @title UnionFindTree - Union Find 木
 * @docs md/graph/UnionFindTree.md
 */
class UnionFindTree {
    vector<int> parent,weights;
    inline int root(int n) {
        return (parent[n]<0?n:parent[n] = root(parent[n]));
    }
public:
    UnionFindTree(int N, vector<int> weights) : parent(N,-1), weights(weights) {

    }
    inline bool connected(int n, int m) {
        return root(n) == root(m);
    }
    inline void merge(int n, int m) {
        n = root(n);
        m = root(m);
        if (n == m) return;
        if(parent[n]>parent[m]) swap(n, m);
        parent[n] += parent[m];
        parent[m] = n;
        weights[n] = weights[n] + weights[m];
    }
    inline int weight(int n) {
        return weights[root(n)];
    }
    inline int size(int n){
        return (-parent[root(n)]);
    }
    inline int operator[](int n) {
        return root(n);
    }
    inline void print() {
        for(int i = 0; i < parent.size(); ++i) cout << root(i) << " ";
        cout << endl;
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

int N;
int T;
const int score_const = 500000;
const int L = 0;
const int U = 1;
const int R = 2;
const int D = 3;
XorShift xorshift;
string LURD = "LURD";

using eval_type = pair<int,int>;

class State {
public:
    vector<vector<int>> grid;
    int y; 
    int x;
    string track;
    State(const vector<string>& t, const int N): track("") {
        unordered_map<char,int> ump;
        for(int i=0;i<10;++i) ump[char('0'+i)]=i;
        for(int i=0;i<10;++i) ump[char('a'+i)]=i+10;

        grid = multivector(N,N,0);
        for(int i=0;i<N;++i) for(int j=0;j<N;++j) {
            grid[i][j]=ump[t[i][j]];
            if(grid[i][j]==0) y=i,x=j;
        }
    }

    int size() {
        return track.size();
    }

    eval_type eval() const {
        vector<int> weights(5*N*N,0);
        for(int i=0;i<N;++i) for(int j=0;j<N;++j) if(grid[i][j]) weights[(i*N+j)*5+4] = 1;

        UnionFindTree uf(5*N*N, weights);
        for(int i=0;i<N;++i) {
            for(int j=0;j<N;++j) {
                int p = (i*N+j)*5;
                if( (grid[i][j]>>L) & 1 ) uf.merge(p+L,p+4);
                if( (grid[i][j]>>U) & 1 ) uf.merge(p+U,p+4);
                if( (grid[i][j]>>R) & 1 ) uf.merge(p+R,p+4);
                if( (grid[i][j]>>D) & 1 ) uf.merge(p+D,p+4);

                if(i+1<N) {
                    int q = ((i+1)*N+j)*5;
                    if( (grid[i][j]>>D) & (grid[i+1][j]>>U) ) {
                        if(uf.connected(p+D,q+U)) {
                            return {-N*N*N,-N*N*N};
                        }
                        uf.merge(p+D,q+U);
                    }
                }
                if(j+1<N) {
                    int q = (i*N+j+1)*5;
                    if( (grid[i][j]>>R) & (grid[i][j+1]>>L) ) {
                        if(uf.connected(p+R,q+L)) {
                            return {-N*N*N,-N*N*N};
                        }
                        uf.merge(p+R,q+L);
                    }
                }

            }
        }

        vector<int> tmp;
        for(int i=0;i<N;++i) for(int j=0;j<N;++j) tmp.push_back(uf.weight((i*N+j)*5+4));
        // int S = *max_element(ALL(tmp));
        // double dS = S;
        // double K = track.size();
        // return (S == N*N-1) ? (score_const * (2 - (K/T)) ) : (score_const * (dS / (N*N-1)) );
        int S = *max_element(ALL(tmp));
        int negative_count = 0;
        for(int i=0;i<N;++i) if((grid[i][0]  >>L)&1) negative_count--;
        for(int i=0;i<N;++i) if((grid[i][N-1]>>R)&1) negative_count--;
        for(int j=0;j<N;++j) if((grid[0][j]  >>U)&1) negative_count--;
        for(int j=0;j<N;++j) if((grid[N-1][j]>>D)&1) negative_count--;
        return {negative_count,S};
    }

    void trace(const string& directions) {
        for(char d:directions) trace(d);
    }

    void trace(const char& direction) {
        int ny=y,nx=x;
        if(direction=='L') nx=x-1;
        if(direction=='U') ny=y-1;
        if(direction=='R') nx=x+1;
        if(direction=='D') ny=y+1;
        {
            swap(grid[y][x],grid[ny][nx]);
            y=ny,x=nx;
            track.push_back(direction);
        }
    }

    void random_walk(const int turn) {
        for(int i=0;i<turn;++i) random_walk();
    }

    int random_walk() {
        int ny=y,nx=x;
        int ra1 = xorshift.rand()%3;
        int ra2 = xorshift.rand()%3;
        if(ra1==2) ra1=3;
        int p = get_prev_direction();
        int d = (p + ra1) % 4;
        if(d==L) nx--;
        if(d==U) ny--;
        if(d==R) nx++;
        if(d==D) ny++;
        if(!(0<=ny&&ny<N&&0<=nx&&nx<N)) return -1;
        if(y==0   && d==D && ((grid[ny][nx]>>U) & 1) && (ra2)) return -1;
        if(y==N-1 && d==U && ((grid[ny][nx]>>D) & 1) && (ra2)) return -1;
        if(x==0   && d==R && ((grid[ny][nx]>>L) & 1) && (ra2)) return -1;
        if(x==N-1 && d==L && ((grid[ny][nx]>>R) & 1) && (ra2)) return -1;
        {
            swap(grid[y][x],grid[ny][nx]);
            y=ny,x=nx;
            track.push_back(LURD[d]);
        }
        return d;
    }

    int get_prev_direction() {
        if(track=="") return 0;
        if(track.back()=='L') return L;
        if(track.back()=='U') return U;
        if(track.back()=='R') return R;
        if(track.back()=='D') return D;
    }
};

tuple<eval_type,string> turn_move(State state, int turn) {
    string directions;
    for(int i=0;i<turn;) {
        int d = state.random_walk();
        if(d==-1) continue;
        directions += LURD[d];
        ++i;
    }
    return {state.eval(),directions};
}

State get_max_eval_state(const vector<State>& states) {
    int m = states.size();
    vector<eval_type> evals(m);
    for(int i=0;i<m;++i) evals[i]=states[i].eval();
    int idx = max_element(ALL(evals))-evals.begin();
    return states[idx];
}


/**
 * @url 
 * @est
 */ 
int main() {
    //setup ----
    cin.tie(0);ios::sync_with_stdio(false);
    cin >> N >> T;
    vector<string> grid_string(N);
    for(int i=0;i<N;++i) cin >> grid_string[i];
    chrono::system_clock::time_point start, end;
	double diff,max_diff = 2900;//ms
    start = chrono::system_clock::now();
    //setup ----

    //init ----
    State init_state(grid_string,N);
    int parallel_size = 100;
    int init_random_walk_turn_size = 0;

    const int challenge_size = 3;
    array<int, challenge_size> random_walk_turn_sizes = {5,30,2};
    array<double, challenge_size> random_walk_turn_ratios = {0.1,0.9,0.0};
    array<double, challenge_size> challenge_time_diff_ratios = {0.3,0.5,0.1};
    array<int, challenge_size> eval_types = {1,0,0};

    //init ----

    //parallel ----
    vector<State> states(parallel_size, init_state);
    double challenge_time_sum = 0.0;
    for(auto& state: states) {
        state.random_walk(init_random_walk_turn_size);
        auto pre_ev = state.eval();

        // vector<int> tmp_v(1,0);
        //challenge
        double random_walk_turn_ratio_sum = 0.0;
        for(int i=0;i<challenge_size;++i) {
            double challenge_time_diff = max_diff / parallel_size * challenge_time_diff_ratios[i];
            random_walk_turn_ratio_sum += random_walk_turn_ratios[i];
            int max_turn_size = T * random_walk_turn_ratio_sum;
            for( ; state.size() + random_walk_turn_sizes[i] <= max_turn_size ;) {

                //-------------------------------------
                end = chrono::system_clock::now();
                diff = (chrono::duration_cast<chrono::microseconds>(end - start).count() / 1000.0);
                if(diff > challenge_time_sum + challenge_time_diff) break;
                //-------------------------------------

                auto [ev,directions] = turn_move(state,random_walk_turn_sizes[i]);
                if(eval_types[i]) {
                    if(pre_ev > ev) continue;
                } else {
                    if(make_pair(pre_ev.second,pre_ev.first) > make_pair(ev.second,ev.first)) continue;
                }
                pre_ev = ev;
                state.trace(directions);
            }
            challenge_time_sum += challenge_time_diff;
            // tmp_v.push_back(state.track.size());
        }
        // for(int i=0;i<challenge_size;++i) cout << tmp_v[i+1]-tmp_v[i] << " \n"[i==challenge_size-1];
    }

    //parallel ----
    auto max_eval_state = get_max_eval_state(states);
    cout << max_eval_state.track << "\n";
    return 0;
}
