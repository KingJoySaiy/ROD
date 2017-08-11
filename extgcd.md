# 扩展欧几里德算法
## 一、题目描述
* 来源: hihoCoder 1297(数论四.扩展欧几里德)
* 给定环形m块石板，二人从不同处以不同速度同向行走，求第一次相遇的时间？
* 条件:0<=v1,v2<=1e9,1000ms
## 二、知识储备
### 1、最大公约数(GCD)
若A>B且B不为0,则分别把B,AmodB分别赋值给A,B，反之亦然，直至min(A,B)为0时max(A,B)即为gcd(A,B)。
```c++
int gcd(int a,int b){
	return b?gcd(b,a%b):a;
}
```
### 2、贝祖定理(BI)
给定方程Ax+By=gcd(A,B),若A,B为整数，则必然至少存在一组(x,y)使得原方程成立。
### 3、扩展欧几里德(EXTGCD)
形如 `Ax+By=C` 的二元一次方程，要求解出一组(x,y)使得原方程成立。根据贝祖定理，若方程有解，则C必为gcd(A,B)的整数倍，即存在整数n使得`C=n*gcd(A,B)`成立。

判定有解之后，由于A,B,C存在公约数gcd(A,B)，则可分别除以gcd(A,B)。令`A'=A/gcd(A,B),B'=gcd(A,B)`,此时方程简化为`A'x+B'y=n`,考虑到此方程的解是方程`A'x+B'y=1`的n倍，所以不妨先求出后者的一组解，继而把解扩大n倍。

根据贝祖定理，若方程`Ax+By=1`有解，则`gcd(A,B)=1`，即A,B互质。根据原有的欧几里德算法，假设已求得`Bx'+(AmodB)y'=gcd(A,B)`的解(x',y')，将取模运算公式`AmodB=A-(A/B)B`带入，得`Ay'+B(x'-(A/B)y')=gcd(A,B)`，而当B=0时，有`1A+0B=A=gcd(A,B)`作为终止条件，此时x',y'记为原方程的一组解。
```c++
void exgcd(int a,int b,int &x,int &y){
	b?exgcd(b,a%b,y,x),y-=(a/b)*x:x=1,y=0;
}
```
易知gcd和extgcd的复杂度都是`O(logmax(A,B))`，而求extgcd求解的同时也把gcd求出来了，继而二者可以合并，复杂度不变。
```c++
int extgcd(int a,int b,int &x,int &y){
	int t=a;
	if(b){
		t=extgcd(b,a%b,y,x);
		y-=(a/b)*x;
	}
	else{
		x=1;
		y=0;
	}
	return t;
}
```
## 三、基本思路
题目给出二人初始位置s1,s2和速度v1,v2，m块石板对应编号为0,1,...m-1。假定v1<v2则二人相遇时有等式`(s2-s1+t(v2-v1))mod m=0`,即存在非负整数k使得`mk+(v2-v1)t=s2-s1`。此方程中只有k和t是未知变量，而我们的目标是求出使方程成立的解系中t的最小非负值。

令`x=t,y=k,A=v1-v2,B=m,C=s2-s1`，则原方程转化为`Ax+By=C`，利用上述的扩展欧几里德算法即可求出(x,y)。但是在求解过程中并不能保证x是最小的非负整数，它不能直接作为最优解。所以需要将(A',B',x',y')扩充为一个解系，由于A,B互质，可以进行如下扩展:
```
        A'x' + B'y' = 1
=>      A'x' + B'y' + (p-p)A'B' = 1
=>      (x'+pB')A' + (y'-pA')B' = 1
=>      x = x' + pB', y = y' - pA'
```
可以求得最小的x为`(x'+pB)modB,(x'+pB>0)`。由于要求`Ax+By=C`的解而不是`Ax+By=1`的解，所以还需将x扩大C倍，因此最优解为`x=(x*C)modB`。还需注意的是，当x<0时，要将x不断累加B，直到x为非负整数。
## 四、具体实现
```c++
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
void extgcd(int a,int b,LL &x,LL &y){
	
	b?(extgcd(b,a%b,y,x),y-=(a/b)*x):(x=1,y=0);
}
int gcd(int a,int b){
	
	return b?gcd(b,a%b):a;
}
int main(){
	
	LL x,y,c;
	int s1,s2,v1,v2,a,b;
	cin>>s1>>s2>>v1>>v2>>b;
	a=v1-v2;
	c=s2-s1;
	
	if(a<0) a+=b;
	int xx=gcd(a,b);
	if(c%xx){
		puts("-1");
		return 0;
	}
	a/=xx;
	b/=xx;
	c/=xx;
	extgcd(a,b,x,y);
	
	x=(x*c)%b;
	while(x<0) x+=b;
	cout<<x<<endl;

return 0;
}
```



