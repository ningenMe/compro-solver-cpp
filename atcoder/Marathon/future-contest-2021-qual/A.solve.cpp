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

class XorShift{
	unsigned int x,y,z,w;
public:
	XorShift():x(123456789),y(362436069),z(521288629),w(88675123){}
	unsigned int rand() {
		unsigned int t = (x ^ (x << 11)); x = y; y = z; z = w;
		return (w = (w ^ (w >> 19)) ^ (t ^ (t >> 8)));
	}
};

constexpr int H = 20;
constexpr int W = 20;
constexpr int N = 100;
constexpr int FIRST_PQ_SIZE = 150;
constexpr int SECOND_PQ_SIZE = 80;
constexpr int THIRD_PQ_SIZE = 30;
constexpr int COST_DIFF_THRESHOLD = 30;
constexpr int STATE_MOVE_WIDTH = 40;
constexpr int NEAR_SEARCH_WIDTH = 15; // manhattan dist
constexpr int FIRST  = 10;
constexpr int SECOND = 40;
constexpr int THIRD = 100;
XorShift xor_shift;

struct State {
    int y,x;
    array<int,H*W> grid;
    array<int,N> cy;
    array<int,N> cx;
    stack<int> st;
    string op;
    int cost;
    int near_sum;
    State(){
        y=0;x=0;cost=0;near_sum=0;op="";
        for(int i=0;i<H;++i) for(int j=0;j<W;++j) grid[i*W+j]=-1;
        for(int i=0;i<N;++i) cy[i]=cx[i]=-1;
    }
    inline bool is_collected(int p) {
        return (cy[p]==-1||cx[p]==-1);
    }
    inline void move_r(const int d) {
        x+=d;
        cost+=d;
        op+=string(d,'R');
    }
    inline void move_l(const int d) {
        x-=d;
        cost+=d;
        op+=string(d,'L');
    }
    inline void move_u(const int d) {
        y-=d;
        cost+=d;
        op+=string(d,'U');
    }
    inline void move_d(const int d) {
        y+=d;
        cost+=d;
        op+=string(d,'D');
    }
    inline void move_random() {   
        int rand = xor_shift.rand()&1;
        for(int i=0; i<=H*W;++i) {
            for(int sy=0;sy<=i;++sy) {
                int sx=i-sy;
                if(rand==0&&y+sy<H&&x+sx<W&&grid[(y+sy)*W+x+sx]==-1) {
                    move_d(sy);                    
                    move_r(sx);                    
                    return;
                }
                else if(rand==0&&sy<=y&&x+sx<W&&grid[(y-sy)*W+x+sx]==-1) {
                    move_u(sy);                    
                    move_r(sx);                    
                    return;
                }
                else if(rand==1&&sy<=y&&sx<=x&&grid[(y-sy)*W+x-sx]==-1) {
                    move_u(sy);                    
                    move_l(sx);                    
                    return;
                }
                else if(rand==1&&y+sy<H&&sx<=x&&grid[(y+sy)*W+x-sx]==-1) {
                    move_d(sy);                    
                    move_l(sx);                    
                    return;
                }
            }
        }

    }
    inline void push() {
        int p = grid[y*W+x];
        op.push_back('I');
        cy[p]=cx[p]=-1;
        grid[y*W+x]=-1;
        st.push(p);
    }
    inline void pop() {

        if(grid[y*W+x]!=-1) return;

        int p = st.top();
        st.pop();
        op.push_back('O');
        cy[p]=y,cx[p]=x;
        grid[y*W+x]=p;
    }    
    inline int dx(int p) {
        return cx[p]-x;
    }
    inline int dy(int p) {
        return cy[p]-y;
    }
    inline void near_search() {
        for(int i=0; i<=NEAR_SEARCH_WIDTH;++i) {
            for(int sy=0;sy<=i;++sy) {
                int sx=i-sy;
                if(y+sy<H&&x+sx<W&&grid[(y+sy)*W+x+sx]!=-1) {
                    move_d(sy);                    
                    move_r(sx);                    
                    push();
                    ++near_sum;
                    return;
                }
                else if(sy<=y&&x+sx<W&&grid[(y-sy)*W+x+sx]!=-1) {
                    move_u(sy);                    
                    move_r(sx);                    
                    push();
                    ++near_sum;
                    return;
                }
                else if(y+sy<H&&sx<=x&&grid[(y+sy)*W+x-sx]!=-1) {
                    move_d(sy);                    
                    move_l(sx);                    
                    push();
                    ++near_sum;
                    return;
                }
                else if(sy<=y&&sx<=x&&grid[(y-sy)*W+x-sx]!=-1) {
                    move_u(sy);                    
                    move_l(sx);                    
                    push();
                    ++near_sum;
                    return;
                }
            }
        }
    }
    inline int get_grid() {
        return grid[y*W+x];
    }
};

struct FirstState : State{
    bool operator<(const State& s) const {
        return near_sum > s.near_sum;
    }
    FirstState(){}
    FirstState(State state) {
        y=state.y;
        x=state.x;
        grid=state.grid;
        cy=state.cy;
        cx=state.cx;
        st=state.st;
        op=state.op;
        cost=state.cost;
        near_sum=state.near_sum;
    }
};
struct SecondState : State{
    bool operator<(const State& s) const {
        return (abs(cost-s.cost) > COST_DIFF_THRESHOLD ?cost < s.cost:near_sum > s.near_sum);
    }
    SecondState(State state) {
        y=state.y;
        x=state.x;
        grid=state.grid;
        cy=state.cy;
        cx=state.cx;
        st=state.st;
        op=state.op;
        cost=state.cost;
        near_sum=state.near_sum;
    }
};
struct ThirdState : State{
    bool operator<(const State& s) const {
        return cost < s.cost;
    }
    ThirdState(State state) {
        y=state.y;
        x=state.x;
        grid=state.grid;
        cy=state.cy;
        cx=state.cx;
        st=state.st;
        op=state.op;
        cost=state.cost;
        near_sum=state.near_sum;
    }
};


// stackにpをpush
void collect(State& state,int p,int near_search = 0) {
    if(state.is_collected(p)) return;
    while(state.dx(p) != 0 || state.dy(p) != 0) {

        if(near_search) state.near_search();
        if(state.is_collected(p)) return;

        int dx = state.dx(p);
        int adx = abs(dx);
        if(dx > 0) state.move_r(1);
        if(dx < 0) state.move_l(1);

        if(near_search) state.near_search();
        if(state.is_collected(p)) return;

        int dy = state.dy(p);
        int ady = abs(dy);
        if(dy > 0) state.move_d(1);
        if(dy < 0) state.move_u(1);
    }
    if(state.get_grid()!=-1) {
        state.push();
    }
}

// stackが[0,r)になるように近くに置く
void release(State& state,int r) {
    while(state.st.size() > r) {
        state.pop();
        if(state.st.size() > r)state.move_random();
    }
}

void transition(State tmp_state,int i,vector<priority_queue<FirstState>>& state_list1, vector<priority_queue<SecondState>>& state_list2,vector<priority_queue<ThirdState>>& state_list3) {
    {
        auto state=tmp_state;
        collect(state,i);

        if(i+1<=FIRST) {
            state_list1[i+1].push(state);
            if(i+1<N&&state_list1[i+1].size() > FIRST_PQ_SIZE) state_list1[i+1].pop();                
        }
        else if(FIRST < i+1&&i+1 <= SECOND) {
            state_list2[i+1].push(state);
            if(i+1<N&&state_list2[i+1].size() > SECOND_PQ_SIZE) state_list2[i+1].pop();                
        }
        else if(SECOND < i+1&&i+1 <= THIRD) {
            state_list3[i+1].push(state);
            if(i+1<N&&state_list3[i+1].size() > THIRD_PQ_SIZE) state_list3[i+1].pop();                
        }
    }

    for(int j=i+1; j<=min(i+STATE_MOVE_WIDTH,N);++j) {

        auto state = tmp_state;
        for(int k=i;k<j;++k) collect(state,k,1);
        release(state,i);
        for(int k=i;k<j;++k) collect(state,k);

        {
            if(j<=FIRST) {
                state_list1[j].push(state);
                if(j<N&&state_list1[j].size() > FIRST_PQ_SIZE) state_list1[j].pop();
            }
            else if(FIRST < j&&j <= SECOND) {
                state_list2[j].push(state);
                if(i+1<N&&state_list2[j].size() > SECOND_PQ_SIZE) state_list2[j].pop();                
            }
            else if(SECOND < j&&j <= THIRD) {
                state_list3[j].push(state);
                if(i+1<N&&state_list3[j].size() > THIRD_PQ_SIZE) state_list3[j].pop();                
            }
        }
    }

}

int main() {
    cin.tie(0);ios::sync_with_stdio(false);
    vector<priority_queue<FirstState>>  state_list1(N+1);
    vector<priority_queue<SecondState>> state_list2(N+1);
    vector<priority_queue<ThirdState>>  state_list3(N+1);
    FirstState init_state;

    for(int i=0;i<N;++i) {
        int cy,cx;
        cin >> cy >> cx;
        init_state.cy[i]=cy;
        init_state.cx[i]=cx;
        init_state.grid[cy*W+cx]=i;
    }

    state_list1[0].push(init_state);

    for(int i=0;i<N;++i) {
        while(state_list1[i].size()) {
            auto tmp_state = state_list1[i].top(); 
            state_list1[i].pop();
            transition(tmp_state,i,state_list1,state_list2,state_list3);
        }
        while(state_list2[i].size()) {
            auto tmp_state = state_list2[i].top(); 
            state_list2[i].pop();
            transition(tmp_state,i,state_list1,state_list2,state_list3);
        }
        while(state_list3[i].size()) {
            auto tmp_state = state_list3[i].top(); 
            state_list3[i].pop();
            transition(tmp_state,i,state_list1,state_list2,state_list3);
        }
    }

    int cost = 12345678;    
    State ans;
    while(state_list3[N].size()) {
        auto state = state_list3[N].top();
        state_list3[N].pop();
        if(cost>state.cost) {
            cost = state.cost;
            ans = state;
        }
    }
    cout << ans.op << "\n";
    return 0;
}
