/*
 * UVA 12333 (斐波那契+高精度+字典树)
 * 题目大意：在斐波那契数中查询，给定长度不超过40的前缀，
 * 求前1e5个斐波那契数中满足该前缀的最小数的序号（可能不存在）。
 */
#include<bits/stdc++.h>
using namespace std;

struct node{    //字典树

    int id=-1;
    node *ne[10]={};
}*root=new node;
string a="0",b="1",sum,xx;

void insert(string t,int id){   //插入新数和id

    node *tmp=root;
    for(int i=0,x;i<t.length();i++){
        x=t[i]-'0';
        if(tmp->ne[x]==NULL){
            tmp->ne[x]=new node;
            tmp->ne[x]->id=id;
        }
        tmp=tmp->ne[x];
    }
}
int query(string t){    //查询该数的id，不存在返回-1

    node *tmp=root;
    for(int i=0,x;i<t.length();i++){
        x=t[i]-'0';
        if(tmp->ne[x]==NULL) return -1;
        tmp=tmp->ne[x];
    }
    return tmp->id;
}
string add(const string &a,const string &b){    //高精度加法

    string res;
    int i=a.length()-1,j=b.length()-1,in=0,t;
    while(i>=0&&j>=0){
        t=a[i]-'0'+b[j]-'0'+in;
        res+=(t%10+'0');
        in=t/10;
        i--,j--;
    }
    while(i>=0){
        t=a[i]-'0'+in;
        res+=t%10+'0';
        in=t/10;
        i--;
    }
    while(j>=0){
        t=b[j]-'0'+in;
        res+=t%10+'0';
        in=t/10;
        j--;
    }
    if(in) res+=in+'0';
    reverse(res.begin(),res.end());
    return res;
}
int main(){

    insert("0",0);
    insert("1",1);
    for(int i=2;i<1e5;i++){
        sum=add(a,b);   //递推斐波那契数
        a=b;
        b=sum;
        if(sum.length()>40) sum=sum.substr(0,40);   //只需满足40位的精度即可
        insert(sum,i);
    }
    int ct,kase=0,res;
    cin>>ct;
    while(ct--){
        cin>>xx;
        printf("Case #%d: ",++kase);
        if((res=query(xx))==-1) cout<<res<<endl;
        else cout<<res-1<<endl;     //题意中1是第0个斐波那契数，所以减一
    }

//    system("pause");
    return 0;
}
/*
15
1
12
123
1234
12345
9
98
987
9876
98765
89
32
51075176167176176176
347746739
5610
 */