
#ifndef TWOD_H
#define TWOD_H

#include "curves.h"
#include "path.h"

/*----------2D layer----------*/
//decide the boundary of the shape firstly, make sure the head of the boundary array with the max value of x, draw the boundary anticlockwise, than use the function area to design the path to fill the shape
//if the head of the boundary array is the dot with the max value of y, use the function area0 to design the path to fill the shape
//首先确定图形边界线，默认起点为x最大值处，逆时针走线。确定边界后使用area函数确定填充路径。若起点为y最大值处，使用area1函数确定填充路径
class Triangle//make sure the head of the boundary array (a) with the max value of x, draw the boundary anticlockwise from a to b to c back to a   起点a点需要保证x最大，逆时针方向依次b，c，回到a
{
private:
    Dot a,b,c;
    Dot* point;
    int len;
public:
    Triangle(const Dot& A,const Dot& B,const Dot& C);//Triangle(a，b，c)
    Triangle();
    Triangle(const Triangle& org);
    Triangle(Triangle&& org);
    ~Triangle();
    Triangle& operator=(const Triangle& org);
    void Area();//path to fill the shape (virtical)     填充路径（竖直方向）
    int GetL();
    Dot*& GetP();
};

class Rectangle//make sure the head of the boundary array (a) with the max value of x, draw the boundary anticlockwise from a to b to c to d back to a  起点a点需要保证x最大，逆时针方向依次b，c，d回到a
{
private:
    Dot a,b,c,d;
    Dot* point;
    int len;
public:
    Rectangle(const Dot& A,const Dot& B,const Dot& C,const Dot& D);
    Rectangle();
    Rectangle(const Rectangle& org);
    Rectangle(Rectangle&& org);
    ~Rectangle();
    Rectangle& operator=(const Rectangle& org);
    void Area();//path to fill the shape (virtical)     填充路径（竖直方向）
    int GetL();
    Dot*& GetP();
};

class Circle
{
private:
    Dot o;
    Dot* point;
    int r,len;
public:
    Circle(const Dot& O,int R);//Circle(centre point，radius)
    Circle();
    Circle(const Circle& org);
    Circle(Circle&& org);
    ~Circle();
    Circle& operator=(const Circle& org);
    void Area();//path to fill the shape (virtical)    填充路径（竖直方向）
    int GetL();
    Dot*& GetP();
};

class Sector
{
private:
    Dot o,a,b;//o is the centre point of the circle    a,b are the start and the end of the arc
    Dot* point;
    int r,len;
    double c,d;//c and d are from 0 degree to 360 degree, d is allowed to be smaller than c   c和d都为0到360度，d可以小于c
public:
    Sector(const Dot& O,int R,double C,double D);//Sector(center，radius，start angle，end angle)
    Sector();
    Sector(const Sector& org);
    Sector(Sector&& org);
    ~Sector();
    Sector& operator=(const Sector& org);
    void Area();//path to fill the shape (virtical)    填充路径（竖直方向）
    int GetL();
    Dot*& GetP();
};

//customized shape, the boundary should start from the max value of x or y, draw the boundary anticlockwise
//自定义形状，起点为x最大值处或y最大值处,逆时针画线
class Shape
{
private:
    Dot* point;
    int len;
public:
    Shape(const Dot*p,int l);//Shape(point to boundary curve，length)
    Shape();
    Shape(const Shape& org);
    Shape(Shape&& org);
    ~Shape();
    Shape& operator=(const Shape& org);
    Shape& Change(const Shape& a,int x,int y,int z);//every dot in the shape plus x，y，z
    void Area();//path to fill the shape (virtical)   填充路径（竖直方向）
    void Area1();//path to fill the shape (horizonal)   填充路径（水平方向）
    int GetL();
    Dot*& GetP();
};

//dig shape b out from shape a
//从图形a中将图形b挖去
template<typename T1,typename T2>
class Hollow
{
private:
    T1 a;
    T2 b;
    Dot* point;
    int len;
public:
    Hollow(const T1& A,const T2& B);//Hollow(shape a，shape b)
    Hollow(const Hollow& org);
    Hollow(Hollow&& org);
    ~Hollow();
    Hollow& operator=(const Hollow& org);
    void Area();//path to fill the shape (virtical)，still using the path of shape a, but change the value of draw from 1 to 0 in the digged out part(shape b)     填充路径（竖直方向），依旧是a的填充路径，但是会改变挖去部分的喷涂料状态
    void Area1();//path to fill the shape (horizonal)     填充路径（水平方向）
    int GetL();
    Dot*& GetP();
};

template<typename T1,typename T2>
Hollow<T1,T2>::Hollow(const T1& A,const T2& B):a(A),b(B)//Hollow(shape a，shape b)
{
    len=a.GetL();
    point=new Dot [len];
    for(int i=0;i<len;i++)
    {
        point[i]=a.GetP()[i];
        point[i].ChangeN(i);
    }
}
template<typename T1,typename T2>
Hollow<T1,T2>::Hollow(const Hollow& org)
{
    a=org.a;
    b=org.b;
    len=org.len;
    point=new Dot [len];
    for(int i=0;i<len;i++)
        point[i]=org.point[i];
}template<typename T1,typename T2>
Hollow<T1,T2>::Hollow(Hollow&& org)
{
    a=org.a;
    b=org.b;
    len=org.len;
    point=org.point;
    org.point=nullptr;
}
template<typename T1,typename T2>
Hollow<T1,T2>::~Hollow()
{
    delete [] point;
}
template<typename T1,typename T2>
Hollow<T1,T2>& Hollow<T1,T2>::operator=(const Hollow& org)
{
    if(this!=&org)
    {
        a=org.a;
        b=org.b;
        len=org.len;
        delete [] point;
        point=new Dot [len];
        for(int i=0;i<len;i++)
            point[i]=org.point[i];
    }
    return *this;
}
template<typename T1,typename T2>
void Hollow<T1,T2>::Area()//path to fill the shape (virtical)，still using the path of shape a, but change the value of draw from 1 to 0 in the digged out part(shape b)     填充路径（竖直方向），依旧是a的填充路径，但是会改变挖去部分的喷涂料状态
{
    a.Area();
    len=a.GetL();
    int j=0;//start from the start dot of the boundary of b      b边界曲线起点
    int k=b.GetL()-1;//start from the end dot of the boundary of b     b边界曲线末端
    int l=b.GetP()[0].Getx();
    int l0=l;
    while(a.GetP()[0].Getx()<b.GetP()[j].Getx())
        j++;
    while(a.GetP()[0].Getx()<b.GetP()[k].Getx())
        k--;//when the x of the start dot of the path of a is smaller than the x of the start dot of the boundary of shape b, find the dot in the boundary b that the x of that dot equal to the x of the start dot of the path of a     d当图形a填充路径的起点x值小于图形b边界曲线起点x值时，首先找到b边界曲线x值=图形a填充路径的起点x值的位置
    l=b.GetP()[j].Getx();
    l0=l;
    int ytop;
    int ybottom;
    delete [] point;
    point=new Dot [len];
    l0=l;
    for(int i=0;i<len;i++)//when path of a is on or inside the boundary of b, change the value of draw from 1 to 0     当a的填充路径在b的边界曲线上或内部时，将路径上的点的喷涂料状态改为0
    {
        if(a.GetP()[i].Getx()==l&&b.GetP()[j].Getx()>=b.GetP()[j+1].Getx())
        {
            ytop=b.GetP()[j].Gety();
            for(;b.GetP()[j].Getx()==l;j++)
                if(ytop<b.GetP()[j].Gety())
                    ytop=b.GetP()[j].Gety();//the highest dot at the top corresponding to the given x in the boundary b     b边界曲线给定x值的顶部最高点
            ybottom=b.GetP()[k].Gety();
            if(k==b.GetL()-1)
                ybottom=b.GetP()[0].Gety();
            for(;b.GetP()[k].Getx()==l;k--)
                if(ybottom>b.GetP()[k].Gety())
                    ybottom=b.GetP()[k].Gety();//the lowest dot at the bottom corresponding to the given x in the boundary     边界曲线给定x值的顶部最低点
            l0=l;
            l--;
        }
        if(a.GetP()[i].Gety()<=ytop
                &&a.GetP()[i].Gety()>=ybottom
                &&a.GetP()[i].Getx()==l0
                &&a.GetP()[0].Getz()==b.GetP()[0].Getz())//when the path of a is on the line with the given x of boundary b, and between the top and bottom of y of boundary b, and with the same z,  change the value of draw from 1 to 0      a的填充路径上的点在b曲线给定x值，且在y的最大最小值之间的这条直线上时，且z相同时改涂料状态
        {
            a.GetP()[i].ChangeD();
        }
        point[i]=a.GetP()[i];
    }
}
template<typename T1,typename T2>
void Hollow<T1,T2>::Area1()//path to fill the shape (horizonal)     填充路径（水平方向）
{
    a.Area1();
    len=a.GetL();
    int j=0;
    int k=b.GetL()-1;
    int l=b.GetP()[0].Gety();
    int l0=l;
    while(a.GetP()[0].Gety()<b.GetP()[j].Gety())
        j++;
    while(a.GetP()[0].Gety()<b.GetP()[k].Gety())
        k--;
    l=b.GetP()[j].Gety();
    l0=l;
    int xtop;
    int xbottom;
    delete [] point;
    point=new Dot [len];
    for(int i=0;i<len;i++)
    {
        if(a.GetP()[i].Gety()==l&&b.GetP()[j].Gety()>=b.GetP()[j+1].Gety())
        {
            xtop=b.GetP()[j].Getx();
            for(;b.GetP()[j].Gety()==l;j++)
                if(xtop<b.GetP()[j].Getx())
                    xtop=b.GetP()[j].Getx();
            xbottom=b.GetP()[k].Getx();
            if(k==b.GetL()-1)
                xbottom=b.GetP()[0].Getx();
            for(;b.GetP()[k].Gety()==l;k--)
                if(xbottom>b.GetP()[k].Getx())
                    xbottom=b.GetP()[k].Getx();
            l0=l;
            l--;
        }
        if(a.GetP()[i].Getx()<=xtop
                &&a.GetP()[i].Getx()>=xbottom
                &&a.GetP()[i].Getx()==l0
                &&a.GetP()[0].Getz()==b.GetP()[0].Getz())
        {
            a.GetP()[i].ChangeD();
        }
        point[i]=a.GetP()[i];
    }
}
template<typename T1,typename T2>
int Hollow<T1,T2>::GetL()
{
    return len;
}
template<typename T1,typename T2>
Dot*& Hollow<T1,T2>::GetP()
{
    return point;
}

#endif // TWOD_H
