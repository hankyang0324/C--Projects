#include "threed.h"

/*----------3D Shape----------*/

Prism3::Prism3(const Dot& A,const Dot& B,const Dot& C,int H):a(A),b(B),c(C),h(H)//Prism3(bottom dot a，b，c，height h)
{
    triangle=new Triangle [h+1];
    for(int i=0;i<=h;i++)
    {
        Triangle temp(Dot(a.Getx(),a.Gety(),a.Getz()+i),
                      Dot(b.Getx(),b.Gety(),b.Getz()+i),
                      Dot(c.Getx(),c.Gety(),c.Getz()+i));
        triangle[i]=temp;
    }
}
Prism3::Prism3()
{
    a=b=c=Dot();
    h=0;
    triangle=nullptr;
}
Prism3::Prism3(const Prism3& org)
{
    a=org.a;
    b=org.b;
    c=org.c;
    h=org.h;
    triangle=new Triangle [h+1];
    for(int i=0;i<h+1;i++)
        triangle[i]=org.triangle[i];
}
Prism3::Prism3(Prism3&& org)
{
    a=org.a;
    b=org.b;
    c=org.c;
    h=org.h;
    triangle=org.triangle;
    org.triangle=nullptr;
}
Prism3::~Prism3()
{
    delete [] triangle;
}
Prism3& Prism3::operator=(const Prism3& org)
{
    if(this!=&org)
    {
        a=org.a;
        b=org.b;
        c=org.c;
        h=org.h;
        delete [] triangle;
        triangle=new Triangle [h+1];
        for(int i=0;i<h+1;i++)
            triangle[i]=org.triangle[i];
    }
    return *this;
}
int Prism3::GetN()
{
    return h+1;
}
Triangle*& Prism3::GetLayer()
{
    return triangle;
}

//
Pyramid3::Pyramid3(const Dot& A,const Dot& B,const Dot& C,const Dot& T):a(A),b(B),c(C),t(T)//Pyramid3(bottom dot a，b，c，vertex t)
{
    h=t.Getz()-a.Getz();//height
    Line at(a,t);
    Line bt(b,t);
    Line ct(c,t);
    Dot* a1=new Dot [h+1];
    Dot* b1=new Dot [h+1];
    Dot* c1=new Dot [h+1];
    a1[0]=at.GetP()[0];
    b1[0]=bt.GetP()[0];
    c1[0]=ct.GetP()[0];
    for(int j=1,i=1;j<at.GetL();j++)//using the first dot at eath height(z) of line at,bt,ct to decide the a,b,c in each layer       通过at，bt，ct每个高度z上的第一个点确定每一层的a，b，c
    {
        if(at.GetP()[j].Getz()>at.GetP()[j-1].Getz())
        {
            a1[i]=at.GetP()[j];
            i++;
        }
    }
    for(int j=1,i=1;j<bt.GetL();j++)
    {
        if(bt.GetP()[j].Getz()>bt.GetP()[j-1].Getz())
        {
            b1[i]=bt.GetP()[j];
            i++;
        }
    }
    for(int j=1,i=1;j<ct.GetL();j++)
    {
        if(ct.GetP()[j].Getz()>ct.GetP()[j-1].Getz())
        {
            c1[i]=ct.GetP()[j];
            i++;
        }
    }
    triangle=new Triangle [h+1];//decide the triangle in each layer       确定每一层的三角形
    for(int i=0;i<=h;i++)
    {
        Triangle temp(a1[i],b1[i],c1[i]);
        triangle[i]=temp;
    }
    delete [] c1;
    delete [] b1;
    delete [] a1;
}
Pyramid3::Pyramid3()
{
    a=b=c=t=Dot(0,0,0);
    h=0;
    triangle=nullptr;
}
Pyramid3::Pyramid3(const Pyramid3& org)
{
    a=org.a;
    b=org.b;
    c=org.c;
    t=org.t;
    h=org.h;
    triangle=new Triangle [h+1];
    for(int i=0;i<h+1;i++)
        triangle[i]=org.triangle[i];
}
Pyramid3::Pyramid3(Pyramid3&& org)
{
    a=org.a;
    b=org.b;
    c=org.c;
    t=org.t;
    h=org.h;
    triangle=org.triangle;
    org.triangle=nullptr;
}
Pyramid3::~Pyramid3()
{
    delete [] triangle;
}
Pyramid3& Pyramid3::operator=(const Pyramid3& org)
{
    if(this!=&org)
    {
        a=org.a;
        b=org.b;
        c=org.c;
        t=org.t;
        h=org.h;
        delete [] triangle;
        triangle=new Triangle [h+1];
        for(int i=0;i<h+1;i++)
            triangle[i]=org.triangle[i];
    }
    return *this;
}
int Pyramid3::GetN()
{
    return h+1;
}
Triangle*& Pyramid3::GetLayer()
{
    return triangle;
}

//
XPrism3::XPrism3(const Dot& A,const Dot& B,const Dot& C,const Dot& A0,const Dot& B0,const Dot& C0):a(A),b(B),c(C),a0(A0),b0(B0),c0(C0)//XPrism3(bottom a,b,c,  top a0,b0,c0)
{
    h=a0.Getz()-a.Getz();
    Line at(a,a0);
    Line bt(b,b0);
    Line ct(c,c0);
    Dot* a1=new Dot [h+1];
    Dot* b1=new Dot [h+1];
    Dot* c1=new Dot [h+1];
    a1[0]=at.GetP()[0];
    b1[0]=bt.GetP()[0];
    c1[0]=ct.GetP()[0];
    for(int j=1,i=1;j<at.GetL();j++)
    {
        if(at.GetP()[j].Getz()>at.GetP()[j-1].Getz())
        {
            a1[i]=at.GetP()[j];
            i++;
        }
    }
    for(int j=1,i=1;j<bt.GetL();j++)
    {
        if(bt.GetP()[j].Getz()>bt.GetP()[j-1].Getz())
        {
            b1[i]=bt.GetP()[j];
            i++;
        }
    }
    for(int j=1,i=1;j<ct.GetL();j++)
    {
        if(ct.GetP()[j].Getz()>ct.GetP()[j-1].Getz())
        {
            c1[i]=ct.GetP()[j];
            i++;
        }
    }
    triangle=new Triangle [h+1];
    for(int i=0;i<=h;i++)
    {
        Triangle temp(a1[i],b1[i],c1[i]);
        triangle[i]=temp;
    }
    delete [] c1;
    delete [] b1;
    delete [] a1;
}
XPrism3::XPrism3()
{
    a=b=c=a0=b0=c0=Dot();
    h=0;
    triangle=nullptr;
}
XPrism3::XPrism3(const XPrism3& org)
{
    a=org.a;
    b=org.b;
    c=org.c;
    a0=org.a0;
    b0=org.b0;
    c0=org.c0;
    h=org.h;
    triangle=new Triangle [h+1];
    for(int i=0;i<h+1;i++)
        triangle[i]=org.triangle[i];
}
XPrism3::XPrism3(XPrism3&& org)
{
    a=org.a;
    b=org.b;
    c=org.c;
    a0=org.a0;
    b0=org.b0;
    c0=org.c0;
    h=org.h;
    triangle=org.triangle;
    org.triangle=nullptr;
}
XPrism3::~XPrism3()
{
    delete [] triangle;
}
XPrism3& XPrism3::operator=(const XPrism3& org)
{
    if(this!=&org)
    {
        a=org.a;
        b=org.b;
        c=org.c;
        a0=org.a0;
        b0=org.b0;
        c0=org.c0;
        h=org.h;
        delete [] triangle;
        triangle=new Triangle [h+1];
        for(int i=0;i<h+1;i++)
            triangle[i]=org.triangle[i];
    }
    return *this;
}
int XPrism3::GetN()
{
    return h+1;
}
Triangle*& XPrism3::GetLayer()
{
    return triangle;
}

//
Prism4::Prism4(const Dot& A,const Dot& B,const Dot& C,const Dot& D,int H):a(A),b(B),c(C),d(D),h(H)//Prism4(bottom dot a，b，c，d  height h)
{
    rectangle=new Rectangle [h+1];
    for(int i=0;i<=h;i++)
    {
        Rectangle temp(Dot(a.Getx(),a.Gety(),a.Getz()+i),
                       Dot(b.Getx(),b.Gety(),b.Getz()+i),
                       Dot(c.Getx(),c.Gety(),c.Getz()+i),
                       Dot(d.Getx(),d.Gety(),d.Getz()+i));
        rectangle[i]=temp;
    }
}
Prism4::Prism4()
{
    a=b=c=d=Dot();
    h=0;
    rectangle=nullptr;
}
Prism4::Prism4(const Prism4& org)
{
    a=org.a;
    b=org.b;
    c=org.c;
    d=org.d;
    h=org.h;
    rectangle=new Rectangle [h+1];
    for(int i=0;i<h+1;i++)
        rectangle[i]=org.rectangle[i];
}
Prism4::Prism4(Prism4&& org)
{
    a=org.a;
    b=org.b;
    c=org.c;
    d=org.d;
    h=org.h;
    rectangle=org.rectangle;
    org.rectangle=nullptr;
}
Prism4::~Prism4()
{
    delete [] rectangle;
}
Prism4& Prism4::operator=(const Prism4& org)
{
    if(this!=&org)
    {
        a=org.a;
        b=org.b;
        c=org.c;
        d=org.d;
        h=org.h;
        delete [] rectangle;
        rectangle=new Rectangle [h+1];
        for(int i=0;i<h+1;i++)
            rectangle[i]=org.rectangle[i];
    }
    return *this;
}
int Prism4::GetN()
{
    return h+1;
}
Rectangle*& Prism4::GetLayer()
{
    return rectangle;
}

//
Pyramid4::Pyramid4(const Dot& A,const Dot& B,const Dot& C,const Dot& D,const Dot& T):a(A),b(B),c(C),d(D),t(T)//Pyramid4(bottom dot a，b，c，d  vertex t)
{
    h=t.Getz()-a.Getz();
    Line at(a,t);
    Line bt(b,t);
    Line ct(c,t);
    Line dt(d,t);
    Dot* a1=new Dot [h+1];
    Dot* b1=new Dot [h+1];
    Dot* c1=new Dot [h+1];
    Dot* d1=new Dot [h+1];
    a1[0]=at.GetP()[0];
    b1[0]=bt.GetP()[0];
    c1[0]=ct.GetP()[0];
    d1[0]=dt.GetP()[0];
    for(int j=1,i=1;j<at.GetL();j++)
    {
        if(at.GetP()[j].Getz()>at.GetP()[j-1].Getz())
        {
            a1[i]=at.GetP()[j];
            i++;
        }
    }
    for(int j=1,i=1;j<bt.GetL();j++)
    {
        if(bt.GetP()[j].Getz()>bt.GetP()[j-1].Getz())
        {
            b1[i]=bt.GetP()[j];
            i++;
        }
    }
    for(int j=1,i=1;j<ct.GetL();j++)
    {
        if(ct.GetP()[j].Getz()>ct.GetP()[j-1].Getz())
        {
            c1[i]=ct.GetP()[j];
            i++;
        }
    }
    for(int j=1,i=1;j<dt.GetL();j++)
    {
        if(dt.GetP()[j].Getz()>dt.GetP()[j-1].Getz())
        {
            d1[i]=dt.GetP()[j];
            i++;
        }
    }
    rectangle=new Rectangle [h+1];
    for(int i=0;i<=h;i++)
    {
        Rectangle temp(a1[i],b1[i],c1[i],d1[i]);
        rectangle[i]=temp;
    }
    delete [] d1;
    delete [] c1;
    delete [] b1;
    delete [] a1;
}
Pyramid4::Pyramid4()
{
    a=b=c=d=t=Dot();
    h=0;
    rectangle=nullptr;
}
Pyramid4::Pyramid4(const Pyramid4& org)
{
    a=org.a;
    b=org.b;
    c=org.c;
    d=org.d;
    t=org.t;
    h=org.h;
    rectangle=new Rectangle [h+1];
    for(int i=0;i<h+1;i++)
        rectangle[i]=org.rectangle[i];
}
Pyramid4::Pyramid4(Pyramid4&& org)
{
    a=org.a;
    b=org.b;
    c=org.c;
    d=org.d;
    t=org.t;
    h=org.h;
    rectangle=org.rectangle;
    org.rectangle=nullptr;
}
Pyramid4::~Pyramid4()
{
    delete [] rectangle;
}
Pyramid4& Pyramid4::operator=(const Pyramid4& org)
{
    if(this!=&org)
    {
        a=org.a;
        b=org.b;
        c=org.c;
        d=org.d;
        t=org.t;
        h=org.h;
        delete [] rectangle;
        rectangle=new Rectangle [h+1];
        for(int i=0;i<h+1;i++)
            rectangle[i]=org.rectangle[i];
    }
    return *this;
}
int Pyramid4::GetN()
{
    return h+1;
}
Rectangle*& Pyramid4::GetLayer()
{
    return rectangle;
}

//
XPrism4::XPrism4(const Dot& A,const Dot& B,const Dot& C,const Dot& D,const Dot& A0,const Dot& B0,const Dot& C0,const Dot& D0):a(A),b(B),c(C),d(D),a0(A0),b0(B0),c0(C0),d0(D0)//XPrism4(bottom a,b,c,d,  top a0,b0,c0,d0)
{
    h=a0.Getz()-a.Getz();
    Line at(a,a0);
    Line bt(b,b0);
    Line ct(c,c0);
    Line dt(d,d0);
    Dot* a1=new Dot [h+1];
    Dot* b1=new Dot [h+1];
    Dot* c1=new Dot [h+1];
    Dot* d1=new Dot [h+1];
    a1[0]=at.GetP()[0];
    b1[0]=bt.GetP()[0];
    c1[0]=ct.GetP()[0];
    d1[0]=dt.GetP()[0];
    for(int j=1,i=1;j<at.GetL();j++)
    {
        if(at.GetP()[j].Getz()>at.GetP()[j-1].Getz())
        {
            a1[i]=at.GetP()[j];
            i++;
        }
    }
    for(int j=1,i=1;j<bt.GetL();j++)
    {
        if(bt.GetP()[j].Getz()>bt.GetP()[j-1].Getz())
        {
            b1[i]=bt.GetP()[j];
            i++;
        }
    }
    for(int j=1,i=1;j<ct.GetL();j++)
    {
        if(ct.GetP()[j].Getz()>ct.GetP()[j-1].Getz())
        {
            c1[i]=ct.GetP()[j];
            i++;
        }
    }
    for(int j=1,i=1;j<dt.GetL();j++)
    {
        if(dt.GetP()[j].Getz()>dt.GetP()[j-1].Getz())
        {
            d1[i]=dt.GetP()[j];
            i++;
        }
    }
    rectangle=new Rectangle [h+1];
    for(int i=0;i<=h;i++)
    {
        Rectangle temp(a1[i],b1[i],c1[i],d1[i]);
        rectangle[i]=temp;
    }
    delete [] d1;
    delete [] c1;
    delete [] b1;
    delete [] a1;
}
XPrism4::XPrism4()
{
    a=b=c=d=a0=b0=c0=d0=Dot();
    h=0;
    rectangle=nullptr;
}
XPrism4::XPrism4(const XPrism4& org)
{
    a=org.a;
    b=org.b;
    c=org.c;
    d=org.d;
    a0=org.a0;
    b0=org.b0;
    c0=org.c0;
    d0=org.d0;
    h=org.h;
    rectangle=new Rectangle [h+1];
    for(int i=0;i<h+1;i++)
        rectangle[i]=org.rectangle[i];
}
XPrism4::XPrism4(XPrism4&& org)
{
    a=org.a;
    b=org.b;
    c=org.c;
    d=org.d;
    a0=org.a0;
    b0=org.b0;
    c0=org.c0;
    d0=org.d0;
    h=org.h;
    rectangle=org.rectangle;
    org.rectangle=nullptr;
}
XPrism4::~XPrism4()
{
    delete [] rectangle;
}
XPrism4& XPrism4::operator=(const XPrism4& org)
{
    if(this!=&org)
    {
        a=org.a;
        b=org.b;
        c=org.c;
        d=org.d;
        a0=org.a0;
        b0=org.b0;
        c0=org.c0;
        d0=org.d0;
        h=org.h;
        delete [] rectangle;
        rectangle=new Rectangle [h+1];
        for(int i=0;i<h+1;i++)
            rectangle[i]=org.rectangle[i];
    }
    return *this;
}
int XPrism4::GetN()
{
    return h+1;
}
Rectangle*& XPrism4::GetLayer()
{
    return rectangle;
}

//
Cylinder::Cylinder(const Dot& O,int R,int H):o(O),r(R),h(H)//Cyclinder(centre point on the bottom，radius，height)
{
    circle=new Circle [h+1];
    for(int i=0;i<=h;i++)
    {
        Circle a(Dot(o.Getx(),o.Gety(),o.Getz()+i),r);
        circle[i]=a;
    }
}
Cylinder::Cylinder()
{
    o=Dot();
    r=h=0;
    circle=nullptr;
}
Cylinder::Cylinder(const Cylinder& org)
{
    o=org.o;
    r=org.r;
    h=org.h;
    circle=new Circle [h+1];
    for(int i=0;i<h+1;i++)
        circle[i]=org.circle[i];
}
Cylinder::Cylinder(Cylinder&& org)
{
    o=org.o;
    r=org.r;
    h=org.h;
    circle=org.circle;
    org.circle=nullptr;
}
Cylinder::~Cylinder()
{
    delete [] circle;
}
Cylinder& Cylinder::operator=(const Cylinder& org)
{
    if(this!=&org)
    {
        o=org.o;
        r=org.r;
        h=org.h;
        delete [] circle;
        circle=new Circle [h+1];
        for(int i=0;i<h+1;i++)
            circle[i]=org.circle[i];
    }
    return *this;
}
int Cylinder::GetN()
{
    return h+1;
}
Circle*& Cylinder::GetLayer()
{
    return circle;
}

//
Cone::Cone(const Dot& O,int R,int H):o(O),r(R),h(H)//Conecentre point on the bottom，radius，height)
{
    Dot a(o.Getx()+r,o.Gety(),o.Getz());
    Dot t(o.Getx(),o.Gety(),o.Getz()+h);
    Line at(a,t);
    int* r1=new int [h+1];
    r1[0]=r;
    for(int j=1,i=1;j<at.GetL();j++)
    {
        if(at.GetP()[j].Getz()>at.GetP()[j-1].Getz())
        {
            r1[i]=at.GetP()[j].Getx()-o.Getx();
            i++;
        }
    }
    circle=new Circle [h+1];
    for(int i=0;i<=h;i++)
    {
        Circle temp(Dot(o.Getx(),o.Gety(),o.Getz()+i),r1[i]);
        circle[i]=temp;
    }
    delete [] r1;
}
Cone::Cone()
{
    o=Dot();
    r=h=0;
    circle=nullptr;
}
Cone::Cone(const Cone& org)
{
    o=org.o;
    r=org.r;
    h=org.h;
    circle=new Circle [h+1];
    for(int i=0;i<h+1;i++)
        circle[i]=org.circle[i];
}
Cone::Cone(Cone&& org)
{
    o=org.o;
    r=org.r;
    h=org.h;
    circle=org.circle;
    org.circle=nullptr;
}
Cone::~Cone()
{
    delete [] circle;
}
Cone& Cone::operator=(const Cone& org)
{
    if(this!=&org)
    {
        o=org.o;
        r=org.r;
        h=org.h;
        delete [] circle;
        circle=new Circle [h+1];
        for(int i=0;i<h+1;i++)
            circle[i]=org.circle[i];
    }
    return *this;
}
int Cone::GetN()
{
    return h+1;
}
Circle*& Cone::GetLayer()
{
    return circle;
}

//
XCylinder::XCylinder(const Dot& O,int R,const Dot& O0,int R0):o(O),r(R),o0(O0),r0(R0)//Xcyclinder(center point of the bottom，radius，center point of the top，radius0)
{
    h=o0.Getz()-o.Getz();
    Dot a(o.Getx()+r,o.Gety(),o.Getz());
    Dot a0(o0.Getx()+r0,o0.Gety(),o0.Getz());
    Line at(a,a0);
    Line oo(o,o0);
    Dot* a1=new Dot [h+1];
    Dot* o1=new Dot [h+1];
    a1[0]=at.GetP()[0];
    o1[0]=oo.GetP()[0];
    for(int j=1,i=1;j<at.GetL();j++)
    {
        if(at.GetP()[j].Getz()>at.GetP()[j-1].Getz())
        {
            a1[i]=at.GetP()[j];
            i++;
        }
    }
    for(int j=1,i=1;j<oo.GetL();j++)
    {
        if(oo.GetP()[j].Getz()>oo.GetP()[j-1].Getz())
        {
            o1[i]=oo.GetP()[j];
            i++;
        }
    }
    circle=new Circle [h+1];
    for(int i=0;i<=h;i++)
    {
        Circle temp(Dot(o1[i].Getx(),o1[i].Gety(),o1[i].Getz()),a1[i].Getx()-o1[i].Getx());
        circle[i]=temp;
    }
    delete [] o1;
    delete [] a1;
}
XCylinder::XCylinder()
{
    o=o0=Dot();
    r=r0=h=0;
    circle=nullptr;
}
XCylinder::XCylinder(const XCylinder& org)
{
    o=org.o;
    r=org.r;
    o0=org.o0;
    r0=org.r0;
    h=org.h;
    circle=new Circle [h+1];
    for(int i=0;i<h+1;i++)
        circle[i]=org.circle[i];
}
XCylinder::XCylinder(XCylinder&& org)
{
    o=org.o;
    r=org.r;
    o0=org.o0;
    r0=org.r0;
    h=org.h;
    circle=org.circle;
    org.circle=nullptr;
}
XCylinder::~XCylinder()
{
    delete [] circle;
}
XCylinder& XCylinder::operator=(const XCylinder& org)
{
    if(this!=&org)
    {
        o=org.o;
        r=org.r;
        o0=org.o0;
        r0=org.r0;
        h=org.h;
        delete [] circle;
        circle=new Circle [h+1];
        for(int i=0;i<h+1;i++)
            circle[i]=org.circle[i];
    }
    return *this;
}
int XCylinder::GetN()
{
    return h+1;
}
Circle*& XCylinder::GetLayer()
{
    return circle;
}

//
SemiSphere::SemiSphere(const Dot& O,int R):o(O),r(R)//SemiSphere(centre point of the sphere，radius)
{
    Arc arc(o,r,0,90);
    int* r1=new int [r+1];
    r1[0]=r;
    for(int j=1,i=1;j<arc.GetL();j++)
    {
        if(arc.GetP()[j].Gety()>arc.GetP()[j-1].Gety())
        {
            r1[i]=arc.GetP()[j].Getx()-o.Getx();
            i++;
        }
    }
    circle=new Circle [r+1];
    for(int i=0;i<=r;i++)
    {
        Circle temp(Dot(o.Getx(),o.Gety(),o.Getz()+i),r1[i]);
        circle[i]=temp;
    }
    delete [] r1;
}
SemiSphere::SemiSphere()
{
    o=Dot();
    r=0;
    circle=nullptr;
}
SemiSphere::SemiSphere(const SemiSphere& org)
{
    o=org.o;
    r=org.r;
    circle=new Circle [r+1];
    for(int i=0;i<r+1;i++)
        circle[i]=org.circle[i];
}
SemiSphere::SemiSphere(SemiSphere&& org)
{
    o=org.o;
    r=org.r;
    circle=org.circle;
    org.circle=nullptr;
}
SemiSphere::~SemiSphere()
{
    delete [] circle;
}
SemiSphere& SemiSphere::operator=(const SemiSphere& org)
{
    if(this!=&org)
    {
        o=org.o;
        r=org.r;
        delete [] circle;
        circle=new Circle [r+1];
        for(int i=0;i<r+1;i++)
            circle[i]=org.circle[i];
    }
    return *this;
}
int SemiSphere::GetN()
{
    return r+1;
}
Circle*& SemiSphere::GetLayer()
{
    return circle;
}

//
XSphere::XSphere(const Dot& O,int R,int H1,int H2):o(O),r(R),h1(H1),h2(H2)//XSphere(centre point of the bottom,radius of the sphere,height1 from the bottom to the centre point of the sphere,height2 from the top to the centre point of the sphere)
{
    h=h2-h1;
    SemiSphere a(Dot(o.Getx(),o.Gety(),o.Getz()-h1),r);
    circle=new Circle [h+1];
    for(int i=0;i<=h;i++)
        circle[i]=a.GetLayer()[i+h1];
}
XSphere::XSphere()
{
    o=Dot();
    r=h1=h2=h=0;
    circle=nullptr;
}
XSphere::XSphere(const XSphere& org)
{
    o=org.o;
    r=org.r;
    h1=org.h1;
    h2=org.h2;
    h=org.h;
    circle=new Circle [h+1];
    for(int i=0;i<h+1;i++)
        circle[i]=org.circle[i];
}
XSphere::XSphere(XSphere&& org)
{
    o=org.o;
    r=org.r;
    h1=org.h1;
    h2=org.h2;
    h=org.h;
    circle=org.circle;
    org.circle=nullptr;
}
XSphere::~XSphere()
{
    delete [] circle;
}
XSphere& XSphere::operator=(const XSphere& org)
{
    if(this!=&org)
    {
        o=org.o;
        r=org.r;
        h1=org.h1;
        h2=org.h2;
        h=org.h;
        delete [] circle;
        circle=new Circle [h+1];
        for(int i=0;i<h+1;i++)
            circle[i]=org.circle[i];
    }
    return *this;
}
int XSphere::GetN()
{
    return h+1;
}
Circle*& XSphere::GetLayer()
{
    return circle;
}

//
PrismSector::PrismSector(const Dot& O,int R,double C,double D,int H):o(O),r(R),c(C),d(D),h(H)//PrismSector(centre point of the bottom,radius,start angle c,end angle d,height)
{
    sector=new Sector [h+1];
    for(int i=0;i<=h;i++)
    {
        Sector temp(Dot(o.Getx(),o.Gety(),o.Getz()+i),r,c,d);
        sector[i]=temp;
    }
}
PrismSector::PrismSector()
{
    o=Dot();
    r=h=0;
    c=d=0;
    sector=nullptr;
}
PrismSector::PrismSector(const PrismSector& org)
{
    o=org.o;
    r=org.r;
    h=org.h;
    c=org.c;
    d=org.d;
    sector=new Sector [h+1];
    for(int i=0;i<h+1;i++)
        sector[i]=org.sector[i];
}
PrismSector::PrismSector(PrismSector&& org)
{
    o=org.o;
    r=org.r;
    h=org.h;
    c=org.c;
    d=org.d;
    sector=org.sector;
    org.sector=nullptr;
}
PrismSector::~PrismSector()
{
    delete [] sector;
}
PrismSector& PrismSector::operator=(const PrismSector& org)
{
    if(this!=&org)
    {
        o=org.o;
        r=org.r;
        h=org.h;
        c=org.c;
        d=org.d;
        delete [] sector;
        sector=new Sector [h+1];
        for(int i=0;i<h+1;i++)
            sector[i]=org.sector[i];
    }
    return *this;
}
int PrismSector::GetN()
{
    return h+1;
}
Sector*& PrismSector::GetLayer()
{
    return sector;
}

//
XPrismSector::XPrismSector(const Dot& O,int R,const Dot& O0,int R0,double C,double D):o(O),r(R),o0(O0),r0(R0),c(C),d(D)//XPrismSector(centre point of the bottom,radius,centre point of the top,radius0,start angle c,end angle d)
{
    h=o0.Getz()-o.Getz();
    Dot a(o.Getx()+r,o.Gety(),o.Getz());
    Dot a0(o0.Getx()+r0,o0.Gety(),o0.Getz());
    Line at(a,a0);
    Line oo(o,o0);
    Dot* a1=new Dot [h+1];
    Dot* o1=new Dot [h+1];
    a1[0]=at.GetP()[0];
    o1[0]=oo.GetP()[0];
    for(int j=1,i=1;j<at.GetL();j++)
    {
        if(at.GetP()[j].Getz()>at.GetP()[j-1].Getz())
        {
            a1[i]=at.GetP()[j];
            i++;
        }
    }
    for(int j=1,i=1;j<oo.GetL();j++)
    {
        if(oo.GetP()[j].Getz()>oo.GetP()[j-1].Getz())
        {
            o1[i]=oo.GetP()[j];
            i++;
        }
    }
    sector=new Sector [h+1];
    for(int i=0;i<=h;i++)
    {
        Sector temp(Dot(o1[i].Getx(),o1[i].Gety(),o1[i].Getz()),a1[i].Getx()-o1[i].Getx(),c,d);
        sector[i]=temp;
    }
    delete [] o1;
    delete [] a1;
}
XPrismSector::XPrismSector()
{
    o=o0=Dot();
    r=r0=h=0;
    c=d=0;
    sector=nullptr;
}
XPrismSector::XPrismSector(const XPrismSector& org)
{
    o=org.o;
    r=org.r;
    o0=org.o;
    r0=org.r;
    h=org.h;
    c=org.c;
    d=org.d;
    sector=new Sector [h+1];
    for(int i=0;i<h+1;i++)
        sector[i]=org.sector[i];
}
XPrismSector::XPrismSector(XPrismSector&& org)
{
    o=org.o;
    r=org.r;
    o0=org.o;
    r0=org.r;
    h=org.h;
    c=org.c;
    d=org.d;
    sector=org.sector;
    org.sector=nullptr;
}
XPrismSector::~XPrismSector()
{
    delete [] sector;
}
XPrismSector& XPrismSector::operator=(const XPrismSector& org)
{
    if(this!=&org)
    {
        o=org.o;
        r=org.r;
        o0=org.o;
        r0=org.r;
        h=org.h;
        c=org.c;
        d=org.d;
        delete [] sector;
        sector=new Sector [h+1];
        for(int i=0;i<h+1;i++)
            sector[i]=org.sector[i];
    }
    return *this;
}
int XPrismSector::GetN()
{
    return h+1;
}
Sector*& XPrismSector::GetLayer()
{
    return sector;
}

//
PrismShape::PrismShape(Shape& a,const Dot& T):t(T)//PrismShape(shape a on the bottom layer,start dot t on the top layer)
{
    h=t.Getz()-a.GetP()[0].Getz();
    Line at(a.GetP()[0],t);
    Dot* a1=new Dot [h+1];
    a1[0]=Dot(0,0,0);
    for(int j=1,i=1;j<at.GetL();j++)//using the first dot in each height(z) to decide the start dot of the shape in each layer   通过at每个高度z上的第一个点确定每一层的起点
    {
        if(at.GetP()[j].Getz()>at.GetP()[j-1].Getz())
        {
            a1[i]=at.GetP()[j]-a.GetP()[0];//a1 is uesd to store deviation between the start dot of each layer and the bottom layer     a1存放每一层起点与底层起点的偏移差
            i++;
        }
    }
    shape=new Shape [h+1];
    for(int i=0;i<=h;i++)
        shape[i].Change(a,a1[i].Getx(),a1[i].Gety(),a1[i].Getz());//every dot plus the deviation in each layer    每层加上偏移差
    delete [] a1;
}
PrismShape::PrismShape()
{
    shape=nullptr;
    t=Dot();
    h=0;
}
PrismShape::PrismShape(const PrismShape& org)
{
    a=org.a;
    h=org.h;
    shape=new Shape [h+1];
    for(int i=0;i<h+1;i++)
        shape[i]=org.shape[i];
}
PrismShape::PrismShape(PrismShape&& org)
{
    a=org.a;
    h=org.h;
    shape=org.shape;
    org.shape=nullptr;
}
PrismShape::~PrismShape()
{
    delete [] shape;
}
PrismShape& PrismShape::operator=(const PrismShape& org)
{
    if(this!=&org)
    {
        a=org.a;
        h=org.h;
        delete [] shape;
        shape=new Shape [h+1];
        for(int i=0;i<h+1;i++)
            shape[i]=org.shape[i];
    }
    return *this;
}
int PrismShape::GetN()
{
    return h+1;
}
Shape*& PrismShape::GetLayer()
{
    return shape;
}
