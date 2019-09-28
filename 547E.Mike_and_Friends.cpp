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

const int N          = (int)4e5 + 5 ;
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

const int K = 18 ;
int dp[N][K + 1], Log[N] ;
vector < int > T[N << 2], position ;

struct SuffixArray{

	vi CyclicShift(const string &s){
		int n = sz(s), sec = 0 ;
		vi p(n), c(n), tmp(n), cnt(max(256, n), 0) ;
		for(int i = 0 ; i < n ; ++i)cnt[s[i]]++ ;
		for(int i = 1 ; i < 256 ; ++i)cnt[i] += cnt[i - 1] ;
		for(int i = 0 ; i < n ; ++i)p[--cnt[s[i]]] = i ;
		c[p[0]] = 0, sec = 1 ;
		for(int i = 1 ; i < n ; ++i)c[p[i]] = (sec += (s[p[i]] != s[p[i - 1]])) - 1 ;
		for(int h = 0 ; (1 << h) < n ; ++h){
			for(int i = 0 ; i < n ; ++i)tmp[i] = ((p[i] - (1 << h)) + n) % n ;
			fill(cnt.begin(), cnt.begin() + sec, 0) ;
			for(int i = 0 ; i < n ; ++i)cnt[c[tmp[i]]]++ ;
			for(int i = 1 ; i < sec ; ++i)cnt[i] += cnt[i - 1] ;
			for(int i = n - 1 ; i >= 0 ; --i)p[--cnt[c[tmp[i]]]] = tmp[i] ;
			tmp[p[0]] = 0, sec = 1 ;
			for(int i = 1 ; i < n ; ++i){
				pii cur = {c[p[i]], c[(p[i] + (1 << h)) % n]} ;
				pii pre = {c[p[i - 1]], c[(p[i - 1] + (1 << h)) % n]} ;
				tmp[p[i]] = (sec += (cur != pre)) - 1 ;
			}
			c.swap(tmp) ;
			if(sec == n)return p ;
		}
		return p ;
	}
	vi LCp(const string s, const vi& p){
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

	void build(int i, int b, int e){
		if(b == e){
			T[i].pb(position[b - 1]) ;
			return ;
		}
		int mid = (b + e) >> 1 ;
		build(i << 1, b, mid) ;
		build(i << 1 | 1, mid + 1, e) ;
		merge(all(T[i << 1]), all(T[i << 1 | 1]), back_inserter(T[i])) ;
	}

	int Query(int i, int b, int e, int l, int r, int u, int v){
		if(b > r or e < l)return 0 ;
		if(l <= b and e <= r){
			return upper_bound(all(T[i]), v) - lower_bound(all(T[i]), u) ;
		}
		int mid = (b + e) >> 1 ;
		return Query(i << 1, b, mid, l, r, u, v) + Query(i << 1 | 1, mid + 1, e, l, r, u, v) ;
	}
	void buildSparseTable(const vi lcp, int n){
		for(int i = 0 ; i < n ; ++i){
			dp[i][0] = lcp[i] ;
		}
		for(int j = 1 ; (1 << j) <= n ; ++j){
			for(int i = 0 ; i + (1 << j) <= n ; ++i){
				dp[i][j] = min(dp[i][j - 1], dp[i + (1 << (j - 1))][j - 1]) ;
			}
		}
	}

	void buildLogTable(){
		Log[1] = 0 ;
		for(int i = 2 ; i < N ; ++i)
			Log[i] = Log[i >> 1] + 1 ;
	}
	int query(int l, int r){
		int rng = Log[r - l + 1] ;
		return min(dp[l][rng], dp[r - (1 << rng) + 1][rng]) ;
	}
}sa ;

int main(){
    int test = 1 , tc = 0 ;
    while(test--){
        string s = "", sub ;
        int n = Int, q = Int ;
        vi pos(n + 2), cnt(N, 0) ;
        for(int i = 1 ; i <= n ; ++i){
        	cin >> sub ;
        	pos[i] = sz(s) ;
        	cnt[pos[i]] = i ;
        	s += sub ;
        	s += i == n ? '$' : '`' ;
        }
        pos[n+1] = sz(s) ;
        n = sz(s) ;
        vi p = sa.CyclicShift(s) ;
        vi lcp = sa.LCp(s, p) ;
        sa.buildSparseTable(lcp, n - 1) ;
        sa.buildLogTable() ;
        position.resize(n) ;
        for(int i = 0 ; i < n ; ++i)position[i] = upper_bound(all(pos), p[i]) - pos.begin() - 1 ;
        sa.build(1, 1, n) ;
        vi mark(n + 1, -1) ;
        for(int i = 0 ; i < n ; ++i)if(cnt[p[i]])mark[cnt[p[i]]] = i ;
        while(q--){
        	int ll = Int, rr = Int, id = Int ;
        	int f = mark[id], len = pos[id + 1] - pos[id] - 1 ;
        	int l = 1, r = f, Lpos = f, Rpos = f ;
        	/*note: when search to left part of f, mid = (l + r) >> 1 */
        	/*note: when search to right part of f, mid = (l + r + 1) >> 1 */
        	while(l <= r){
        		int mid = (l + r) >> 1 ; /* for searching in the left side */ 
        		int res = sa.query(mid, f - 1) ;
        		if(res >= len)r = mid - 1, Lpos = mid ;
        		else l = mid + 1 ;
        	}
        	l = f, r = n ;
        	while(l <= r){
        		int mid = (l + r + 1) >> 1 ; /* for searching in the right side */ 
        		int res = sa.query(f, mid - 1) ;
        		if(res >= len)Rpos = mid, l = mid + 1 ;
        		else r = mid - 1 ;
        	}
        	int res = sa.Query(1, 1, n, Lpos + 1, Rpos + 1, ll, rr) ;
        	printf("%d\n",res);
        }
    }
    return 0 ;
}

/*...Always look at the part - 04...*/
/*...............END................*/



