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

int Int(){int x ; scanf("%d",&x) ; return x ;}
ll Long(){ll x ; scanf("%lld",&x) ; return x ;}

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

const int N          = (int)3e5 + 5 ;
const int maxN       = (int)1e6 + 6 ;
const ll  Mod        = (ll)1e9 + 7 ;
const int inf        = (int)2e9 ;
const ll  Inf        = (ll)1e18 ;

/*..........................................................*/
/*...Part - 05...*/

#define     debug(x)    cerr << #x << " = " << x << '\n' ;
#define     rep(i,b,e)  for(__typeof(e) i = (b) ; i != (e + 1) - 2 * ((b) > (e))  ; i += 1 - 2 * ((b) > (e)))
#define     Int         Int()
#define     Long        Long()
#define     all(x)      x.begin() , x.end()
#define     sz(x)       (int)x.size()
#define     ff          first
#define     ss          second
#define     pb          push_back
#define     eb          emplace_back
#define     mem(a)      memset(a , 0 ,sizeof a)
#define     memn(a)     memset(a , -1 ,sizeof a)

/*...Part - 06...*/
/*...... ! Code start from here ! ......*/

int tree[N][26], link[N], len[N] ;
ll occ[N] ;
int idx, t ;
char s[N] ;

void extend(int p){
	while(s[p - len[t] - 1] != s[p])t = link[t] ;
	int x = link[t], c = s[p] - 'a' ;
	while(s[p - len[x] - 1] != s[p])x = link[x] ;
	if(!tree[t][c]){
		tree[t][c] = ++idx ;
		len[idx] = 2 + len[t] ;
		link[idx] = len[idx] == 1 ? 2 : link[tree[x][c]] ;
	}
	t = tree[t][c] ;
	++occ[t] ;
}

int main(){
    int test = 1 , tc = 0 ;
    while(test--){
        link[1] = link[2] = 1 ;
        len[1] = -1, len[2] = 0 ;
        idx = t = 2 ;
        scanf("%s",s + 1) ;
        int n = strlen(s + 1) ;
        ll ans = 0 ;
        for(int i = 1 ; i <= n ; ++i) extend(i) ;
        for(int i = idx ; i > 2 ; --i){
        	occ[link[i]] += occ[i], ans = max(ans, max(occ[i] * len[i], occ[link[i]] * len[link[i]])) ;
        	error(len[i], occ[i], i)
        }
        cout << ans << '\n' ;
    }
    return 0 ;
}

/*...Always look at the part - 04...*/
/*...............END................*/


