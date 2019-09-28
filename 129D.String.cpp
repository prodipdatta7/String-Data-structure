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

struct SaffixArray{

	vi CyclicShift(string s){
		int n = sz(s) ;
		vi p(n), c(n), tmp(n), cnt(max(n, 30)) ;
		for(int i = 0 ; i < n ; ++i)cnt[s[i] - 96]++ ;
		for(int i = 1 ; i < 27 ; ++i)cnt[i] += cnt[i - 1] ;
		for(int i = 0 ; i < n ; ++i)p[--cnt[s[i] - 96]] = i ;
		c[p[0]] = 0 ;
		int sec = 1 ;
		for(int i = 1 ; i < n ; ++i)c[p[i]] = (sec += (s[p[i]] != s[p[i - 1]])) - 1 ;
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
			if(sec == n)return p ;
		}
		return p ;
	}

	vi LCP(string s, vi& p){
		int n = sz(s) ;
		vi rank(n, 0) ;
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
}sa ;

int main(){
    int test = 1 , tc = 0 ;
    while(test--){
        string s, str = "" ; cin >> s ;
        int k = Int ;
        int n = sz(s) ;
        if(1LL * n * (n + 1) / 2LL < k)return puts("No such line."), 0 ;
        s += '`' ;
        ++n ;
        vi p = sa.CyclicShift(s) ;
        vi lcp = sa.LCP(s, p) ;
        vll cnt(29, 0) ;
        for(int i = 1 ; i < n ; ++i)cnt[s[p[i]] - 'a'] += n - p[i] - 1 ;
        int id = 0 ;
        for(int i = 0 ; i < 26 ; ++i){
        	if(k - cnt[i] <= 0)break ;
        	k -= cnt[i] ;
        	id = i + 1 ;
        }
        int l = 1, r = n - 1, Lpos = -1, Rpos = -1, cur  ;
        while(l <= r){
        	int mid = (l + r) >> 1 ;
        	if(s[p[mid]] - 'a' >= id)r = mid - 1, Lpos = mid;
        	else l = mid + 1 ;
        }
        l = Lpos, r = n - 1 ; 
        while(l <= r){
        	int mid = (l + r) >> 1 ;
        	if(s[p[mid]] - 'a' < id)r = mid - 1 ;
        	else l = mid + 1, Rpos = mid ;
        }
        while(k){
	        for(int i = p[Lpos] + lcp[Lpos - 1] ; i < n - 1 ; ++i){
	        	str += s[i] ;
	        	l = Lpos, r = Rpos, cur = Lpos ;
	        	while(l <= r){
	        		int mid = (l + r) >> 1 ;
	        		if(sz(str) > n - p[mid] - 1){
	        			r = mid - 1 ;
	        		}
	        		else{
	        			int ck = 0 ;
	        			for(int j = 0 ; j < sz(str) ; ++j){
	        				if(str[j] != s[p[mid] + j]){
	        					if(str[j] < s[p[mid] + j])ck = -1 ;
	        					else ck = 1 ;
	        					break ;
	        				}
	        			}
	        			if(!ck)l = mid + 1, cur = mid ;
	        			else {
	        				if(ck == -1)r = mid - 1 ;
	        				else l = mid + 1, cur = mid ;
	        			}
	        		}
	        	}
	        	if(cur == Lpos){
	        		if(sz(str))str.pop_back() ;
	        		int left = n - p[Lpos] - 1 - sz(str) ;
	        		if(k <= left){
	        			while(k--){
	        				str += s[i++] ;
	        			}
	        			return cout << str << '\n', 0 ;
	        		}
	        		else k -= left ;
	        		break ;
	        	}
	        	int f = (cur - Lpos + 1);
	        	if(f < k)k -= f ;
	        	else return cout << str << '\n', 0 ;
	        }
	        ++Lpos ;
	        str = "" ;
	        for(int j = p[Lpos] ; j < p[Lpos] + lcp[Lpos - 1] ; ++j)str += s[j] ;
	    }
    }
    return 0 ;
}

/*...Always look at the part - 04...*/
/*...............END................*/



