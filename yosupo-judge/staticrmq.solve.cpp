#include <iostream>
#include <vector>
#include <numeric>
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
 * @title SparseTable
 * @docs md/data-structure/range-query/SparseTable.md
 */
template<class Operator> class SparseTable{
public:
    using TypeNode = typename Operator::TypeNode;
    vector<TypeNode> node;
    vector<size_t> idx;
    size_t depth;
    size_t length;

    SparseTable(const vector<TypeNode>& vec) {
        for(depth = 0;(1<<depth)<=vec.size();++depth);
        length = (1<<depth);
        node.resize(depth*length);
        for(int i = 0; i < vec.size(); ++i) node[i] = vec[i];
        for(int i = 1; i < depth; ++i) for(int j = 0; j + (1<<i) < (1<<depth); ++j) node[i*length+j] = Operator::func_fold(node[(i-1)*length+j],node[(i-1)*length+j + (1 << (i-1))]);
        idx.resize(vec.size()+1);
        for(int i = 2; i < vec.size()+1; ++i) idx[i] = idx[i>>1] + 1;
    }

    //[l,r)
    TypeNode fold(const int l,const int r) {
        size_t bit = idx[r-l];
        return Operator::func_fold(node[bit*length+l],node[bit*length+r - (1<<bit)]);
    }
};

template<class T> struct NodeMin {
    using TypeNode = T;
    inline static constexpr TypeNode unitNode = 1LL<<31;
    inline static constexpr TypeNode func_fold(TypeNode l,TypeNode r){return min(l,r);}
};


int main(){
	cin.tie(0);ios::sync_with_stdio(false);
    int N,Q; 
	read(N); read(Q);
    vector<long long> A(N);
    for(int i = 0; i < N; ++i) {
        read(A[i]);
    }
    SparseTable<NodeMin<long long>> st(A);
    while(Q--){
        int l,r; 
		read(l);read(r);
        cout << st.fold(l,r) << "\n";
    }
}

