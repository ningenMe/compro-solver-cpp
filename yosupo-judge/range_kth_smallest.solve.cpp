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

/*
 * @title WaveletMatrix
 * @docs md/data-structure/WaveletMatrix.md
 */
template<class T> class WaveletMatrix{
    using u64 = unsigned long long;
    using u32 = unsigned int;

    class BitVector{
        inline static constexpr size_t BIT_BLOCK_SIZE = 5;
        inline static constexpr size_t BIT_BLOCK_NUM  = (1<<BIT_BLOCK_SIZE) - 1; //31
        vector<u32> ar, acc;
        u32 popcount(u32 x) const {return __builtin_popcount(x);}
        u32 length;
    public:
        u32 sum_bit0;
        BitVector(const u32 N): length(N) {
            u32 tmp = (N + BIT_BLOCK_NUM) / (BIT_BLOCK_NUM+1);
            ar.assign(tmp, 0);
            acc.assign(tmp, 0);
        }
        void build() { 
            for (size_t i = 0,sum = 0; i < acc.size(); ++i) acc[i] = (sum += popcount(ar[i]) );
            sum_bit0 = rank(length, 0);
        }
        //[0,r) count of bit
        u32 rank(const u32 r, const bool bit) const {
            u32 bit_r = r >> BIT_BLOCK_SIZE; 
            u32 sum = (bit_r ? acc[bit_r - 1] : 0) + popcount(ar[bit_r] & ((1U << (r & BIT_BLOCK_NUM)) - 1));
            return bit ? sum : r - sum;
        }
        //[l,l+1) = bit
        void update(const u32 l, const bool bit) {
            u32 bit_l = l >> BIT_BLOCK_SIZE;
            if (bit) ar[bit_l] |=   1U << (l & BIT_BLOCK_NUM);
            else     ar[bit_l] &= ~(1U << (l & BIT_BLOCK_NUM));
        }
        //[l,l+1)
        bool operator[](const u32 l) const {
            return ((ar[l >> BIT_BLOCK_SIZE] >> (l & BIT_BLOCK_NUM)) & 1);
        }
    };
    size_t length;
    size_t depth;
    vector<BitVector> bit_vector;
    vector<T> ar;
    set<T> st;
    void build() {
        length = ar.size();       
        vector<u32> ord(ar.size()),compressed(ar.size());
        iota(ord.begin(),ord.end(),0);
        sort(ord.begin(),ord.end(),[&](size_t l, size_t r){return ar[l]<ar[r];});
        u32 cnt = 0;
        compressed.front() = 0;
        T pre = ar[ord.front()];
        for(size_t i=1;i<ord.size();++i) {
            size_t j=ord[i];
            if(pre < ar[j]) ++cnt;
            compressed[j] = cnt;
            pre = ar[j];
        }
        sort(ar.begin(),ar.end());
        ar.erase(unique(ar.begin(),ar.end()),ar.end());

        for(depth=0; (1<<depth) <= cnt+2; ++depth );
        bit_vector.assign(depth, BitVector(length));
        vector<u32> prev = compressed, next = prev;
        for(u32 d = 0; d < depth; ++d,swap(prev,next)) {
            u32 bit = 1UL << (depth - d - 1);
            u32 idx_bit0 = 0, idx_bit1 = 0;
            for(u32 i = 0; i < length; ++i) idx_bit1 += !(prev[i] & bit);
            for(u32 i = 0; i < length; ++i) {
                if (prev[i] & bit) bit_vector[d].update(i,1), next[idx_bit1++] = prev[i];
                else next[idx_bit0++] = prev[i];
            }
            bit_vector[d].build();
        }
    }
    inline T get_impl(u32 l) const {
        u32 key = 0;
        for (u32 d = 0; d < depth; ++d) {
            const bool bit = bit_vector[d][l];
            key = ((key << 1) | bit);
            l = bit_vector[d].rank(l, bit);
            if(bit) l += bit_vector[d].sum_bit0;
        }
        return ar[key];
    }
    inline T range_kth_smallest_impl(u32 l, u32 r, u32 k) const {
        u32 key = 0;
        for (u32 d = 0; d < depth; ++d) {
            u32 cnt_bit_off = bit_vector[d].rank(r, 0) - bit_vector[d].rank(l, 0);
            const bool bit = (k >= cnt_bit_off);
            key = ((key << 1) | bit);
            l = bit_vector[d].rank(l, bit);
            r = bit_vector[d].rank(r, bit);
            if (bit) l += bit_vector[d].sum_bit0, r += bit_vector[d].sum_bit0, k -= cnt_bit_off;
        }
        return ar[key];
    }
    // count of val in [0,r)
    // inline u32 prefix_freq_impl(u32 r, T val) const {
    //     auto itr=lower_bound(ar.begin(),ar.end(),val);
    //     if(itr == ar.end() || (*itr != val)) return 0;
    //     u32 key = (itr - ar.begin());

    //     for (u32 d = 0; d < depth; ++d) {
    //         u32 bit = (key >> (depth - d - 1)) & 1U;
    //         r = bit_vector[d].rank(r,bit);
    //         if(bit) r += sum_bit_off[d];
    //     }
    // }
    // count of val ( val < upper )
    inline u32 range_freq_upper_impl(u32 l, u32 r, T upper) const {
        if(ar.back() < upper) return (r-l);
        if(r-l<=0) return 0;
        auto itr = lower_bound(ar.begin(),ar.end(),upper);
        u32 key = (itr - ar.begin());

        u32 cnt=0;
        for (u32 d = 0; d < depth; ++d) {
            u32 bit = (key >> (depth - d - 1)) & 1U;
            u32 tl = bit_vector[d].rank(l,0);
            u32 tr = bit_vector[d].rank(r,0);
            if(bit) {
                cnt += tr-tl;
                l += bit_vector[d].sum_bit0-tl;
                r += bit_vector[d].sum_bit0-tr;
            }
            else {
                l = tl;
                r = tr;
            }
        }
        return cnt;
    }

public:
    WaveletMatrix(const vector<T> &ar): ar(ar) { build(); }
    //[l,l+1) element
    inline T get(const u32 l) const {return get_impl(l);}
    //[l,r) range k (0-indexed) th smallest number
    T range_kth_smallest(const u32 l, const u32 r, const u32 k) const {return range_kth_smallest_impl(l,r,k);}
    //[l,r) range k (0-indexed) th largest number
    T range_kth_largest(const u32 l, const u32 r, const u32 k) const {return range_kth_smallest_impl(l,r,(r-l)-(k+1));}
    //[l,r) range freq of val (val < upper)
    u32 range_freq_upper(const u32 l, const u32 r, const T upper) const {return range_freq_upper_impl(l,r,upper);}
    //[l,r) range freq of val (lower <= val < upper)
    u32 range_freq_lower_upper(const u32 l, const u32 r, const T lower, const T upper) const {return range_freq_upper_impl(l,r,upper) - range_freq_upper_impl(l,r,lower);}
    //[l,r) range freq of val
    u32 range_freq(const u32 l, const u32 r, const T val) const {return range_freq_lower_upper(l,r,val,val+1);}
};

/**
 * @url 
 * @est
 */ 
int main() {
    cin.tie(0);ios::sync_with_stdio(false);
    int N,Q; read(N); read(Q);
    vector<long long> A(N);
    for(int i=0;i<N;++i) read(A[i]);
    WaveletMatrix<long long> wm(A);
    while(Q--) {
        int l,r,k; read(l); read(r); read(k);
        cout << wm.range_kth_smallest(l,r,k) << "\n";
    }
    return 0;
}
