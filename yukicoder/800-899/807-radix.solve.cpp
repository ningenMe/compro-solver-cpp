#include <vector>
#include <iostream>
#include <algorithm>
#include <array>
using namespace std;

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

/*
 * @title RadixHeap - 非負整数heap
 * @docs md/heap/RadixHeap.md
 */
template<class T, class Key = unsigned long long> class RadixHeap{
    using TypeNode = pair<Key, T>;
    template<class InnerKey, class ZZ=InnerKey> class Inner{};
    template<class InnerKey> class Inner<InnerKey, unsigned long long>{
        array<vector<TypeNode>,65> vq;
        unsigned long long size_num;
        TypeNode last;
        inline int bit(unsigned long long a) { return a ? 64 - __builtin_clzll(a) : 0;}
    public:
        Inner(T mini) : size_num(0), last(make_pair(0, mini)) {}
        inline bool empty() { return size_num == 0; }
        inline size_t size(){ return size_num; }
        inline void push(TypeNode x){ ++size_num; vq[bit(x.first^last.first)].push_back(x);}
        inline void emplace(unsigned long long key,T val){ ++size_num; vq[bit(key^last.first)].emplace_back(key,val);}
        inline TypeNode pop() {
            if(vq[0].empty()) {
                int i = 1;
                while(vq[i].empty()) ++i;
                last = *min_element(vq[i].begin(),vq[i].end());
                for(auto &p : vq[i]) vq[bit(p.first ^ last.first)].push_back(p);
                vq[i].clear();
            }
            --size_num;
            auto res = vq[0].back(); vq[0].pop_back();
            return res;
        }
    };
    template<class InnerKey> class Inner<InnerKey, unsigned int>{
        array<vector<TypeNode>,33> vq;
        unsigned int size_num;
        TypeNode last;
        inline int bit(unsigned int a) { return a ? 32 - __builtin_clz(a) : 0;}
    public:
        Inner(T mini) : size_num(0), last(make_pair(0, mini)) {}
        inline bool empty() { return size_num == 0; }
        inline size_t size(){ return size_num; }
        inline void push(TypeNode x){ ++size_num; vq[bit(x.first^last.first)].push_back(x);}
        inline void emplace(unsigned int key,T val){ ++size_num; vq[bit(key^last.first)].emplace_back(key,val);}
        inline TypeNode pop() {
            if(vq[0].empty()) {
                int i = 1;
                while(vq[i].empty()) ++i;
                last = *min_element(vq[i].begin(),vq[i].end());
                for(auto &p : vq[i]) vq[bit(p.first ^ last.first)].push_back(p);
                vq[i].clear();
            }
            --size_num;
            auto res = vq[0].back(); vq[0].pop_back();
            return res;
        }
    };
    Inner<Key,Key> inner;
public:
    RadixHeap(T mini) : inner(mini) {}
    inline bool empty() { return inner.empty();}
    inline size_t size(){ return inner.size();}
    inline void push(TypeNode x){ inner.push(x);}
    inline void emplace(unsigned long long key,T val){ inner.emplace(key,val);}
    inline TypeNode pop() { return inner.pop(); }
};

//Dijkstra
template<class T> class Dijkstra {
public:
	int N;
	T inf;
	vector<T> cost;
	vector<vector<pair<T, int>>> edge;

	Dijkstra(const int N, T inf) : N(N), inf(inf), cost(N), edge(N) {
	}

	void make_edge(int from, int to, T w) {
		edge[from].push_back({ w,to });
	}

	void solve(int start) {
		for (int i = 0; i < N; ++i) cost[i] = inf;

		RadixHeap<int,unsigned long long> pq(0);
		cost[start] = 0;
		pq.push({ 0,start });

		while (!pq.empty()) {
			auto p = pq.pop();
			T v = p.first;
			int from = p.second;
			if(cost[from]<v) continue;
			for (auto u : edge[from]) {
				T w = v + u.first;
				int to = u.second;
				if (w < cost[to]) {
					cost[to] = w;
					pq.push({ w,to });
				}
			}
		}
		return;
	}
};

int main() {
	cin.tie(0);ios::sync_with_stdio(false);
	int N, M; 
    read(N); read(M);
	Dijkstra<long long> dijk(2*N, 1LL<<60);
	for(int i = 0; i < M; ++i){
		int a, b;
		long long c;
        read(a); read(b); read(c);
		a--, b--;
		dijk.make_edge(a, b, c);
		dijk.make_edge(b, a, c);
		dijk.make_edge(a+N, b+N, c);
		dijk.make_edge(b+N, a+N, c);
		dijk.make_edge(a, b+N, 0);
		dijk.make_edge(b, a+N, 0);
	}
	dijk.solve(0);
	dijk.cost[N]=0;
	for (int i = 0; i < N; ++i) cout << dijk.cost[i]+dijk.cost[i+N] << "\n";

	return 0;
}