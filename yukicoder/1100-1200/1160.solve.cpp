#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;
template <class T> void chmax(T& a, const T b){a=max(a,b);}

int main() {
	int N; cin >> N;
	long long dp0,dp1;
	N--;
	{
		long long p,a; cin >> p >> a;
		dp0=p,dp1=a;
	}
	while(N--) {
		long long p,a,tp0=dp0,tp1=dp1; cin >> p >> a;
		chmax(dp0,tp0+p);
		chmax(dp0,tp1+2*p);
		chmax(dp1,tp0+a);
		chmax(dp1,tp1+2*a);
	}
	cout << max(dp0,dp1) << endl;
    return 0;
}