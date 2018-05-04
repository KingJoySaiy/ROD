#ifndef BASIC_FUNCTION_HEAD_H
#define BASIC_FUNCTION_HEAD_H

#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;

struct Point;
typedef Point Vector;   //向量和点的都用xy表示，但要区分

const double eps = 1e-10;
const double PI = acos(-1.0);
const double inf = 1e12;

int dcmp(double x) {     //判断x是否为0

    if(fabs(x) < eps) return 0;
    return x < 0 ? -1 : 1;
}
struct Point{           //定义点(向量)

    double x, y;
    Point(double x = 0, double y = 0):x(x),y(y){}
    double len(){       //返回向量的长度
        return sqrt(x * x + y * y);
    }
    Vector operator +(const Vector &b) const {       //向量+向量
        return Vector(x + b.x, y + b.y);
    }
    Vector operator -(const Point &b) const {        //向量-向量 or 点-点
        return Vector(x - b.x, y - b.y);
    }
    double operator ^(const Vector &b) const {       //向量的叉积
        return x*b.y - y*b.x;
    }
    double operator *(const Vector &b) const {       //向量的点积
        return x*b.x + y*b.y;
    }
    Vector operator *(const double t) const {        //向量乘浮点数
        return Vector(t * x, t * y);
    }
    bool operator ==(const Point &b) const {
        return !dcmp(x - b.x) and !dcmp(y - b.y);
    }
    void trans_XY(double B) {    //绕原点左旋B（弧度）
        double tx = x,ty = y;
        x = tx*cos(B) - ty*sin(B);
        y = tx*sin(B) + ty*cos(B);
    }
    Vector normal(){    //返回向量的单位法线（左旋90度,长度归一）
        double l = len();
        return Vector(-y / l, x / l);
    }
};
struct Line{

    Point s, e;
    Line(){}
    Line(Point s, Point e):s(s),e(e){}
    pair<int, Point> operator &(const Line &b) const {   //两直线相交求交点

        //第一个值为0表示直线重合，为0表示重合，为1表示平行，为2是相交
        Point res = s;
        if (dcmp((s - e) ^ (b.s - b.e)) == 0){
            if (dcmp((s - b.e) ^ (b.s - b.e)) == 0) return make_pair(0, res);    //重合
            else return make_pair(1, res);              //平行
        }
        double t = ((s - b.s) ^ (b.s - b.e)) / ((s - e) ^ (b.s - b.e)); //用到定比分点
        res.x += (e.x - s.x) * t;
        res.y += (e.y - s.y) * t;
        return make_pair(2, res);                        //只有第一个值为2时，交点才有意义
    }
};

#endif //BASIC_FUNCTION_HEAD_H