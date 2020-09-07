#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define ALL(obj) (obj).begin(),(obj).end()

template <class T, class U>ostream &operator<<(ostream &o, const map<T, U>&obj) {o << "{"; for (auto &x : obj) o << " {" << x.first << " : " << x.second << "}" << ","; o << " }"; return o;}
template <class T>ostream &operator<<(ostream &o, const set<T>&obj) {o << "{"; for (auto itr = obj.begin(); itr != obj.end(); ++itr) o << (itr != obj.begin() ? ", " : "") << *itr; o << "}"; return o;}
template <class T>ostream &operator<<(ostream &o, const multiset<T>&obj) {o << "{"; for (auto itr = obj.begin(); itr != obj.end(); ++itr) o << (itr != obj.begin() ? ", " : "") << *itr; o << "}"; return o;}
template <class T>ostream &operator<<(ostream &o, const vector<T>&obj) {o << "{"; for (int i = 0; i < (int)obj.size(); ++i)o << (i > 0 ? ", " : "") << obj[i]; o << "}"; return o;}
template <class T, class U>ostream &operator<<(ostream &o, const pair<T, U>&obj) {o << "{" << obj.first << ", " << obj.second << "}"; return o;}
void print(void) {cout << endl;}
template <class Head> void print(Head&& head) {cout << head;print();}
template <class Head, class... Tail> void print(Head&& head, Tail&&... tail) {cout << head << " ";print(forward<Tail>(tail)...);}
/*
 * @title Gcd
 */
class Gcd{
	inline static long long impl(long long n, long long m) {
		static constexpr long long K = 5;
		long long t,s;
		for(int i = 0; t = n - m, s = n - m * K, i < 80; ++i) {
			if(t<m){
				if(!t) return m;
				n = m, m = t;
			}
			else{
				if(!m) return t;
				n=t;
				if(t >= m * K) n = s;
			}
		}
		return impl(m, n % m);
	}
	inline static long long pre(long long n, long long m) {
		long long t;
		for(int i = 0; t = n - m, i < 4; ++i) {
			(t < m ? n=m,m=t : n=t);
			if(!m) return n;
		}
		return impl(n, m);
	}
public:
	inline static long long gcd(long long n, long long m) {
		return (n>m ? pre(n,m) : pre(m,n));
	}
	inline static constexpr long long pureGcd(long long a, long long b) {
		return (b ? pureGcd(b, a % b):a);
	}
	inline static constexpr long long lcm(long long a, long long b) {
		return (a*b ? (a / gcd(a, b)*b): 0);
	}
	inline static constexpr long long extGcd(long long a, long long b, long long &x, long long &y) {
		if (b == 0) return x = 1, y = 0, a;
		long long d = extGcd(b, a%b, y, x);
		return y -= a / b * x, d;
	}
};

/*
 * @title Prime
 */
class Prime{
	using int128 = __int128_t;
	using int64  = long long;
	long long pow(long long x, long long n, long long mod) {
		long long res = 1;
		for (x %= mod; n > 0; n >>= 1, x=(int128(x)*x)%mod) if (n & 1) res = (int128(res)*x)%mod;
		return res;
	}
    int64 rho(int64 n){
        if(miller_rabin(n)) return n;
        if(n%2 == 0) return 2;
        for(int64 c=1,x=2,y=2,d;;c++){
            do{
                x=(int128(x)*x+c)%n;
                y=(int128(y)*y+c)%n;
                y=(int128(y)*y+c)%n;
                d=Gcd::gcd(x-y+n,n);
            }while(d==1);
            if(d<n) return d;
        }
    }
    vector<int64> factor(int64 n) {
        if(n <= 1) return {};
        int64 p = rho(n);
        if(p == n) return {p};
        auto l = factor(p);
        auto r = factor(n / p);
        copy(r.begin(), r.end(), back_inserter(l));
        return l;
    }
public:
	int miller_rabin(const int64 n) {
        if(n == 2) return 1;
        if(n < 2 || n%2 == 0) return 0;
		int64 m = n - 1;
		for (;!(m&1);m>>=1);
		for (int64 a: {2,325,9375,28178,450775,9780504,1795265022}) {
			if(a>=n) break;
            int64 x=m,r=pow(a,x,n);
            for(;x != n-1 && r != 1 && r != n-1;x <<= 1) r = (int128(r)*r)%n;
            if(r!=n-1 && x%2==0) return 0;
		}
		return 1;
	}
    vector<pair<int64,int64>> factorization(int64 n) {
        auto v = factor(n);
        vector<pair<int64,int64>> vp;
        sort(v.begin(),v.end());
        int64 prev = 0;
        for(int64 p:v) {
            if(p == prev) vp.back().second++;
            else vp.emplace_back(p,1);
            prev = p;
        }
        return vp;
    }
};


int main() {
    cin.tie(0);ios::sync_with_stdio(false);
    int N, SQRT_A = 100000, p3=0; cin >> N;
    int ans = 0;
    Prime P;
    map<vector<pair<int,int>>,pair<int,int>> mp;
    for(int i = 0; i < N; ++i) {
        ll A; cin >> A;
        vector<pair<int,int>> l,r;
        auto pf = P.factorization(A);
        for(auto p:pf) if(p.second%=3) l.push_back(p);
        if(l.empty()) {
            p3 = 1;
            continue;
        }
        if(l.back().first > SQRT_A) {
            ans++;
            continue;
        }
        for(auto& e:l) r.emplace_back(e.first,3-e.second);
        if(l.front().second > r.front().second) {
            swap(l,r);
            if(!mp.count(l)) mp[l]={0,0};
            mp[l].second++;
        }
        else {
            if(!mp.count(l)) mp[l]={0,0};
            mp[l].first++;
        }
    }
    for(auto& e:mp) ans += max(e.second.first,e.second.second);
    ans += p3;
    cout << ans << endl;
    return 0;
}
