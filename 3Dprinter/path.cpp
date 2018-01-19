#include "path.h"

/*----------path----------*/
//after the closed boundary of the shape is given, design the path to fill the shape
//确定图形的封闭边界曲线后（逆时针），设计路径填充图形内部
void area(int xmax,int xmin,int z,Dot*& point,int& len)//using vertical curves fill the shape from the max of x to the min of the x, start from the head of the boundary array    从x的最大值向x的最小值竖直方向之字形填充，边界的起点为x最大值处
//area(boundary xmax，boundary xmin，height，pointer to the boundary array，length of the boundary array)
{
    int* ytop=new int [xmax-xmin+1];
    int* ybottom=new int [xmax-xmin+1];
    ytop[0]=ybottom[0]=point[0].Gety();
    int count=0;//record the sum of the dots needed to be filled in the shape(length of the path)     需要填充的点数（数组长度）
    int i=0;
    int j=0;
    int k=len-1;
    int l=xmax;
    while(l>xmin)
    {
        for(;point[j].Getx()==l;j++)//the lowest dot at the top corresponding to the given x in the boundary    边界曲线给定x值的顶部最低点
            if(ytop[i]>=point[j].Gety())
                ytop[i]=point[j].Gety();
        for(;point[k].Getx()==l;k--)//the highest dot at the bottom corresponding to the given x in the boundary     边界曲线给定x值的底部最高点
            if(ybottom[i]<=point[k].Gety())
                ybottom[i]=point[k].Gety();
        if(ytop[i]>ybottom[i])
            count+=ytop[i]-ybottom[i]-1;//the sum of the dots in one vertical curve     一条竖直线上的需填充点数
        i++;
        l--;
        ytop[i]=point[j].Gety();
        ybottom[i]=point[k].Gety();
    }
    delete [] point;
    len=count;//length of the path      填充路径长度
    point=new Dot [len];
    for(int i=1,j=0;i<xmax-xmin;i=i+2)//using broken line in the path(from top to bottom than back to the top again)    之字行走线
    {
        for(int k=ytop[i]-1;k>ybottom[i];k--,j++)
            point[j]=Dot(xmax-i,k,z,j);
        for(int k=ybottom[i+1]+1;k<ytop[i+1];k++,j++)
            if(i+1<xmax-xmin)
                point[j]=Dot(xmax-i-1,k,z,j);
    }
    delete [] ybottom;
    delete [] ytop;
}

void area1(int ymax,int ymin,int z,Dot*& point,int& len)///using horizonal curves fill the shape from the max of y to the min of the y, start from the head of the boundary array      从y的最大值向y的最小值水平方向之字形填充，边界的起点为y最大值处
{
    int* xtop=new int [ymax-ymin+1];
    int* xbottom=new int [ymax-ymin+1];
    xtop[0]=xbottom[0]=point[0].Getx();
    int count=0;
    int i=0;
    int j=0;
    int k=len-1;
    int l=ymax;
    while(l>ymin)
    {
        for(;point[j].Gety()==l;j++)
            if(xbottom[i]<=point[j].Getx())
                xbottom[i]=point[j].Getx();
        for(;point[k].Gety()==l;k--)
            if(xtop[i]>=point[k].Getx())
                xtop[i]=point[k].Getx();
        if(xbottom[i]<xtop[i])
            count+=xtop[i]-xbottom[i]-1;
        i++;
        l--;
        xbottom[i]=point[j].Getx();
        xtop[i]=point[k].Getx();
    }
    delete [] point;
    len=count;
    point=new Dot [len];
    for(int i=1,j=0;i<ymax-ymin;i=i+2)
    {
        for(int k=xbottom[i]+1;k<xtop[i];k++,j++)
            point[j]=Dot(k,ymax-i,z,j);
        for(int k=xtop[i+1]-1;k>xbottom[i+1];k--,j++)
            if(i+1<ymax-ymin)
                point[j]=Dot(k,ymax-i-1,z,j);
    }
    delete [] xbottom;
    delete [] xtop;
}
