/*
 * @模板题
 * POJ 2689 （素数筛选）
 * 题目大意：求给定区间内相邻两素数之差的最小值和最大值。
 */
#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;
typedef long long LL;

const int maxn=1e5+5;
int prime[maxn+1],len;  //记录小区间[1,1e5]的素数
bool nprime[10*maxn];   //判定区间[l,r]内的数是否为素数
int a[10*maxn],n;       //二次筛选出区间[l,r]中的所有素数

void init(){    //埃氏筛法枚举素数

    bool book[maxn+1]={};
    for(int i=2;i<=maxn;i++)
        if(!book[i]){
            prime[len++]=i;
            for(int j=i+i;j<=maxn;j++) book[i]=true;
        }
}
void work(int l,int r){ //二次筛选区间内的素数

    memset(nprime,0,sizeof(nprime));
    l=max(l,2);

    //用小区间的素数筛选大的数，防止爆炸
    for(int i=0;i<len&&(LL)prime[i]*prime[i]<=r;i++){
        int t=l/prime[i]+!!(l%prime[i]);    //找出[l,r]中最小的prime[i]倍数t
        if(t==1) t=2;
        for(int j=t;(LL)j*prime[i]<=r;j++)
            if((LL)j*prime[i]>=l) nprime[j*prime[i]-l]=true;
    }
    n=0;
    for(int i=0;i<=r-l;i++)
        if(!nprime[i]) a[n++]=i+l;
}
int main(){

    init();
    int l,r;
    while(cin>>l>>r){
        work(l,r);
        if(n<2) puts("There are no adjacent primes.");
        else{
            int x1=0,x2=1e8,y1=0,y2=0;
            for(int i=1;i<n;i++){   //暴力枚举更新最优解
                if(a[i]-a[i-1]<x2-x1){
                    x1=a[i-1];
                    x2=a[i];
                }
                if(a[i]-a[i-1]>y2-y1){
                    y1=a[i-1];
                    y2=a[i];
                }
            }
            printf("%d,%d are closest, %d,%d are most distant.\n",x1,x2,y1,y2);
        }
    }
    return 0;
}
