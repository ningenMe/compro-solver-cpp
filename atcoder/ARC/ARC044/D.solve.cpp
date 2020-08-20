#include <bits/stdc++.h>
using namespace std;
using ll = long long;

array<int,1000002> A,B,X;
int main() {
    cin.tie(0);ios::sync_with_stdio(false);
	int N,maxi=0; cin >> N;
	for(int i = 1; i <= N; ++i) cin >> A[i];
	for(int i = 1; i <= N; ++i) B[A[i]]=i;
	for(int i = 1; i+1 <= N; ++i) {
		int& a = A[i];
		int& b = A[i+1];
		X[b] = X[a]+(B[a+1] > B[b+1]);
		maxi = max(maxi,X[b]);
	}
	if(maxi > 25){
		cout << -1 << "\n";
		return 0;
	}
	string ans;
	for(int i = 1; i <= N; ++i) ans.push_back(char('A'+X[i]));
	ans.push_back('\n');
	cout << ans;
    return 0;
}
