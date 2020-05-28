#include <iostream>
#include <vector>
#include <numeric>
#include <cmath>
#include <algorithm>
using namespace std;

//points = {x, y}
class Argument {
public:
    template<class T> inline static vector<int> sort_by_atan2l(vector<pair<T,T>> points){
        int N = points.size();
        vector<long double> arg(N);
        for(int i = 0; i < N; ++i) arg[i] = atan2l(points[i].second,points[i].first);
        vector<int> res(N);
        iota(res.begin(),res.end(),0);
        sort(res.begin(),res.end(),[&](int l,int r){return arg[l] < arg[r];});
        return res;
    }
};

int main(void){
    int N; cin >> N;
    vector<pair<long long,long long>> points(N);
    for(int i = 0; i < N; ++i) {
        long long a,b; cin >> a >> b;
        points[i] = {a,b};
    }
    auto idx = Argument::sort_by_flaction<long long>(points);
    for(int i = 0; i < N; ++i) {
        cout << points[idx[i]].first << " " << points[idx[i]].second << endl; 
    }
}
