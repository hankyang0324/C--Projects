#ifndef THREED_H
#define THREED_H

#include "twod.h"

/*----------3D Shape----------*/

class Prism3//triangular prism    三棱柱
{
private:
    Dot a,b,c;
    int h;
    Triangle* triangle;
public:
    Prism3(const Dot& A,const Dot& B,const Dot& C,int H);//Prism3(bottom dot a，b，c，height h)
    Prism3();
    Prism3(const Prism3& org);
    Prism3(Prism3&& org);
    ~Prism3();
    Prism3& operator=(const Prism3& org);
    int GetN();
    Triangle*& GetLayer();
};

class Pyramid3//triangular pyramind   三棱锥
{
private:
    Dot a,b,c,t;
    int h;
    Triangle* triangle;
public:
    Pyramid3(const Dot& A,const Dot& B,const Dot& C,const Dot& T);//Pyramid3(bottom dot a，b，c，vertex t)
    Pyramid3();
    Pyramid3(const Pyramid3& org);
    Pyramid3(Pyramid3&& org);
    ~Pyramid3();
    Pyramid3& operator=(const Pyramid3& org);
    int GetN();
    Triangle*& GetLayer();
};

class XPrism3//inclined triangle prism and others   斜三棱柱等
{
private:
    Dot a,b,c,a0,b0,c0;
    int h;
    Triangle* triangle;
public:
    XPrism3(const Dot& A,const Dot& B,const Dot& C,const Dot& A0,const Dot& B0,const Dot& C0);//XPrism3(bottom a,b,c,  top a0,b0,c0)
    XPrism3();
    XPrism3(const XPrism3& org);
    XPrism3(XPrism3&& org);
    ~XPrism3();
    XPrism3& operator=(const XPrism3& org);
    int GetN();
    Triangle*& GetLayer();
};

class Prism4//quadrangular   四棱柱
{
private:
    Dot a,b,c,d;
    int h;
    Rectangle* rectangle;
public:
    Prism4(const Dot& A,const Dot& B,const Dot& C,const Dot& D,int H);//Prism4(bottom dot a，b，c，d  height h)
    Prism4();
    Prism4(const Prism4& org);
    Prism4(Prism4&& org);
    ~Prism4();
    Prism4& operator=(const Prism4& org);
    int GetN();
    Rectangle*& GetLayer();
};

class Pyramid4//rectangular pyramid
{
private:
    Dot a,b,c,d,t;
    int h;
    Rectangle* rectangle;
public:
    Pyramid4(const Dot& A,const Dot& B,const Dot& C,const Dot& D,const Dot& T);//Pyramid4(bottom dot a，b，c，d  vertex t)
    Pyramid4();
    Pyramid4(const Pyramid4& org);
    Pyramid4(Pyramid4&& org);
    ~Pyramid4();
    Pyramid4& operator=(const Pyramid4& org);
    int GetN();
    Rectangle*& GetLayer();
};

class XPrism4//inclined quadrangular and others
{
private:
    Dot a,b,c,d,a0,b0,c0,d0;
    int h;
    Rectangle* rectangle;
public:
    XPrism4(const Dot& A,const Dot& B,const Dot& C,const Dot& D,const Dot& A0,const Dot& B0,const Dot& C0,const Dot& D0);//XPrism4(bottom a,b,c,d,  top a0,b0,c0,d0)
    XPrism4();
    XPrism4(const XPrism4& org);
    XPrism4(XPrism4&& org);
    ~XPrism4();
    XPrism4& operator=(const XPrism4& org);
    int GetN();
    Rectangle*& GetLayer();
};

class Cylinder//cyclinder    圆柱
{
private:
    Dot o;
    int r,h;
    Circle* circle;
public:
    Cylinder(const Dot& O,int R,int H);//Cyclinder(centre point on the bottom，radius，height)
    Cylinder();
    Cylinder(const Cylinder& org);
    Cylinder(Cylinder&& org);
    ~Cylinder();
    Cylinder& operator=(const Cylinder& org);
    int GetN();
    Circle*& GetLayer();
};

class Cone//cone    圆锥
{
private:
    Dot o;
    int r,h;
    Circle* circle;
public:
    Cone(const Dot& O,int R,int H);//Conecentre point on the bottom，radius，height)
    Cone();
    Cone(const Cone& org);
    Cone(Cone&& org);
    ~Cone();
    Cone& operator=(const Cone& org);
    int GetN();
    Circle*& GetLayer();
};

class XCylinder//inclined cyclinder or cone   斜圆柱、圆锥
{
private:
    Dot o,o0;
    int r,r0,h;
    Circle* circle;
public:
    XCylinder(const Dot& O,int R,const Dot& O0,int R0);//Xcyclinder(center point of the bottom，radius，center point of the top，radius0)
    XCylinder();
    XCylinder(const XCylinder& org);
    XCylinder(XCylinder&& org);
    ~XCylinder();
    XCylinder& operator=(const XCylinder& org);
    int GetN();
    Circle*& GetLayer();
};

class SemiSphere//semisphere    半球
{
private:
    Dot o;
    int r;
    Circle* circle;
public:
    SemiSphere(const Dot& O,int R);//SemiSphere(centre point of the sphere，radius)
    SemiSphere();
    SemiSphere(const SemiSphere& org);
    SemiSphere(SemiSphere&& org);
    ~SemiSphere();
    SemiSphere& operator=(const SemiSphere& org);
    int GetN();
    Circle*& GetLayer();
};

class XSphere//part of the semisphere     部分半球
{
private:
    Dot o;
    int r,h1,h2,h;
    Circle* circle;
public:
    XSphere(const Dot& O,int R,int H1,int H2);//XSphere(centre point of the bottom,radius of the sphere,height1 from the bottom to the centre point of the sphere,height2 from the top to the centre point of the sphere)
    XSphere();
    XSphere(const XSphere& org);
    XSphere(XSphere&& org);
    ~XSphere();
    XSphere& operator=(const XSphere& org);
    int GetN();
    Circle*& GetLayer();
};

class PrismSector
{
private:
    Dot o;
    int r,h;
    double c,d;
    Sector* sector;
public:
    PrismSector(const Dot& O,int R,double C,double D,int H);//PrismSector(centre point of the bottom,radius,start angle c,end angle d,height)
    PrismSector();
    PrismSector(const PrismSector& org);
    PrismSector(PrismSector&& org);
    ~PrismSector();
    PrismSector& operator=(const PrismSector& org);
    int GetN();
    Sector*& GetLayer();
};

class XPrismSector
{
private:
    Dot o,o0;
    int r,r0,h;
    double c,d;
    Sector* sector;
public:
    XPrismSector(const Dot& O,int R,const Dot& O0,int R0,double C,double D);//XPrismSector(centre point of the bottom,radius,centre point of the top,radius0,start angle c,end angle d)
    XPrismSector();
    XPrismSector(const XPrismSector& org);
    XPrismSector(XPrismSector&& org);
    ~XPrismSector();
    XPrismSector& operator=(const XPrismSector& org);
    int GetN();
    Sector*& GetLayer();
};

class PrismShape//customized (inclined) prism   自定(斜)柱体
{
private:
    Shape a;
    Shape* shape;
    Dot t;
    int h;
public:
    PrismShape(Shape& a,const Dot& T);//PrismShape(shape a on the bottom layer,start dot t on the top layer)
    PrismShape();
    PrismShape(const PrismShape& org);
    PrismShape(PrismShape&& org);
    ~PrismShape();
    PrismShape& operator=(const PrismShape& org);
    int GetN();
    Shape*& GetLayer();
};
#endif // THREED_H
