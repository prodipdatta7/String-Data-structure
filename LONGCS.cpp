/*...Part - 01...*/

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <cmath>
#include <vector>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <stack>
#include <queue>
#include <deque>
#include <iterator>
#include <bitset>
#include <assert.h>
#include <new>
#include <sstream>
//#include <bits/stdc++.h>
using namespace std ;

/*...Part - 02...*/

typedef long long               ll ;
typedef long double             ld ;
typedef unsigned long long      ull ;
typedef pair<int,int>           pii ;
typedef pair<ll,ll>             pll ;
typedef vector<int>             vi ;
typedef vector<ll>              vll ;
typedef vector<vector<int>>     vvi ;

inline int Int(){int x ; scanf("%d",&x) ; return x ;}
inline ll Long(){ll x ; scanf("%lld",&x) ; return x ;}

/*...Part - 03...*/
/*....Debugger....*/

#define error(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); err(_it, args); }
void err(istream_iterator<string> it) {cout << endl ;}
template<typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {
    cerr << *it << " = " << a << ' ' ;
    err(++it, args...);
}

/*...Part - 04...*/
/*...Needed to change according to problem requirements...*/

const int N          = (int)2e5 + 5 ;
const int maxN       = (int)1e6 + 6 ;
const ll  Mod        = (ll)1e9 + 7 ;
const int inf        = (int)2e9 ;
const ll  Inf        = (ll)1e18 ;
const int mod        = (int)1e9 + 7 ;

/*..........................................................*/
/*...Part - 05...*/

#define     debug(x)    cerr << #x << " = " << x << '\n' ;
#define     rep(i,b,e)  for(__typeof(e) i = (b) ; i != (e + 1) - 2 * ((b) > (e))  ; i += 1 - 2 * ((b) > (e)))
#define     Int         Int()
#define     Long        Long()
#define     all(x)      x.begin() , x.end()
#define     rall(x)     x.rbegin() , x.rend()
#define     sz(x)       (int)x.size()
#define     ff          first
#define     ss          second
#define     pb          push_back
#define     eb          emplace_back
#define     mem(a)      memset(a , 0 ,sizeof a)
#define     memn(a)     memset(a , -1 ,sizeof a)
#define     filein      freopen("input.txt","r",stdin)
#define     fileout     freopen("output.txt","w",stdout)

inline int add(int a, int b, int mod){a += b ;return a >= mod ? a - mod : a ;}
inline int sub(int a, int b, int mod){a -= b ;return a < 0 ? a + mod : a ;}
inline int mul(int a, int b, int mod){return (ll)a * b % mod ;}

/*...Part - 06...*/
/*...... ! Code start from here ! ......*/

struct SuffixArray{
	int get(char c){
		if(c == '$')return 0 ;
		if(c <= '9')return c - '0' + 27 ;
		return c - 'a' + 1 ;
	}
	vi CyclicShift(string s){
		int n = sz(s) ;
		int alpha = 40 ;
		vi p(n), c(n), tmp(n), cnt(max(n, alpha), 0) ;
		for(int i = 0 ; i < n ; ++i)
			++cnt[get(s[i])] ;
		for(int i = 1 ; i < alpha ; ++i)
			cnt[i] += cnt[i - 1] ;
		for(int i = 0 ; i < n ; ++i)
			p[--cnt[get(s[i])]] = i ;
		c[p[0]] = 0 ;
		int sec = 1 ;
		for(int i = 1 ; i < n ; ++i){
			if(s[p[i]] != s[p[i - 1]])++sec ;
			c[p[i]] = sec - 1 ;
		}
		pii cur, prev ;
		for(int h = 0 ; (1 << h) < n ; ++h){
			for(int i = 0 ; i < n  ; ++i){
				tmp[i] = p[i] - (1 << h) ;
				if(tmp[i] < 0)tmp[i] += n ;
			}
			fill(cnt.begin(), cnt.begin() + sec, 0) ;
			for(int i = 0 ; i < n ; ++i)
				cnt[c[tmp[i]]]++ ;
			for(int i = 1 ; i < sec ; ++i)
				cnt[i] += cnt[i - 1] ;
			for(int i = n - 1 ; i >= 0 ; --i)
				p[--cnt[c[tmp[i]]]] = tmp[i] ;
			tmp[p[0]] = 0 ;
			sec = 1 ;
			for(int i = 1 ; i < n ; ++i){
				cur = {c[p[i]], c[(p[i] +(1 << h)) % n]} ;
				prev = {c[p[i - 1]], c[(p[i - 1] +(1 << h)) % n]} ;
				sec += (cur != prev) ;
				tmp[p[i]] = sec - 1 ;
			}
			c.swap(tmp) ;
			if(sec == n)return p ;
		}
		return p ;
	}
	int LCP(string s, vi& p, vi& pos, int cn){
		int n = sz(s) ;
		vi rank(n, 0) ;
		for(int i = 0 ; i < n ; ++i)
			rank[p[i]] = i ;
		int k = 0, res = inf ;
		int mx[cn][cn] ;
		for(int i = 0 ; i < cn ; ++i)for(int j = i + 1 ; j < cn ; ++j)mx[i][j] = 0 ;
		for(int i = 0 ; i < n ; ++i){
			if(rank[i] == n - 1){
				k = 0 ;
				continue ;
			}
			int j = p[rank[i] + 1] ;
			while(i + k < n and j + k < n and s[i + k] == s[j + k])++k ;
			int u = upper_bound(all(pos), i) - pos.begin() - 1 ;
			int v = upper_bound(all(pos), j) - pos.begin() - 1 ;
			if(u > v)swap(u, v) ;
			if(u != v)mx[u][v] = max(mx[u][v], k) ;
			if(k)--k ;
		}
		for(int i = 0 ; i < cn ; ++i)
			for(int j = i + 1 ; j < cn ; ++j){
				error(mx[i][j], i, j)
				res = min(res, mx[i][j]) ;
			}
		return res ;
	}

	void SAConstruction(string s, vi& pos, int cn){
		int n = sz(s) ;
		vi p = CyclicShift(s) ;
		for(int i = 0 ; i < n ; ++i)cout << p[i] << " \n"[i == n - 1] ;
		int res = LCP(s, p, pos, cn) ;
		printf("%d\n",res);
	}
} ;

int main(){
    int test = Int , tc = 0 ;
    while(test--){
        SuffixArray sa ;
        vector < int > pos ;
        int k = Int, cur = 0 ;
        string s = "", t ;
        for(int i = 0 ; i < k ; ++i){
        	pos.pb(cur) ;
        	cin >> t ;
        	s += t ;
        	s += (i + '0') ;
        	cur += sz(t) + 1 ;
        }
        s.back() = '$' ;
        sa.SAConstruction(s, pos, k) ;
    }
    return 0 ;
}

/*...Always look at the part - 04...*/
/*...............END................*/



