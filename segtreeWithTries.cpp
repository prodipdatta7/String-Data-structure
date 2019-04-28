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

struct trie{
    vector < array <int, 2 > > t ;
    trie(){
        t.assign(1, {-1, -1}) ;
    }

    void insert(int x){
        int cur = 0 ;
        for(int i = 20 ; i >= 0 ; --i){
            int f = (x >> i) & 1 ;
            if(t[cur][f] == -1){
                t[cur][f] = sz(t) ;
                t.pb({-1, -1}) ;
            }
            cur = t[cur][f] ;
        }
    }

    int query(int x){
        int tt = 0, res = 0 ;
        for(int i = 20 ; i >= 0 ; --i){
            int f = (x >> i) & 1 ;
            if(t[tt][f ^ 1] != -1){
                res |= (1 << i) ;
                tt = t[tt][f ^ 1] ;
            }
            else tt = t[tt][f] ;
        }
        return res ;
    }
} ;

struct segtree{
    int n ;
    vector < trie > tree ;
    segtree(int n):n(n){
        tree.resize(n << 2) ;
    }

    int query(int i, int b, int e, int l, int r, int x){
        if(b > r or e < l)return 0 ;
        if(l <= b and e <= r){
            return tree[i].query(x) ;
        }
        int mid = (b + e) >> 1 ;
        return max(query(i << 1, b, mid, l, r, x), query(i << 1 | 1, mid + 1, e, l, r, x)) ;
    }

    void add(int i, int b, int e, int p, int x){
        tree[i].insert(x) ;
        if(b == e)return ;
        int mid = (b + e) >> 1 ;
        if(p <= mid)add(i << 1, b, mid, p, x) ;
        else add(i << 1 | 1, mid + 1, e, p, x) ;
    }
} ;



int main(){
    int test = 1 , tc = 0 ;
    while(test--){
        int n = Int ;
        segtree T(n + 1) ;
        for(int i = 1 ; i <= n ; ++i){
            int x = Int ;
            T.add(1, 1, n, i, x) ;
        }
        int q = Int ;
        while(q--){
            int l = Int, r = Int, x = Int ;
            int res = T.query(1, 1, n, l, r, x) ;
            printf("%d\n",res);
        }
    }
    return 0 ;
}

/*...Always look at the part - 04...*/
/*...............END................*/


