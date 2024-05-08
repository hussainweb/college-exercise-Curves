#include "curves.h"
#define MAXPOINTS 20

int numpoints=0,extcurves=0;
int showhelp=0,numsteps=1000;
Point c[MAXPOINTS];
Point CB[MAXPOINTS];
Point nB[MAXPOINTS];
Point BS[MAXPOINTS];

void drawscreen(){
	int i;
	char *pstr="P   ";

	hidemouse();
	clrscr();
	cleardevice();
	setcolor(15);
	line(320,0,320,479);
	line(0,240,639,240);

	for (i=0;i<numpoints;i++){
		CB[i].x=c[i].x+320;
		CB[i].y=c[i].y;
		nB[i].x=c[i].x;
		nB[i].y=c[i].y+240;
		BS[i].x=c[i].x+320;
		BS[i].y=c[i].y+240;
	}

	setcolor(8);
	outtextxy(327,7,"Cubic Bezier Curves");
	outtextxy(7,247,"n degree Bezier Curve");
	outtextxy(327,247,"B-Spline Curve");
	setcolor(15);
	if (showhelp){
		outtextxy(7,2,"H to toggle this message");
		outtextxy(7,10,"P to toggle show Control Points");
		outtextxy(7,18,"I to Insert a point");
		outtextxy(7,26,"D to Delete a point");
		outtextxy(7,34,"C to Clear all the points");
		outtextxy(7,42,"S to change the Steps value");
		outtextxy(7,52,"Esc to quit without saving");
		outtextxy(7,60,"RightClick to quit with saving");
	}
	outtextxy(325,5,"Cubic Bezier Curves");
	outtextxy(5,245,"n degree Bezier Curve");
	outtextxy(325,245,"B-Spline Curve");

	setcolor(7);
	setlinestyle(SOLID_LINE,0,1);
	for (i=0;i<numpoints;i++){
		line(c[i].x-3,c[i].y,c[i].x+3,c[i].y);
		line(c[i].x,c[i].y-3,c[i].x,c[i].y+3);
		itoa(i+1,pstr+1,10);
		outtextxy(c[i].x+3,c[i].y-8,pstr);
	}

	if (extcurves){
		setcolor(8);
		setlinestyle(USERBIT_LINE,0xe0e0,1);
		for (i=1;i<numpoints;i++)
			line(c[i-1].x,c[i-1].y,c[i].x,c[i].y);
		setlinestyle(SOLID_LINE,0,1);
		setcolor(7);
	}

	CubicBezier(CB,numsteps,numpoints,extcurves);
	nBezier(nB,numsteps,numpoints,extcurves);
	CubicBSpline(BS,numsteps,numpoints,extcurves);

	showmouse();
}

int load(){
	FILE *fp;
	fp=fopen("points.dat","rb");
	if (fp==NULL)
		return 0;
	fread(&numpoints,sizeof(numpoints),1,fp);
	fread(&c[0],sizeof(c[0]),numpoints,fp);
	fclose(fp);
	return 1;
}

void savenquit(){
	FILE *fp;
	fp=fopen("points.dat","wb");
	fwrite(&numpoints,sizeof(numpoints),1,fp);
	fwrite(&c[0],sizeof(c[0]),numpoints,fp);
	fclose(fp);
	closegraph();
	exit(0);
}

int main(){
	int gd=DETECT,gm;
	int mx,my,mb;
	int i,j,ch;

	if (load())
		printf("File POINTS.DAT successfully loaded\n");
	else
		printf("Could not load POINTS.DAT\n\a");

	printf("Press H for help regarding commands.\n");
	printf("Click to add a new point.\nMaximum number of points allowed is %d.",MAXPOINTS);
	getch();

	initgraph(&gd,&gm,"");
	drawscreen();
	initmouse();
	boundmouse(0,0,320,240);
	showmouse();
	flushall();

	while(1){
		mb=getmouseloc(&mx,&my);
		if (kbhit()){
			ch=getch();
			if (ch==0)	ch=256+getch();

			switch(ch){
				case 27:
					hidemouse();
					closegraph();
					exit(0);
				case 'C':
				case 'c':
					numpoints=0;
					for (i=0;i<MAXPOINTS;i++)
						c[i].x=c[i].y=0;
					break;
				case 'H':
				case 'h':
					showhelp=!showhelp;
					break;
				case 'P':
				case 'p':
					extcurves=!extcurves;
					break;
				case 'S':
				case 's':
					printf("Enter new value for steps. Current value is %d: ",numsteps);
					scanf("%d",&numsteps);
					if (numsteps<0)
						numsteps=1000;
					break;
				case 'I':
				case 'i':
					printf("Insert where: ");
					scanf("%d",&j);
					j--;
					if (j<0)
						break;
					else if (j>numpoints)
						j=numpoints;
					for (i=numpoints;i>j;i--){
						c[i].x=c[i-1].x;
						c[i].y=c[i-1].y;
					}
					printf("Click to locate the point");
					while(1){
						mb=getmouseloc(&mx,&my);
						if (mb==1){
							c[j].x=mx;
							c[j].y=my;
							while(mb==1)
								mb=getmouseloc(&mx,&my);
							break;
						}
					}
					numpoints++;
					break;
				case 'D':
				case 'd':
					printf("Delete which point: ");
					scanf("%d",&j);
					j--;
					if (j>numpoints || j<0)
						printf("\a");
					else{
						for (i=j+1;i<numpoints;i++){
							c[i-1].x=c[i].x;
							c[i-1].y=c[i].y;
						}
						numpoints--;
					}
					break;
				default:
					continue;
			}
			drawscreen();
			continue;
		}

		if (mb==1){
			if (numpoints==MAXPOINTS){
				printf("\a");
				continue;
			}
			for (i=numpoints;i<MAXPOINTS;i++){
				c[i].x=mx;
				c[i].y=my;
			}
			numpoints++;

			drawscreen();
			while (mb==1)
				mb=getmouseloc(&mx,&my);
		}
		else if (mb==2){
			hidemouse();
			break;
		}
	}

	savenquit();
	return 0;
}