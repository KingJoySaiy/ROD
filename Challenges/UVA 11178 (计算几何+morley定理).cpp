/*
 * UVA 11178 (计算几何 + morley定理)
 * 题目大意：给定三角形三个定点，分别作三个内角的三分线，求对应相邻两线的三个交点坐标
 */
#include <bits/stdc++.h>

using namespace std;

struct Point;
typedef Point Vector;

const double eps = 1e-10;

int dcmp(double x) {     //判断x是否为0

    if(fabs(x) < eps) return 0;
    return x < 0 ? -1 : 1;
}
struct Point{

    double x, y;
    Point(double x = 0, double y = 0):x(x),y(y){}
    double len(){       //向量的长度
        return sqrt(x * x + y * y);
    }
    Vector operator +(const Vector &b) const {       //向量+向量
        return Vector(x + b.x, y + b.y);
    }
    Vector operator -(const Point &b) const {        //向量-向量 or 点-点
        return Vector(x - b.x, y - b.y);
    }
    double operator ^(const Vector &b) const {       //向量的叉积
        return x * b.y - y * b.x;
    }
    double operator *(const Vector &b) const {       //向量的点积
        return x * b.x + y * b.y;
    }
    double angle(Vector &b){           //两向量的夹角
        return acos((*this * b) / len() / b.len());
    }
    void trans_XY(double B) {           //绕原点左旋B（弧度）
        double tx = x, ty = y;
        x = tx * cos(B) - ty * sin(B);
        y = tx * sin(B) + ty * cos(B);
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
Point a, b, c;
Point d, e, f;

Point work(Point A, Point B, Point C){

    Vector v1 = C - B, v2 = B - C;

    v1.trans_XY((A - B).angle(v1) / 3);     //v1逆时针旋转
    v2.trans_XY(-(A - C).angle(v2) / 3);    //v2顺时针旋转
    Line l1(B, B + v1), l2(C, C + v2);

    return (l1 & l2).second;    //题意中两直线必然有交点，不必判断
}
int main(){

    int ct;
    cin>>ct;
    while(ct--){
        cin>>a.x>>a.y>>b.x>>b.y>>c.x>>c.y;
        d = work(a, b, c);
        e = work(b, c, a);
        f = work(c, a, b);
        printf("%.6f %.6f %.6f %.6f %.6f %.6f\n", d.x, d.y, e.x, e.y, f.x, f.y);
    }


//    system("pause");
    return 0;
}
/*
2
1 1 2 2 1 2
0 0 100 0 50 50
 */