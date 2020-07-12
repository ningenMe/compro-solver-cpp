#include <bits/stdc++.h>
using namespace std;
using ll = long long;
constexpr long long MOD = (long long)1e9 + 7;

int main() {
    string S; cin >> S;
    vector<ll> dp(13,0);
    int N = S.size();
    
    //1桁目が数字ならその値で初期化
    if(S[0]!='?') dp[S[0]-'0']++;
    //そうじゃないなら0-9を初期化
    else for(int i = 0; i < 10; ++i) dp[i]++;

    //上の桁からdp
    for(int i = 1; i < N; ++i){
        vector<ll> tmp(13,0);
        if(S[i]=='?'){
            for(int k = 0; k < 10; ++k){
                for(int j = 0; j < 13; ++j){
                    (tmp[(j*10+k)%13] += dp[j]) %= MOD;
                }
            }
        }
        else{
            int m = S[i] - '0';
            for(int j = 0; j < 13; ++j){
                (tmp[(j*10+m)%13] += dp[j]) %= MOD;
            }
        }
        dp = tmp;
    }
    cout << dp[5] << endl;
    return 0;
}
