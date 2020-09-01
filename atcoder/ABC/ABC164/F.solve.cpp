#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define ALL(obj) (obj).begin(),(obj).end()
template<class T> using priority_queue_reverse = priority_queue<T,vector<T>,greater<T>>;

constexpr long long MOD = 1'000'000'000LL + 7;
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

bool validate(const vector<int>& S,const vector<int>& U,const vector<int>& T,const vector<int>& V,const vector<vector<ll>>& grid) {
    int N = S.size();
    for(int i = 0; i < N; ++i) {
        if(S[i]==0) {
            int acc=1;
            for(int j = 0; j < N; ++j) acc &= grid[i][j];
            if(acc!=U[i]) return 0;
        }
        else {
            int acc=0;
            for(int j = 0; j < N; ++j) acc |= grid[i][j];
            if(acc!=U[i]) return 0;
        }
    }
    for(int j = 0; j < N; ++j) {
        if(T[j]==0) {
            int acc=1;
            for(int i = 0; i < N; ++i) acc &= grid[i][j];
            if(acc!=V[j]) return 0;
        }
        else {
            int acc=0;
            for(int i = 0; i < N; ++i) acc |= grid[i][j];
            if(acc!=V[j]) return 0;
        }
    }
    return 1;
}

vector<vector<ll>> solve(const vector<int>& S,const vector<int>& U,const vector<int>& T,const vector<int>& V) {
    int N = S.size();
    vector<vector<ll>> grid(N,vector<ll>(N,-1));
    vector<int> y,x;
    for(int i = 0; i < N; ++i) {
        // and
        if(S[i] == 0) {
            if(U[i] == 1) {
                for(int j = 0; j < N; ++j) {
                    if(grid[i][j]==-1 || grid[i][j]==1) grid[i][j] = 1;
                    else throw exception();
                }
            }
            else {
                y.push_back(i);
            }
        }
        // or
        else {
            if(U[i] == 0) {
                for(int j = 0; j < N; ++j) {
                    if(grid[i][j]==-1 || grid[i][j]==0) grid[i][j] = 0;
                    else throw exception();
                }
            }
            else {
                y.push_back(i);
            }
        }
    }

    for(int j = 0; j < N; ++j) {
        // and
        if(T[j] == 0) {
            if(V[j] == 1) {
                for(int i = 0; i < N; ++i) {
                    if(grid[i][j]==-1 || grid[i][j]==1) grid[i][j] = 1;
                    else throw exception();
                }
            }
            else {
                x.push_back(j);
            }
        }
        // or
        else {
            if(V[j] == 0) {
                for(int i = 0; i < N; ++i) {
                    if(grid[i][j]==-1 || grid[i][j]==0) grid[i][j] = 0;
                    else throw exception();
                }
            }
            else {
                x.push_back(j);
            }
        }
    }

    if(y.empty() || x.empty()) {
        if(validate(S,U,T,V,grid)) return grid;
        else throw exception();
    }
    
    if(y.size()==1) {
        for(int j:x) {
            int flg = 0;
            for(int i = 0; i < N; ++i) if(grid[i][j]==T[j]) flg = 1;
            if(flg) continue;
            else grid[y[0]][j] = T[j];
        }
        for(int j = 0; j < N; ++j) if(grid[y[0]][j]==-1) grid[y[0]][j] = S[y[0]];
        if(validate(S,U,T,V,grid)) return grid;
        else throw exception();
    }

    if(x.size()==1) {
        for(int i:y) {
            int flg = 0;
            for(int j = 0; j < N; ++j) if(grid[i][j]==S[i]) flg = 1;
            if(flg) continue;
            else grid[i][x[0]] = S[i];
        }
        for(int i = 0; i < N; ++i) if(grid[i][x[0]]==-1) grid[i][x[0]] = T[x[0]];
        if(validate(S,U,T,V,grid)) return grid;
        else throw exception();
    }

    {
        int ss=0;
        for(int i:y) {
            int prt = ss;
            for(int j:x) {
                grid[i][j] = prt;
                prt ^= 1;
            }
            ss ^= 1;
        }
        if(validate(S,U,T,V,grid)) return grid;
        else throw exception();
    }    
}

int main() {
    cin.tie(0);ios::sync_with_stdio(false);
    int N; cin >> N;
    vector<int> S(N),T(N),A(N),B(N);
    vector<unsigned long long> U(N),V(N);
    for(int i = 0; i < N; ++i) cin >> S[i];
    for(int i = 0; i < N; ++i) cin >> T[i];
    for(int i = 0; i < N; ++i) cin >> U[i];
    for(int i = 0; i < N; ++i) cin >> V[i];
    auto grid = multivector(N,N,0ull);
    for(unsigned long long i = 0; i < 64; ++i) {
        for(int j = 0; j < N; ++j) A[j] = ((U[j]>>i)&1ull);
        for(int j = 0; j < N; ++j) B[j] = ((V[j]>>i)&1ull);
        try{
            auto C = solve(S,A,T,B);
            for(int j = 0; j < N; ++j) {
                for(int k = 0; k < N; ++k) {
                    unsigned long long c = C[j][k]; 
                    grid[j][k] |= (c<<i);
                }
            }
        }
        catch(exception e) {
            corner(1,-1);
        }
    }
    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < N; ++j) {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
