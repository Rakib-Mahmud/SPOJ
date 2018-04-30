#include<bits/stdc++.h>

using namespace std;

int main()
{
    int n,k,ara[100005],mx=-1,indx;
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        scanf("%d",&ara[i]);
    }
    scanf("%d",&k);
    int low=0, high=k-1;
    for(int i=0;i<k;i++){
        if(mx<ara[i]){ mx=ara[i]; indx=i;}
    }
    printf("%d",mx);
    while(high<n){
            low++; high++;
            if(indx>=low){
                if(mx<ara[high]){
                    mx=ara[high]; indx=high;
                }
            }
            else{
                mx=-1;
                for(int i=low;i<=high;i++){
                    if(mx<ara[i]){ mx=ara[i]; indx=i;}
                    }
            }
            if(high<n)
            printf(" %d",mx);
    }
    return 0;
}
