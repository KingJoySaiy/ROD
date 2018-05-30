/*
 * POJ 2991 (计算几何 + 线段树)
 */
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <cstring>

using namespace std;

const int maxn = int(1e4 + 5);
const int maxt = (1 << 15) - 1;
const double pi = acos(-1);

double x[maxt], y[maxt];    //当前的点指向终点的向量
double ang[maxt];           //x轴负半轴逆时针旋转形成的夹角
double pre[maxt], angle;
int len[maxn], choose;
int n, c, t;

void ini(int k, int l, int r) {

    ang[k] = x[k] = 0;
    if(l + 1 == r) {
        y[k] = len[l];
        return;
    }
    int chl = 2 * k + 1, chr = 2 * k + 2, mid = (l + r) >> 1;
    ini(chl, l, mid);
    ini(chr, mid, r);
    y[k] = y[chl] + y[chr];
}
void change(int s, double angle, int v, int l, int r) {

    if(s <= l or s >= r) return;
    int chl = v * 2 + 1, chr = v * 2 + 2, mid = (l + r) >> 1;
    change(s, angle, chl, l, mid);
    change(s, angle, chr, mid, r);
    if(s <= mid) ang[v] += angle;
    double si = sin(ang[v]), co = cos(ang[v]);
    x[v] = x[chl] + co * x[chr] - si * y[chr];
    y[v] = y[chl] + si * x[chr] + co * y[chr];
}
void solve() {

    static int flag = 0;
    if(flag++) puts("");
    memset(x, 0, sizeof(x));
    memset(y, 0, sizeof(y));
    memset(ang, 0, sizeof(ang));
    fill(pre, pre + maxt, pi);

    for(int i = 0; i < n; i++) scanf("%d", len + i);
    ini(0, 0, n);
    while(c--) {
        scanf("%d%d", &choose, &t);
        angle = t * pi / 180;
        change(choose, angle - pre[choose], 0, 0, n);
        pre[choose] = angle;
        printf("%.2f %.2f\n", x[0], y[0]);
    }
}
int main() {

    while(cin >> n >> c) solve();

//    system("pause");
    return 0;
}
