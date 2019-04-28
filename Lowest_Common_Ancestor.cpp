#include <bits/stdc++.h>
using namespace std ;

const int N = 1e5 + 5 ;
const int k = 16 ;
int par[N][k + 1] , dep[N];
vector < vector < int > > g ;

void dfs(int s, int p = 0){
	par[s][0] = p ;
	dep[s] = 1 + dep[p] ;
	for(int i = 1 ; i <= k ; ++i){
		par[s][i] = par[par[s][i - 1]][i - 1] ;
	}
	for(int i : g[s]){
		if(i != p)
			dfs(i, s) ;
	}
}

int LCA(int x, int y){
	if(dep[x] < dep[y])swap(x, y) ;
	int d = dep[x] - dep[y] ;
	for(int i = k ; i >= 0 ; --i){
		if(d & (1 << i))
			x = par[x][i] ;
	}
	if(x == y)return x ;
	for(int i = k ; i >= 0 ; --i){
		if(par[x][i] != par[y][i]){
			x = par[x][i], y = par[y][i] ;
		}
	}
	return par[x][0] ;
}

int main(){
	int n ; cin >> n ;
	g.resize(n + 1) ;
	for(int i = 1 ; i < n ; ++i){
		int x, y ; cin >> x >> y ;
		g[x].push_back(y);
		g[y].push_back(x);
	}
	dfs(1) ;
	int q ; cin >> q ;
	for(int i = 1 ; i <= q ; ++i){
		int x, y ; cin >> x >> y ;
		printf("%d\n",LCA(x, y));
	}
	return 0 ;
}
