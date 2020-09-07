#include <bits/stdc++.h>
using namespace std;

class Prime{
	using int128 = __int128_t;
	using int64  = long long;
	long long pow(long long x, long long n, long long mod) {
		long long res = 1;
		for (x %= mod; n > 0; n >>= 1, x=(int128(x)*x)%mod) if (n & 1) res = (int128(res)*x)%mod;
		return res;
	}
public:
	int miller_rabin(const int64 n) {
        if(n == 2) return 1;
        if(n < 2 || n%2 == 0) return 0;
		int64 m = n - 1;
		for (;!(m&1);m>>=1);
		for (int64 a: {2,325,9375,28178,450775,9780504,1795265022}) {
			if(a>=n) break;
            int64 x=m,r=pow(a,x,n);
            for(;x != n-1 && r != 1 && r != n-1;x <<= 1) r = (int128(r)*r)%n;
            if(r!=n-1 && x%2==0) return 0;
		}
		return 1;
	}
};

int main() {
	cin.tie(0);ios::sync_with_stdio(false);
    long long N; cin >> N;
	Prime P;
    for(int i = 0; i < N; ++i) {
		long long A; cin >> A;
		cout << A << " " << P.miller_rabin(A) << "\n";
	}
    return 0;
}
