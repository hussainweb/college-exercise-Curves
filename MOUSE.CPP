#include <dos.h>

int initmouse(){
	REGS regs;
	regs.x.ax=0;
	int86(0x33,&regs,&regs);
	return regs.x.ax;
}

void showmouse(){
	REGS regs;
	regs.x.ax=1;
	int86(0x33,&regs,&regs);
	return;
}

void hidemouse(){
	REGS regs;
	regs.x.ax=2;
	int86(0x33,&regs,&regs);
	return;
}

int getmouseloc(int *x,int *y){
	REGS regs;
	regs.x.ax=3;
	regs.x.bx=0;
	int86(0x33,&regs,&regs);
	*x=regs.x.cx;
	*y=regs.x.dx;
	return regs.x.bx;
}

void setmouseloc(int x,int y){
	REGS regs;
	regs.x.ax=4;
	regs.x.cx=x;
	regs.x.dx=y;
	int86(0x33,&regs,&regs);
	return;
}

void boundmouse(int x1,int y1,int x2,int y2){
	REGS regs;
	regs.x.ax=7;
	regs.x.cx=x1;
	regs.x.dx=x2;
	int86(0x33,&regs,&regs);
	regs.x.ax=8;
	regs.x.cx=y1;
	regs.x.dx=y2;
	int86(0x33,&regs,&regs);
	return;
}