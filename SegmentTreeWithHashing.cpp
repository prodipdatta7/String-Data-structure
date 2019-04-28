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

const int N          = (int)1e5 + 5 ;
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

const ll base = 31LL ;

ll power[N] ;
char s[N] ;

void PowerSeries(){
	power[0] = 1LL ;
	for(int i = 1 ; i < N ; ++i){
		power[i] = (power[i - 1] * base) % Mod ;
	}
}

struct data{
	int p ;
	ll fhash, bhash ;
	data():p(0),fhash(0),bhash(0){}
	data(int p, ll f, ll b):p(p),fhash(f),bhash(b){}
} tree[N << 2] ;

data merge(data a, data b){
	data res = data(0, 0, 0) ;
	res.p = a.p + b.p ;
	res.fhash = (a.fhash + (b.fhash * power[a.p]) % Mod) % Mod ;
	res.bhash = (b.bhash + (a.bhash * power[b.p]) % Mod) % Mod ;
	return res ;
}

void update(int i, int b, int e, int p, ll v){
	if(p > e or p < b)return ;
	if(b == e and p == b){
		tree[i] = data(1, v, v) ;
		return ;
	}
	int mid = (b + e) >> 1 ;
	update(i << 1, b, mid, p, v) ;
	update(i << 1 | 1, mid + 1, e, p, v) ;
	tree[i] = merge(tree[i << 1], tree[i << 1 | 1]) ;
}

data query(int i, int b, int e, int l, int r){
	if(b > r or e < l)return data(0, 0, 0) ;
	if(l <= b and e <= r)return tree[i] ;
	int mid = (b + e) >> 1 ;
	return merge(query(i << 1, b, mid, l, r), query(i << 1 | 1, mid + 1, e, l, r)) ; 
}

void refresh(int n){
	for(int i = 0 ; i <= (n << 2) ; ++i)
		tree[i] = data(0, 0, 0) ;
}


int main(){
    int test = Int , tc = 0 ;
    PowerSeries() ;
    while(test--){
        int n = Int, q = Int ;
        scanf("%s",s + 1) ;
        refresh(n + 1) ;
        for(int i = 1 ; i <= n ; ++i){
        	update(1, 1, n, i, s[i] - 'a' + 1) ;
        }
        while(q--){
        	int tp = Int ;
        	if(tp == 1){
        		int p = Int ;
        		getchar() ;
        		char c = getchar() ;
        		update(1, 1, n, p, c - 'a' + 1) ;
        	}
        	else {
        		int l = Int, r = Int ;
        		data res = query(1, 1, n, l, r) ;
        		if(res.fhash == res.bhash)puts("Adnan Wins") ;
        		else puts("ARCNCD!") ;
        	}
        }
    }
    return 0 ;
}

/*...Always look at the part - 04...*/
/*...............END................*/


