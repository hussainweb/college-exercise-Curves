#ifndef __CURVES_MOUSE
#define __CURVES_MOUSE
int initmouse();
void showmouse();
void hidemouse();
int getmouseloc(int *,int *);
void setmouseloc(int,int);
void boundmouse(int,int,int,int);
#endif