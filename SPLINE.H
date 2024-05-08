#ifndef __CURVES_BEZIER
#define __CURVES_BEZIER
void CubicBezier(Point *,int,int,int);
void nBezier(Point *,int,int,int);
void CubicBSpline(Point *,int,int,int);

double b_in(int,int,float);
int C(int,int);
#endif