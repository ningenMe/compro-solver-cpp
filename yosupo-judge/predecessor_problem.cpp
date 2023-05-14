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
    template<typename T> inline static void read_integer(T &x) {
        int neg=0; char ch; x=0;
        ch=getchar();
        if(ch==ch_n) neg=1,ch=getchar();
        for(;(ch_0 <= ch && ch <= ch_9); ch = getchar()) x = x*10 + (ch-ch_0);
        if(neg) x*=-1;
    }
    template<typename T> inline static void read_unsigned_integer(T &x) {
        char ch; x=0;
        ch=getchar();
        for(;(ch_0 <= ch && ch <= ch_9); ch = getchar()) x = x*10 + (ch-ch_0);
    }
    inline static void read_string(string &x) {
        char ch; x="";
        ch=getchar();
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

class WordSizeTreeSet {
public:
    using u64 = unsigned long long;
    inline static constexpr u64 max_length=(1ULL<<24);
private:
    inline static constexpr u64 word_size=(1ULL<<6);
    inline static constexpr array<u64,word_size> pow2 = {1ULL, 2ULL, 4ULL, 8ULL, 16ULL, 32ULL, 64ULL, 128ULL, 256ULL, 512ULL, 1024ULL, 2048ULL, 4096ULL, 8192ULL, 16384ULL, 32768ULL, 65536ULL, 131072ULL, 262144ULL, 524288ULL, 1048576ULL, 2097152ULL, 4194304ULL, 8388608ULL, 16777216ULL, 33554432ULL, 67108864ULL, 134217728ULL, 268435456ULL, 536870912ULL, 1073741824ULL, 2147483648ULL, 4294967296ULL, 8589934592ULL, 17179869184ULL, 34359738368ULL, 68719476736ULL, 137438953472ULL, 274877906944ULL, 549755813888ULL, 1099511627776ULL, 2199023255552ULL, 4398046511104ULL, 8796093022208ULL, 17592186044416ULL, 35184372088832ULL, 70368744177664ULL, 140737488355328ULL, 281474976710656ULL, 562949953421312ULL, 1125899906842624ULL, 2251799813685248ULL, 4503599627370496ULL, 9007199254740992ULL, 18014398509481984ULL, 36028797018963968ULL, 72057594037927936ULL, 144115188075855872ULL, 288230376151711744ULL, 576460752303423488ULL, 1152921504606846976ULL, 2305843009213693952ULL, 4611686018427387904ULL, 9223372036854775808ULL};
    inline static constexpr array<u64,word_size> next_lower_bound_mask = {18446744073709551615ULL, 18446744073709551614ULL, 18446744073709551612ULL, 18446744073709551608ULL, 18446744073709551600ULL, 18446744073709551584ULL, 18446744073709551552ULL, 18446744073709551488ULL, 18446744073709551360ULL, 18446744073709551104ULL, 18446744073709550592ULL, 18446744073709549568ULL, 18446744073709547520ULL, 18446744073709543424ULL, 18446744073709535232ULL, 18446744073709518848ULL, 18446744073709486080ULL, 18446744073709420544ULL, 18446744073709289472ULL, 18446744073709027328ULL, 18446744073708503040ULL, 18446744073707454464ULL, 18446744073705357312ULL, 18446744073701163008ULL, 18446744073692774400ULL, 18446744073675997184ULL, 18446744073642442752ULL, 18446744073575333888ULL, 18446744073441116160ULL, 18446744073172680704ULL, 18446744072635809792ULL, 18446744071562067968ULL, 18446744069414584320ULL, 18446744065119617024ULL, 18446744056529682432ULL, 18446744039349813248ULL, 18446744004990074880ULL, 18446743936270598144ULL, 18446743798831644672ULL, 18446743523953737728ULL, 18446742974197923840ULL, 18446741874686296064ULL, 18446739675663040512ULL, 18446735277616529408ULL, 18446726481523507200ULL, 18446708889337462784ULL, 18446673704965373952ULL, 18446603336221196288ULL, 18446462598732840960ULL, 18446181123756130304ULL, 18445618173802708992ULL, 18444492273895866368ULL, 18442240474082181120ULL, 18437736874454810624ULL, 18428729675200069632ULL, 18410715276690587648ULL, 18374686479671623680ULL, 18302628885633695744ULL, 18158513697557839872ULL, 17870283321406128128ULL, 17293822569102704640ULL, 16140901064495857664ULL, 13835058055282163712ULL, 9223372036854775808ULL};
    inline static constexpr array<u64,word_size> prev_lower_bound_mask = {1ULL, 3ULL, 7ULL, 15ULL, 31ULL, 63ULL, 127ULL, 255ULL, 511ULL, 1023ULL, 2047ULL, 4095ULL, 8191ULL, 16383ULL, 32767ULL, 65535ULL, 131071ULL, 262143ULL, 524287ULL, 1048575ULL, 2097151ULL, 4194303ULL, 8388607ULL, 16777215ULL, 33554431ULL, 67108863ULL, 134217727ULL, 268435455ULL, 536870911ULL, 1073741823ULL, 2147483647ULL, 4294967295ULL, 8589934591ULL, 17179869183ULL, 34359738367ULL, 68719476735ULL, 137438953471ULL, 274877906943ULL, 549755813887ULL, 1099511627775ULL, 2199023255551ULL, 4398046511103ULL, 8796093022207ULL, 17592186044415ULL, 35184372088831ULL, 70368744177663ULL, 140737488355327ULL, 281474976710655ULL, 562949953421311ULL, 1125899906842623ULL, 2251799813685247ULL, 4503599627370495ULL, 9007199254740991ULL, 18014398509481983ULL, 36028797018963967ULL, 72057594037927935ULL, 144115188075855871ULL, 288230376151711743ULL, 576460752303423487ULL, 1152921504606846975ULL, 2305843009213693951ULL, 4611686018427387903ULL, 9223372036854775807ULL, 18446744073709551615ULL};
    inline static constexpr array<u64,word_size> next_upper_bound_mask = {18446744073709551614ULL, 18446744073709551612ULL, 18446744073709551608ULL, 18446744073709551600ULL, 18446744073709551584ULL, 18446744073709551552ULL, 18446744073709551488ULL, 18446744073709551360ULL, 18446744073709551104ULL, 18446744073709550592ULL, 18446744073709549568ULL, 18446744073709547520ULL, 18446744073709543424ULL, 18446744073709535232ULL, 18446744073709518848ULL, 18446744073709486080ULL, 18446744073709420544ULL, 18446744073709289472ULL, 18446744073709027328ULL, 18446744073708503040ULL, 18446744073707454464ULL, 18446744073705357312ULL, 18446744073701163008ULL, 18446744073692774400ULL, 18446744073675997184ULL, 18446744073642442752ULL, 18446744073575333888ULL, 18446744073441116160ULL, 18446744073172680704ULL, 18446744072635809792ULL, 18446744071562067968ULL, 18446744069414584320ULL, 18446744065119617024ULL, 18446744056529682432ULL, 18446744039349813248ULL, 18446744004990074880ULL, 18446743936270598144ULL, 18446743798831644672ULL, 18446743523953737728ULL, 18446742974197923840ULL, 18446741874686296064ULL, 18446739675663040512ULL, 18446735277616529408ULL, 18446726481523507200ULL, 18446708889337462784ULL, 18446673704965373952ULL, 18446603336221196288ULL, 18446462598732840960ULL, 18446181123756130304ULL, 18445618173802708992ULL, 18444492273895866368ULL, 18442240474082181120ULL, 18437736874454810624ULL, 18428729675200069632ULL, 18410715276690587648ULL, 18374686479671623680ULL, 18302628885633695744ULL, 18158513697557839872ULL, 17870283321406128128ULL, 17293822569102704640ULL, 16140901064495857664ULL, 13835058055282163712ULL, 9223372036854775808ULL, 0ULL};
    inline static constexpr array<u64,word_size> prev_upper_bound_mask = {0ULL, 1ULL, 3ULL, 7ULL, 15ULL, 31ULL, 63ULL, 127ULL, 255ULL, 511ULL, 1023ULL, 2047ULL, 4095ULL, 8191ULL, 16383ULL, 32767ULL, 65535ULL, 131071ULL, 262143ULL, 524287ULL, 1048575ULL, 2097151ULL, 4194303ULL, 8388607ULL, 16777215ULL, 33554431ULL, 67108863ULL, 134217727ULL, 268435455ULL, 536870911ULL, 1073741823ULL, 2147483647ULL, 4294967295ULL, 8589934591ULL, 17179869183ULL, 34359738367ULL, 68719476735ULL, 137438953471ULL, 274877906943ULL, 549755813887ULL, 1099511627775ULL, 2199023255551ULL, 4398046511103ULL, 8796093022207ULL, 17592186044415ULL, 35184372088831ULL, 70368744177663ULL, 140737488355327ULL, 281474976710655ULL, 562949953421311ULL, 1125899906842623ULL, 2251799813685247ULL, 4503599627370495ULL, 9007199254740991ULL, 18014398509481983ULL, 36028797018963967ULL, 72057594037927935ULL, 144115188075855871ULL, 288230376151711743ULL, 576460752303423487ULL, 1152921504606846975ULL, 2305843009213693951ULL, 4611686018427387903ULL, 9223372036854775807ULL};

    inline static constexpr u64 ctz(const u64& value){
        // 1010100010101000101010001010100010101000101010001010100010101000 -> 3
        // 1010100010101000101010001010100010101000101010001010100010101001 -> 0
        // 1010100010101000101010001010100010101000101010001010100010100000 -> 5
        // 0000000000000000000000000000000000000000000000000000000000000000 -> undef
        return __builtin_ctzll(value);
    }
    inline static constexpr u64 clz(const u64& value){
        // 0000100010101000101010001010100010101000101010001010100010101000 -> 63 - 4 = 59
        // 1000100010101000101010001010100010101000101010001010100010101000 -> 63 - 0 = 63
        // 0000000010101000101010001010100010101000101010001010100010101000 -> 63 - 9 = 54
        // 0000000000000000000000000000000000000000000000000000000000000000 -> undef
        return word_size - 1 - __builtin_clzll(value);
    }

    template<u64 length, u64 ZZ=length> class Inner{
    private:        
        static_assert(length%word_size==0);
        inline static constexpr u64 child_length = length/word_size;
        u64 node;
        array<Inner<child_length, child_length>, word_size> child;
    public:
        Inner(): node(0ULL),child() {}
        bool insert_impl(const u64& value) {
            u64 idx = value / (child_length);
            node |= pow2[idx];
            return child[idx].insert_impl(value % child_length);
        }
        bool erase_impl(const u64& value) {
            u64 idx = value / (child_length);
            bool is_exist_child_node = child[idx].erase_impl(value % child_length);
            if(!is_exist_child_node) node &= ~pow2[idx];
            return node;
        }
        bool count_impl(const u64& value) const {
            u64 idx = value / (child_length);
            return (node & pow2[idx]) && child[idx].count_impl(value % child_length);
        }
        u64 next_lower_bound_impl(const u64& value) const {
            u64 idx = value / (child_length);
            if(node & pow2[idx]) {
                const u64 res = child[idx].next_lower_bound_impl(value % child_length);
                if(res != max_length) return idx*child_length + res;
            }
            u64 masked_node = (node & next_upper_bound_mask[idx]);
            if(masked_node==0) return max_length;
            {
                u64 idx2=ctz(masked_node);
                u64 res = child[idx2].next_lower_bound_impl(0);
                return idx2*child_length + res;
            }
        }
        u64 prev_lower_bound_impl(const u64& value) const {
            u64 idx = value / (child_length);
            if(node & pow2[idx]) {
                const u64 res = child[idx].prev_lower_bound_impl(value % child_length);
                if(res != max_length) return idx*child_length + res;
            }
            u64 masked_node = (node & prev_upper_bound_mask[idx]);
            if(masked_node==0) return max_length;
            {
                u64 idx2=clz(masked_node);
                u64 res = child[idx2].prev_lower_bound_impl(child_length - 1);
                return idx2*child_length + res;
            }
        }
    };
    template<unsigned long long length> class Inner<length, word_size>{
    private:
        u64 node;
    public:
        Inner(): node(0ULL){}
        bool insert_impl(const u64& idx) {
            bool is_inserted = (node & pow2[idx]);
            node |= pow2[idx];
            return !is_inserted;        
        }
        bool erase_impl(const u64& idx) {
            bool is_inserted = (node & pow2[idx]);
            node &= ~pow2[idx];
            return node;
        }
        bool count_impl(const u64& idx) const {
            return (node & pow2[idx]);
        }
        u64 next_lower_bound_impl(const u64& idx) const {
            u64 masked_node = (node & next_lower_bound_mask[idx]);
            if(masked_node==0) return max_length;
            return ctz(masked_node);
        }
        u64 prev_lower_bound_impl(const u64& idx) const {
            u64 masked_node = (node & prev_lower_bound_mask[idx]);
            if(masked_node==0) return max_length;
            return clz(masked_node);
        }
    };
    Inner<max_length> inner;
public:
    WordSizeTreeSet():inner(){}
    void insert(const u64& value){inner.insert_impl(value);}
    void erase(const u64& value){inner.erase_impl(value);}
    bool count(const u64& value) const {return inner.count_impl(value);}
    u64 next_lower_bound(const u64& value) const {return inner.next_lower_bound_impl(value);}
    u64 prev_lower_bound(const u64& value) const {return inner.prev_lower_bound_impl(value);}
};

/**
 * @url 
 * @est
 */ 
int main() {
    cin.tie(0);ios::sync_with_stdio(false);

    int N,Q; read(N);read(Q);
    string T; read(T);
    WordSizeTreeSet wsts;
    for(int i=0;i<N;++i) if(T[i]=='1') wsts.insert(i);
    while(Q--) {
        unsigned long long q,k;
        read(q); read(k);
        if(q==0) {
            wsts.insert(k);
        }
        if(q==1) {
            wsts.erase(k);
        }
        if(q==2) {
            cout << wsts.count(k) << "\n";
        }
        if(q==3) {
            unsigned long long t = wsts.next_lower_bound(k);
            long long v = (t==WordSizeTreeSet::max_length ? -1 : (long long)t);
            cout << v << "\n";
        }
        if(q==4) {
            unsigned long long t = wsts.prev_lower_bound(k);
            long long v = (t==WordSizeTreeSet::max_length ? -1 : (long long)t);
            cout << v << "\n";
        }
    }

    return 0;
}
