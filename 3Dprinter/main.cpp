#include <cmath>
#include <iomanip>
#include "curves.h"
#include "path.h"
#include "twod.h"
#include "threed.h"
/*This program is designed based on cartesian coordinate system.

We first give the classes of dot, line and arc.

we have function Area and Area1 to give the vertical or horizontal path to fill the shape after the boundary of the shape are given.

Then in the layer level, we use dot, line, arc create some basic geometric shape class include triangle, convex quadrilateral, circle, sector to draw the boundaries of these shapes from the maximum value of x, anticlockwise.
In each of these class we can also use function Area() to get the path to fill the shape.
You can design some more complicated shapes combining the use of these classes.
We also create a class Shape so you can input your customized shape and call the function Area() or Area1() depending on different situations to get the path.
There is also a class Hollow so you can create some hollow shapes by digging out a shape from another shape.

In the 3D space level, we use those classes in layer level to build some solid figures including class prism3, pyramid3, xprism, prism4, pyramid4, xprism4, cyclinder, cone, xcyclinder, semisphere, xsphere, prismsector and prismshape(customized shape). You can also design some more complicated shapes or hollow shapes combining the use of these classes.

Temporarily we use bitmap to show the shape in each layer, 0 means draw nothing, 1 means the boundary of the shape, 7 means the path to fill the shape.*／

/*----------coordinate to angle & display----------*/
//this class is to change the coordinates to the motion of the arm, hasn't been designed by far
class Arm
{
private:
    double a,b,c;//angles of the pedestal and two arms
    const int h=1,r1=2,r2=3;//height of pedestal the length of two arms
public:
    Arm(double a=0,double b=0,double c=0):a(a),b(b),c(c){}
    Dot getLocation()//current location of the head
    {
        return Dot((r1*sin(b)+r2*sin(c))*cos(a),(r1*sin(b)+r2*sin(c))*sin(a),h+r1*cos(b)+r2*cos(c));
    }
    Arm GetAngle(Dot d)//transform from x,y,z to a,b,c
    {   double x=d.Getx();
        double y=d.Gety();
        double z=d.Getz();
        a=atan2(y,x);
        double R=sqrt(x*x+y*y+(z-h)*(z-h));
        double L=sqrt(x*x+y*y);
        double C=atan2(L,z-h);
        double A=acos((r2*r2+R*R-r1*r1)/(2*r2*R));
        c=C+A;
        double cosb =(z-h-r2*cos(c))/r1;
        b=acos(cosb);

        return Arm(a,0,0);
    }

    Arm GetAngelPath(){}//motion of the arms in one step which is expressed by changes of angle a,b,c
    Dot Curve(Dot a,Dot b,Dot c){}//design the track of drawing a curve, from a to b, center point is c
    double Geta()
    {
        return a;
    }
    double Getb()
    {
        return b;
    }
    double Getc()
    {
        return c;
    }
    friend Arm operator-(Arm A,Arm B)//dalta angle
    {
        return Arm(B.a-A.a,B.b-A.b,B.c-A.c);
    }
};

//temporarily using bitmap to show the shape in each layer, 0 means draw nothing, 1 means the boundary of the shape, 7 means the path to fill the shape
class Bitmap
{
private:
    #define row 60
    int x[row][row]={{0}};
public:
    void Draw(Dot*& point,int len,int rgb)
    {
        for(int i=0;i<len;i++)
            if(point[i].Getd()==1)
                x[point[i].Gety()][point[i].Getx()]=rgb;
    }
    friend ostream& operator<<(ostream& cout,const Bitmap& a)
    {
        for (int i=row-1;i>=0;i--)
        {
            for (int j=0; j<row;j++)
                cout<<setw(2)<<a.x[i][j];
            cout<<endl;
        }
        return cout;
    }
};

/*----------end----------*/
//some printed examples (layer 0 to 20)
int main()
{
    for(int i=0;i<=20;i++){
    cout<<"layer:"<<i<<endl;
    Bitmap pic[21];

    Dot a(10,10,0);
    Dot b(1,15,0);
    Dot c(5,1,0);
    Dot a0(15,15,20);
    Dot b0(6,20,20);
    Dot c0(10,20,20);
    Dot t(1,1,20);
    //Prism3 abc(a,b,c,20);
    //XPrism3 abc(a,b,c,a0,b0,c0);
    Pyramid3 abc(a,b,c,t);
    pic[i].Draw(abc.GetLayer()[i].GetP(),abc.GetLayer()[i].GetL(),1);
    abc.GetLayer()[i].Area();
    pic[i].Draw(abc.GetLayer()[i].GetP(),abc.GetLayer()[i].GetL(),7);

    Dot d(58,6,0);
    Dot e(53,11,0);
    Dot f(48,6,0);
    Dot g(53,1,0);
    Dot d0(48,6,20);
    Dot e0(48,11,20);
    Dot f0(43,6,20);
    Dot g0(48,1,20);
    Dot h(58,1,20);
    //Prism4 defg(d,e,f,g,20);
    //XPrism4 defg(d,e,f,g,d0,e0,f0,g0);
    Pyramid4 defg(d,e,f,g,h);
    pic[i].Draw(defg.GetLayer()[i].GetP(),defg.GetLayer()[i].GetL(),1);
    defg.GetLayer()[i].Area();
    pic[i].Draw(defg.GetLayer()[i].GetP(),defg.GetLayer()[i].GetL(),7);

    Dot o(30,30,0);
    Dot o0(20,20,20);
    Dot a1(25,25,0);
    Dot b1(0,25,0);
    Dot c1(25,5,0);
    Prism3 a1b1c1(a1,b1,c1,20);
    Cylinder oo(o,20,20);
//    XCyclinder o20(o,20,o0,10);
//    Cone o20(o,20,20);
    SemiSphere ooo(o,20);
//    XSphere o20(o,20,5,20);
//    pic1.Draw(o20.GetLayer()[i].GetP(),o20.GetLayer()[i].GetL(),1);
//    o20.GetLayer()[i].Area();
//    pic1.Draw(o20.GetLayer()[i].GetP(),o20.GetLayer()[i].GetL(),7);

    Hollow<Circle,Circle>ab(oo.GetLayer()[i],ooo.GetLayer()[i]);
    Hollow<Hollow<Circle,Circle>,Triangle>aa(ab,a1b1c1.GetLayer()[i]);//a semisphere and part of a triangle prism are digged out from a cyclinder
    pic[i].Draw(aa.GetP(),aa.GetL(),1);
    aa.Area();
    pic[i].Draw(aa.GetP(),aa.GetL(),7);

    Dot p(11,48,0);
    Dot p0(16,53,20);
    //PrismSector p10(p,10,60,240,20);
    XPrismSector p10(p,10,p0,5,60,240);
    pic[i].Draw(p10.GetLayer()[i].GetP(),p10.GetLayer()[i].GetL(),1);
    p10.GetLayer()[i].Area();
    pic[i].Draw(p10.GetLayer()[i].GetP(),p10.GetLayer()[i].GetL(),7);

    Dot z(45,58,0);
    Dot y(50,53,0);
    Dot x(45,48,0);
    Dot w(58,53,0);
    Dot v(45,58,20);
    Line zy(z,y);
    Line yx(y,x);
    Line xw(x,w);
    Line wz(w,z);
    int len=zy.GetL()+yx.GetL()+xw.GetL()+wz.GetL()-4;
    Dot* point=new Dot [len];
    for(int i=0;i<zy.GetL()-1;i++)
        point[i]=zy.GetP()[i];
    for(int i=0;i<yx.GetL()-1;i++)
        point[zy.GetL()-1+i]=yx.GetP()[i];
    for(int i=0;i<xw.GetL()-1;i++)
        point[zy.GetL()+yx.GetL()-2+i]=xw.GetP()[i];
    for(int i=0;i<wz.GetL()-1;i++)
        point[zy.GetL()+yx.GetL()+xw.GetL()-3+i]=wz.GetP()[i];
    Shape zyxw(point,len);//a customized shape shown on the right top corner
    delete [] point;
    PrismShape zyxwv(zyxw,v);
    pic[i].Draw(zyxwv.GetLayer()[i].GetP(),zyxwv.GetLayer()[i].GetL(),1);
    zyxwv.GetLayer()[i].Area1();
    pic[i].Draw(zyxwv.GetLayer()[i].GetP(),zyxwv.GetLayer()[i].GetL(),7);

    cout<<pic[i]<<endl;
}
}
