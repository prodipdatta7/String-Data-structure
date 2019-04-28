#include <cstdio>
#include<vector>
using namespace std ;
const int N = 10100 ;

int chainHead[N], chainId[N], pos[N], cost[N], par[N][14];
vector < int > g[N], costs[N], index[N] ;
int sz[N], dep[N], End[N], cur, chainNo;
int tree[N << 2] ;


void fresh(int n){
	for(int i = 0 ; i <= n ; ++i){
		g[i].clear() ;
		costs[i].clear() ;
		index[i].clear() ;
		chainHead[i] = -1 ;
		for(int j = 0 ; j < 14 ; ++j)
			par[i][j] = -1 ;
	}
}

void dfs(int s, int p = 0){
	par[s][0] = p ;
	sz[s] = 1 ;
	dep[s] = 1 + dep[p] ;
	for(int i = 1 ; i < 14 ; ++i)
		par[s][i] = par[par[s][i - 1]][i - 1] ;
	for(int i = 0 ; i < g[s].size() ; ++i){
		if(g[s][i] == p)continue;
		End[index[s][i]] = g[s][i] ;
		dfs(g[s][i], s) ;
		sz[s] += sz[g[s][i]] ;
	}
}

void HLD(int s, int p, int c){
	if(chainHead[chainNo] == -1){
		chainHead[chainNo] = s ;
	}
	chainId[s] = chainNo ;
	pos[s] = ++cur ;
	cost[cur] = c ;
	int mx = -1, id = -1, cst = 0 ;
	for(int i = 0 ; i < g[s].size() ; ++i){
		if(g[s][i] == p)continue ;
		if(sz[g[s][i]] > mx){
			mx = sz[g[s][i]] ;
			id = g[s][i] ;
			cst = costs[s][i] ;
		}
	}
	if(id != -1){
		HLD(id, s, cst) ;
	}
	for(int i = 0 ; i < g[s].size() ; ++i){
		if(g[s][i] == p or g[s][i] == id)continue ;
		++chainNo ;
		HLD(g[s][i], s, costs[s][i]) ;
	}
}

void build(int i, int b, int e){
	if(b == e){
		tree[i] = cost[b] ;
		return ;
	}
	int mid = (b + e) >> 1 ;
	build(i << 1, b, mid) ;
	build(i << 1 | 1, mid + 1, e) ;
	tree[i] = tree[i << 1] > tree[i << 1 | 1] ? tree[i << 1] : tree[i << 1 | 1] ;
}

int lca_query(int a, int b){
	if(dep[a] < dep[b])swap(a, b) ;
	int d = dep[a] - dep[b] ;
	for(int i = 13 ; i >= 0 ; --i)
		if(d & (1 << i))
			a = par[a][i] ;
	if(a == b)return a ;
	for(int i = 13 ; i >= 0 ; --i)
		if(par[a][i] != par[b][i])
			a = par[a][i], b = par[b][i] ;
	return par[a][0] ;
}

int query(int i, int b, int e, int l, int r){
	if(e < l or b > r)return 0 ;
	if(l <= b and e <= r)return tree[i] ;
	int mid = (b + e) >> 1 ;
	int x = query(i << 1, b, mid, l, r) ;
	int y = query(i << 1 | 1, mid + 1, e, l, r) ;
	return x >= y ? x : y ;
}

int query_up(int u, int v){
	if(u == v)return 0;
	int uchain, vchain = chainId[v], res = -1 ;
	while(true){
		uchain = chainId[u] ;
		if(uchain == vchain){
			if(u != v){
				int x = query(1, 1, cur, pos[v] + 1, pos[u]) ;
				if(res < x)res = x ;
			}
			break ;
		}
		int x = query(1, 1, cur, pos[chainHead[uchain]], pos[u]) ;
		if(res < x)res = x ;
		u = chainHead[uchain] ;
		u = par[u][0] ;
	}
	return res ;
}

void update(int i, int b, int e, int p, int v){
	if(p > e or p < b)return ;
	if(p == e and b == p){
		tree[i] = v ;
		return ;
	}
	int mid = (b + e) >> 1 ;
	update(i << 1, b, mid, p, v) ;
	update(i << 1 | 1, mid + 1, e, p, v) ;
	tree[i] = (tree[i << 1] > tree[i << 1 | 1]) ? tree[i << 1] : tree[i << 1 | 1] ;
}

int answer(int a, int b){
	int lca = lca_query(a, b) ;
	int res = query_up(a, lca) ;
	int tmp = query_up(b, lca) ;
	if(res < tmp)res = tmp ;
	return res ;
}

void modify(int a, int b){
	int u = End[a] ;
	update(1, 1, cur, pos[u], b) ;
}


int main(){
	int tc ; scanf("%d",&tc) ;
	while(tc--){
		int n ; 
		scanf("%d",&n) ;
		fresh(n) ;
		int a, b, c ;
		for(int i = 1 ; i < n ; ++i){
			scanf("%d %d %d",&a, &b, &c) ;
			g[a].push_back(b) ;
			costs[a].push_back(c) ;
			index[a].push_back(i) ;
			g[b].push_back(a) ;
			costs[b].push_back(c) ;
			index[b].push_back(i) ;
		}
		cur = chainNo = 0 ;
		dfs(1) ;
		HLD(1, -1, -1) ;
		build(1, 1, cur) ;
		while(true){
			char s[10] ;
			scanf("%s",s) ;
			if(s[0] == 'D')break ;
			scanf("%d %d",&a, &b) ;
			if(s[0] == 'Q'){
				printf("%d\n",answer(a, b)) ;
			}
			else{
				modify(a, b) ;
			}
		}
	}
	return 0 ;
}
