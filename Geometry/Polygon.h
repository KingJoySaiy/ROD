#ifndef INC_233_POLYGON_H
#define INC_233_POLYGON_H

#include "Point.h"
#include "Line.h"
#include "Circle.h"
#include <algorithm>

const int maxn = 100;

struct Polygon {

    int n;          //n个顶点p，相邻2点线段为l
    Point p[maxn];
    Line l[maxn];
    void add(Point q) {
        p[n++] = q;
    }
    void getLines() {
        for (int i = 0; i < n; i++) l[i] = Line(p[i], p[(i + 1) % n]);
    }
    double circum() {       //多边形的周长
        double res = 0;
        for (int i = 0; i < n; i++) res += p[i].distance(p[(i + 1) % n]);
        return res;
    }
    double area() {         //多边形面积
        double res = 0;
        for (int i = 0; i < n; i++) res += p[i] ^ p[(i + 1) % n];
        return fabs(res) / 2;
    }
    bool direction() {      //判断顶点顺序方向, 1逆时针, 0顺时针
        double res = 0;
        for (int i = 0; i < n; i++) res += p[i] ^ p[(i + 1) % n];
        return dcmp(res) > 0;
    }
    struct cmp {        //比较类，用于顶点的排序
        Point p;
        cmp(const Point &p0) : p(p0) {}
        bool operator () (const Point &aa, const Point &bb) {
            Point a = aa, b = bb;
            int d = dcmp((a - p) ^ (b - p));
            if (!d) return dcmp(a.distance(p) - b.distance(p)) < 0;
            return d > 0;
        }
    };
    void norm() {       //按照逆时针极角排序，Point < 要重载为按x升序再按y升序
        Point mi = *min_element(p, p + n);
        sort(p, p + n, cmp(mi));
    }
    void Andrew(Polygon &convex) {   //Andrew扫描法，由this得到凸包到convex中（需要特判所有点共点或共线）
        sort(p, p + n);
        convex.n = n;
        for(int i = 0; i < min(n, 2); i++) convex.p[i] = p[i];
        if(convex.n == 2 and convex.p[0] == convex.p[1]) convex.n-- ;//特判
        if(n <= 2) return;
        int &top = convex.n;
        top = 1;
        for(int i = 2; i < n; i++) {
            while(top and dcmp((convex.p[top] - p[i])^(convex.p[top - 1] - p[i])) <= 0) top--;
            convex.p[++top] = p[i];
        }
        int temp = top;
        convex.p[++top] = p[n - 2];
        for(int i = n - 3; i >= 0; i--) {
            while (top != temp and dcmp((convex.p[top] - p[i]) ^ (convex.p[top - 1] - p[i])) <= 0) top--;
            convex.p[++top] = p[i];
        }
        if(convex.n == 2 and convex.p[0] == convex.p[1]) convex.n--;   //特判
        convex.norm();      //原来得到的是顺时针的点,排序后逆时针
    }
    void Graham(Polygon &convex) {  //Graham扫描法，得到凸包
        norm();
        int &top = convex.n;
        top = 0;
        if(n == 1){
            top = 1;
            convex.p[0] = p[0];
            return;
        }
        if(n == 2){
            top = 2;
            convex.p[0] = p[0];
            convex.p[1] = p[1];
            if(convex.p[0] == convex.p[1]) top--;
            return;
        }
        convex.p[0] = p[0];
        convex.p[1] = p[1];
        top = 2;
        for(int i = 2; i < n; i++) {
            while(top > 1 and dcmp((convex.p[top - 1] - convex.p[top - 2]) ^ (p[i] - convex.p[top - 2])) <= 0 ) top--;
            convex.p[top++] = p[i];
        }
        if(convex.n == 2 and (convex.p[0] == convex.p[1])) convex.n--;   //特判
    }
    bool checkConvex() {        //判断是否是凸多边形
        bool s[3] = {};
        for (int i = 0; i < n; i++) {
            s[dcmp((p[(i + 1) % n] - p[i]) ^ (p[(i + 2) % n] - p[i])) + 1] = true;
            if (s[0] and s[2]) return false;
        }
        return true;
    }
    int relationPoint(Point t) {    //判断点与任意多边形的关系（0外部，1内部，2边上，3点上）
        for(int i = 0;i < n;i++){
            if(p[i] == t) return 3;
        }
        getLines();
        for(int i = 0;i < n;i++){
            if(l[i].onSegment(t))return 2;
        }
        int cnt = 0;
        for(int i = 0;i < n;i++){
            int k = dcmp((t - p[(i + 1) % n])^(p[i] - p[(i + 1) % n]));
            int u = dcmp(p[i].y - t.y);
            int v = dcmp(p[(i + 1) % n].y - t.y);
            if(k > 0 and u < 0 and v >= 0) cnt++;
            if(k < 0 and v < 0 and u >= 0) cnt -- ;
        }
        return cnt != 0;
    }
    Point barycentre() {        //多边形重心
        Point res(0, 0);
        double area = 0, t;
        for(int i = 1; i < n - 1;i++){
            double tmp = (p[i] - p[0]) ^ (p[i + 1] - p[0]);
            if(!dcmp(tmp)) continue;
            area += tmp;
            res.x += (p[0].x + p[i].x + p[i+1].x) / 3 * tmp;
            res.y += (p[0].y + p[i].y + p[i+1].y) / 3 * tmp;
        }
        return dcmp(area) ? (res / area) : res;
    }
    double areaCircle(Circle c) {   //多边形与圆的面积交
        double res = 0;
        for (int i = 0; i < n; i++) {
            if(dcmp( (p[(i + 1) % n] - c.o) ^ (p[i] - c.o)) >= 0) res += c.areaTriang(p[i], p[(i + 1) % n]);
            else res -= c.areaTriang(p[i], p[(i + 1) % n]);
        }
        return fabs(res);
    }
    int relationcircle(Circle c) {
        getLines();
        int x = 2;
        if (relationPoint(c.o) != 1) return 0;   //圆心不在内部
        for (int i = 0; i < n; i++) {
            if (c.relationSeg(l[i]) == 2) return 0;
            if (c.relationSeg(l[i]) == 1) x = 1;
        }
        return x;
    }

};

int in_convex_poly(Point a, Point p[], int n) {     //判断点与凸多边形的关系

    //-1:点在凸多边形外，0:点在凸多边形边界上，1:点在凸多边形内
    for (int i = 0; i < n; i++) {
        if (dcmp((p[i] - a) ^ (p[(i + 1) % n] - a)) < 0) return -1;
        else if (Line(p[i], p[(i + 1) % n]).onSegment(a)) return 0;
    }
    return 1;
}

int relationPoint(Point p, Point poly[], int n) {      //射线法判断点与任意多边形的关系，前提顶点数≥3

    //-1:点在多边形外，0:点在多边形边界上，1:点在多边形内
    int cnt = 0;
    Line ray, side;
    ray.s = p;
    ray.e.y = p.y;
    ray.e.x = -inf;         //-inf, 注意取值防止越界
    for (int i = 0; i < n; i++) {
        side.s = poly[i];
        side.e = poly[(i + 1) % n];
        if (side.onSegment(p)) return 0;            //如果平行轴则不考虑
        if (!dcmp(side.s.y - side.e.y)) continue;
        if (ray.onSegment(side.s)) {
            if (dcmp(side.s.y - side.e.y) > 0) cnt++;
        } else if (ray.onSegment(side.e)) {
            if (dcmp(side.e.y - side.s.y) > 0) cnt++;
        } else if (interSeg(ray, side)) cnt++;
    }
    if (cnt % 2 == 1) return 1;
    return -1;
}

#endif //INC_233_POLYGON_H
