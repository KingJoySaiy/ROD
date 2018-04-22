/*
 * UVA 10479 (规律+DFS)
 * 题目大意：给定一个序列，有如下规则：第一个数是0，每次对于前一次推出来的每个数字x，先添加x个0，
 * 再添加x+1。0 -> 1 -> 02 -> 1003 -> 02110004...，继而序列为:0102100302110004...，
 * 求出序列中第n个数为多少，0<n<2^63。
 */
#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long ULL;

ULL a[64];

int dfs(ULL n,int p){//第p堆第n个数

    int ct=1;      //第i堆有ct个，ct=1,2,3...p-1
    ULL len;       //第i堆的长度
    for(int i=p-2;i>=0;i--){
        len=i?a[i-1]:1;     //注意第0堆长度为1
        for(int j=0;j<ct;j++){
            if(n>len) n-=len;
            else return dfs(n,i);
        }
        ct++;
    }
    return p;   //第p堆最后位置为p
}
int main(){

    ULL n;
    for(int i=0;i<64;i++) a[i]=1ull<<i;
    while(cin>>n,n){
        size_t t=lower_bound(a,a+64,n)-a;
        cout<<dfs(n-a[t-1],t)<<endl;    //找到n在第t堆第n-a[t]处
    }

//    system("pause");
    return 0;
}
/*
4
7
44
806856837013209088
0
 */