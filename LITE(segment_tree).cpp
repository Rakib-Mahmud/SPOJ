#include<bits/stdc++.h>
#define mx 100005
using namespace std;

struct lazy{
    int on=0,off,prop;
}tree[mx*3];


void make_tree(int node,int i,int j)
{
    if(i==j){
        tree[node].on=0;   tree[node].off=1;
        tree[node].prop=0;
        return;
    }
    int left=2*node;
    int right=2*node+1;
    int mid=(i+j)/2;
    make_tree(left,i,mid);
    make_tree(right,mid+1,j);

    tree[node].off=tree[left].off+tree[right].off;
    tree[node].prop=0;
    return;
}

void update(int node,int b,int e,int i,int j,int carry=0,int x=1)
{
    if(b>j || e<i){
        int tmp;
        for(int i=0;i<(carry%2);i++){
            tmp=tree[node].off;
            tree[node].off=tree[node].on;
            tree[node].on=tmp;
        }
        tree[node].prop+=carry;
        return;
    }

    if(b>=i && e<=j){
        int tmp;
        for(int i=0;i<((carry+1)%2);i++){
            tmp=tree[node].off;
            tree[node].off=tree[node].on;
            tree[node].on=tmp;
        }
        tree[node].prop+=x+carry;
        return;
    }
    int left=2*node;
    int right=2*node+1;
    int mid=(b+e)/2;
    update(left,b,mid,i,j,carry+tree[node].prop);
    update(right,mid+1,e,i,j,carry+tree[node].prop);
    tree[node].prop=0;
    tree[node].on=tree[left].on+tree[right].on;
    tree[node].off=tree[left].off+tree[right].off;
    return;
}

int query(int node,int b,int e,int i,int j,int carry=0)
{
    if(b>j || e<i){
        return 0;
    }

    if(b>=i && e<=j){
        int tmp;
        lazy ob;
        ob=tree[node];
        for(int i=0;i<(carry%2);i++){
            tmp=ob.off;
            ob.off=ob.on;
            ob.on=tmp;
        }
        return ob.on;
    }

    int left=2*node;
    int right=2*node+1;
    int mid=(b+e)/2;
    int ob1=query(left,b,mid,i,j,carry+tree[node].prop);
    int ob2=query(right,mid+1,e,i,j,carry+tree[node].prop);
    return (ob1+ob2);
}

int main()
{
    int n,q,a,b,c;
    scanf("%d%d",&n,&q);
    make_tree(1,1,n);

    for(int i=0;i<q;i++){
    scanf("%d",&c);
    if(c==0){
        scanf("%d%d",&a,&b);
        update(1,1,n,a,b);
        }
    else{
        scanf("%d%d",&a,&b);
        printf("%d\n",query(1,1,n,a,b));
        }
    }

    return 0;
}
