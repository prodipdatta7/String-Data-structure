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


struct lowest_common_ancestor{
    const static int N = 1e5 + 5 ;
    const static int k = 17 ;
    int par[N][k + 1] , lev[N] ;
    vector < vector < int > > g , city;
    vector< int > ID[N][k + 1] ;
    lowest_common_ancestor(){
        for(int i = 0 ; i < N ; ++i){
            for(int j = 0 ; j <= k ; ++j)
                par[i][j] = 0 ;
            lev[i] = 0 ;
        }
    }

    void merge(vi &a, vi &b){
        vi tmp ;
        auto i = a.begin(), j = b.begin() ;
        for(int k = 1 ; k <= min(10, sz(a) + sz(b)) ; ++k){
            if(i != a.end() and j != b.end()){
                if(*i < *j)tmp.pb(*i), ++i ;
                else tmp.pb(*j), ++j ;
            }
            else if(i != a.end())tmp.pb(*i), ++i ;
            else tmp.pb(*j), ++j ;
        }
        a.assign(all(tmp)) ;
    }

    void build(int s, int p = 0){
        lev[s] = 1 + lev[p] ;
        par[s][0] = p ;
        ID[s][0].assign(all(city[p])) ;
        for(int i = 1 ; i <= k ; ++i){
            par[s][i] = par[par[s][i - 1]][i - 1] ;
            merge(ID[s][i], ID[s][i - 1]) ;
            merge(ID[s][i], ID[par[s][i - 1]][i - 1]) ;
        }
        for(int i : g[s])
            if(i != p) build(i, s) ;
    }

    void getLCA(int a, int b, int t){
        if(lev[a] < lev[b])swap(a, b) ;
        vector < int > res(all(city[a])) ;
        int d = lev[a] - lev[b] ;
        int tt = b ;
        for(int i = k ; i >= 0 ; --i){
            if((d >> i) & 1){
            	merge(res, ID[a][i]) ;
                a = par[a][i] ;
            }
        }
        if(a == b){
            printf("%d",min(sz(res),t)) ;
            for(int i = 0 ; i < min(sz(res), t) ; ++i)printf(" %d",res[i]);
            cout << '\n' ;
        	return ;
        }
        for(int i = k ; i >= 0 ; --i){
            if(par[a][i] != par[b][i]){
            	merge(res, ID[a][i]) ;
            	merge(res, ID[b][i]) ;
                b = par[b][i] ;
                a = par[a][i] ;
            }
        }
        merge(res , city[par[a][0]]) ;
        merge(res, city[tt]) ;
        printf("%d",min(sz(res),t)) ;
        for(int i = 0 ; i < min(sz(res), t) ; ++i)printf(" %d",res[i]);
        cout << '\n' ;
    	return ;
    }

    void solve(){
        int n = Int, m = Int, q = Int ;
        g.resize(n + 1) ;
        city.resize(n + 1) ;
        for(int i = 1 ; i < n ; ++i){
        	int x = Int, y = Int ;
        	g[x].eb(y) ;
        	g[y].eb(x) ;
        }
        for(int i = 1 ; i <= m ; ++i){
        	int c = Int ;
        	if(sz(city[c]) < 10) city[c].eb(i) ;
        }
        build(1) ;
        while(q--){ 
        	int l = Int, r = Int, t = Int ;
        	getLCA(l, r, t) ;
        }
    }
} ;

lowest_common_ancestor lca ;


int main(){
    int test = 1 , tc = 0 ;
    while(test--){
        lca.solve() ;
    }
    return 0 ;
}

/*...Always look at the part - 04...*/
/*...............END................*/


