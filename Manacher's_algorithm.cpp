#include <bits/stdc++.h>
using namespace std ;

const int N = 1e5 + 5 ;

int p[N] ;

string preProcess(string s){
    if(s.size() == 0)return "^$" ;
    string res = "^" ;
    for(int i = 0 ; s[i] ; ++i){
        res += "#" + s.substr(i , 1);
    }
    res += "#$" ;
    return res ;
}

string longestPalindrome(string s){
    string T = preProcess(s) ;
    int n = T.size() ;
    int C = 0 , R = 0 ;
    for(int i = 1 ; i < n - 1 ; ++i){
        int mirror = (C << 1) - i ;
        p[i] = (R > i) ? min(R - i , p[mirror]) : 0 ;
        while(T[i + 1 + p[i]] == T[i - 1 - p[i]])++p[i] ;
        if(i + p[i] > R){
            C = i ;
            R = i + p[i] ;
        }
    }
    int maxLen = 0 , centerIndex = 0 ;
    for(int i = 1 ; i < n - 1 ; ++i){
        if(maxLen < p[i]){
            maxLen = p[i] ;
            centerIndex = i ;
        }
    }
    return s.substr((centerIndex - 1 - maxLen) / 2 , maxLen) ;
}

int main(){
    string s ; cin >> s ;
    cout << longestPalindrome(s) << '\n' ;
}