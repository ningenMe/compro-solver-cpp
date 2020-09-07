#include <bits/stdc++.h>
using namespace std;

#define SPEED cin.tie(0);ios::sync_with_stdio(false);
template <class T> void chmax(T& a, const T b){a=max(a,b);}

int main() {
    SPEED
    int N; cin >> N;
    vector<int> V(N+1),W(N+1);
    for(int i = 1; i <= N; ++i) cin >> V[i] >> W[i];

    //O(Q)
    constexpr int nl = 1<<10,L_max=100001;
    array<int,nl> msb;
    for(int i = 1; i < nl; ++i) msb[i]=31-__builtin_clz(i);

    array<int,nl> bit_w_dp;
    array<int,nl> bit_v_dp;
    vector<vector<int>> dp(nl,vector<int>(L_max,0));
    //前計算
    int m = min(nl,N+1);
    for(int n = 1; n < m; ++n) {
        int k = 2*n;
        vector<int> l;
        while(k/=2) l.push_back(k);
        int sz=l.size();
        //bit全探索
        for(int i = 1; i < (1<<sz); ++i) {
            bit_w_dp[i]=bit_w_dp[i^(1<<msb[i])]+W[l[msb[i]]];
            bit_v_dp[i]=bit_v_dp[i^(1<<msb[i])]+V[l[msb[i]]];
            if(bit_w_dp[i]<=L_max) chmax(dp[n][bit_w_dp[i]],bit_v_dp[i]);
        }
        //累積max
        for(int i = 1; i < L_max; ++i) {
            chmax(dp[n][i],dp[n][i-1]);
        }
    }

    int Q; cin >> Q;
    string ans_str="";

    //クエリ
    while(Q--) {
        int p,L,l_idx=0;; cin >> p >> L;
        vector<int> r;
        p *= 2;
        while(p/=2) {
            if(p<nl) chmax(l_idx,p);
            else r.push_back(p);
        }
        int sz = r.size(),ans=dp[l_idx][L];
        //bit全探索
        for(int i = 1; i < (1<<sz); ++i) {
            bit_w_dp[i]=bit_w_dp[i^(1<<msb[i])]+W[r[msb[i]]];
            bit_v_dp[i]=bit_v_dp[i^(1<<msb[i])]+V[r[msb[i]]];
            if(bit_w_dp[i]<=L) chmax(ans,dp[l_idx][L - bit_w_dp[i]]+bit_v_dp[i]);
        }
        ans_str += to_string(ans)+"\n";
    }
    cout << ans_str;

    return 0;
}
