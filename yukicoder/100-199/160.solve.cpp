#include <bits/stdc++.h>
using namespace std;
template<class T> using priority_queue_reverse = priority_queue<T,vector<T>,greater<T>>;

int main() {
    cin.tie(0);ios::sync_with_stdio(false);
    int N,M,S,G;
    cin >> N >> M >> S >> G;
    vector<vector<pair<int,int>>> edge(N);
    for(int i=0;i<M;++i){
        int a,b,c; cin >> a >> b >> c;
        edge[a].push_back({b,c});
        edge[b].push_back({a,c});
    }
    for(int i=0;i<N;++i) sort(edge[i].begin(),edge[i].end());
    int inf = 12345678;
    vector<int> dp(N,inf);
    priority_queue_reverse<pair<int,int>> pq;
    dp[G]=0;
    pq.push({0,G});
    while(pq.size()) {
        auto p = pq.top(); pq.pop();
        int from = p.second;
        if(p.first > dp[from]) continue;
        for(auto q:edge[from]) {
            int to = q.first;
            if(dp[to] > dp[from]+q.second) {
                dp[to] = dp[from]+q.second;
                pq.push({dp[to],to});
            }
        }
    }
    vector<int> ans = {S};
    int sum = 0;
    while(ans.back()!=G) {
        int from = ans.back();
        for(auto q:edge[from]) {
            int to = q.first;
            if(sum + q.second + dp[to] == dp[S]) {
                ans.push_back(to);
                sum += q.second;
                break;
            }
        }
    }
    for(int i=0;i<ans.size();++i) cout << ans[i] << " \n"[i==ans.size()-1];
    return 0;
}
