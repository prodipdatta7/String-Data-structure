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

const int N          = (int)2e5 + 5 ;
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

int par[N][17], dep[N] ;
vvi g ;

void dfs(int s, int p = 0){
	dep[s] = 1 + dep[p] ;
	par[s][0] = p ;
	for(int i = 1 ; i <= 16 ; ++i){
		par[s][i] = par[par[s][i - 1]][i - 1] ;
	}
	for(int i : g[s]){
		if(p - i)
			dfs(i, s) ;
	}
}

int LCA(int a, int b){
	if(dep[a] < dep[b])swap(a, b) ;
	int d = dep[a] - dep[b] ;
	for(int i = 16 ; i >= 0 ; --i){
		if(d & (1 << i))a = par[a][i] ;
	}
	if(a == b)return a ;
	for(int i = 16 ; i >= 0 ; --i){
		if(par[a][i] != par[b][i]){
			a = par[a][i] ;
			b = par[b][i] ;
		}
	}
	return par[a][0] ;
}

int dist(int x, int y){
	return dep[x] + dep[y] - 2 * dep[LCA(x, y)] ;
}


int main(){
    int test = 1 , tc = 0 ;
    while(test--){
        int n = Int ;
        g.resize(n + 1) ;
        for(int i = 1 ; i < n ; ++i){
        	int x = Int, y = Int ;
        	g[x].pb(y) ;
        	g[y].pb(x) ;
        }
        dfs(1) ;
        int q = Int ;
        while(q--){
        	int r = Int, u = Int, v = Int ;
        	vector < pii > p ;
        	vi pos = {r, u, v, LCA(u, v), LCA(u, r), LCA(v, r)} ;
        	for(int i : pos){
        		int x = dist(i, r) + dist(i, u) + dist(i, v) ;
        		p.pb({x, i}) ;
        	}
        	sort(all(p)) ;
        	printf("%d\n",p[0].ss);
        }
    }
    return 0 ;
}

/*...Always look at the part - 04...*/
/*...............END................*/


