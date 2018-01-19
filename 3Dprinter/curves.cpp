#include "curves.h"

/*----------dot & string----------*/
//Dot. Num is used to record the order of the dot in the array. The default value of draw =1, spray; draw=0, not spray
//点 xyz坐标值。num记录点在数组中的序号。draw默认=1, 喷涂料；draw=0,不喷涂料。
Dot::Dot(int X,int Y,int Z,int N,int D):x(X),y(Y),z(Z),num(N),draw(D){} //Dot(x,y,z,n,d)
void Dot::ChangeN(int i)
{
    num=i;
}
void Dot::ChangeD()
{
    draw=0;
}
int Dot::Getx()
{
    return x;
}
int Dot::Gety()
{
    return y;
}
int Dot::Getz()
{
    return z;
}
int Dot::Getn()
{
    return num;
}
int Dot::Getd()
{
    return draw;
}
void Dot::YZswap()
{
    swap(y,z);
}
void Dot::XZswap()
{
    swap(x,z);
}
Dot operator-(Dot b,Dot a)
{
    return Dot(b.x-a.x,b.y-a.y,b.z-a.z);
}
ostream& operator<<(ostream& cout,Dot a)
{
    return cout<<"x:"<<a.x<<" y:"<<a.y<<" z:"<<a.z<<endl<<"num:"<<a.num<<" draw:"<<a.draw;
}

//a line from Dot a to Dot b. bresenham algorithm.
//起点a，终点b，确定一条直线。使用bresenham算法
Line::Line(const Dot& A,const Dot& B):a(A),b(B)// Line(start，end）
{
    if(a.Getx()==b.Getx()&&a.Gety()==b.Gety()&&a.Getz()==b.Getz())//if a,b are at the same position. point to a, len=1  如果a，b在同一点，指向a点，长度为1
    {
        len=1;
        point =new Dot [len];
        point[0]=a;
        point[0].ChangeN(0);
    }
    else
    {
        int dx=b.Getx()-a.Getx();
        int dy=b.Gety()-a.Gety();
        int dz=b.Getz()-a.Getz();
        int x=a.Getx();
        int y=a.Gety();
        int z=a.Getz();
        int e1=0;
        int e2=0;
        int i=0;
        if(abs(dx)>=abs(dy))
            len=abs(dx);
        else
            len=abs(dy);
        if(len<abs(dz))
            len=abs(dz);
        len+=1;
        point=new Dot[len];
        if(abs(dx)>=abs(dy)&&abs(dx)>=abs(dz))
        {
            e1=e2=-abs(dx);
            for(i=0;i<=abs(dx);i++)
            {
                point[i]=Dot(x,y,z,i);
                x+=dx/abs(dx);
                e1+=2*abs(dy);
                e2+=2*abs(dz);
                if(e1>=0)
                {
                    y+=dy/abs(dy);
                    e1-=2*abs(dx);
                }
                if(e2>=0)
                {
                    z+=dz/abs(dz);
                    e2-=2*abs(dx);
                }
            }
        }
        if(abs(dy)>abs(dx)&&abs(dy)>=abs(dz))
        {
            e1=e2=-abs(dy);
            for(i=0;i<=abs(dy);i++)
            {
                point[i]=Dot(x,y,z,i);
                y+=dy/abs(dy);
                e1+=2*abs(dx);
                e2+=2*abs(dz);
                if(e1>=0)
                {
                    x+=dx/abs(dx);
                    e1-=2*abs(dy);
                }
                if(e2>=0)
                {
                    z+=dz/abs(dz);
                    e2-=2*abs(dy);
                }
            }
        }
        if(abs(dz)>abs(dx)&&abs(dz)>abs(dy))
        {
            e1=e2=-abs(dz);
            for(i=0;i<=abs(dz);i++)
            {
                point[i]=Dot(x,y,z,i);
                z+=dz/abs(dz);
                e1+=2*abs(dx);
                e2+=2*abs(dy);
                if(e1>=0)
                {
                    x+=dx/abs(dx);
                    e1-=2*abs(dz);
                }
                if(e2>=0)
                {
                    y+=dy/abs(dy);
                    e2-=2*abs(dz);
                }
            }
        }
    }
}
Line::Line()
{
    a=b=Dot();
    point=nullptr;
    len=0;
}
Line::Line(const Line& org)
{
    a=org.a;
    b=org.b;
    len=org.len;
    point=new Dot [len];
    for(int i=0;i<len;i++)
        point[i]=org.point[i];
}
Line::Line(Line&& org)
{
    a=org.a;
    b=org.b;
    len=org.len;
    point=org.point;
    org.point=nullptr;
}
Line::~Line()
{
    delete [] Line::point;
}
Line& Line::operator=(const Line& org)
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
int Line::GetL()
{
    return len;
}
Dot*& Line::GetP()
{
    return point;
}

//draw a circle, centre point o, radius=r, start from(r,0), anticlockwise. cut out the arc from the circe accroding to angle a,b (0<=a<=b<=360), bresenham algorithm
//画圆形为o，半径为r的圆，起点(r,0), 逆时针。根据角度a，b (0<=a<=b<=360) 从数组中提取弧。中点画圆法（1/8）
Arc::Arc(const Dot& O,int R,double A,double B):o(O),r(R),a(A),b(B) //Arc(centre,radius,start angle,end angle）
{
    int e=5-4*r;
    int i=0;
    int x=r;
    int y=0;
    while(x>=y)//i-1:sum of dots in 1/4 circle.    i-1 确定1/4圆点数
    {
        if(x==y)//in this situation, two same dots at 1/8 circle, delete one of them   此情况下1/8位置该点被重复两次，删除一个点
            i-=1;
        if(e<0)
            e+=8*y+12;
        else
        {
            e+=8*(y-x)+20;
            x--;
        }
        y++;
        i+=2;
    }
    Dot* circlepoint=new Dot [4*i-3];// last element is spared for the start dot    多出最后一个点放置起点
    e=5-4*r;
    x=r;
    y=0;
    int j=0;
    while(x>=y)//replicate dots of the 1/8 circle to the whole circle, and plus the centre point coordinates  将1/8翻转复制到到整个圆，加上圆心坐标，起点多算一次(终点=起点)
    {
        circlepoint[j]=Dot(x+o.Getx(),y+o.Gety(),o.Getz(),j);
        circlepoint[i-1-j]=Dot(y+o.Getx(),x+o.Gety(),o.Getz(),i-1-j);
        circlepoint[i-1+j]=Dot(-y+o.Getx(),x+o.Gety(),o.Getz(),i-1+j);
        circlepoint[2*i-2-j]=Dot(-x+o.Getx(),y+o.Gety(),o.Getz(),2*i-2-j);
        circlepoint[2*i-2+j]=Dot(-x+o.Getx(),-y+o.Gety(),o.Getz(),2*i-2+j);
        circlepoint[3*i-3-j]=Dot(-y+o.Getx(),-x+o.Gety(),o.Getz(),3*i-3-j);
        circlepoint[3*i-3+j]=Dot(y+o.Getx(),-x+o.Gety(),o.Getz(),3*i-3+j);
        circlepoint[4*i-4-j]=Dot(x+o.Getx(),-y+o.Gety(),o.Getz(),4*i-4-j);
        if(e<0)
            e+=8*y+12;
        else
        {
            e+=8*(y-x)+20;
            x--;
        }
        y++;
        j++;
    }
    int start=((4*i-4)*a/360);
    int end;
    if(b==360)//in this situation: end=start-1  该情况下:终点=起点(原数组终点)-1
        end=((4*i-4)*b/360);
    else
        end=((4*i-4)*b/360)+1;
    len=end-start;//end and start are at the same position, len=1    终点与起点重合，设长度为1
    if(len==0)
    {
        len=1;
    }
    point=new Dot [len];//cut the arc out from the circle
    for(i=0;i<len;i++)
    {
        point[i]=circlepoint[start+i];
        point[i].ChangeN(i);
    }
    delete [] circlepoint;
}
Arc::Arc()
{
    o=Dot();
    r=len=0;
    a=b=0;
    point=nullptr;
}
Arc::Arc(const Arc& org)
{
    o=org.o;
    r=org.r;
    a=org.a;
    b=org.b;
    len=org.len;
    point=new Dot [len];
    for(int i=0;i<len;i++)
        point[i]=org.point[i];
}
Arc::Arc(Arc&& org)
{
    o=org.o;
    r=org.r;
    a=org.a;
    b=org.b;
    len=org.len;
    point=org.point;
    org.point=nullptr;
}
Arc::~Arc()
{
    delete [] point;
}
Arc& Arc::operator=(const Arc& org)
{
    if(this!=&org)
    {
        o=org.o;
        r=org.r;
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
int Arc::GetL()
{
    return len;
}
Dot*& Arc::GetP()
{
    return point;
}

//draw the arc clockwise, to deal with concave arc in a shape
//Arc的顺时针画法，用以处理凹弧的情况
Arc1::Arc1(const Dot& O,int R,double A,double B):o(O),r(R),a(A),b(B)
{
    Arc arc(o,r,a,b);
    len=arc.GetL();
    point=new Dot [len];
    for(int i=0;i<len;i++)
    {
        point[i]=arc.GetP()[len-1-i];
        point[i].ChangeN(i);
    }
}
Arc1::Arc1()
{
    o=Dot();
    r=len=0;
    a=b=0;
    point=nullptr;
}
Arc1::Arc1(const Arc1& org)
{
    o=org.o;
    r=org.r;
    a=org.a;
    b=org.b;
    len=org.len;
    point=new Dot [len];
    for(int i=0;i<len;i++)
        point[i]=org.point[i];
}
Arc1::Arc1(Arc1&& org)
{
    o=org.o;
    r=org.r;
    a=org.a;
    b=org.b;
    len=org.len;
    point=org.point;
    org.point=nullptr;
}
Arc1::~Arc1()
{
    delete [] point;
}
Arc1& Arc1::operator=(const Arc1& org)
{
    if(this!=&org)
    {
        o=org.o;
        r=org.r;
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
int Arc1::GetL()
{
    return len;
}
Dot*& Arc1::GetP()
{
    return point;
}

