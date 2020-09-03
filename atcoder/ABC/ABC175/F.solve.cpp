#pragma GCC target("avx2")
#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define ALL(obj) (obj).begin(),(obj).end()
template<class T> using priority_queue_reverse = priority_queue<T,vector<T>,greater<T>>;
constexpr long long LOWINF = (long long)1e15;

template <class T> void chmin(T& a, const T b){a=min(a,b);}
inline bool is_palindrome(const string& s) {
    for(int i = 0; i < s.size()/2; ++i) if(s[i] != s[s.size()-1-i]) return 0;
    return 1;
}

map<string,int> prefix,suffix;
array<ll,50> C;
array<map<string,ll>,100> dp;
priority_queue_reverse<tuple<ll,int,string>> pq;

int main() {
    cin.tie(0);ios::sync_with_stdio(false);
    int N; cin >> N;

    for(int i = 0; i < N; ++i) {
        string R; cin >> R >> C[i];
        string S = R;
        reverse(ALL(R));
        if(!prefix.count(S)) prefix[S]=i;
        else {
            int j = prefix[S];
            if(C[i]<C[j]) prefix[S] = i;
        }
        if(!suffix.count(R)) suffix[R]=N+i;
        else {
            int j = suffix[R];
            if(C[i]<C[j]) suffix[R] = i;
        }
        dp[i][S]=C[i];
        pq.push({C[i],i,S});
    }

    ll ans = LOWINF;
    while(pq.size()) {
        auto t = pq.top(); pq.pop();
        ll f_cost = get<0>(t);
        int f_point = get<1>(t);
        string f_rest = get<2>(t);
        
        if(is_palindrome(f_rest)) {
            chmin(ans,f_cost);
            continue;
        }
        if(dp[f_point][f_rest] < f_cost) continue;

        int M = f_rest.size();
        if(f_point < N) {

            for(int i = 1; i <= M; ++i) {
                auto str = f_rest.substr(0,i);
                if(!suffix.count(str)) continue;
                auto& weight = C[suffix[str]%N];

                ll t_cost = f_cost + weight;
                int t_point = f_point;
                string t_rest = f_rest.substr(i);

                if(!dp[t_point].count(t_rest)) dp[t_point][t_rest] = LOWINF;
                if(dp[t_point][t_rest] > t_cost) {
                    dp[t_point][t_rest] = t_cost;
                    pq.push({t_cost,t_point,t_rest});
                }
            }

            for(auto& p:suffix){
                if(f_rest.size() >= p.first.size()) continue;
                if(f_rest != p.first.substr(0,M)) continue;

                auto& weight = C[p.second%N];
                ll t_cost = f_cost + weight;
                int t_point = p.second;
                string t_rest = p.first.substr(M);

                if(!dp[t_point].count(t_rest)) dp[t_point][t_rest] = LOWINF;
                if(dp[t_point][t_rest] > t_cost) {
                    dp[t_point][t_rest] = t_cost;
                    pq.push({t_cost,t_point,t_rest});
                }
            }
        }
        else {

            for(int i = 1; i <= M; ++i) {
                auto str = f_rest.substr(0,i);
                if(!prefix.count(str)) continue;
                auto& weight = C[prefix[str]%N];

                ll t_cost = f_cost + weight;
                int t_point = f_point;
                string t_rest = f_rest.substr(i);

                if(!dp[t_point].count(t_rest)) dp[t_point][t_rest] = LOWINF;
                if(dp[t_point][t_rest] > t_cost) {
                    dp[t_point][t_rest] = t_cost;
                    pq.push({t_cost,t_point,t_rest});
                }
            }

            for(auto& p:prefix){
                if(f_rest.size() >= p.first.size()) continue;
                if(f_rest != p.first.substr(0,M)) continue;

                auto& weight = C[p.second%N];
                ll t_cost = f_cost + weight;
                int t_point = p.second;
                string t_rest = p.first.substr(M);

                if(!dp[t_point].count(t_rest)) dp[t_point][t_rest] = LOWINF;
                if(dp[t_point][t_rest] > t_cost) {
                    dp[t_point][t_rest] = t_cost;
                    pq.push({t_cost,t_point,t_rest});
                }
            }
        }

    }
    if(ans == LOWINF) ans = -1;
    cout << ans << endl;
}
