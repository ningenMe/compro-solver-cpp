#pragma GCC optimize ("Ofast")
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
constexpr long long MOD = 1'000'000'007LL;
int main() {
    cin.tie(0);ios::sync_with_stdio(false);
    string S; cin >> S;
    array<ll,26> num={};
    ll acc=0,sum=0,ans=0,pow2=1;
    int i=1;
    for(char& a:S) {
        int c=a-'a';
        ll cnt = 1 + acc + sum + (MOD - num[c]);

        ans += cnt;
        acc += cnt;
        sum += pow2;
        num[c]+= pow2;
        pow2 *= 2;
        if(!((i+=1)%5))continue;
        ans %= MOD;
        acc %= MOD;
        sum %= MOD;
        num[c]%= MOD; 
        pow2 %= MOD;
    }
    cout << ans%MOD << "\n";
    return 0;
}
