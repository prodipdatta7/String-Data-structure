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

const int N          = (int)5e4 + 5 ;
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

const int k = 15 ;
int dp[N][k + 1], Log[N] ;

void LogTable(){
	for(int i = 2 ; i < N ; ++i){
		Log[i] = 1 + Log[i >> 1] ;
	}
}

struct SuffixArray{

	vi cyclicShift(vi& a){
		int n = sz(a) ;
		vi p(n), c(n), tmp(n), cnt(n, 0) ;
		for(int i = 0 ; i < n ; ++i)cnt[a[i]]++ ;
		for(int i = 1 ; i < n ; ++i)cnt[i] += cnt[i - 1] ;
		for(int i = 0 ; i < n ; ++i)p[--cnt[a[i]]] = i ;
		c[p[0]] = 0 ;
		int sec = 1 ;
		for(int i = 1 ; i < n ; ++i)c[p[i]] = (sec += (a[p[i]] != a[p[i - 1]])) - 1 ;
		for(int h = 0 ; (1 << h) < n ; ++h){
			for(int i = 0 ; i < n ; ++i)tmp[i] = ((p[i] - (1 << h)) + n) % n ;
			fill(cnt.begin(), cnt.begin() + sec, 0) ;
			for(int i = 0 ; i < n ; ++i)cnt[c[tmp[i]]]++ ;
			for(int i = 1 ; i < sec ; ++i)cnt[i] += cnt[i - 1] ;
			for(int i = n - 1 ; i >= 0 ; --i)p[--cnt[c[tmp[i]]]] = tmp[i] ;
			tmp[p[0]] = 0 ;
			sec = 1 ;
			for(int i = 1 ; i < n ; ++i){
				pii cur = {c[p[i]], c[(p[i] + (1 << h)) % n]} ;
				pii pre = {c[p[i - 1]], c[(p[i - 1] + (1 << h)) % n]} ;
				tmp[p[i]] = (sec += (cur != pre)) - 1 ;
			}
			c.swap(tmp) ;
		}
		return p ;
	}

	void build(vi &a){
		int n = sz(a) ;
		vi rank(n) ;
		for(int i = 0 ; i < n ; ++i)rank[a[i]] = i ;
		for(int i = 0 ; i < n ; ++i){
			dp[i][0] = rank[i] ;
		}
		for(int j = 1 ; j <= k ; ++j){
			for(int i = 0 ; i + (1 << j) <= n ; ++i){
				dp[i][j] = min(dp[i][j - 1], dp[i + (1 << (j - 1))][j - 1]) ;
			}
		}
	}

	int getMin(int l, int r){
		int rng = Log[r - l + 1] ;
		return min(dp[l][rng], dp[r - (1 << rng) + 1][rng]) ;
	}
} ;

int main(){
	LogTable() ;
    int test = Int , tc = 0 ;
    while(test--){
        SuffixArray sa ;
        int n = Int, q = Int ;
        vi a(n), b(n) ;
        for(int i = 0 ; i < n ; ++i)a[i] = Int, b[i] = a[i] ;
        sort(all(b)) ;
    	b.erase(unique(all(b)), b.end()) ;
    	for(int i = 0 ; i < n ; ++i)a[i] = lower_bound(all(b), a[i]) - b.begin() + 1 ;
    	a.pb(0) ;
    	vi p = sa.cyclicShift(a) ;
    	p.erase(p.begin()) ;
    	sa.build(p) ;
    	printf("Case %d:\n",++tc);
    	while(q--){
    		int l = Int - 1, r = Int - 1 ;
    		int mn = sa.getMin(l, r) ;
    		printf("%d\n",p[mn] + 1);
    	}
    }
    return 0 ;
}

/*...Always look at the part - 04...*/
/*...............END................*/



