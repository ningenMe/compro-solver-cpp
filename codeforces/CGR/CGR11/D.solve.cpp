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
template <class T>ostream &operator<<(ostream &o, const deque<T>&obj) {o << "{"; for (int i = 0; i < (int)obj.size(); ++i)o << (i > 0 ? ", " : "") << obj[i]; o << "}"; return o;}
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

vector<int> calc(deque<int> dq,vector<int> A) {
    vector<vector<int>> B(dq.size());
    int offset = 0;
    for(int j=0;j<dq.size();++j) {
        for(int k=0;k<dq[j];++k) {
            B[j].push_back(A[k+offset]);
        }
        offset += dq[j];
    }
    reverse(ALL(B));
    int cnt=0;
    for(auto& v:B) {
        for(auto& e:v) {
            A[cnt++]=e;
        }
    }
    return A;
}

int main() {
    cin.tie(0);ios::sync_with_stdio(false);
    int N; cin >> N;
    vector<int> A(N),B(N);
    for(int i=0;i<N;++i) cin >> A[i];
    iota(ALL(B),1);
    corner(A==B,0);
    auto C = B;
    reverse(ALL(C));

    vector<deque<int>> ans;
    int pre=0;
    //0:left
    //1:right
    for(int n=1;n+1<=N;++n) {
        if(A==B) break;
        if(A==C) {
            deque<int> dq;            
            for(int i=0;i<N;++i) dq.push_back(1);
            ans.push_back(dq);
            A = calc(dq,A);
            continue;
        }
        int idx1,idx2;
        for(int j=0;j<N;++j) if(A[j]==n)   idx1 = j;
        for(int j=0;j<N;++j) if(A[j]==n+1) idx2 = j;
        if(idx2 < idx1 && pre==0) {
            deque<int> dq;
            dq.push_back(idx2);
            dq.push_back(1);
            dq.push_back(idx1-idx2);
            dq.push_back(N-1-idx1);
            while(dq.front()==0) dq.pop_front();
            while(dq.back()==0) dq.pop_back();
            ans.push_back(dq);
            A = calc(dq,A);
            pre=0;
            continue;
        }
        if(idx2 < idx1 && pre==1) {
            if(idx2+1==idx1) continue;
            deque<int> dq;
            dq.push_back(idx2);
            dq.push_back(idx1-idx2);
            for(int i=idx1;i<N;++i) dq.push_back(1);
            while(dq.front()==0) dq.pop_front();
            while(dq.back()==0) dq.pop_back();
            ans.push_back(dq);
            A = calc(dq,A);
            pre=0;
            continue;
        }
        if(idx1 < idx2 && pre==0) {
            if(idx1+1==idx2) continue;
            deque<int> dq;
            for(int i=0;i<=idx1;++i) dq.push_back(1);
            dq.push_back(idx2-idx1);
            dq.push_back(N-1-idx2);
            while(dq.front()==0) dq.pop_front();
            while(dq.back()==0) dq.pop_back();
            ans.push_back(dq);
            A = calc(dq,A);
            pre=1;
            continue;
        }
        if(idx1 < idx2 && pre==1) {
            deque<int> dq;
            dq.push_back(idx1);
            dq.push_back(idx2-idx1);
            dq.push_back(1);
            dq.push_back(N-1-idx2);
            while(dq.front()==0) dq.pop_front();
            while(dq.back()==0) dq.pop_back();
            ans.push_back(dq);
            A = calc(dq,A);
            pre=1;
            continue;
        }
    }
    {
        if(A==C) {
            deque<int> dq;            
            for(int i=0;i<N;++i) dq.push_back(1);
            ans.push_back(dq);
            A = calc(dq,A);
        }
    }

    cout << ans.size() << endl;
    for(auto v:ans) {
        cout << v.size();
        for(auto& e:v) cout << " " << e;
        cout << endl;
    }
    return 0;
}
