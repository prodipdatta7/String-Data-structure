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

struct node{
	ll sum, lazy ;
	node *l, *r ;
	node():sum(0),lazy(0),l(NULL),r(NULL){}
	node(ll x, ll y):sum(x),lazy(y){}
} ;

void propagate(node* cur, int b, int e){
	if(cur -> lazy){
		cur -> sum += 1LL * (e - b + 1) * cur -> lazy ;
		if(b != e){
			if(cur -> l == NULL)cur -> l = new node() ;
			if(cur -> r == NULL)cur -> r = new node() ;
			cur -> l -> lazy += cur -> lazy ;
			cur -> r -> lazy += cur -> lazy ;
		}
		cur -> lazy = 0 ;
	}
}

void update(node* cur, int b, int e, int l, int r, ll v){
	propagate(cur, b, e) ;
	if(b > r or e < l)return ;
	if(l <= b and e <= r){
		cur -> sum += v * (e - b + 1) ;
		if(b != e){
			if(cur -> l == NULL)cur -> l = new node() ;
			if(cur -> r == NULL)cur -> r = new node() ;
			cur -> l -> lazy += v ;
			cur -> r -> lazy += v ;
		}
		return ;
	}
	int mid = (b + e) >> 1 ;
	if(cur -> l == NULL)cur -> l = new node() ;
	if(cur -> r == NULL)cur -> r = new node() ;
	update(cur -> l, b, mid, l, r, v) ;
	update(cur -> r, mid + 1, e, l, r, v) ;
	cur -> sum = cur -> l -> sum + cur -> r -> sum ;
}

ll query(node* cur, int b, int e, int l, int r){
	//error(b, e, l, r, cur->sum, cur->lazy)
	propagate(cur, b, e) ;
	if(!cur -> sum or b > r or e < l)return 0 ;
	if(l <= b and e <= r)return cur -> sum ;
	int mid = (b + e) >> 1 ;
	return query(cur -> l, b, mid, l, r) + query(cur -> r, mid + 1, e, l, r) ;
}

ll get(int l, int r){
	int h = r - l + 1 ;
	return 1LL * (l + r) * h / 2LL ;
}


int main(){
    int test = 1 , tc = 0 ;
    while(test--){
        int n = Int, q = Int ;
        node *root = new node() ;
        while(q--){
        	int tp = Int ;
        	if(tp == 1){
        		int l = Int, r = Int, v = Int ;
        		update(root, 1, n, l, r, v) ;
        	}
        	else{
        		int l = Int, r = Int ;
        		ll res = query(root, 1, n, l, r) ;
        		ll base = get(l, r) ;
        		printf("%lld\n",base - res);
        	}
        }
    }
    return 0 ;
}

/*...Always look at the part - 04...*/
/*...............END................*/


