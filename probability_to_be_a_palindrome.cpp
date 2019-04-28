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

//Palindromic Tree // 

int tree[N][26], link[N], len[N], ans[N];
int idx, t ;
char s[N] ;
ll res[N] ;

void PalindromicTree(){
	len[1] = -1, len[2] = 0 ;
	link[1] = link[2] = 1 ;
	idx = t = 2 ;
	int n = strlen(s + 1) ;
	for(int i = 1 ; i <= n ; ++i){
		while(s[i - len[t] - 1] != s[i])t = link[t] ;
		int x = link[t], c = s[i] - 'a' ;
		while(s[i - len[x] - 1] != s[i])x = link[x] ;
		if(!tree[t][c]){
			tree[t][c] = ++idx ;
			len[idx] = len[t] + 2 ;
			link[idx] = len[idx] == 1 ? 2 : tree[x][c] ;
			ans[idx] = 1 + ans[link[idx]] ;
			res[idx] += ans[idx] + res[idx - 1] ;
		}
		else res[idx] += ans[tree[t][c]] ;
		t = tree[t][c] ;
	}
	ll tot = 1LL * n * (n + 1) / 2LL ;
	ll gcd = __gcd(res[idx], tot) ;
	res[idx] /= gcd, tot /= gcd ;
	printf("%lld/%lld\n",res[idx], tot);
}

int main(){
    int test = 1 , tc = 0 ;
    while(test--){
        scanf("%s",s + 1) ;
        mem(tree) ;
        PalindromicTree() ;
    }
    return 0 ;
}

/*...Always look at the part - 04...*/
/*...............END................*/


