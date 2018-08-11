#ifndef INC_233_LINE_H
#define INC_233_LINE_H

#include "Point.h"

struct Line {

    Point s, e;
    Line() {}
    Line(Point s, Point e) : s(s), e(e) {}
    Line(Point p, double ang) {         //根据点和倾斜角确定一条直线
        s = p;
        if (!dcmp(ang - PI / 2)) e = s + Vector(0, 1);
        else e = s + Point(1, tan(ang));
    }
    Line(double a, double b, double c) {    //根据直线的一般方程ax + by + c = 0求直线
        if(!dcmp(a)) {
            s = Point(0, -c / b);
            e = Point(1, -c / b);
        } else if (!dcmp(b)) {
            s = Point(-c / a, 0);
            e = Point(-c / a, 1);
        } else {
            s = Point(0, -c / b);
            e = Point(1, (-c - a) / b);
        }
    }
    bool operator == (Line &t) {        //判断2线段是否相等
        return s == t.s and e == t.e;
    }
    double len() {                      //返回线段长度
        return s.distance(e);
    }
    double angle() {                    //返回倾斜角
        double k = atan2(e.y - s.y, e.x - s.x);
        if (dcmp(k) < 0) k += PI;
        if (dcmp(k - PI) == 0) k -= PI;
        return k;
    }
    bool onLine(Point p) {              //判断点是否在直线上
        return !dcmp((p - s) ^ (p - e));
    }
    bool onSegment(Point p) {           //判断点是否在线段上
        return !dcmp((p - s) ^ (p - e)) and dcmp((p - s) * (p - e)) <= 0;
    }
    bool parallel(Line t) {             //判断2线段是否平行
        return !dcmp((e - s) ^ (t.e - t.s));
    }
    double disPointLine(Point p) {      //点到直线的最短距离
        return fabs((p - s) ^ (e - s)) / len();
    }
    double disPointSeg(Point p) {       //点到线段的距离
        if (dcmp((p - s) * (e - s)) < 0 or dcmp((p - e) * (s - e)) < 0)
            return min(p.distance(s), p.distance(e));
        return disPointLine(p);
    }
    double disSegSeg(Line v) {          //线段到线段的距离（前提2线段不相交，相交则距离为0）
        return min(min(disPointSeg(v.s), disPointSeg(v.e)), min(v.disPointSeg(s), v.disPointSeg(e)));
    }
    Point lineProg(Point p) {           //点在直线上的投影点
        return s + (((e-s)*((e-s)*(p-s)))/((e-s).len2()) );
    }
    Point sysmmetryPoint(Point p) {     //点关于直线的对称点
        Point t = lineProg(p);
        return Point(2 * t.x - p.x, 2 * t.y - p.y);
    }
    int relationLine(Line v) {         //判断直线关系（2相交，1重合，0平行）
        if (this->parallel(v)) return v.onLine(s) == 3;
        return 2;
    }
    Point lineCross(Line v) {      //求2直线交点，保证不平行或重合
        double a1 = (v.e - v.s) ^ (s - v.s);
        double a2 = (v.e - v.s) ^ (e - v.s);
        return Point((s.x * a2 - e.x * a1) / (a2 - a1),(s.y * a2 - e.y * a1) / (a2 - a1));
    }
    int interSeg(Line v) {        //判断线段关系（2规范相交，1不规范相交，0不相交）
        int d1 = dcmp((e - s) ^ (v.s - s));
        int d2 = dcmp((e - s) ^ (v.e - s));
        int d3 = dcmp((v.e - v.s) ^ (s - v.s));
        int d4 = dcmp((v.e - v.s) ^ (e - v.s));
        if ((d1 ^ d2) == -2 and (d3 ^ d4) == -2) return 2;
        return (!d1 and dcmp((v.s - s) * (v.s - e)) <= 0) or
               (!d2 and dcmp((v.e - s) * (v.e - e)) <= 0) or
               (!d3 and dcmp((s - v.s) * (s - v.e)) <= 0) or
               (!d4 and dcmp((e - v.s) * (e - v.e)) <= 0);
    }
    pair<int, Point> lineCross2(Line b) {   //两直线相交求交点（first -> 0重合，1平行，2相交）

        Point res = s;
        if (dcmp((s - e) ^ (b.s - b.e)) == 0) {
            if (dcmp((s - b.e) ^ (b.s - b.e)) == 0) return make_pair(0, res);    //重合
            else return make_pair(1, res);              //平行
        }
        double t = ((s - b.s) ^ (b.s - b.e)) / ((s - e) ^ (b.s - b.e)); //用到定比分点
        res.x += (e.x - s.x) * t;
        res.y += (e.y - s.y) * t;
        return make_pair(2, res);                        //只有第一个值为2时，交点才有意义
    }
};

bool interSeg(Line l1, Line l2) {           //判断线段相交（允许在端点处相交）
    return
            max(l1.s.x, l1.e.x) >= min(l2.s.x, l2.e.x) and
            max(l2.s.x, l2.e.x) >= min(l1.s.x, l1.e.x) and
            max(l1.s.y, l1.e.y) >= min(l2.s.y, l2.e.y) and
            max(l2.s.y, l2.e.y) >= min(l1.s.y, l1.e.y) and
            dcmp((l2.s - l1.e) ^ (l1.s - l1.e)) * dcmp((l2.e - l1.e) ^ (l1.s - l1.e)) <= 0 and
            dcmp((l1.s - l2.e) ^ (l2.s - l2.e)) * dcmp((l1.e - l2.e) ^ (l2.s - l2.e)) <= 0;
}
bool interSeg2(Line l1, Line l2) {          //判断线段相交（任一线段的两端点都在另一条线段的两侧）

    double c1 = (l1.e - l1.s) ^(l2.s - l1.s), c2 = (l1.e - l1.s) ^(l2.e - l1.s);
    double c3 = (l2.e - l2.s) ^(l1.s - l2.s), c4 = (l2.e - l2.s) ^(l1.e - l2.s);
    return dcmp(c1) * dcmp(c2) < 0 and dcmp(c3) * dcmp(c4) < 0;
}

int line_inter_seg(Line l1, Line l2) {      //判断直线l1与线段l2相交（2规范相交，1不规范相交，0不相交）

    int d1 = dcmp((l1.e - l1.s) ^ (l2.s - l1.s));
    int d2 = dcmp((l1.e - l1.s) ^ (l2.e - l1.s));
    if ((d1 ^ d2) == -2) return 2;
    return !d1 or !d2;
}

Point point_line(Point P, Line L) {     //点到直线最近的点

    Point v = L.e - L.s;
    return L.s + v * (((P - L.s) * v) / (v * v));
}

Point point_lineSeg(Point P, Line L) {      //点到线段的最近点

    Point result;
    double t = ((P - L.s) * (L.e - L.s)) / ((L.e - L.s) * (L.e - L.s));
    if (t >= 0 and t <= 1) {
        result.x = L.s.x + (L.e.x - L.s.x) * t;
        result.y = L.s.y + (L.e.y - L.s.y) * t;
    } else {
        if (P.distance(L.s) < P.distance(L.e)) result = L.s;
        else result = L.e;
    }
    return result;
}

#endif //INC_233_LINE_H
