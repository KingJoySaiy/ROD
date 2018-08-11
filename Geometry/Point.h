#ifndef INC_233_POINT_H
#define INC_233_POINT_H

#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;

const double eps = 1e-8;
const double PI = acos(-1);
const double inf = 1e12;

int dcmp(double x) {     //判断x是否为0

    if (fabs(x) < eps) return 0;
    return x < 0 ? -1 : 1;
}

#define Vector Point   //向量和点的都用xy表示，但要区分

struct Point {           //定义点(向量)

    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {}
    Point(const Point &t) {
        x = t.x, y = t.y;
    }
    Vector operator + (const Vector &b) const {       //向量+向量
        return Vector(x + b.x, y + b.y);
    }
    Vector operator - (const Point &b) const {        //向量-向量 or 点-点
        return Vector(x - b.x, y - b.y);
    }
    double operator ^ (const Vector &b) const {       //向量的叉积
        return x * b.y - y * b.x;
    }
    double operator * (const Vector &b) const {       //向量的点积
        return x * b.x + y * b.y;
    }
    Vector operator * (const double t) const {        //向量乘浮点数
        return Vector(t * x, t * y);
    }
    Vector operator / (const double &t) const {       //向量除以浮点数
        return Point(x / t, y / t);
    }
    bool operator == (const Point &b) const {         //判断两点坐标相等
        return !dcmp(x - b.x) and !dcmp(y - b.y);
    }
    bool operator < (const Point &b) const {          //按x升序，x相等则按y升序
        return dcmp(x - b.x) ? (x < b.x) : (dcmp(y - b.y) < 0);
    }
    double len() {       //返回向量的长度
        return hypot(x, y); //cmath库函数，由2直角边长求斜边长
    }
    double len2() {      //返回向量长度的平方
        return x * x + y * y;
    }
    double distance(Point &t) {  //返回2点之间距离
        return hypot(x - t.x, y - t.y);
    }
    double angle(Vector &b) {           //两向量的夹角
        return acos((*this * b) / len() / b.len());
    }
    double rad(Point &a, Point &b) {    //计算向量pa与向量pb的夹角
        Point &p = *this;
        return fabs(atan2(fabs((a - p) ^ (b - p)), (a - p) * (b - p)));
    }
    Point changeLen(double r) {       //转换为长度为r的向量
        double l = len();
        if (!dcmp(l)) return *this;
        r /= l;
        return Vector(x * r, y * r);
    }
    Point rotate(double ang) {          //绕圆点逆时针旋转ang弧度
        return Point(x * cos(ang) - y * sin(ang), x * sin(ang) + y * cos(ang));
    }
    Point rotate(Point p, double ang) { //绕点p逆时针旋转ang弧度
        Point v = (*this) - p;
        double c = cos(ang), s = sin(ang);
        return Point(p.x + v.x * c - v.y * s, p.y + v.x * s + v.y * c);
    }
    Vector normal() {                    //返回向量的单位法线（左旋90度,长度归一）
        double l = len();
        return Vector(-y / l, x / l);
    }
};

#endif //INC_233_POINT_H
