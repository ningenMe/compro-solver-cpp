#pragma GCC target("avx2")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

class Mod{
public:
	//Pow_Mod O(log(n))
	inline static long long pow(long long x, long long n, long long mod) {
		long long res = 1;
		for (x %= mod; n > 0; n >>= 1, (x *= x) %= mod) if (n & 1) (res *= x) %= mod;
		return res;
	}
	//Inv_Mod O(log(mod))
	inline static long long inv(long long x, long long mod){
		return pow(x,mod-2,mod); 
	}
};

int main() {
	long long A,B,C;
	scanf("%lld%lld%lld",&A,&B,&C);
	long long ans = 0;
	array<long long,100001> cnt;
	for(long long i = 1; i <= C; ++i) {
		cnt[i] = Mod::pow(i,B,C);
	}
	for(long long i = 1; i <= A%C; ++i) {
		ans += cnt[i];
	}
	ans += (accumulate(cnt.begin(),cnt.begin()+C,0LL)%C)*(A/C);
	printf("%lld\n",ans%C);
    return 0;
}