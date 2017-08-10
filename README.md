#include<bits/stdc++.h>
using namespace std;
const int N =1e6+5;
int tree[N];
int lazy[N<<2];
char ch[N];
void build(int n) {
    for(int i=1; i<=n; i++)
        tree[i]=ch[i-1]-'0';
}
void update(int id,int l,int r,int x,int y) {
    if(l>r)return;
    if(lazy[id]!=0) {
        if(l!=r) {
            lazy[id*2]+=lazy[id];
            lazy[id*2+1]+=lazy[id];
            lazy[id]=0;
        }

    }
    if(x>r or y<l)return;
    if(x<=l and r<=y) {
        lazy[id]++;
        return;
    }
    int mid=(l+r)>>1;
    update(id*2,l,mid,x,y);
    update(id*2+1,mid+1,r,x,y);
}
int query(int id,int l,int r,int x,int y) {
    if(l>r) return 0;
    if(lazy[id]!=0) {
        if(l!=r) {
            lazy[id*2]+=lazy[id];
            lazy[id*2+1]+=lazy[id];
            lazy[id]=0;
        }
    }
    if(x>r or y<l)return 0;
    if(x<=l and r<=y) {
        //cerr<<tree[x]<<endl;
        if(lazy[id]&1)
            return tree[x]^1;
        else
            return tree[x];
    }
    int mid=(l+r)>>1;
    return max(query(id*2,l,mid,x,y),query(id*2+1,mid+1,r,x,y));
}
int main() {
    int n,m;
    cin>>n>>m;
    scanf("%s",ch);
    build(n);
    while(m--) {
        char s[2];
        scanf("%s",s);
        if(s[0]=='Q') {
            int l;
            scanf("%d",&l);
            printf("%d\n",query(1,1,n,l,l));
        } else {
            int l,r;
            scanf("%d%d",&l,&r);
            update(1,1,n,l,r);
        }
    }
    return 0;
}


