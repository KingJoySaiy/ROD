#include "head.h"

double dist(Point a, Point b) {         //两点间距离

    return sqrt((a - b) * (a - b));
}
bool inter(Line l1, Line l2) {           //判断线段相交（允许在端点处相交）
    return
            max(l1.s.x, l1.e.x) >= min(l2.s.x, l2.e.x) and
            max(l2.s.x, l2.e.x) >= min(l1.s.x, l1.e.x) and
            max(l1.s.y, l1.e.y) >= min(l2.s.y, l2.e.y) and
            max(l2.s.y, l2.e.y) >= min(l1.s.y, l1.e.y) and
            dcmp((l2.s - l1.e) ^ (l1.s - l1.e)) * dcmp((l2.e - l1.e) ^ (l1.s - l1.e)) <= 0 and
            dcmp((l1.s - l2.e) ^ (l2.s - l2.e)) * dcmp((l1.e - l2.e) ^ (l2.s - l2.e)) <= 0;
}
bool inter_2(Line l1, Line l2){          //判断线段相交（任一线段的两端点都在另一条线段的两侧）

    double c1 = (l1.e - l1.s) ^ (l2.s - l1.s), c2 = (l1.e - l1.s) ^ (l2.e - l1.s);
    double c3 = (l2.e - l2.s) ^ (l1.s - l2.s), c4 = (l2.e - l2.s) ^ (l1.e - l2.s);
    return dcmp(c1) * dcmp(c2) < 0 and dcmp(c3) * dcmp(c4) < 0;
}
bool seg_inter_line(Line l1, Line l2) {  //判断直线l1和线段l2是否相交

    return dcmp((l2.s - l1.e) ^ (l1.s - l1.e)) * dcmp((l2.e - l1.e) ^ (l1.s - l1.e)) <= 0;
}
double dis_point_line(Point p, Line l){ //点到直线的最短距离

    Vector v1 = l.e - l.s, v2 = p - l.s;
    return fabs((v1 ^ v2) / v1.len());
}
Point point_line(Point P, Line L) {     //点到直线最近的点

    Point v = L.e - L.s;
    return L.s + v * (((P - L.s) * v) / (v * v));
}
double dis_point_lineseg(Point P, Line L){  //点到线段的最近距离

    if(L.s == L.e) return (P - L.s).len();
    Vector v1 = L.e - L.s, v2 = P - L.s, v3 = P - L.e;
    if(dcmp(v1 * v2) < 0) return v2.len();
    if(dcmp(v1 * v3) > 0) return v3.len();
    return fabs(v2 ^ v2) / v1.len();
}
Point point_lineSeg(Point P, Line L) {      //点到线段的最近点

    Point result;
    double t = ((P - L.s) * (L.e - L.s)) / ((L.e - L.s) * (L.e - L.s));
    if(t >= 0 and t <= 1) {
        result.x = L.s.x + (L.e.x - L.s.x) * t;
        result.y = L.s.y + (L.e.y - L.s.y) * t;
    }
    else {
        if(dist(P,L.s) < dist(P,L.e)) result = L.s;
        else result = L.e;
    }
    return result;
}
double calc_area(Point p[],int n) {              //点的编号从0~n-1，计算多边形面积

    double res = 0;
    for(int i = 1; i < n - 1; i++) res += (p[i] - p[0]) ^ (p[i + 1] - p[0]);
    return res / 2;
}
bool on_seg(Point P,Line L) {                    //判断点是否在线段上

    return
            dcmp((L.s-P)^(L.e-P)) == 0 and
            dcmp((P.x - L.s.x) * (P.x - L.e.x)) <= 0 and
            dcmp((P.y - L.s.y) * (P.y - L.e.y)) <= 0;
}
int in_convex_poly(Point a,Point p[],int n) {     //判断点在凸多边形内

    //-1:点在凸多边形外，0:点在凸多边形边界上，1:点在凸多边形内
    for(int i = 0; i < n; i++) {
        if(dcmp((p[i] - a) ^ (p[(i + 1) % n] - a)) < 0) return -1;
        else if(on_seg(a, Line(p[i], p[(i + 1) % n]))) return 0;
    }
    return 1;
}
int inPoly(Point p, Point poly[], int n) {      //射线法判断点在任意多边形内，顶点数≥3

    //-1:点在凸多边形外，0:点在凸多边形边界上，1:点在凸多边形内
    int cnt = 0;
    Line ray,side;
    ray.s = p;
    ray.e.y = p.y;
    ray.e.x = -inf;         //-INF,注意取值防止越界
    for(int i = 0;i < n;i++) {
        side.s = poly[i];
        side.e = poly[(i + 1) % n];
        if(on_seg(p, side)) return 0;            //如果平行轴则不考虑
        if(!dcmp(side.s.y - side.e.y)) continue;
        if(on_seg(side.s, ray)) {
            if(dcmp(side.s.y - side.e.y) > 0) cnt++;
        }
        else if(on_seg(side.e, ray)) {
            if(dcmp(side.e.y - side.s.y) > 0) cnt++;
        }
        else if(inter(ray, side)) cnt++;
    }
    if(cnt % 2 == 1) return 1;
    return -1;
}
bool isconvex(Point *poly, int n) {             //判断凸多边形

    bool s[3];
    memset(s, false, sizeof(s));
    for(int i = 0; i < n; i++) {
        s[dcmp( (poly[(i + 1) % n] - poly[i]) ^ (poly[(i + 2) % n] - poly[i])) + 1] = true;
        if(s[0] and s[2]) return false;
    }
    return true;
}

int main() {



    return 0;
}



