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

const int logn = 35 ;
ll tree[N * logn], lazy[N * logn] ;
int L[N * logn], R[N * logn] ;
int cnt = 1 ;

int create(int &v){
	if(!v)
		v = ++cnt ;
	return v ;
}

void propagate(int i, int b, int e){
	if(lazy[i]){
		tree[i] += lazy[i] * (e - b + 1) ;
		if(b != e){
			lazy[create(L[i])] += lazy[i] ;
			lazy[create(R[i])] += lazy[i] ;
		}
		lazy[i] = 0 ;
	}
}

void update(int i, int b, int e, int l, int r, int v){
	propagate(i, b, e);
	if(b > r or e < l)return ;
	if(l <= b and e <= r){
		tree[i] += 1LL * v * (e - b + 1) ;
		if(b != e){
			lazy[create(L[i])] += v ;
			lazy[create(R[i])] += v ;
		}
		return ;
	}
	int mid = (b + e) >> 1 ;
	update(create(L[i]), b, mid, l, r, v) ;
	update(create(R[i]), mid + 1, e, l, r, v) ;
	tree[i] = tree[L[i]] + tree[R[i]] ;
}

ll ask(int i, int b, int e, int l, int r){
	propagate(i, b, e) ;
	if(b > r or e < l or !i)return 0 ;
	if(l <= b and e <= r)return tree[i] ;
	int mid = (b + e) >> 1 ;
	return ask(L[i], b, mid, l, r) + ask(R[i], mid + 1, e, l, r) ;
}

ll get(int l, int r){
	return 1LL * (l + r) * (r - l + 1) / 2LL ;
}


int main(){
    int test = 1 , tc = 0 ;
    while(test--){
        int n = Int, q = Int ;
        while(q--){
        	int tp = Int ;
        	if(tp == 1){
        		int l = Int, r = Int, v = Int ;
        		update(1, 1, n, l, r, v) ;
        	}
        	else{
        		int l = Int, r = Int ;
        		printf("%lld\n",get(l, r) - ask(1, 1, n, l, r));
        	}
        }
    }
    return 0 ;
}

/*...Always look at the part - 04...*/
/*...............END................*/


