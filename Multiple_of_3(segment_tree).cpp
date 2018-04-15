#include<bits/stdc++.h>
#define mx 100005
using namespace std;

struct lazy{
    int prop=0,plus_one=0,plus_two=0,div_three;
}tree[mx*3];

void make_tree(int node,int i,int j)
{
    if(i==j){
        tree[node].div_three=1;
        return;
    }
    int left=2*node+1;
    int right=2*node+2;
    int mid=(i+j)/2;
    make_tree(left,i,mid);
    make_tree(right,mid+1,j);

    tree[node].div_three=tree[left].div_three+tree[right].div_three;
    return;
}

void update(int node,int b,int e,int i,int j,int carry=0,int x=1)
{
    if(b>j || e<i){
        int tmp1,tmp2;
        tree[node].prop+=carry;
        for(int i=0;i<(carry%3);i++){
        tmp1=tree[node].plus_one;
        tmp2=tree[node].plus_two;
        tree[node].plus_one=tree[node].div_three;
        tree[node].plus_two=tmp1;
        tree[node].div_three=tmp2;
        }
        return;
    }

    if(b>=i && e<=j){
        int tmp1,tmp2;
        tree[node].prop+=(x+carry);
        for(int i=0;i<((carry+1)%3);i++){
        tmp1=tree[node].plus_one;
        tmp2=tree[node].plus_two;
        tree[node].plus_one=tree[node].div_three;
        tree[node].plus_two=tmp1;
        tree[node].div_three=tmp2;
        }
        return;
    }
    int left=2*node+1;
    int right=2*node+2;
    int mid=(b+e)/2;
    update(left,b,mid,i,j,tree[node].prop+carry);
    update(right,mid+1,e,i,j,tree[node].prop+carry);
    tree[node].prop=0;
    tree[node].div_three=tree[left].div_three+tree[right].div_three;
    tree[node].plus_one=tree[left].plus_one+tree[right].plus_one;
    tree[node].plus_two=tree[left].plus_two+tree[right].plus_two;
    return;
}

int query(int node,int b,int e,int i,int j,int carry=0)
{
    if(b>j || e<i){
        return 0;
    }

    if(b>=i && e<=j){
        if(carry==0){
                return (tree[node].div_three);
        }
        else{
            int tmp1,tmp2;
            lazy ob;
            ob=tree[node];
            for(int i=0;i<(carry%3);i++){
                tmp1=ob.plus_one;
                tmp2=ob.plus_two;
                ob.plus_one=ob.div_three;
                ob.plus_two=tmp1;
                ob.div_three=tmp2;
            }
            return (ob.div_three);
        }
    }

    int left=2*node+1;
    int right=2*node+2;
    int mid=(b+e)/2;
    int ob1=query(left,b,mid,i,j,carry+tree[node].prop);
    int ob2=query(right,mid+1,e,i,j,carry+tree[node].prop);
    return ob1+ob2;
}

int main()
{
    int n,q,u,a,b,c;
    scanf("%d%d",&n,&q);
    make_tree(0,0,n-1);
    for(int i=0;i<q;i++){
        scanf("%d%d%d",&a,&b,&c);
        if(a==0){
            update(0,0,n-1,b,c);
        }
        else{
            printf("%d\n",query(0,0,n-1,b,c));
        }
    }

    return 0;
}

