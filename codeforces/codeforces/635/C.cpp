#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define ALL(obj) (obj).begin(),(obj).end()
#define SPEED cin.tie(0);ios::sync_with_stdio(false);

template<class T> using PQ = priority_queue<T>;
template<class T> using PQR = priority_queue<T,vector<T>,greater<T>>;

constexpr long long MOD = (long long)1e9 + 7;
constexpr long long MOD2 = 998244353;

int main() {
	SPEED
    string S,T,U; cin >> S >> T;
    ll N = S.size();
	ll M = T.size();
	U = T;
	for(int i = M; i < N; ++i) U.push_back('.');
    ll ans = 0;
	vector<vector<ll>> dp(N,vector<ll>(N,0));
	for(int i = 0; i < N; ++i){
		if(S[0]==U[i] || U[i]=='.') dp[i][i] += 2;
	}
	for(int i = 1; i < N; ++i){
		for(int j = 0; j < N; ++j){
			int l = j, r = l + i-1;
			if(0<=l-1 && r < N && (S[i]==U[l-1] || U[l-1]=='.')) (dp[l-1][r] += dp[l][r]) %= MOD2;
			if(0<= l  && r+1<N  && (S[i]==U[r+1] || U[r+1]=='.')) (dp[l][r+1] += dp[l][r]) %= MOD2;
		}
	}
	for(int i = M-1; i < N; ++i) (ans += dp[0][i]) %= MOD2;
    cout << ans << endl;
    return 0;
}
