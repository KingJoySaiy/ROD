1. **数位dp** 一般用于处理小于等于n的满足某些特征的数字个数，或是用 **前缀和之差** 维护一个区间`[L, R]`中的个数。其本质是一种 **暴力枚举** ，由于枚举方式满足dp性质，因而可以记忆化。

2. **问题特征** 

* 对求区间[0, n]内满足条件的数的个数有通用做法。
* 满足条件的数特征与数的大小无关，只与数的组成有关。
* 数的规模较大（位数>100），无法直接枚举。
* 数字枚举存在大量重复性，暴力 + 枚举 = 记忆化搜索

3. **注意点**

* 记忆化搜索思路要清晰
* 开适当的空间（能省则省）
* 寻找合适的状态，简化计算量

4. **具体实现**
```c++
#include <bits/stdc++.h>

using namespace std;

const int maxn = 100;
int dp[maxn][maxn];     //记忆化dp数组
int num[maxn], ct;      //记录处理串中每个数值位
int st;                 //初始状态

//id为处理索引(高位到低位)，status记录状态以便回溯，pre上一位数字(防止大于n)，flag限制当前位能否随便取值
int dfs(int id, int status, int pre, bool flag) {

    if (id == -1) return status;      //处理结束后返回最终状态
    if (!flag and dp[id][status] != -1) return dp[id][status];  //若已处理过则直接取出

    int res = 0, up = flag ? num[id] : 9;   //up为当前为最大取值(保证数不大于n)
    for (int i = 0; i <= up; i++) {         //视具体题目修改status
        res += dfs(id - 1, status, i, flag and i == up);
    }
    return flag ? res : dp[id][status] = res;   //若不受限制则用dp记录最终状态
}
int work(int n) {       //数字处理函数

    while (n) {
        num[ct++] = n % 10;
        n /= 10;
    }
    return dfs(ct - 1, st, 0, true);
}
int main() {

    memset(dp, -1, sizeof(dp));             //放在多组数据外面
    int n, l, r;
    cout << work(n) << endl;                //小于n满足条件的个数
    cout << work(r) - work(l - 1) << endl;  //[l, r]区间内满足条件个数

    return 0;
}
```

* 例题：<a href = "https://github.com/KingJoySaiy/Iterator/blob/master/%E5%A4%9A%E6%A0%A1%E8%AE%AD%E7%BB%83/2018%20Nowcoder%20Contest%203-4/Nowcoder%203rd-4th.md">2018牛客多校第4场C题</a><br>
