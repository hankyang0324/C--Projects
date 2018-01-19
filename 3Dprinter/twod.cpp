#include "twod.h"

/*----------2D layer----------*/
//decide the boundary of the shape firstly, make sure the head of the boundary array with the max value of x, draw the boundary anticlockwise, than use the function area to design the path to fill the shape
//if the head of the boundary array is the dot with the max value of y, use the function area0 to design the path to fill the shape
//首先确定图形边界线，默认起点为x最大值处，逆时针走线。确定边界后使用area函数确定填充路径。若起点为y最大值处，使用area1函数确定填充路径

Triangle::Triangle(const Dot& A,const Dot& B,const Dot& C):a(A),b(B),c(C)//Triangle(a，b，c)
{
    Line ab(a,b);
    Line bc(b,c);
    Line ca(c,a);
    len=ab.GetL()+bc.GetL()+ca.GetL()-3;
    if(len==0)//if a,b,c are at the same position. point to a, len=1   abc三点重合，长度设为1，指向a
    {
        len=1;
    }
    point=new Dot [len];
    point[0]=a;
    point[0].ChangeN(0);
    for(int i=0;i<ab.GetL()-1;i++)
    {
        point[i]=ab.GetP()[i];
        point[i].ChangeN(i);
    }
    for(int i=0;i<bc.GetL()-1;i++)
    {
        point[ab.GetL()-1+i]=bc.GetP()[i];
        point[ab.GetL()-1+i].ChangeN(ab.GetL()-1+i);
    }
    for(int i=0;i<ca.GetL()-1;i++)
    {
        point[ab.GetL()+bc.GetL()-2+i]=ca.GetP()[i];
        point[ab.GetL()+bc.GetL()-2+i].ChangeN(ab.GetL()+bc.GetL()-2+i);
    }
}
Triangle::Triangle()
{
    a=b=c=Dot();
    len=0;
    point=nullptr;
}
Triangle::Triangle(const Triangle& org)
{
    a=org.a;
    b=org.b;
    c=org.c;
    len=org.len;
    point=new Dot [len];
    for(int i=0;i<len;i++)
        point[i]=org.point[i];
}
Triangle::Triangle(Triangle&& org)
{
    a=org.a;
    b=org.b;
    c=org.c;
    len=org.len;
    point=org.point;
    org.point=nullptr;
}
Triangle::~Triangle()
{
    delete [] point;
}
Triangle& Triangle::operator=(const Triangle& org)
{
    if(this!=&org)
    {
        a=org.a;
        b=org.b;
        c=org.c;
        len=org.len;
        delete [] point;
        point=new Dot [len];
        for(int i=0;i<len;i++)
            point[i]=org.point[i];
    }
    return *this;
}
void Triangle::Area()//path to fill the shape (virtical)     填充路径（竖直方向）
{
    int xmax=a.Getx();
    int xmin=b.Getx()<=c.Getx()?b.Getx():c.Getx();
    int z=a.Getz();
    area(xmax,xmin,z,point,len);
}
int Triangle::GetL()
{
    return len;
}
Dot*& Triangle::GetP()
{
    return point;
}

//
Rectangle::Rectangle(const Dot& A,const Dot& B,const Dot& C,const Dot& D):a(A),b(B),c(C),d(D)
{
    Line ab(a,b);
    Line bc(b,c);
    Line cd(c,d);
    Line da(d,a);
    len=ab.GetL()+bc.GetL()+cd.GetL()+da.GetL()-4;
    if(len==0)//if a,b,c are at the same position. point to a, len=1     abcd四点重合，长度设为1，指向a
    {
        len=1;
    }
    point=new Dot [len];
    point[0]=a;
    point[0].ChangeN(0);
    for(int i=0;i<ab.GetL()-1;i++)
    {
        point[i]=ab.GetP()[i];
        point[i].ChangeN(i);
    }
    for(int i=0;i<bc.GetL()-1;i++)
    {
        point[ab.GetL()-1+i]=bc.GetP()[i];
        point[ab.GetL()-1+i].ChangeN(ab.GetL()-1+i);
    }
    for(int i=0;i<cd.GetL()-1;i++)
    {
        point[ab.GetL()+bc.GetL()-2+i]=cd.GetP()[i];
        point[ab.GetL()+bc.GetL()-2+i].ChangeN(ab.GetL()+bc.GetL()-2+i);
    }
    for(int i=0;i<da.GetL()-1;i++)
    {
        point[ab.GetL()+bc.GetL()+cd.GetL()-3+i]=da.GetP()[i];
        point[ab.GetL()+bc.GetL()+cd.GetL()-3+i].ChangeN(ab.GetL()+bc.GetL()+cd.GetL()-3+i);
    }
}
Rectangle::Rectangle()
{
    a=b=c=d=Dot();
    len=0;
    point=nullptr;
}
Rectangle::Rectangle(const Rectangle& org)
{
    a=org.a;
    b=org.b;
    c=org.c;
    d=org.d;
    len=org.len;
    point=new Dot [len];
    for(int i=0;i<len;i++)
        point[i]=org.point[i];
}
Rectangle::Rectangle(Rectangle&& org)
{
    a=org.a;
    b=org.b;
    c=org.c;
    d=org.d;
    len=org.len;
    point=org.point;
    org.point=nullptr;
}
Rectangle::~Rectangle()
{
    delete [] point;
}
Rectangle& Rectangle::operator=(const Rectangle& org)
{
    if(this!=&org)
    {
        a=org.a;
        b=org.b;
        c=org.c;
        d=org.d;
        len=org.len;
        delete [] point;
        point=new Dot [len];
        for(int i=0;i<len;i++)
            point[i]=org.point[i];
    }
    return *this;
}
void Rectangle::Area()//path to fill the shape (virtical)     填充路径（竖直方向）
{
    int xmax=a.Getx();
    int xmin=b.Getx()<=c.Getx()?b.Getx():c.Getx();
    if(xmin>d.Getx())
        xmin=d.Getx();
    int z=a.Getz();
    area(xmax,xmin,z,point,len);
}
int Rectangle::GetL()
{
    return len;
}
Dot*& Rectangle::GetP()
{
    return point;
}

//
Circle::Circle(const Dot& O,int R):o(O),r(R)//Circle(centre point，radius)
{
    Arc a(o,r,0,360);
    len=a.GetL();
    point=new Dot [len];
    for(int i=0;i<len;i++)
    {
        point[i]=a.GetP()[i];
        point[i].ChangeN(i);
    }
}
Circle::Circle()
{
    o=Dot();
    r=0;
    len=0;
    point=nullptr;
}
Circle::Circle(const Circle& org)
{
    o=org.o;
    r=org.r;
    len=org.len;
    point=new Dot [len];
    for(int i=0;i<len;i++)
        point[i]=org.point[i];
}
Circle::Circle(Circle&& org)
{
    o=org.o;
    r=org.r;
    len=org.len;
    point=org.point;
    org.point=nullptr;
}
Circle::~Circle()
{
    delete [] point;
}
Circle& Circle::operator=(const Circle& org)
{
    if(this!=&org)
    {
        o=org.o;
        r=org.r;
        len=org.len;
        delete [] point;
        point=new Dot [len];
        for(int i=0;i<len;i++)
            point[i]=org.point[i];
    }
    return *this;
}
void Circle::Area()//path to fill the shape (virtical)    填充路径（竖直方向）
{
    int xmax=o.Getx()+r;
    int xmin=o.Getx()-r;
    int z=o.Getz();
    area(xmax,xmin,z,point,len);
}
int Circle::GetL()
{
    return len;
}
Dot*& Circle::GetP()
{
    return point;
}

//
Sector::Sector(const Dot& O,int R,double C,double D):o(O),r(R),c(C),d(D)//Sector(center，radius，start angle，end angle)
{
    if(c<=d)//the situation that the start angle is smaller than the end angle     起始角小于等于终止角的情况
    {
        Arc arc(o,r,c,d);
        a=arc.GetP()[0];
        b=arc.GetP()[arc.GetL()-1];
        if(a.Getx()==b.Getx()&&a.Gety()==b.Gety()&&a.Getz()==b.Getz())//the situation that the start dot and the end dot of the arc are at the same position     两个端点重合的情况
        {
            len=arc.GetL();
            point=new Dot [len];
            for(int i=0;i<arc.GetL();i++)
            {
                point[i]=arc.GetP()[i];
                point[i].ChangeN(i);
            }
        }
        else
        {
            Line ba(b,a);//when c<=d, draw the line ba from the end of the arc to the start of the arc        c<=d的情况下由弧的末端向起点做线
            len=arc.GetL()+ba.GetL()-2;
            point=new Dot [len];
            if(a.Getx()>=b.Getx())//when a.x>=b.x, start from dot a, draw the arc then draw the line        a.x>=b.x时，起点为a，先做弧线，后做直线
            {
                for(int i=0;i<arc.GetL();i++)
                {
                    point[i]=arc.GetP()[i];
                    point[i].ChangeN(i);
                }
                for(int i=0;i<ba.GetL()-2;i++)
                {
                    point[arc.GetL()+i]=ba.GetP()[1+i];
                    point[arc.GetL()+i].ChangeN(arc.GetL()+i);
                }
            }
            else//when a.x<=b.x, start from dot b, draw the line then draw the arc       a.x<b.x时，起点为b，先做直线，后做弧线
            {
                for(int i=0;i<ba.GetL();i++)
                {
                    point[i]=ba.GetP()[i];
                    point[i].ChangeN(i);
                }
                for(int i=0;i<arc.GetL()-2;i++)
                {
                    point[ba.GetL()+i]=arc.GetP()[1+i];
                    point[ba.GetL()+i].ChangeN(ba.GetL()+i);
                }
            }
        }
    }
    else//when the start angle is larger than the end angle, draw the arc from 0 degree to the end angle, then draw the line ab, then draw the arc from start angle to 360  degree, the boundary is composed by this three parts of curves  起始角大于终止角的情况，需要画弧从0度到终止角，直线ab，再画弧从起始角到360度，三段线围成边界
    {
        Arc arc1(o,r,0,d);
        Arc arc2(o,r,c,360);
        a=arc1.GetP()[arc1.GetL()-1];
        b=arc2.GetP()[0];
        if(a.Getx()==b.Getx()&&a.Gety()==b.Gety()&&a.Getz()==b.Getz())//the situation that the start and end dots are at the same position    两个端点重合的情况
        {
            len=arc1.GetL()+arc2.GetL();
            point=new Dot [len];
            for(int i=0;i<arc1.GetL();i++)
            {
                point[i]=arc1.GetP()[i];
                point[i].ChangeN(i);
            }
            for(int i=0;i<arc2.GetL();i++)
            {
                point[arc1.GetL()+i]=arc2.GetP()[i];
                point[arc1.GetL()+i].ChangeN(arc1.GetL()+i);
            }
        }
        else
        {
            Line ab(a,b);
            len=arc1.GetL()+arc2.GetL()+ab.GetL()-2;
            point=new Dot [len];
            for(int i=0;i<arc1.GetL();i++)
            {
                point[i]=arc1.GetP()[i];
                point[i].ChangeN(i);
            }
            for(int i=0;i<ab.GetL()-2;i++)
            {
                point[arc1.GetL()+i]=ab.GetP()[1+i];
                point[arc1.GetL()+i].ChangeN(arc1.GetL()+i);
            }
            for(int i=0;i<arc2.GetL();i++)
            {
                point[arc1.GetL()+ab.GetL()-2+i]=arc2.GetP()[i];
                point[arc1.GetL()+ab.GetL()-2+i].ChangeN(arc1.GetL()+ab.GetL()-2+i);
            }
        }
    }
}
Sector::Sector()
{
    o=a=b=Dot();
    r=0;
    len=0;
    c=d=0;
    point=nullptr;
}
Sector::Sector(const Sector& org)
{
    o=org.o;
    a=org.a;
    b=org.b;
    c=org.c;
    d=org.d;
    r=org.r;
    len=org.len;
    point=new Dot [len];
    for(int i=0;i<len;i++)
        point[i]=org.point[i];
}
Sector::Sector(Sector&& org)
{
    o=org.o;
    a=org.a;
    b=org.b;
    c=org.c;
    d=org.d;
    r=org.r;
    len=org.len;
    point=org.point;
    org.point=nullptr;
}
Sector::~Sector()
{
    delete [] point;
}
Sector& Sector::operator=(const Sector& org)
{
    if(this!=&org)
    {
        o=org.o;
        a=org.a;
        b=org.b;
        c=org.c;
        d=org.d;
        r=org.r;
        len=org.len;
        delete [] point;
        point=new Dot [len];
        for(int i=0;i<len;i++)
            point[i]=org.point[i];
    }
    return *this;
}
void Sector::Area()//path to fill the shape (virtical)    填充路径（竖直方向）
{
    int xmax=point[0].Getx();//the max value of x  is at the head of the boundary array   最大值必然是边界线起点
    int xmin;
    if(c<=d)
    {
        if(c<=180&&d>=180) //when the 180 degree is included, the min value of x      包含180度时,x的最小值
            xmin=o.Getx()-r;
        else
            xmin=a.Getx()<b.Getx()?a.Getx():b.Getx();
    }
    else
    {
        if(c<=180||d>=180)//when the 180 degree is included, the min value of x     包含180度水平方向的x的最小值
            xmin=o.Getx()-r;
        else
            xmin=a.Getx()<b.Getx()?a.Getx():b.Getx();
    }
    int z=o.Getz();
    area(xmax,xmin,z,point,len);
}
int Sector::GetL()
{
    return len;
}
Dot*& Sector::GetP()
{
    return point;
}

//customized shape, the boundary should start from the max value of x or y, draw the boundary anticlockwise
//自定义形状，起点为x最大值处或y最大值处,逆时针画线
Shape::Shape(const Dot*p,int l):len(l)//Shape(point to boundary curve，length)
{
    point=new Dot [len];
    for(int i=0;i<len;i++)
    {
        point[i]=p[i];
        point[i].ChangeN(i);
    }
}
Shape::Shape()
{
    point=nullptr;
    len=0;
}
Shape::Shape(const Shape& org)
{
    len=org.len;
    point=new Dot [len];
    for(int i=0;i<len;i++)
        point[i]=org.point[i];
}
Shape::Shape(Shape&& org)
{
    len=org.len;
    point=org.point;
    org.point=nullptr;
}
Shape::~Shape()
{
    delete [] point;
}
Shape& Shape::operator=(const Shape& org)
{
    if(this!=&org)
    {
        len=org.len;
        delete [] point;
        point=new Dot [len];
        for(int i=0;i<len;i++)
            point[i]=org.point[i];
    }
    return *this;
}
Shape& Shape::Change(const Shape& a,int x,int y,int z)//every dot in the shape plus x，y，z
{
    len=a.len;
    delete [] point;
    point=new Dot [len];
    for(int i=0;i<len;i++)
        point[i]=Dot(a.point[i].Getx()+x,a.point[i].Gety()+y,a.point[i].Getx()+z);
    return *this;
}
void Shape::Area()//path to fill the shape (virtical)   填充路径（竖直方向）
{
    int xmax=point[0].Getx();
    int i=0;
    while(point[i].Getx()>=point[i+1].Getx())
        i++;
    int xmin=point[i].Getx();
    int z=point[0].Getz();
    area(xmax,xmin,z,point,len);
}
void Shape::Area1()//path to fill the shape (horizonal)   填充路径（水平方向）
{
    int ymax=point[0].Gety();
    int i=0;
    while(point[i].Gety()>=point[i+1].Gety())
        i++;
    int ymin=point[i].Gety();
    int z=point[0].Getz();
    area1(ymax,ymin,z,point,len);
}
int Shape::GetL()
{
    return len;
}
Dot*& Shape::GetP()
{
    return point;
}
