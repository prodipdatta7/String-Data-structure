#include <bits/stdc++.h>
using namespace std ;

const int N = 1e5 + 5 ;
const int K = 16 ;
int dp[N][K + 1], a[N], Log[N];

void build(int n){
	for(int i = 0 ; i < n ; ++i){
		dp[i][0] = a[i] ;
	}

	for(int j = 1 ; j <= K ; ++j){
		for(int i = 0 ; i + (1 << j) <= n ; ++i){
			dp[i][j] = min(dp[i][j - 1], dp[i + (1 << (j - 1))][j - 1]) ;
		}
	}
}

void build_log(){
	Log[1] = 0 ;
	for(int i = 2 ; i < N ; ++i){
		Log[i] = Log[i / 2] + 1 ;
	}
}

int query(int l, int r){
	//int Log = log2(r - l + 1) ;
	//return min(dp[l][Log], dp[r - (1 << Log) + 1][Log]) ;
	int x = Log[r - l + 1] ;
	return min(dp[l][x], dp[r - (1 << x) + 1][x]) ;
}

int main(){
	int n ; cin >> n ;
	for(int i = 0 ; i < n ; ++i){
		cin >> a[i] ;
	}
	build(n) ;
	build_log() ;
	int q ; cin >> q ;
	for(int i = 1 ; i <= q ; ++i){
		int l, r ; cin >> l >> r ;
		printf("%d\n",query(l, r));
	}
	return 0 ;
}