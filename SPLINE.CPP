#include "curves.h"

#define CTableN 20
#define CTableK 20

void CubicBezier(Point *p,int steps,int n,int ext){
	float t,stepval;
	float t2,t3;
	float ax,bx,cx;
	float ay,by,cy;
	float x,y;

	if (n>4){
		CubicBezier(p,steps,4,ext);
		CubicBezier(&p[3],steps,n-4,ext);
	}

	if (ext){
		fillsettingstype fi;
		linesettingstype li;
		int c;

		getfillsettings(&fi);
		getlinesettings(&li);
		c=getcolor();
		setlinestyle(DOTTED_LINE,0,1);
		setcolor(9);

		line(p[0].x,p[0].y,p[1].x,p[1].y);
		line(p[2].x,p[2].y,p[3].x,p[3].y);

		setlinestyle(USERBIT_LINE,0xf060,1);
		setcolor(1);

		line(p[1].x,p[1].y,p[2].x,p[2].y);

		setcolor(9);
		setfillstyle(SOLID_FILL,3);
		fillellipse(p[0].x,p[0].y,3,3);
		fillellipse(p[3].x,p[3].y,3,3);

		setcolor(1);
		circle(p[1].x,p[1].y,2);
		circle(p[2].x,p[2].y,2);

		setfillstyle(fi.pattern,fi.color);
		setlinestyle(li.linestyle,li.upattern,li.thickness);
		setcolor(c);
	}

	if (steps==-1){
		// Calculate (approx) steps if none specified
	}
	stepval=1.0/(float)steps;
	t=0;

	do{
		// Calculate the polynomial co-effecients

		cx = 3.0 * (p[1].x - p[0].x);
		bx = 3.0 * (p[2].x - p[1].x) - cx;
		ax = p[3].x - p[0].x - cx - bx;

		cy = 3.0 * (p[1].y - p[0].y);
		by = 3.0 * (p[2].y - p[1].y) - cy;
		ay = p[3].y - p[0].y - cy - by;

		t2=t*t;
		t3=t2*t;

		x = (ax*t3) + (bx*t2) + (cx*t) + p[0].x;
		y = (ay*t3) + (by*t2) + (cy*t) + p[0].y;

		putpixel((int)(x+0.5),(int)(y+0.5),15);

		t+=stepval;
	}while(t<=1);
}

void nBezier(Point *p,int steps,int n,int ext){
	int i;
	float t,stepval;
	double b;
	double x,y;

	if (ext){
		fillsettingstype fi;
		linesettingstype li;
		int c;

		getfillsettings(&fi);
		getlinesettings(&li);
		c=getcolor();

		for (i=0;i<n;i++){
			if (i==0||i==n-1){
				setcolor(9);
				setfillstyle(SOLID_FILL,3);
				fillellipse(p[i].x,p[i].y,3,3);
				setlinestyle(DOTTED_LINE,0,1);
				if (i==0)
					line(p[i].x,p[i].y,p[i+1].x,p[i+1].y);
				else
					line(p[i-1].x,p[i-1].y,p[i].x,p[i].y);
			}
			else{
				setcolor(1);
				setlinestyle(USERBIT_LINE,0xf060,1);
				circle(p[i].x,p[i].y,2);
				if (i>1)
					line(p[i-1].x,p[i-1].y,p[i].x,p[i].y);
			}
		}

		setfillstyle(fi.pattern,fi.color);
		setlinestyle(li.linestyle,li.upattern,li.thickness);
		setcolor(c);
	}

	if (steps==-1){
		// Calculate (approx) steps if none specified
	}
	stepval=1.0/(float)steps;
	t=0;

	do{
		x=0;y=0;
		for (i=0;i<n;i++){
			b=b_in(i,n-1,t);
			x+=p[i].x*b;
			y+=p[i].y*b;
		}

		putpixel((int)(x+0.5),(int)(y+0.5),15);

		t+=stepval;
	}while(t<=1);
}

void CubicBSpline(Point *p,int steps,int n,int ext){
	int i,k;
	float t,stepval;
	float ax,bx,cx,dx;
	float ay,by,cy,dy;
	float b;
	float x,y;

	if (ext){
		fillsettingstype fi;
		linesettingstype li;
		int c;

		getfillsettings(&fi);
		getlinesettings(&li);
		c=getcolor();

		for (i=0;i<n;i++){
			if (i==0||i==n-1){
				setcolor(9);
				setfillstyle(SOLID_FILL,3);
				fillellipse(p[i].x,p[i].y,3,3);
				setlinestyle(DOTTED_LINE,0,1);
				if (i==0)
					line(p[i].x,p[i].y,p[i+1].x,p[i+1].y);
				else
					line(p[i-1].x,p[i-1].y,p[i].x,p[i].y);
			}
			else{
				setcolor(1);
				setlinestyle(USERBIT_LINE,0xf060,1);
				circle(p[i].x,p[i].y,2);
				if (i>1)
					line(p[i-1].x,p[i-1].y,p[i].x,p[i].y);
			}
		}

		setfillstyle(fi.pattern,fi.color);
		setlinestyle(li.linestyle,li.upattern,li.thickness);
		setcolor(c);
	}

	if (steps==-1){
		// Calculate (approx) steps if none specified
	}
	stepval=1.0/(float)steps;

	for (i=1;i<n-2;i++){
		t=0;

		ax=(3 * (p[i].x - p[i+1].x) + p[i+2].x - p[i-1].x) / 6.0;
		bx=3 * (p[i-1].x + p[i+1].x - 2*p[i].x) / 6.0;
		cx=3 * (p[i+1].x - p[i-1].x) / 6.0;
		dx=(p[i-1].x + 4*p[i].x + p[i+1].x) / 6.0;

		ay=(3 * (p[i].y - p[i+1].y) + p[i+2].y - p[i-1].y) / 6.0;
		by=3 * (p[i-1].y + p[i+1].y - 2*p[i].y) / 6.0;
		cy=3 * (p[i+1].y - p[i-1].y) / 6.0;
		dy=(p[i-1].y + 4*p[i].y + p[i+1].y) / 6.0;

		do{
			x=dx + t * (cx + t * (bx + t * ax));
			y=dy + t * (cy + t * (by + t * ay));

			putpixel((int)(x+0.5),(int)(y+0.5),15);

			t+=stepval;
		}while(t<=1);
	}
}


double b_in(int i,int n,float t){
	if (t==0&&i==0)
		return 1.0;
	return C(n,i)*pow(t,i)*pow(1-t,n-i);
}

int C(int n,int i){
	static int Cinit=0;
	static int Carr[CTableN][CTableK];

	if (Cinit==0){
		int j,k;
		for (j=0;j<CTableN;j++)
			for (k=0;k<CTableK;k++)
				if ((j==k)||(k==0))
					Carr[j][k]=1;
				else
					Carr[j][k]=-1;
		Cinit=1;
	}

	if (Carr[n][i]==-1)
		Carr[n][i]=C(n-1,i-1)+C(n-1,i);
	return Carr[n][i];
}