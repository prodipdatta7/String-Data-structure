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
	int alphabet = 256 ;

	vi CyclicShift(string s){
		int n = sz(s) ;
		vi sa(n), c(n), tmp(n), cnt(max(n, alphabet), 0) ;
		for(int i = 0 ; i < n ; ++i)++cnt[s[i]] ;
		for(int i = 1 ; i < alphabet ; ++i)cnt[i] += cnt[i - 1] ;
		for(int i = 0 ; i < n ; ++i)sa[--cnt[s[i]]] = i ;
		c[sa[0]] = 0 ;
		int sec = 1 ;
		for(int i = 1 ; i < n ; ++i)c[sa[i]] = (sec += (s[sa[i]] != s[sa[i - 1]])) - 1 ;
		for(int h = 0 ; (1 << h) < n ; ++h){
			for(int i = 0 ; i < n ; ++i)tmp[i] = ((sa[i] - (1 << h)) + n) % n ;
			fill(cnt.begin(), cnt.begin() + sec, 0) ;
			for(int i = 0 ; i < n ; ++i)cnt[c[tmp[i]]]++ ;
			for(int i = 1 ; i < sec ; ++i)cnt[i] += cnt[i - 1] ;
			for(int i = n - 1 ; i >= 0 ; --i)sa[--cnt[c[tmp[i]]]] = tmp[i] ;
			tmp[sa[0]] = 0 ;
			sec = 1 ;
			for(int i = 1 ; i < n ; ++i){
				pii cur = {c[sa[i]], c[(sa[i] + (1 << h)) % n]} ;
				pii pre = {c[sa[i - 1]], c[(sa[i - 1] + (1 << h)) % n]} ;
				tmp[sa[i]] = (sec += (cur != pre)) - 1 ;
			}
			if(sec == n)return sa;
			c.swap(tmp) ;
		}
	}

	vi LCP(string s, vi& p){
		int n = sz(s) ;
		vi rank(n, 0) ;
		for(int i = 0 ; i < n ; ++i)rank[p[i]] = i ;
		int k = 0 ;
		vi lcp(n, 0) ;
		for(int i = 0 ; i < n ; ++i){
			if(rank[i] == n - 1){
				k = 0 ;
				continue ;
			}
			int j = p[rank[i] + 1] ;
			while(i + k < n and j + k < n and s[i + k] == s[j + k])++k ;
			lcp[rank[i]] = k ;
			if(k)--k ;
		}
		return lcp ;
	}

}sfx ;

int main(){
    int test = 1 , tc = 0 ;
    while(test--){
    	string s1, s2, s = "" ;
    	cin >> s1 >> s2 ;
    	s += s1 + "}" + s2 + "$" ;
    	int n = sz(s) ;
    	int m1 = sz(s1) ;
        vi p = sfx.CyclicShift(s) ;
        vi lcp = sfx.LCP(s, p) ;
        int res = inf ;
        for(int i = 1 ; i < n - 1 ; ++i){
        	if(lcp[i] > 0 and lcp[i - 1] < lcp[i] and lcp[i + 1] < lcp[i]){
        		int x = p[i], y = p[i + 1] ;
        		if(x > y)swap(x, y) ;
        		int mn = max(lcp[i - 1], lcp[i + 1]) ;
        		if(x < m1 and m1 < y)res = min(res, mn + 1) ;
        	}
        }
        if(res == inf)res = -1 ;
        printf("%d\n",res);
    }
    return 0 ;
}

/*...Always look at the part - 04...*/
/*...............END................*/



