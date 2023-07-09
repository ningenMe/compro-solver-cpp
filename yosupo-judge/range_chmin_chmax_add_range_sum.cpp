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

/*
 * @title SegmentTreeBeats
 * @docs md/segment-tree/SegmentTreeBeats.md
 */
template<class T> class SegmentTreeBeats {
    T inf;
    size_t length;
    vector<T>
            node_max_first,node_max_second,count_max_first,
            node_min_first,node_min_second,count_min_first,
            node_sum,lazy_add,lazy_update;
    vector<pair<int,int>> range;
    stack<int> down,up;
    inline void internal_chmax(int k, long long x) {
        node_sum[k] += (x - node_max_first[k]) * count_max_first[k];
        if(node_max_first[k] == node_min_first[k]) node_max_first[k] = node_min_first[k] = x;
        else if(node_max_first[k] == node_min_second[k]) node_max_first[k] = node_min_second[k] = x;
        else node_max_first[k] = x;
        if(lazy_update[k] != inf && x < lazy_update[k]) lazy_update[k] = x;
    }
    inline void internal_chmin(int k, long long x) {
        node_sum[k] += (x - node_min_first[k]) * count_min_first[k];
        if(node_max_first[k] == node_min_first[k]) node_max_first[k] = node_min_first[k] = x;
        else if(node_max_second[k] == node_min_first[k]) node_min_first[k] = node_max_second[k] = x;
        else node_min_first[k] = x;
        if(lazy_update[k] != inf && lazy_update[k] < x) lazy_update[k] = x;
    }
    inline void internal_add(int k, long long x) {
        node_max_first[k] += x;
        if(node_max_second[k] != -inf) node_max_second[k] += x;
        node_min_first[k] += x;
        if(node_min_second[k] != inf) node_min_second[k] += x;
        node_sum[k] += x * (range[k].second - range[k].first);
        (lazy_update[k] != inf ? lazy_update[k]:lazy_add[k]) += x;
    }
    inline void internal_update(int k, long long x) {
        node_max_first[k] = x; node_max_second[k] = -inf;
        node_min_first[k] = x; node_min_second[k] = inf;
        count_max_first[k] = count_min_first[k] = (range[k].second - range[k].first);
        node_sum[k] = x * (range[k].second - range[k].first);
        lazy_update[k] = x;
        lazy_add[k] = 0;
    }
    inline void propagate(int k) {
        if(length-1 <= k) return;
        if(lazy_update[k] != inf) {
            internal_update(2*k+0, lazy_update[k]);
            internal_update(2*k+1, lazy_update[k]);
            lazy_update[k] = inf;
            return;
        }
        if(lazy_add[k] != 0) {
            internal_add(2*k+0, lazy_add[k]);
            internal_add(2*k+1, lazy_add[k]);
            lazy_add[k] = 0;
        }
        if(node_max_first[k] < node_max_first[2*k+0]) {
            internal_chmax(2*k+0, node_max_first[k]);
        }
        if(node_min_first[2*k+0] < node_min_first[k]) {
            internal_chmin(2*k+0, node_min_first[k]);
        }
        if(node_max_first[k] < node_max_first[2*k+1]) {
            internal_chmax(2*k+1, node_max_first[k]);
        }
        if(node_min_first[2*k+1] < node_min_first[k]) {
            internal_chmin(2*k+1, node_min_first[k]);
        }
    }
    inline void merge(int k) {
        node_sum[k] = node_sum[2*k+0] + node_sum[2*k+1];
        if(node_max_first[2*k+0] < node_max_first[2*k+1]) {
            node_max_first[k] = node_max_first[2*k+1];
            count_max_first[k] = count_max_first[2*k+1];
            node_max_second[k] = max(node_max_first[2*k+0], node_max_second[2*k+1]);
        }
        else if(node_max_first[2*k+0] > node_max_first[2*k+1]) {
            node_max_first[k] = node_max_first[2*k+0];
            count_max_first[k] = count_max_first[2*k+0];
            node_max_second[k] = max(node_max_second[2*k+0], node_max_first[2*k+1]);
        }
        else {
            node_max_first[k] = node_max_first[2*k+0];
            count_max_first[k] = count_max_first[2*k+0] + count_max_first[2*k+1];
            node_max_second[k] = max(node_max_second[2*k+0], node_max_second[2*k+1]);
        }
        if(node_min_first[2*k+0] < node_min_first[2*k+1]) {
            node_min_first[k] = node_min_first[2*k+0];
            count_min_first[k] = count_min_first[2*k+0];
            node_min_second[k] = min(node_min_second[2*k+0], node_min_first[2*k+1]);
        }
        else if(node_min_first[2*k+0] > node_min_first[2*k+1]) {
            node_min_first[k] = node_min_first[2*k+1];
            count_min_first[k] = count_min_first[2*k+1];
            node_min_second[k] = min(node_min_first[2*k+0], node_min_second[2*k+1]);
        }
        else {
            node_min_first[k] = node_min_first[2*k+0];
            count_min_first[k] = count_min_first[2*k+0] + count_min_first[2*k+1];
            node_min_second[k] = min(node_min_second[2*k+0], node_min_second[2*k+1]);
        }
    }
    inline void up_merge(void){
        while(up.size()) {
            merge(up.top());
            up.pop();
        }
    }
    inline void down_propagate(const int& k) {
        propagate(k);
        down.push(2*k+0);
        down.push(2*k+1);
    }
public:
    SegmentTreeBeats(const int num,const T inf = (1LL<<60)) {
        vector<T> a(num,0);
        *this = SegmentTreeBeats(a,inf);
    }
    SegmentTreeBeats(const vector<T>& a,const T inf = (1LL<<60)) : inf(inf){
        int num = a.size();
        for (length = 1; length <= num; length *= 2);
        node_max_first.resize(2*length);
        node_max_second.resize(2*length);
        count_max_first.resize(2*length);
        node_min_first.resize(2*length);
        node_min_second.resize(2*length);
        count_min_first.resize(2*length);
        node_sum.resize(2*length);
        range.resize(2*length);
        lazy_add.resize(2*length);
        lazy_update.resize(2*length);

        for(int i=0; i<2*length; ++i) lazy_add[i] = 0, lazy_update[i] = inf;
        for(int i = 0; i < length; ++i) range[i+length] = make_pair(i,i+1);
        for(int i = length - 1; i >= 0; --i) range[i] = make_pair(range[(i<<1)+0].first,range[(i<<1)+1].second);

        for(int i=0; i<num; ++i) {
            node_max_first[length+i] = node_min_first[length+i] = node_sum[length+i] = a[i];
            node_max_second[length+i] = -inf;
            node_min_second[length+i] = inf;
            count_max_first[length+i] = count_min_first[length+i] = 1;
        }
        for(int i=num; i<length; ++i) {
            node_max_first[length+i] = node_max_second[length+i] = -inf;
            node_min_first[length+i] = node_min_second[length+i] = inf;
            count_max_first[length+i] = count_min_first[length+i] = 0;
        }
        for(int i=length-1; i; --i) merge(i);
    }
    inline void range_chmin(int a, int b, long long x) {
        down.push(1);
        while(down.size()) {
            int k = down.top();
            down.pop();
            if(b <= range[k].first || range[k].second <= a || node_max_first[k] <= x) continue;
            if(a <= range[k].first && range[k].second <= b && node_max_second[k] < x) {
                internal_chmax(k, x);
                continue;
            }
            down_propagate(k);
            up.push(k);
        }
        up_merge();
    }
    inline void range_chmax(int a, int b, long long x,int k = 1) {
        down.push(1);
        while(down.size()) {
            int k = down.top();
            down.pop();
            if(b <= range[k].first || range[k].second <= a || x <= node_min_first[k]) continue;
            if(a <= range[k].first && range[k].second <= b && x < node_min_second[k]) {
                internal_chmin(k, x);
                continue;
            }
            down_propagate(k);
            up.push(k);
        }
        up_merge();
    }
    inline void range_add(int a, int b, long long x,int k = 1) {
        down.push(1);
        while(down.size()) {
            int k = down.top();
            down.pop();
            if(b <= range[k].first || range[k].second <= a) continue;
            if(a <= range[k].first && range[k].second <= b) {
                internal_add(k, x);
                continue;
            }
            down_propagate(k);
            up.push(k);
        }
        up_merge();
    }
    inline void range_update(int a, int b, long long x,int k = 1) {
        down.push(1);
        while(down.size()) {
            int k = down.top();
            down.pop();
            if(b <= range[k].first || range[k].second <= a) continue;
            if(a <= range[k].first && range[k].second <= b) {
                internal_update(k, x);
                continue;
            }
            down_propagate(k);
            up.push(k);
        }
        up_merge();
    }
    inline T get_max(int a, int b, int k = 1) {
        down.push(1);
        long long v = inf;
        while(down.size()) {
            int k = down.top();
            down.pop();
            if(b <= range[k].first || range[k].second <= a) continue;
            if(a <= range[k].first && range[k].second <= b) {
                v = max(v,node_max_first[k]);
                continue;
            }
            down_propagate(k);
        }
        return v;
    }
    inline T get_min(int a, int b, int k = 1) {
        down.push(1);
        long long v = inf;
        while(down.size()) {
            int k = down.top();
            down.pop();
            if(b <= range[k].first || range[k].second <= a) continue;
            if(a <= range[k].first && range[k].second <= b) {
                v = min(v,node_min_first[k]);
                continue;
            }
            down_propagate(k);
        }
        return v;
    }
    inline T get_sum(int a, int b, int k=1) {
        down.push(1);
        long long v = 0;
        while(down.size()) {
            int k = down.top();
            down.pop();
            if(b <= range[k].first || range[k].second <= a) continue;
            if(a <= range[k].first && range[k].second <= b) {
                v += node_sum[k];
                continue;
            }
            down_propagate(k);
        }
        return v;
    }
};

int main() {
	int N,Q; 
	read(N), read(Q);
	vector<long long> A(N);
	for(int i = 0; i < N; ++i) read(A[i]);
	SegmentTreeBeats<long long> seg(A);
	while(Q--){
		long long q,l,r,b;
		read(q),read(l),read(r);
		if(q==3){
			cout << seg.get_sum(l,r) << "\n";
		}
		else{
			read(b);
			if(q==0) {
				seg.range_chmin(l,r,b);
			}
			if(q==1) {
				seg.range_chmax(l,r,b);
			}
			if(q==2) {
				seg.range_add(l,r,b);
			}
		}
	}
    return 0;
}