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
int dp[N][K + 1], Log[N] ;

void LogTable(){
	Log[1] = 0 ;
	for(int i = 2 ; i < N ; ++i){
		Log[i] = 1 + Log[i >> 1] ;
	}
}


struct SuffixArray{
	vi cyclicShift(string &s){
		int n = sz(s) ;
		vi p(n), c(n), tmp(n), cnt(max(n, 30), 0) ;
		for(int i = 0 ; i < n ; ++i)cnt[s[i] - '`']++ ;
		for(int i = 1 ; i < 27 ; ++i)cnt[i] += cnt[i - 1] ;
		for(int i = 0 ; i < n ; ++i)p[--cnt[s[i] - '`']] = i ;
		c[p[0]] = 0 ;
		int cls = 1 ;
		for(int i = 1 ; i < n ; ++i)c[p[i]] = (cls += (s[p[i]] != s[p[i - 1]])) - 1 ;
		for(int h = 0 ; (1 << h) < n ; ++h){
			for(int i = 0 ; i < n ; ++i)tmp[i] = (p[i] - (1 << h) + n) % n ;
			fill(cnt.begin(), cnt.begin() + cls, 0) ;
			for(int i = 0 ; i < n ; ++i)cnt[c[tmp[i]]]++ ;
			for(int i = 1 ; i < cls ; ++i)cnt[i] += cnt[i - 1] ;
			for(int i = n - 1 ; i >= 0 ; --i)p[--cnt[c[tmp[i]]]] = tmp[i] ;
			cls = 1 ;
			tmp[p[0]] = 0 ;
			for(int i = 1 ; i < n ; ++i){
				pii cur = {c[p[i]], c[(p[i] + (1 << h)) % n]} ;
				pii pre = {c[p[i - 1]], c[(p[i - 1] + (1 << h)) % n]} ;
				tmp[p[i]] = (cls += (cur != pre)) - 1 ;
			}
			if(cls == n)return p ;
			c.swap(tmp) ;
		}
	}

	vi LCP(string s, vi p){
		int n = sz(s) ;
		vi rank(n, 0) ;
		for(int i = 0 ; i < n ; ++i)rank[p[i]] = i ;
		int k = 0 ;
		vi lcp(n, 0) ;
		for(int i = 0 ; i < n - 1 ; ++i){
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

	void sparseTable(vi lcp){
		int n = sz(lcp) - 1 ;
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
		int len = Log[r - l + 1] ;
		return min(dp[l][len], dp[r - (1 << len) + 1][len]) ;
	}

	ll solve(string s){
		s += '`' ;
		int n = sz(s) ;
		vi p = cyclicShift(s) ;
		vi lcp = LCP(s, p) ;
		sparseTable(lcp) ;
		ll res = 0 ;
		for(int i = 1 ; i < n ; ++i){
			int cur = lcp[i - 1] + 1, len = n - p[i] - 1 ;
			while(cur <= len){
				int Rpos = i, l = i, r = n - 1, nxt = 0 ;
				while(l <= r){
					int mid = (l + r + 1) >> 1 ;
					int q = query(i, mid - 1) ;
					if(q >= cur){
						l = mid + 1 ;
						Rpos = mid, nxt = q ;
					}
					else r = mid - 1 ;
				}
				if(i == Rpos){
					res += n - p[i] - cur ;
					break ;
				}
				else {
					int cnt = Rpos - i + 1 ;
					int len = nxt - cur + 1 ;
					res += 1LL * cnt * cnt * len ;
					cur = nxt + 1 ;
				}
			}
		}
		return res ;
	}
} ;

int main(){
    int test = Int , tc = 0 ;
    LogTable() ;
    while(test--){
        SuffixArray sa ;
        string s ; cin >> s ;
        cout << sa.solve(s) << '\n' ;
    }
    return 0 ;
}

/*...Always look at the part - 04...*/
/*...............END................*/



