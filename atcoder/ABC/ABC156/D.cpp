#include <bits/stdc++.h>
using namespace std;
#define ALL(obj) (obj).begin(),(obj).end()

int main() {
    cin.tie(0);ios::sync_with_stdio(false);
    int N,K; cin >> N >> K;
    vector<int> A(N+1,0);
    for(int i = 1; i <= N; ++i) cin >> A[i];
    sort(ALL(A));
    int ng = 0, ok = N+1,md;
    const size_t M = 5000;
    while(ok-ng>1){
        md = (ok+ng)/2;
        bitset<M+1> dp;
        dp.set(0);
        for(int i = 0; i <= N; ++i) {
            if(i==md) continue;
            dp |= (dp<<A[i]);
        } 
        int flg = 0;
        for(int i = 0; i < K; ++i) {
            if(dp[i]&&i+A[md]>=K) flg = 1;
        }
        (flg?ok:ng)=md;
    }
    cout << ok-1 << endl;
    return 0;
}
