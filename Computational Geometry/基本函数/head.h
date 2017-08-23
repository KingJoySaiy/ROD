#ifndef BASIC_FUNCTION_HEAD_H
#define BASIC_FUNCTION_HEAD_H

#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

const double eps = 1e-8;
const double PI = acos(-1.0);
int sgn(double x) {

    if(fabs(x) < eps) return 0;
    if(x < 0) return -1;
    return 1;
}
class Point {//定义点
public:
    double x,y;
    Point(){}
    Point(double _x,double _y) {
        x = _x;
        y = _y;
    }
    Point operator -(const Point &b)const {
        return Point(x - b.x,y - b.y);
    }
    double operator ^(const Point &b)const {//叉积
        return x*b.y - y*b.x;
    }
    double operator *(const Point &b)const {//点积
        return x*b.x + y*b.y;
    }
    void transXY(double B) {//绕原点旋转角度B（弧度值），后x,y的变化
        double tx = x,ty = y;
        x = tx*cos(B) - ty*sin(B);
        y = tx*sin(B) + ty*cos(B);
    }
};
struct Line {
public:
    Point s, e;
    Line() {}
    Line(Point _s, Point _e) {
        s = _s;
        e = _e;
    }
    pair<int, Point> operator&(const Line &b) const {//两直线相交求交点

        //第一个值为0表示直线重合，为1表示平行，为0表示相交,为2是相交
        Point res = s;
        if (sgn((s - e) ^ (b.s - b.e)) == 0) {
            if (sgn((s - b.e) ^ (b.s - b.e)) == 0)
                return make_pair(0, res);//重合
            else return make_pair(1, res);//平行
        }
        double t = ((s - b.s) ^ (b.s - b.e)) / ((s - e) ^ (b.s - b.e));
        res.x += (e.x - s.x) * t;
        res.y += (e.y - s.y) * t;
        return make_pair(2, res);//只有第一个值为2时，交点才有意义
    }
};
#endif //BASIC_FUNCTION_HEAD_H
