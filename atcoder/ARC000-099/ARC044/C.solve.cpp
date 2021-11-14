#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define ALL(obj) (obj).begin(),(obj).end()
template <class T> void chmin(T& a, const T b){a=min(a,b);}

int main() {
	cin.tie(0);ios::sync_with_stdio(false);
	int W,H,Q; cin >> W >> H >> Q;
	constexpr int M=100001;
	array<vector<int>,M> query_x,query_y;
	while(Q--){
		int t,d,x; cin >> t >> d >> x;
		(d?query_y:query_x)[t].push_back(x);
	}
	ll inf = 1LL<<40;

	array<ll,M> sum_x;
	array<pair<int,int>,M> safe_x;
	for(int i=0;i<W+2;++i) safe_x[i]={i,i};

	array<ll,M> sum_y;
	array<pair<int,int>,M> safe_y;
	for(int i=0;i<H+2;++i) safe_y[i]={i,i};

	for(int t=0;t<M;++t) {
		sort(ALL(query_x[t]),greater<>());
		for(int x:query_x[t]) safe_x[x].second=safe_x[x+1].second;
		reverse(ALL(query_x[t]));
		for(int x:query_x[t]) safe_x[x].first=safe_x[x-1].first;
		for(int x:query_x[t]) {
			ll c=sum_x[x];
			sum_x[x]=inf;
			int r = safe_x[x].second;
			chmin(sum_x[r],c+r-x);
			int l = safe_x[x].first;
			chmin(sum_x[l],c+x-l);
		}
		for(int x:query_x[t]) safe_x[x]={x,x};

		sort(ALL(query_y[t]),greater<>());
		for(int y:query_y[t]) safe_y[y].second=safe_y[y+1].second;
		reverse(ALL(query_y[t]));
		for(int y:query_y[t]) safe_y[y].first=safe_y[y-1].first;
		for(int y:query_y[t]) {
			ll c=sum_y[y];
			sum_y[y]=inf;
			int r = safe_y[y].second;
			chmin(sum_y[r],c+r-y);
			int l = safe_y[y].first;
			chmin(sum_y[l],c+y-l);
		}
		for(int y:query_y[t]) safe_y[y]={y,y};
	}
	ll ans = 0;
	ans += *min_element(sum_y.begin()+1,sum_y.begin()+H+1);
	ans += *min_element(sum_x.begin()+1,sum_x.begin()+W+1);
	if(ans >= inf) ans = -1;
	cout << ans << endl;
    return 0;
}