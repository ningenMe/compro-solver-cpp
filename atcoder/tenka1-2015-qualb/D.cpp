#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define ALL(obj) (obj).begin(),(obj).end()
#define SPEED cin.tie(0);ios::sync_with_stdio(false);

template<class T> using PQ = priority_queue<T>;
template<class T> using PQR = priority_queue<T,vector<T>,greater<T>>;

constexpr long long MOD = (long long)1e9 + 7;
constexpr long long MOD2 = 998244353;
constexpr long long HIGHINF = (long long)1e18;
constexpr long long LOWINF = (long long)1e15;
constexpr long double PI = 3.1415926535897932384626433L;

template <class T> vector<T> multivector(size_t N,T init){return vector<T>(N,init);}
template <class... T> auto multivector(size_t N,T... t){return vector<decltype(multivector(t...))>(N,multivector(t...));}
template <class T> void corner(bool flg, T hoge) {if (flg) {cout << hoge << endl; exit(0);}}
template <class T, class U>ostream &operator<<(ostream &o, const map<T, U>&obj) {o << "{"; for (auto &x : obj) o << " {" << x.first << " : " << x.second << "}" << ","; o << " }"; return o;}
template <class T>ostream &operator<<(ostream &o, const set<T>&obj) {o << "{"; for (auto itr = obj.begin(); itr != obj.end(); ++itr) o << (itr != obj.begin() ? ", " : "") << *itr; o << "}"; return o;}
template <class T>ostream &operator<<(ostream &o, const multiset<T>&obj) {o << "{"; for (auto itr = obj.begin(); itr != obj.end(); ++itr) o << (itr != obj.begin() ? ", " : "") << *itr; o << "}"; return o;}
template <class T>ostream &operator<<(ostream &o, const vector<T>&obj) {o << "{"; for (int i = 0; i < (int)obj.size(); ++i)o << (i > 0 ? ", " : "") << obj[i]; o << "}"; return o;}
template <class T, class U>ostream &operator<<(ostream &o, const pair<T, U>&obj) {o << "{" << obj.first << ", " << obj.second << "}"; return o;}
template <template <class tmp>  class T, class U> ostream &operator<<(ostream &o, const T<U> &obj) {o << "{"; for (auto itr = obj.begin(); itr != obj.end(); ++itr)o << (itr != obj.begin() ? ", " : "") << *itr; o << "}"; return o;}
void print(void) {cout << endl;}
template <class Head> void print(Head&& head) {cout << head;print();}
template <class Head, class... Tail> void print(Head&& head, Tail&&... tail) {cout << head << " ";print(forward<Tail>(tail)...);}
template <class T> void chmax(T& a, const T b){a=max(a,b);}
template <class T> void chmin(T& a, const T b){a=min(a,b);}
void YN(bool flg) {cout << (flg ? "YES" : "NO") << endl;}
void Yn(bool flg) {cout << (flg ? "Yes" : "No") << endl;}
void yn(bool flg) {cout << (flg ? "yes" : "no") << endl;}

int main() {
	string S; cin >> S;
	corner(S.size()==1,S);
	map<char,int> isCapital;
	map<char,int> isLower;
	map<char,char> toCapital;
	map<char,char> toLower;
	for(int i = 0; i < 26; ++i) isCapital[char('A'+i)] = 1;
	for(int i = 0; i < 26; ++i) isLower[char('a'+i)] = 1;
	for(int i = 0; i < 26; ++i) toLower[char('A'+i)] = char('a'+i);
	for(int i = 0; i < 26; ++i) toLower[char('a'+i)] = char('a'+i);
	for(int i = 0; i < 10; ++i) toLower[char('0'+i)] = char('0'+i);
	for(int i = 0; i < 26; ++i) toCapital[char('a'+i)] = char('A'+i);
	for(int i = 0; i < 26; ++i) toCapital[char('A'+i)] = char('A'+i);
	for(int i = 0; i < 10; ++i) toCapital[char('0'+i)] = char('0'+i);


	string pre="",suf="";
	while(!S.empty() && S.front()=='_'){
		pre.push_back(S.front());
		S = S.substr(1,S.size());
	}
	while(!S.empty() && S.back()=='_'){
		suf.push_back(S.back());
		S.pop_back();
	}
	int lowerFlag = 1;
	int capitalFlag = 1;
	for(char c:S) {
		if(isCapital[c]) lowerFlag = 0;
		if(c=='_') capitalFlag = 0;
	}
	corner(!lowerFlag && !capitalFlag,pre+S+suf);
	corner(lowerFlag && capitalFlag,pre+S+suf);

	for(int i = 0; i+1 < S.size() && lowerFlag; ++i) {
		corner(S[i]=='_' && !isLower[S[i+1]],pre+S+suf);
		corner(isCapital[S[i]] && isCapital[S[i+1]],pre+S+suf);
	}
	
	string T = "";


	vector<string> VS;
	for(int i = 0; i < S.size();) {
		string T;
		if(S[i]=='_'){
			while(i<S.size() && S[i]=='_'){
				T.push_back(S[i]);
				i++;
			}
			VS.push_back(T);			
		}
		else{
			while(i<S.size() && S[i]!='_'){
				T.push_back(S[i]);
				i++;
			}
			VS.push_back(T);			
		}
	}
	
	int anscoFlg = 1;
	for(int i = 0; i < VS.size(); ++i) {
		if(VS[i].front()=='_') continue;
		corner(!isLower[VS[i].front()],S);
		for(char c:VS[i]) if(isCapital[c]) anscoFlg = 0;
	}
	string ans;
	if (anscoFlg) {
		for(int i = 0; i < S.size(); ++i) {
			if(S[i]=='_'){
				i++;
				T.push_back(toCapital[S[i]]);
			}
			else{
				T.push_back(S[i]);
			}
		}
		cout << pre+T+suf << endl;
		return 0;
	}
	else{
		corner(!isLower[S.front()],pre+S+suf);
		for(int i = 0; i < S.size(); ++i) {
			if(isCapital[S[i]]){
				T.push_back('_');
			}
			T.push_back(toLower[S[i]]);
		}
		cout << pre+T+suf << endl;
		return 0;
	}

    return 0;
}
