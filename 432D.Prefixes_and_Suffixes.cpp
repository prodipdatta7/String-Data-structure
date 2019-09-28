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

const int K = 17 ;
int Log[N], dp[N][K + 1] ;

struct SuffixArray{
	vvi interim ;

	vi CyclicShift(string &s){
		int n = sz(s), sec = 0 ;
		int alpha = 256 ;
		vi p(n), c(n), tmp(n), cnt(max(n, alpha), 0) ;
		for(int i = 0 ; i < n ; ++i)cnt[s[i]]++ ;
		for(int i = 1 ; i < alpha ; ++i)cnt[i] += cnt[i - 1] ;
		for(int i = 0 ; i < n ; ++i)p[--cnt[s[i]]] = i ;
		c[p[0]] = 0, sec = 1 ;
		for(int i = 1 ; i < n ; ++i)c[p[i]] = (sec += (s[p[i]] != s[p[i - 1]])) - 1 ;
		interim.pb(c) ;
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
			interim.pb(c) ;
		}
		return p ;
	}

	vi LCp(string s, vi& p, vi& rank){
		int n = sz(s) ;
		for(int i = 0 ; i < n ; ++i)rank[p[i]] = i ;
		int k = 0 ;
		vi lcp(n - 1, 0) ;
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

	int LcpOfTwoSubstring(int i, int j, int n){
		int k = log2(n), res = 0 ;
		for(int h = k ; h >= 0 ; --h){
			if(interim[h][i] == interim[h][j]){
				res += (1 << h) ;
				i += (1 << h) ;
				j += (1 << h) ;
			}
		}
		return res ;
	}
	void buildLogTable(){
		Log[1] = 0 ;
		for(int i = 2 ; i < N ; ++i)
			Log[i] = Log[i >> 1] + 1 ;
	}

	void buildSparseTable(vi lcp, int n){
		buildLogTable() ;
		for(int i = 0 ; i < n ; ++i){
			dp[i][0] = lcp[i] ;
		}
		for(int j = 1 ; (1 << j) <= n ; ++j){
			for(int i = 0 ; i + (1 << j) <= n ; ++i){
				dp[i][j] = min(dp[i][j - 1], dp[i + (1 << (j - 1))][j - 1]) ;
			}
		}
	}

	int query(int l, int r){
		int rng = Log[r - l + 1] ;
		return min(dp[l][rng], dp[r - (1 << rng) + 1][rng]) ;
	}

	int NumberOfOccurance(int l, int r, int target){
		int res = 0, L = l ;
		while(l <= r){
			int mid = (l + r + 1) >> 1 ;
			int lcp = query(L, mid - 1) ;
			if(lcp < target){
				r = mid - 1 ;
			}
			else res = mid, l = mid + 1 ;
		}
		return res - L + 1 ;
	}
}sa ;

int main(){
    int test = 1 , tc = 0 ;
    while(test--){
        string s ; cin >> s ;
        s += '$' ;
        int n = sz(s) ;
        vi p = sa.CyclicShift(s) ;
        vi rank(n, 0) ;
        vi lcp = sa.LCp(s, p, rank) ;
        sa.buildSparseTable(lcp, n - 1) ;
        vector < pii > res ;
        //for(int i = 0 ; i < n - 1 ; ++i)error(i, lcp[i])
        for(int i = 1 ; i < n - 1 ; ++i){
        	int len = n - i - 1 ;
        	int ans = sa.LcpOfTwoSubstring(0, i, n) ;
        	if(ans == len){
        		int cnt = sa.NumberOfOccurance(rank[i], n - 1, len) ;
        		res.pb({len, cnt}) ;
        	}
        }
        res.pb({n - 1, 1}) ;
        sort(all(res)) ;
        cout << sz(res) << '\n' ;
        for(pii i : res)cout << i.ff << ' ' << i.ss << '\n' ;
    }
    return 0 ;
}

/*...Always look at the part - 04...*/
/*...............END................*/



