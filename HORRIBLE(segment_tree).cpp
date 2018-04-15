#include<bits/stdc++.h>
#define mx 100005
using namespace std;

struct lazy{
    long long int sum=0,prop=0;
}tree[mx*3];

void make_tree(long long int node,long long int i,long long int j)
{
    if(i==j){
        tree[node].sum=0;
        tree[node].prop=0;
        return;
    }

    long long int left=2*node;
    long long int right=2*node+1;
    long long int mid=(i+j)/2;
    make_tree(left,i,mid);
    make_tree(right,mid+1,j);
    tree[node].sum=tree[left].sum+tree[right].sum;
    tree[node].prop=0;
    return;
}

void update(long long int node,long long int b,long long int e,long long int i,long long int j,long long int x)
{
    if(b>j || e<i){
        return;
    }

    if(b>=i && e<=j){
        tree[node].sum+=((e-b+1)*x);
        tree[node].prop+=x;
        return;
    }
    long long int left=2*node;
    long long int right=2*node+1;
    long long int mid=(b+e)/2;
    update(left,b,mid,i,j,x);
    update(right,mid+1,e,i,j,x);

    tree[node].sum=tree[left].sum+tree[right].sum+(e-b+1)*tree[node].prop;
    return;
}

long long int query(long long int node,long long int b,long long int e,long long int i,long long int j,long long int carry=0)
{
    if(b>j || e<i){
        return 0;
    }

    if(b>=i && e<=j){
        return (tree[node].sum+((e-b+1)*carry));
    }

    long long int left=2*node;
    long long int right=2*node+1;
    long long int mid=(b+e)/2;
    long long int ob1=query(left,b,mid,i,j,carry+tree[node].prop);
    long long int ob2=query(right,mid+1,e,i,j,carry+tree[node].prop);
    return ob1+ob2;
}

int main()
{
    long long int n,q,a,b,c,t;
    long long int x;
    scanf("%lld",&t);
    for(long long int i=0;i<t;i++){

        scanf("%lld%lld",&n,&q);
        make_tree(1,1,n);

        for(long long int j=0;j<q;j++){
            scanf("%lld",&c);
            if(c==0){
                scanf("%lld%lld%lld",&a,&b,&x);
                update(1,1,n,a,b,x);
            }

            else{
                scanf("%lld%lld",&a,&b);
                printf("%lld\n",query(1,1,n,a,b));
            }
        }

    }
    return 0;
}
