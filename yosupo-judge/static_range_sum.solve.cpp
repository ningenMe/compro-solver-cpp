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

/*
 * @title DisjointSparseTable
 * @docs md/data-structure/range-query/DisjointSparseTable.md
 */
template<class Operator> class DisjointSparseTable{
public:
    using TypeNode = typename Operator::TypeNode;
    size_t depth;
    size_t length;
    vector<TypeNode> node;
    vector<size_t> msb;

    DisjointSparseTable(const vector<TypeNode>& vec) {
        for(depth = 0;(1<<depth)<=vec.size();++depth);
        length = (1<<depth);

        //msb
        msb.resize(length,0);
        for(int i = 0; i < length; ++i) for(int j = 0; j < depth; ++j) if(i>>j) msb[i] = j;

        //init value
        node.resize(depth*length,Operator::unit_node);
        for(int i = 0; i < vec.size(); ++i) node[i] = vec[i];

        for(int i = 1; i < depth; ++i) {
            for(int r = (1<<i),l = r-1; r < length; r += (2<<i),l = r-1){
                //init accumulate
                node[i*length+l] = node[l];
                node[i*length+r] = node[r];
                //accumulate
                for(int k = 1; k < (1<<i); ++k) {
                    node[i*length+l-k] = Operator::func_fold(node[i*length+l-k+1],node[l-k]);
                    node[i*length+r+k] = Operator::func_fold(node[i*length+r+k-1],node[r+k]);
                }
            }
        }
    }

    //[l,r)
    TypeNode fold(int l,int r) const {
        r--;
        return (l>r||l<0||length<=r) ? Operator::unit_node: (l==r ? node[l] : Operator::func_fold(node[msb[l^r]*length+l],node[msb[l^r]*length+r]));
    }
};

//sum
template<class T> struct NodeSum {
    using TypeNode = T;
    inline static constexpr TypeNode unit_node = 0;
    inline static constexpr TypeNode func_fold(TypeNode l,TypeNode r){return l+r;}
};


int main(){
	cin.tie(0);ios::sync_with_stdio(false);
    int N,Q; 
	read(N); read(Q);
    vector<long long> A(N);
    for(int i = 0; i < N; ++i) {
        read(A[i]);
    }
    DisjointSparseTable<NodeSum<long long>> st(A);
    while(Q--){
		int l,r;
		read(l); read(r);
        cout << st.fold(l,r) << "\n";
    }
}

