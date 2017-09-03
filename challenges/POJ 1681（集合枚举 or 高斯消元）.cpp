/*
 * @模版题
 * POJ 1681（集合枚举 or 高斯消元）
 * 题目大意：给定方阵,求使所有颜色变为黄色所需最小步数。
 */
#include <iostream>
#include <cstring>
#include <cstdio>
#include <climits>
using namespace std;
const int maxn=20;
const int dx[]={0,-1,0,0,1};
const int dy[]={-1,0,0,1,0};
int n,ct;
char a[maxn][maxn];
bool b[maxn][maxn];     //b标记颜色

bool check(int x,int y){  //判定(x,y)是否需要翻转

    int c=a[x][y];
    for(int i=0;i<5;i++){
        int tx=x+dx[i],ty=y+dy[i];
        if(tx>=0&&ty>=0&&tx<n&&ty<n) c+=b[tx][ty];
    }
    return c&1;
}
int calc(){             //已知第1行，求最小操作数

    for(int i=1;i<n;i++)
        for(int j=0;j<n;j++)
            if(check(i-1,j)) b[i][j]=true;

    for(int j=0;j<n;j++)    //如果最后一行不全为白，则无解
        if(check(n-1,j)) return -1;

    int ct=0;
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            ct+=b[i][j];

    return ct;
}
int main() {

    scanf("%d",&ct);
    while(ct--) {
        scanf("%d",&n);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) {
                cin >> a[i][j];
                if (a[i][j] == 'y') a[i][j] = 0;    //黄色标记为0，否则为1
                else a[i][j] = 1;
            }

        int res = INT_MAX;
        for (int i = 0; i < (1 << n); i++) {
            memset(b, 0, sizeof(b));
            for (int j = 0; j < n; j++)
                b[0][j] = (i >> j) & 1;

            int t = calc();
            if (t != -1 && res > t) {
                res = t;
            }
        }

        if (res == INT_MAX) puts("inf");
        else cout << res << endl;
    }
    return 0;
}