#ifndef INC_233_CIRCLE_H
#define INC_233_CIRCLE_H

#include "Point.h"
#include "Line.h"

struct Circle {

    Point o;
    double r;
    Circle() {}
    Circle(Point o, double r) : o(o), r(r) {}               //给定圆心和半径
    Circle(double x, double y, double r) : o(x, y), r(r) {} //给定圆心坐标和半径
    Circle(Point a, Point b, Point c) {                     //三角形外接圆
        Line u = Line((a + b) / 2,((a + b) / 2) + ((b - a).rotate(PI / 2)));
        Line v = Line((b + c) / 2,((b + c) / 2) + ((c - b).rotate(PI / 2)));
        o = u.lineCross(v);
        r = o.distance(a);
    }
    Circle(Point a, Point b, Point c, bool flag) {          //三角形内切圆（flag参数只用以区分）
        Line u,v;
        double m = atan2(b.y - a.y, b.x - a.x), n = atan2(c.y - a.y,c.x - a.x);
        u.s = a;
        u.e = u.s + Point(cos((n + m) / 2),sin((n + m) / 2));
        v.s = b;
        m = atan2(a.y - b.y,a.x - b.x), n = atan2(c.y - b.y,c.x - b.x);
        v.e = v.s + Point(cos((n + m) / 2),sin((n + m) / 2));
        o = u.lineCross(v);
        r = Line(a,b).disPointSeg(o);
    }
    bool operator == (const Circle &t) const {          //2圆相等
        return o == t.o and !dcmp(r - t.r);
    }
    bool operator < (const Circle &t) const {           //按圆点坐标排序，再按半径排序
        return o < t.o or (o == t.o and dcmp(r - t.r) < 0);
    }
    double area() {         //圆的面积
        return PI * r * r;
    }
    double circum() {       //圆的周长
        return 2 * PI * r;
    }
    int relationPoint(Point p) {   //点和圆的关系（0圆外，1圆上，2圆内）
        double dis = p.distance(o);
        if (dcmp(dis - r) < 0) return 2;
        if (!dcmp(dis - r)) return 1;
        return 0;
    }
    int relationSeg(Line t) {            //线段距离圆心最近点和圆的关系（0圆外，1圆上，2圆内）
        double dis = t.disPointSeg(o);
        if (dcmp(dis - r) < 0) return 2;
        if (!dcmp(dis - r)) return 1;
        return 0;
    }
    int relationLine(Line t) {          //直线和圆的关系（0相交，1相切，2相离）
        double dis = t.disPointLine(o);
        if (dcmp(dis - r) < 0) return 2;
        if (!dcmp(dis - r)) return 1;
        return 0;
    }
    int relationCircle(Circle t) {      //两圆关系（1内含，2内切，3相交，4外切，5相离）
        double d = o.distance(t.o);
        if(dcmp(d - r - t.r) > 0) return 5;
        if(!dcmp(d - r - t.r)) return 4;
        double l = fabs(r - t.r);
        if(dcmp(d - r - t.r) < 0 and dcmp(d - l) > 0) return 3;
        if(!dcmp(d - l)) return 2;
        if(dcmp(d - l) < 0) return 1;
    }
    int crossCircle(Circle v, Point &p1, Point &p2) { //求两圆交点，返回交点个数
        int rel = relationCircle(v);
        if(rel == 1 or rel == 5)return 0;
        double d = o.distance(v.o);
        double l = (d*d+r*r - v.r*v.r)/(2*d);
        double h = sqrt(r*r - l*l);
        Point tmp = o + (v.o - o).changeLen(l);
        p1 = tmp + ((v.o - o).rotate(PI / 2).changeLen(h));
        p2 = tmp + ((v.o - o).rotate(-PI / 2).changeLen(h));
        if(rel == 2 || rel == 4) return 1;
        return 2;
    }
    int crossLine(Line v, Point &p1, Point &p2) {  //求圆与直线交点，返回交点个数
        if(!(this->relationLine(v))) return 0;
        Point a = v.lineProg(o);
        double d = v.disPointLine(o);
        d = sqrt(r*r - d*d);
        if(!dcmp(d)){
            p1 = a;
            p2 = a;
            return 1;
        }
        p1 = a + (v.e - v.s).changeLen(d);
        p2 = a - (v.e - v.s).changeLen(d);
        return 2;
    }
    int tangLines(Point p, Line &u, Line &v) {      //过一点做圆外切线（返回切线个数）
        int x = relationPoint(p);
        if(x == 2)return 0;
        if(x == 1){
            u = Line(p, p + (p - o).rotate(PI / 2));
            v = u;
            return 1;
        }
        double d = o.distance(p);
        double l = r * r / d;
        double h = sqrt(r * r - l * l);
        u = Line(p, o + ((p - o).changeLen(l) + (p - o).rotate(PI / 2).changeLen(h)));
        v = Line(p, o + ((p - o).changeLen(l) + (p - o).rotate(-PI / 2).changeLen(h)));
        return 2;
    }
    int getCircles(Point a, Point b, double r1, Circle &c1, Circle &c2) {//得到过ab两点半径为r的2圆，返回2圆交点个数
        Circle x(a, r1), y(b, r1);
        int flag = x.crossCircle(y, c1.o, c2.o);
        if (!flag) return 0;
        c1.r = c2.r = r1;
        return flag;
    }
    int getCircle(Line u, Point q, double r1, Circle &c1, Circle &c2) {//得到与直线u相切，过点q且半径为r的圆
        double dis = u.disPointLine(q);
        if(dcmp(dis - r1 * 2) > 0)return 0;
        if(!dcmp(dis)){
            c1.o = q + ((u.e - u.s).rotate(PI / 2).changeLen(r1));
            c2.o = q + ((u.e - u.s).rotate(-PI / 2).changeLen(r1));
            c1.r = c2.r = r1;
            return 2;
        }
        Line u1 = Line((u.s + (u.e - u.s).rotate(PI / 2).changeLen(r1)),(u.e + (u.e - u.s).rotate(PI / 2).changeLen(r1)));
        Line u2 = Line((u.s + (u.e - u.s).rotate(-PI / 2).changeLen(r1)),(u.e + (u.e - u.s).rotate(-PI / 2).changeLen(r1)));
        Circle cc = Circle(q, r1);
        Point p1, p2;
        if(!cc.crossLine(u1, p1, p2)) cc.crossLine(u2, p1, p2);
        c1 = Circle(p1, r1);
        if(p1 == p2) {
            c2 = c1;
            return 1;
        }
        c2 = Circle(p2,r1);
        return 2;
    }
    int getCircle1(Line u, Line v, double r1, Circle &c1, Circle &c2, Circle &c3, Circle &c4) {//得到与2直线uv相切且半径为r1的圆
        if(u.parallel(v)) return 0;  //两直线平行
        Line u1 = Line(u.s + (u.e - u.s).rotate(PI / 2).changeLen(r1),u.e + (u.e - u.s).rotate(PI / 2).changeLen(r1));
        Line u2 = Line(u.s + (u.e - u.s).rotate(-PI / 2).changeLen(r1),u.e + (u.e - u.s).rotate(-PI / 2).changeLen(r1));
        Line v1 = Line(v.s + (v.e - v.s).rotate(PI / 2).changeLen(r1),v.e + (v.e - v.s).rotate(PI / 2).changeLen(r1));
        Line v2 = Line(v.s + (v.e - v.s).rotate(-PI / 2).changeLen(r1),v.e + (v.e - v.s).rotate(-PI / 2).changeLen(r1));
        c1.r = c2.r = c3.r = c4.r = r1;
        c1.o = u1.lineCross(v1);
        c2.o = u1.lineCross(v2);
        c3.o = u2.lineCross(v1);
        c4.o = u2.lineCross(v2);
        return 4;
    }
    int getCircle2(Circle cx, Circle cy, double r1, Circle &c1, Circle &c2) {   //得到与不想交2圆cxcy外切且半径为r1的圆
        Circle x(cx.o, r1 + cx.r), y(cy.o, r1 + cy.r);
        int flag = x.crossCircle(y, c1.o, c2.o);
        if (!flag) return 0;
        c1.r = c2.r = r1;
        return flag;
    }
    double areaCircle(Circle v) {   //求2圆的面积交
        int rel = relationCircle(v);
        if(rel >= 4) return 0;
        if(rel <= 2) return min(area(), v.area());
        double d = o.distance(v.o);
        double hf = (r + v.r + d) / 2;
        double ss = 2 * sqrt(hf * (hf - r) * (hf - v.r) * (hf - d));
        double a1 = acos((r * r + d * d - v.r * v.r) / (2 * r * d));
        a1 = a1 * r * r;
        double a2 = acos((v.r * v.r + d * d - r * r) / (2.0 * v.r * d));
        a2 = a2 * v.r * v.r;
        return a1+a2 - ss;
    }
    double areaTriang(Point a, Point b) {   //求圆和oab围成三角形的面积交
        if(!dcmp((o - a) ^ (o - b))) return 0;
        Point q[5];
        int len = 0;
        q[len++] = a;
        Line l(a, b);
        if(crossLine(l, q[1], q[2]) == 2) {
            if(dcmp((a - q[1]) * (b - q[1])) < 0) q[len++] = q[1];
            if(dcmp((a - q[2]) * (b - q[2])) < 0) q[len++] = q[2];
        }
        q[len++] = b;
        if(len == 4 and dcmp((q[0] - q[1]) * (q[2] - q[1])) > 0) swap(q[1], q[2]);
        double res = 0;
        for(int i = 0; i < len - 1; i++) {
            if(!relationPoint(q[i]) or !relationPoint(q[i + 1])) {
                double arg = o.rad(q[i], q[i + 1]);
                res += r * r * arg / 2;
            } else res += fabs((q[i] - o) ^ (q[i + 1] - o)) / 2;
        }
        return res;
    }
};

#endif //INC_233_CIRCLE_H
