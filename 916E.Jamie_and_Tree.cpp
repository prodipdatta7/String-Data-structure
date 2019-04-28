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

int st[N], en[N], t, a[N], pos[N], n, q;
int dep[N], par[N][17] ;
vvi g ;

struct segment{
	ll tree[N << 2] , lazy[N << 2] ;
	bool have[N << 2] ;
	
	void reset(){
		mem(tree) ;
		mem(have) ;
		mem(lazy) ;
	}
	void propagate(int i , int b , int e){
		if(have[i]){
			tree[i] += lazy[i] * (e - b + 1) ;
			if(b != e){
				lazy[i << 1] += lazy[i] ;
				lazy[i << 1 | 1] += lazy[i] ;
				have[i << 1] = have[i << 1 | 1] = 1 ;
			}
			lazy[i] = 0;
			have[i] = 0 ;
		}
	}
	
	void upd(int i , int b , int e , int l , int r, ll v){
		propagate(i, b, e) ;
		if(b > r or e < l)return ;
		if(l <= b and e <= r){
			tree[i] += v * (e - b + 1) ;
			if(b != e){
				lazy[i << 1] += v ;
				lazy[i << 1 | 1] += v ;
				have[i << 1] = have[i << 1 | 1] = 1 ;
			}
			return ;
		}
		int mid = (b + e) >> 1 ;
		int l1 = i << 1, l2 = l1 | 1 ;
		upd(l1 , b , mid , l , r, v) ;
		upd(l2 , mid + 1 , e , l , r, v) ;
		tree[i] = tree[l1] + tree[l2] ;
	}

	ll query(int i , int b , int e , int l , int r){
		propagate(i, b, e) ;
		if(b > r or e < l)return 0 ;
		if(l <= b and e <= r)return tree[i] ;
		int mid = (b + e) >> 1 ;
		return query(i << 1 , b , mid , l , r) + query(i << 1 | 1 , mid + 1 , e , l , r) ;
	}
}seg;

void dfs(int s, int p = 0){
	st[s] = ++t ;
	seg.upd(1, 1, n, t, t, a[s]) ;
	dep[s] = 1 + dep[p] ;
	par[s][0] = p ;
	for(int i = 1 ; i < 17 ; ++i)
		par[s][i] = par[par[s][i - 1]][i - 1] ;

	for(int i : g[s]){
		if(i == p)continue ;
		dfs(i, s) ;
	}
	en[s] = t ;
}

int getLca(int a, int b){
	if(dep[a] < dep[b])swap(a, b) ;
	int d = dep[a] - dep[b] ;
	for(int i = 16 ; i >= 0 ; --i)
		if(d & (1 << i))a = par[a][i] ;
	if(a == b)return a ;
	for(int i = 16 ; i >= 0 ; --i){
		if(par[a][i] != par[b][i])
			a = par[a][i], b = par[b][i] ;
	}
	return par[a][0] ;
}

int D(int a, int b){
	return dep[a] + dep[b] - 2 * dep[getLca(a, b)] ;
}

int BinaryLift(int d, int c){
	for(int i = 16 ; i >= 0 ; --i){
		if(d & (1 << i))c = par[c][i] ;
	}
	return c ;
}

int main(){
	//freopen("input.txt","r",stdin) ;
    int test = 1 , tc = 0 ;
    while(test--){
        n = Int, q = Int ;
        g.resize(n + 1) ;
        for(int i = 1 ; i <= n ; ++i)
        	a[i] = Int ;
        for(int i = 1 ; i < n ; ++i){
        	int x = Int, y = Int ;
        	g[x].pb(y) ;
        	g[y].pb(x) ;
        }
        int cur_root = 1 ;
        seg.reset() ;
        dfs(1) ;
        //for(int i = 1 ; i <= n ; ++i)error(st[i], en[i])
        while(q--){
        	int tp = Int ;
        	if(tp == 1){
        		cur_root = Int ;
        	}
        	else if(tp == 2){
        		int x = Int, y = Int, add = Int;
        		vector < pii > v ;
        		vi tmp = {cur_root, x, y, getLca(x, y), getLca(x, cur_root), getLca(cur_root, y)} ;
        		for(int i : tmp){
        			int f = D(i, x) + D(i, y) + D(i, cur_root) ;
        			v.pb({f, i}) ;
        		}
        		sort(all(v)) ;
        		int lca = v[0].ss ;
        		int cros = getLca(lca, cur_root) ;
        		//error(lca, cros, cur_root)
        		if(lca == cur_root)seg.upd(1, 1, n, 1, n, 1LL * add) ;
        		else if(cros == lca){
        			int up = dep[cur_root] - dep[lca] - 1 ;
        			int now = BinaryLift(up, cur_root) ;
        			//error(now, st[now], en[now],up)
        			seg.upd(1, 1, n, 1, st[now] - 1, 1LL * add) ;
        			seg.upd(1, 1, n, en[now] + 1, n, 1LL * add) ;
        		}
        		else{
        			//error(st[lca], en[lca])
        			seg.upd(1, 1, n, st[lca], en[lca], 1LL * add) ;
        		}
        	}
        	else{
        		int p = Int ;
        		int lca = getLca(p, cur_root) ;
        		//error(p, lca, st[p], en[p])
        		ll k = 0 ;
        		if(p == cur_root){
        			k = seg.query(1, 1, n, 1, n) ;
        		}
        		else if(p == lca and lca != cur_root){
        			int up = dep[cur_root] - dep[p] - 1 ;
        			int now = BinaryLift(up, cur_root) ;
        			//error(now, st[now], en[now], up)
        			k += seg.query(1, 1, n, 1, st[now] - 1) ;
        			k += seg.query(1, 1, n, en[now] + 1, n) ;
        		}
        		else{
        			k = seg.query(1, 1, n, st[p], en[p]) ;
        		}
        		printf("%lld\n",k);
        	}
        }
    }
    return 0 ;
}

/*...Always look at the part - 04...*/
/*...............END................*/


