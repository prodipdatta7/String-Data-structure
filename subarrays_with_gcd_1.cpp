/* Complexity : O(NlogN)*/

#include <bits/stdc++.h>
using namespace std ;

const int k = 16 ;
const int N = 1e5 + 5 ;
int table[N][k + 1] , a[N] ;

int main(){
	int n ; cin >> n ;
	for(int i = 0 ; i < n ; ++i){
		cin >> a[i] ;
	}
	/*Build Sparse Table*/
	for(int i = 0 ; i < n ; ++i){
		table[i][0] = a[i] ;
	}
	for(int j = 1 ; j <= k ; ++j){
		for(int i = 0 ; i + (1 << j) <= n ; ++i){
			table[i][j] = __gcd(table[i][j - 1], table[i + (1 << (j - 1))][j - 1]) ;
		}
	}
	/*main part of the solution*/
	long long res = 0 ;
	for(int i = 0 ; i < n ; ++i){
		int R = i ;
		/* We will move R forward as long as gcd(a[i], a[i + 1], ... , a[R]) != 1 or until R reaches n */
		int g = 0 ;
		for(int j = k ; j >= 0 ; --j){
			if(R + (1 << j) - 1 >= n)continue ;
			if(__gcd(g, table[R][j]) > 1){
				g = __gcd(g, table[R][j]) ;
				R += (1 << j) ;
			}
		}
		/* In the end either R = n or gcd(a[i], a[i + 1], ... , a[R]) = 1 */
		res += n - R ;
	}
	cout << res << '\n' ;
}