#ifndef CURVES_H
#define CURVES_H

#include <iostream>
using namespace std;

/*----------dot & string----------*/
//Dot. Num is used to record the order of the dot in the array. The default value of draw =1, spray; draw=0, not spray
//点 xyz坐标值。num记录点在数组中的序号。draw默认=1, 喷涂料；draw=0,不喷涂料。
class Dot
{
private:
    int x,y,z,num,draw;
public:
    Dot(int X=0,int Y=0,int Z=0,int N=0,int D=1); //Dot(x,y,z,n,d)
    void ChangeN(int i);
    void ChangeD();
    int Getx();
    int Gety();
    int Getz();
    int Getn();
    int Getd();
    void YZswap();
    void XZswap();
    friend Dot operator-(Dot b,Dot a);
    friend ostream& operator<<(ostream& cout,Dot a);
};

//a line from Dot a to Dot b. bresenham algorithm.
//起点a，终点b，确定一条直线。使用bresenham算法
class Line
{
private:
    Dot a,b;
    Dot* point;
    int len;
public:
    Line(const Dot& A,const Dot& B);// Line(start，end）
    Line();
    Line(const Line& org);
    Line(Line&& org);
    ~Line();
    Line& operator=(const Line& org);
    int GetL();
    Dot*& GetP();
};

//draw a circle, centre point o, radius=r, start from(r,0), anticlockwise. cut out the arc from the circe accroding to angle a,b (0<=a<=b<=360), bresenham algorithm
//画圆形为o，半径为r的圆，起点(r,0), 逆时针。根据角度a，b (0<=a<=b<=360) 从数组中提取弧。中点画圆法（1/8）
class Arc
{
private:
    Dot o;
    Dot* point;
    int r,len;
    double a,b;
public:
    Arc(const Dot& O,int R,double A,double B);//Arc(centre,radius,start angle,end angle）
    Arc();
    Arc(const Arc& org);
    Arc(Arc&& org);
    ~Arc();
    Arc& operator=(const Arc& org);
    int GetL();
    Dot*& GetP();
};

//draw the arc clockwise, to deal with concave arc in a shape
//Arc的顺时针画法，用以处理凹弧的情况
class Arc1
{
private:
    Dot o;
    Dot* point;
    int r,len;
    double a,b;
public:
    Arc1(const Dot& O,int R,double A,double B);
    Arc1();
    Arc1(Arc1&& org);
    Arc1(const Arc1& org);
    ~Arc1();
    Arc1& operator=(const Arc1& org);
    int GetL();
    Dot*& GetP();
};
#endif // CURVES_H
