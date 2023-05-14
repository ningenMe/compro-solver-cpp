#include <bits/stdc++.h>
using namespace std;
using int128 = __int128_t;
using int64 = long long;

class FastI{
private:
    inline static constexpr int ch_0='0';
    inline static constexpr int ch_9='9';
    template<typename T> inline static void readint(T &x) {
        int neg=0; char ch; x=0;
        ch=getchar();
        if(ch=='-') neg=1,ch=getchar();
        for(;(ch_0 <= ch && ch <= ch_9); ch = getchar()) x = x*10 + (ch-ch_0);
        if(neg) x*=-1;
    }
public:
    inline static void read(int &x) {readint<int>(x);}
    inline static void read(long long &x) {readint<long long>(x);}
};
#define read(arg) FastI::read(arg)

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t; read(t);
    while(t--) {
        int64 x,y; read(x);read(y);
        cout << x+y << "\n";
    }
    return 0;
}
