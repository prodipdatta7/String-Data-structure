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

vector < int > t[N << 2], fen[N << 2] ;

struct query{
	int tp, p, l, r, k ;
	query():tp(0),p(0),l(0),r(0),k(0){}
	query(int tp, int p, int l, int r,int k):tp(tp),p(p),l(l),r(r),k(k){}
} ;

void insert(int i, int b, int e, int p, int k){
	if(b == e){
		t[i].pb(k) ;
		return ;
	}
	int mid = (b + e) >> 1 ;
	if(p <= mid)insert(i << 1, b, mid, p, k) ;
	else insert(i << 1 | 1, mid + 1, e, p, k) ;
}

void order(int i, int b, int e){
	if(b != e){
		int mid = (b + e) >> 1 ;
		order(i << 1, b, mid) ;
		order(i << 1 | 1, mid + 1, e) ;
		merge(all(t[i << 1]), all(t[i << 1 | 1]), back_inserter(t[i])) ;
	}
	else sort(all(t[i])) ;
	t[i].resize(unique(all(t[i])) - t[i].begin()) ;
	fen[i] = vector < int > (t[i].size() + 2, 0) ;
}

void update(int i, int b, int e, int p, int k){
	int st = lower_bound(all(t[i]), k) - t[i].begin() ;
	for(int j = st + 1 ; j < fen[i].size() ; j += (j & -j))
		fen[i][j]++ ;
	if(b == e)return ;
	int mid = (b + e) >> 1 ;
	if(p <= mid)update(i << 1, b, mid, p, k) ;
	else update(i << 1 | 1, mid + 1, e, p, k) ;
}

int ask(int i, int b, int e, int l, int r, int k){
	if(b > r or e < l)return 0;
	if(l <= b and e <= r){
		int f = upper_bound(all(t[i]), k) - t[i].begin() ;
		int res = 0 ;
		for(int j = f ; j > 0 ; j -= (j & -j))
			res += fen[i][j] ;
		return res ;
	}
	int mid = (b + e) >> 1 ;
	return ask(i << 1, b, mid, l, r, k) + ask(i << 1 | 1, mid + 1, e, l, r, k) ;
}


int main(){
    int test = 1 , tc = 0 ;
    while(test--){
        int n = Int, q = Int ;
        std::vector< query > Q ;
        for(int i = 1 ; i <= q ; ++i){
        	int tp = Int ;
        	if(tp == 1){
        		int p = Int, k = Int ;
        		insert(1, 1, n, p, k) ;
        		Q.pb(query(tp, p, 0, 0, k)) ;
        	}
        	else{
        		int l = Int, r = Int, k = Int ;
        		Q.pb(query(tp, 0, l, r, k)) ;
        	}
        }
        order(1, 1, n) ;
        for(int i = 0 ; i < q ; ++i){
        	if(Q[i].tp == 1){
        		update(1, 1, n, Q[i].p, Q[i].k) ;
        	}
        	else{
        		int res = ask(1, 1, n, Q[i].l, Q[i].r, Q[i].k) ;
        		printf("%d\n",res);
        	}
        }
    }
    return 0 ;
}

/*...Always look at the part - 04...*/
/*...............END................*/


