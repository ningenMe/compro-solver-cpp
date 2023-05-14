#include <bits/stdc++.h>
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

template<class T> class DoubleEndedPriorityQuere {
	priority_queue<T> max_pq,poped_max_pq;
	priority_queue<T, vector<T>, greater<T> > min_pq, poped_min_pq;
public:
	DoubleEndedPriorityQuere() {
    }
	inline void push(T &v) {
		max_pq.push(v);
		min_pq.push(v);
	}
	inline T front() {
        while(poped_min_pq.size() && min_pq.top()==poped_min_pq.top()) min_pq.pop(),poped_min_pq.pop();
		return min_pq.top();
	}
	inline T back() {
        while(poped_max_pq.size() && max_pq.top()==poped_max_pq.top()) max_pq.pop(),poped_max_pq.pop();
		return max_pq.top();
	}
	inline void pop_front() {
        while(poped_min_pq.size() && min_pq.top()==poped_min_pq.top()) min_pq.pop(),poped_min_pq.pop();
		poped_max_pq.push(min_pq.top());
		min_pq.pop();
	}
	inline void pop_back() {
        while(poped_max_pq.size() && max_pq.top()==poped_max_pq.top()) max_pq.pop(),poped_max_pq.pop();
		poped_min_pq.push(max_pq.top());
		max_pq.pop();
	}
	inline size_t size() { return max_pq.size(); }
};

/**
 * @url 
 * @est
 */ 
int main() {
    cin.tie(0);ios::sync_with_stdio(false);
    int N,Q; read(N);read(Q);
    DoubleEndedPriorityQuere<long long> pq;
    while(N--) {
        long long s; read(s); pq.push(s);
    }
    while(Q--) {
        int q; read(q); 
        if(q==0) {
            long long x; read(x);
            pq.push(x);
        }
        if(q==1) {
            long long x = pq.front(); pq.pop_front();
            cout << x << "\n";
        }
        if(q==2) {
            long long x = pq.back(); pq.pop_back();
            cout << x << "\n";
        }
    }

    return 0;
}
