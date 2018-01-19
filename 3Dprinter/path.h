#ifndef PATH_H
#define PATH_H

#include "curves.h"

/*----------path----------*/
//after the closed boundary of the shape is given, design the path to fill the shape
//确定图形的封闭边界曲线后（逆时针），设计路径填充图形内部
void area(int xmax,int xmin,int z,Dot*& point,int& len);//using vertical curves fill the shape from the max of x to the min of the x, start from the head of the boundary array    从x的最大值向x的最小值竖直方向之字形填充，边界的起点为x最大值处
//area(boundary xmax，boundary xmin，height，pointer to the boundary array，length of the boundary array)

void area1(int ymax,int ymin,int z,Dot*& point,int& len);///using horizonal curves fill the shape from the max of y to the min of the y, start from the head of the boundary array      从y的最大值向y的最小值水平方向之字形填充，边界的起点为y最大值处
#endif // PATH_H
