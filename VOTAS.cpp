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

const int N          = (int)1e5 + 5 ;
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

int c[20][N], n, prefix[N], p[N], tmp[N], cnt[N] ;

void cyclicshift(string s){
	mem(cnt) ;
	for(int i = 0 ; i < n ; ++i)cnt[s[i] - 96]++ ;
	for(int i = 1 ; i < 27 ; ++i)cnt[i] += cnt[i - 1] ;
	for(int i = 0 ; i < n ; ++i)p[--cnt[s[i] - 96]] = i ;
	c[0][p[0]] = 0 ;
	int sec = 1 ;
	for(int i = 1 ; i < n ;++i){
		c[0][p[i]] = (sec += (s[p[i]] != s[p[i - 1]])) - 1 ;
	}
	for(int h = 0 ; (1 << h) < n ; ++h){
		for(int i = 0 ; i < n ; ++i)tmp[i] = ((p[i] - (1 << h)) + n) % n ;
		fill(cnt, cnt + sec, 0) ;
		for(int i = 0 ; i < n ; ++i)cnt[c[h][tmp[i]]]++ ;
		for(int i = 1 ; i < sec ; ++i)cnt[i] += cnt[i - 1] ;
		for(int i = n - 1 ; i >= 0 ; --i)p[--cnt[c[h][tmp[i]]]] = tmp[i] ;
		c[h + 1][p[0]] = 0 ;
		sec = 1 ;
		for(int i = 1 ; i < n ; ++i){
			pii cur = {c[h][p[i]], c[h][(p[i] + (1 << h)) % n]} ;
			pii pre = {c[h][p[i - 1]], c[h][(p[i - 1] + (1 << h)) % n]} ;
			c[h + 1][p[i]] = (sec += (cur != pre)) - 1 ;
		}
	}
}

int lcp(int i, int j){
	int res = 0 ;
	int k = log2(n) ;
	for(int h = k ; h >= 0 ; --h){
		if(c[h][i] == c[h][j]){
			res += (1 << h) ;
			i += (1 << h) ;
			j += (1 << h) ;
		}
	}
	return res ;
}

int main(){
    int test = Int , tc = 0 ;
    while(test--){
        string s ; 
        cin >> s ;
        s += '`' ;
        n = sz(s) ;
        mem(c) ;
        cyclicshift(s) ;
        mem(prefix) ;
        for(int i = 1 ; i < n - 1 ; ++i){
        	int lc = lcp(0, i) ;
        	prefix[0]++, prefix[lc + 1]-- ;
        }
        prefix[0]++, prefix[n]-- ;
        for(int i = 1 ; i < n ; ++i)prefix[i] += prefix[i - 1] ;
        int q = Int, res = 0 ;
    	while(q--){
    		int k = Int ;
    		res = (k >= n) ? 0 : prefix[k] ;
    		printf("%d ",res);
    	}
    	cout << '\n' ;
    }
    return 0 ;
}

/*...Always look at the part - 04...*/
/*...............END................*/



