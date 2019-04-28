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

ll base[2] = {11LL, 17LL} ;
ll mod[2] = {1000000007LL, 1000000009LL} ;
ll power[2][N], dp[2][11][N];
char s[N] ;

struct data{
	int p;
	ll hash1, hash2;
	bool lazy ;
	int id ;
	data():p(0),hash1(0), hash2(0),lazy(0), id(0){}
	data(int _p, ll _hash1, ll _hash2, bool _lazy, int _id):p(_p),hash1(_hash1),hash2(_hash2),lazy(_lazy),id(_id){}
} tree[N << 2] ;

void powerSeries(){
	power[0][0] = power[1][0] = 1LL ;
	for(int i = 1 ; i < N ; ++i){
		for(int j = 0 ; j < 2 ; ++j)
			power[j][i] = (power[j][i - 1] * base[j]) % mod[j] ;
	}
}

void allSame(){
	for(int i = 1 ; i < 11 ; ++i){
		for(int j = 0 ; j < N ; ++j){
			for(int k = 0 ; k < 2 ; ++k){
				if(!j)dp[k][i][j] = i ;
				else dp[k][i][j] += (dp[k][i][j - 1] + (power[k][j] * i) % mod[k]) % mod[k] ;
				dp[k][i][j] %= mod[k] ;
			}
		}
	}
}

data merge(data a, data b){
	data res = data(0, 0, 0, 0, 0) ;
	res.p = a.p + b.p ;
	res.hash1 = (a.hash1 + (b.hash1 * power[0][a.p]) % mod[0]) % mod[0] ;
	res.hash2 = (a.hash2 + (b.hash2 * power[1][a.p]) % mod[1]) % mod[1] ;
	return res ;
}

data push(int i, int b, int e, int id){
	data res = data(e - b + 1, 0, 0, 0, 0) ;
	res.hash1 = dp[0][id][e - b] ;
	res.hash2 = dp[1][id][e - b] ;
	if(b != e){
		tree[i << 1].lazy = tree[i << 1 | 1].lazy = 1 ;
		tree[i << 1].id = tree[i << 1 | 1].id = id ;
	}
	return res ;
}

void build(int i, int b, int e){
	if(b == e){
		tree[i] = data(1, s[b] - '0' + 1, s[b] - '0' + 1, 0, 0) ;
		return ;
	}
	int mid = (b + e) >> 1 ;
	build(i << 1, b, mid) ;
	build(i << 1 | 1, mid + 1, e) ;
	tree[i] = merge(tree[i << 1], tree[i << 1 | 1]) ;
}

void update(int i, int b, int e, int l, int r, int id){
	if(tree[i].lazy)tree[i] = push(i, b, e, tree[i].id) ;
	if(l > e or r < b)return ;
	if(l <= b and e <= r){
		tree[i] = push(i, b, e, id) ;
		return ;
	}
	int mid = (b + e) >> 1 ;
	update(i << 1, b, mid, l, r, id) ;
	update(i << 1 | 1, mid + 1, e, l, r, id) ;
	tree[i] = merge(tree[i << 1], tree[i << 1 | 1]) ;
}

data query(int i, int b, int e, int l, int r){
	if(tree[i].lazy)tree[i] = push(i, b, e, tree[i].id) ;
	if(b > r or e < l)return data(0, 0, 0, 0, 0) ;
	if(l <= b and e <= r){
		return tree[i] ;
	}
	int mid = (b + e) >> 1 ;
	return merge(query(i << 1, b, mid, l, r), query(i << 1 | 1, mid + 1, e, l, r)) ;
}


int main(){
    int test = 1 , tc = 0 ;
    while(test--){
        powerSeries() ;
        allSame() ;
        int n = Int, m = Int, k = Int ;
        int q = m + k ;
        getchar() ;
        scanf("%s",s + 1) ;
        build(1, 1, n) ;
        while(q--){
        	int tp = Int, l = Int, r = Int, c = Int ;
        	if(tp == 1){
        		++c ;
        		update(1, 1, n, l, r, c) ;
        	}
        	else{
        		data a = query(1, 1, n, l, r - c) ;
        		data b = query(1, 1, n, l + c, r) ;
        		if(a.hash1 == b.hash1 and a.hash2 == b.hash2)puts("YES") ;
        		else puts("NO") ;
        	}
        }
    }
    return 0 ;
}

/*...Always look at the part - 04...*/
/*...............END................*/


