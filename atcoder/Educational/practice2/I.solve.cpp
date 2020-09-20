#include <vector>
#include <iostream>
#include <numeric>
#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;

int main(){
    cin.tie(0);ios::sync_with_stdio(false);
    string s; cin >> s;
    long long n = s.size();
    vector<int> sa = atcoder::suffix_array(s);
    long long ans = n*(n+1)/2;
    for (auto x : atcoder::lcp_array(s, sa)) {
        ans -= x;
    }
    cout << ans << endl;
    return 0;
}
