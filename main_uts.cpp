#include <graphics.h>
#include <stdio.h>
#include <math.h>

#include <iostream> 

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

#define SIN(x) sin(x * 3.141592653589/180) 
#define COS(x) cos(x * 3.141592653589/180) 

#define ROUND(a) ((int)(a+0.6))
	
using namespace std; 

class centerPoint;
void drawcircle(int x0, int y0, int radius, int color);
void draw_circle_points(int x0, int y0, int x, int y, int color);
void ornamen_islam_rotation(int xCenter, int yCenter, int radius);
void create_ornamen_islam(int xCenter, int yCenter, int start_angle_orn1, int start_angle_orn2, int radius);
void store_centerPoint(int xCenter, int yCenter, int index, centerPoint cpList[]);
void store_cross_points(int x1, int x2, int y1, int y2, struct cross_points cp, int index);
void create_cross_ornamen(centerPoint cpList[], int radiusA, int radiusB, bool color_status);
void create_blinking_circle(int xCenter, int yCenter, int color);
void translationX_animation(centerPoint cpList[], int index);


struct cpStruct {
	int xCenter;
	int yCenter;
};

//centerPoint cpList[20];

class centerPoint {
	private:
	int xCenter, yCenter;
	
	public:
	void setXCenter(int xCenterInput) {
		xCenter = xCenterInput;
	}
	
	int getXCenter() {
		return xCenter;
	}
	
	void setYCenter(int yCenterInput) {
		yCenter = yCenterInput;
	}
	
	int getYCenter() {
		return yCenter;
	}
};

void lineDDA (int xa, int ya, int xb, int yb, int color){
	int dx = xb-xa;
	int dy = yb-ya;
	int steps, dk;
	float xIncrement, yIncrement;
	float x = xa;
	float y = ya;
	
	if (abs(dx) > abs(dy))
	steps = abs(dx);
	else
	steps = abs(dy);
	
	xIncrement = dx / (float) steps;
	yIncrement = dy / (float) steps;
	
	putpixel(ROUND(x), ROUND(y), color);
	for(int k=0; k < steps; k++){
	x += xIncrement;
	y += yIncrement;
	putpixel(ROUND(x), ROUND(y), color);
//	delay(50);
	}
}

// To rotate a line
// by Alif Ramdani
void rotate(int x1, int y1, int *x2, int *y2, int angle, int color) 
{ 
   int Tx, Ty, rotX, rotY, rotX2, rotY2;
   
   Tx = *x2 - x1;
   Ty = *y2 - y1; 
   
   rotX = (Tx*COS(angle)) - (Ty*SIN(angle)) + x1;
   rotY = (Tx*SIN(angle)) + (Ty*COS(angle)) + y1;
   
	putpixel(x1,y1,1);
	putpixel(rotX,rotY,1);
   *x2 = rotX;
   *y2 = rotY; 
} 


void drawcircle(int x0, int y0, int radius, int color)
{
    int x = radius;
    int y = 0;
    int err = 0;
 
    while (x >= y)
    {
		draw_circle_points(x0, y0, x, y, color);
 
		if (err <= 0)
		{
		    y += 1;
		    err += 2*y + 1;
		}
	 
		if (err > 0)
		{
		    x -= 1;
		    err -= 2*x + 1;
		}
//		delay(100);
    }
}

void draw_circle_points(int x0, int y0, int x, int y, int color) {
		putpixel(x0 + x, y0 + y, color);
		putpixel(x0 + y, y0 + x, color);
		putpixel(x0 - y, y0 + x, color);
		putpixel(x0 - x, y0 + y, color);
		putpixel(x0 - x, y0 - y, color);
		putpixel(x0 - y, y0 - x, color);
		putpixel(x0 + y, y0 - x, color);
		putpixel(x0 + x, y0 - y, color);
}

int calculate_screen(int xMax, int yMax) {
	float x;
	float y;
	
	x = ((getmaxx() - 50) / 80);
	y = ((getmaxy() - 50) / 80);
	float hayu = 50/32;
//	printf("Percobaan %f\n", hayu);
//	printf("screenCout %f dan %f\n", x,y);
//	
//	printf("screenCount %f\n", x/y);
	return x/y;
}


//cb = circle-based
//author : Alif Ramdani
void create_cb_square(int centerX, int centerY, int radius, int start_angle, int vertices, int color) {
	int x1, y1, x2, y2;
	int cur_x, cur_y;
	
	cur_x = centerX;
	cur_y = centerY+radius; 
	
	for(int count=1; count<=vertices; count++) {
		if(count == 1) {
			//initial point
			rotate(centerX, centerY, &cur_x, &cur_y, start_angle, color);
			x1 = cur_x;
			y1 = cur_y;
		} 
	
		rotate(centerX, centerY, &cur_x, &cur_y, 360/vertices, color);
		x2 = cur_x;
		y2 = cur_y;
		
//		printf("%d, %d, %d, %d\n",x1,y1,x2,y2);
		lineDDA(x1, y1, x2, y2, color);	
		
		x1 = x2;
		y1 = y2;
	}
}

void ornamen_islam_translation(int xCenter, int yCenter, int *translasiX, int *translasiY) {
	int transX = (getmaxx()/7);
	int transY = (getmaxy()/7);
	if(xCenter+*translasiX >= getmaxx()-50) {
		*translasiY += transY;
		*translasiX = 0;
	}else if(*translasiX == 0) {
		*translasiX = transX;
	}else *translasiX += transX;
}

void create_ornamen_islam(int xCenter, int yCenter, int start_angle_orn1, int start_angle_orn2, int vertices, int radius){
	create_cb_square(xCenter, yCenter, radius, start_angle_orn1, vertices, 14);
	create_cb_square(xCenter, yCenter, radius, start_angle_orn2, vertices, 14);
}

void create_ornamen_islam_pattern(int xCenterStart, int yCenterStart, centerPoint cpList[]) {
	int translasiX = 0;
	int translasiY = 0;
	int index = 0;
	bool create_ornamen = true;
	
	int screenCount = calculate_screen(getmaxx(), getmaxy());
	
	while(index<49) {
//		printf("yCenterStart+translasiY : %d\n", yCenterStart+translasiY);

//		if(xCenterStart+translasiX >= 500) {
//			translasiY += 80;
////			create_ornamen = false;
//		}
//			printf("Center %d dan %d\n", xCenterStart, yCenterStart );
//			printf("Translasi %d dan %d\n", translasiX,translasiY );
//			printf("Pertambahan %d dan %d\n",xCenterStart+translasiX, yCenterStart+translasiY);
			
			
			store_centerPoint(xCenterStart+translasiX, yCenterStart+translasiY, index, cpList);
//			printf("\n\n");
			ornamen_islam_translation(xCenterStart, yCenterStart, &translasiX, &translasiY);
			index++;
		
	}
}

void store_centerPoint(int xCenter, int yCenter, int index, centerPoint cpList[]) {
//	printf("Yang di store %d dan %d\n", xCenter, yCenter);
	
	cpList[index].setXCenter(xCenter);
	cpList[index].setYCenter(yCenter);
	
//	printf("Yang di object %d dan %d", 	cpList[index].getXCenter(), cpList[index].getYCenter());
}

void ornamen_islam_animation(int radius, centerPoint cpList[]) {
	int curr_angle_rotation;
	int max_angle_rotation = 360;
	int page = 0;
	int translasiX = 80;
	int translasiY = 0;
	int index;
	bool create_ornamen = true;
	int radiusA, radiusB;
	bool turn_back = false;
	bool color_status = true;
	int YELLOW = 14;
	int translasiXAnim;
	int LEFT = 1;
	int RIGHT = 2;
	bool change_direction = true;
	int transCount = 0;
	int vertices;
//	int indexTransAnim;
	
	radiusA = (getmaxx()+getmaxy())/240; //5
	radiusB = (getmaxx()+getmaxy())/60; //20
	
	vertices = 4;
	
//	indexTransAnim = 0;
		for(curr_angle_rotation = 0; curr_angle_rotation <= 360; curr_angle_rotation++) {
				
				index=0;
				while(index<50) {
					create_ornamen_islam(cpList[index].getXCenter(), cpList[index].getYCenter(), curr_angle_rotation, curr_angle_rotation+45, vertices, radius);
					create_ornamen_islam(cpList[index].getXCenter(), cpList[index].getYCenter(), curr_angle_rotation, curr_angle_rotation+45, vertices, radius+5);
					create_blinking_circle(cpList[index].getXCenter(), cpList[index].getYCenter(), YELLOW);
					index += 2;
				}
				
				create_cross_ornamen(cpList, radiusA, radiusB, color_status);
				
//				index = 0;
//				while(index<50) {
//					translationX_animation(cpList, index);
//					index++;
//				}
				
				
//				translasiXAnim = 2;
//				index=0;
//				while(index<7) {
////				for(int count = 0; count < 3; count++) {
//					if(!change_direction) {	
//						translationX_animation(cpList, index, translasiXAnim, LEFT);
//						translationX_animation(cpList, index+14, translasiXAnim, LEFT);
//						translationX_animation(cpList, index+28, translasiXAnim, LEFT);
//						translationX_animation(cpList, index+42, translasiXAnim, LEFT);
//						transCount++;
//					} else {
//						translationX_animation(cpList, index, translasiXAnim, RIGHT);
//						translationX_animation(cpList, index+14, translasiXAnim, RIGHT);
//						translationX_animation(cpList, index+28, translasiXAnim, RIGHT);
//						translationX_animation(cpList, index+42, translasiXAnim, RIGHT);
//						transCount++;
//					}
//					index++;
//				}
//				}
				
//				if(transCount >= 100) {
//					transCount = 0;
//					if(change_direction == false) {
//						change_direction = true;
//					} else change_direction = false;
//				}
				
				
//				create_blinking_circle(cpList[index].getXCenter(), cpList[index].getYCenter());
//				lineDDA(cpList[1].getXCenter(), cpList[1].getYCenter(), cpList[41].getXCenter(), cpList[41].getYCenter(), 14);
				
				if(radiusA < 15 && !turn_back) {
					if(radiusA >= 3) {
						color_status = true;
					}
					radiusA += 3;
					radiusB += 3;
				} else {
					if(radiusA >= 15) {
						turn_back = true;
					}
					radiusA -= 3;
					radiusB -= 3;
					if(radiusA < 3) {
						color_status = false;
					}
					if(radiusA <= 0) {
						turn_back = false;
					}
				}
				
				curr_angle_rotation += 10; 
				if(curr_angle_rotation >= 360) {
					curr_angle_rotation = 0;
				}
				delay(1);
				setactivepage(page);        
				setvisualpage(1-page);
		        page = 1 - page;
				cleardevice();
//				index++;
//				indexTransAnim++;
		}
}

//Cross-Ornamen

class cross_points {
	private:
	int x1;
	int y1;
	int x2;
	int y2;
	
	public:
	void setX1(int x) {
		x1 = x;
	}
	
	int getX1() {
		return x1;
	}
	
	void setY1(int y) {
		y1 = y;
	}
	
	int getY1() {
		return y1;
	}
	
	void setX2(int x) {
		x2 = x;
	}
	
	int getX2() {
		return x2;
	}
	
	void setY2(int y) {
		y2 = y;
	}
	
	int getY2() {
		return y2;
	}
	
};

void get_cross_point(int centerX, int centerY, int radius, int start_angle, 
					cross_points cp[], int color) {
	int x1, y1, x2, y2;
	int cur_x, cur_y;
	int index;
	
	cur_x = centerX;
	cur_y = centerY+radius; 
	
	for(int count=1; count<=4; count++) {
		if(count == 1) {
			//initial point
			rotate(centerX, centerY, &cur_x, &cur_y, start_angle, color);
			x1 = cur_x;
			y1 = cur_y;
		} 
	
		rotate(centerX, centerY, &cur_x, &cur_y, 90, color);
		x2 = cur_x;
		y2 = cur_y;
		
		index = count-1;
//		lineDDA(x1, y1, x2, y2, 14);
		
		cp[index].setX1(x1);
		cp[index].setY1(y1);
		cp[index].setX2(x2);
		cp[index].setY2(y2);
		
		x1 = x2;
		y1 = y2;
	}
}

//void store_cross_points(int x1, int x2, int y1, int y2, cross_points cp[], int index) {
//		cp[index].setX1 = x1;
//		cp[index].setY1 = y1;
//		cp[index].setX2 = x2;
//		cp[index].setY2 = y2;
//}

void create_cross_ornamen(centerPoint cpList[], int radiusA, int radiusB, bool color_status) {
	int YELLOW = 14;
	int idx = 0;
	int index = 1;
	int idxadd;
	
 	cross_points ccp[4]; //cross center point
	cross_points cpp[4]; //cross peak point
	
	int screenCount = calculate_screen(getmaxx(), getmaxy());
	
	while(index<50) {
		//mendapatkan titik 
			get_cross_point(cpList[index].getXCenter(), cpList[index].getYCenter(), radiusA, 0, ccp, YELLOW);
			get_cross_point(cpList[index].getXCenter(), cpList[index].getYCenter(), radiusB, 45, cpp, YELLOW);
			
			//gambar crossnya
			
			setfillstyle(SOLID_FILL, YELLOW);
			while(idx<4) {
			switch (idx) {
				case 0 : idxadd = 2; break;
				case 1 : idxadd = 3; break;
				case 2 : idxadd = 0; break;
				case 3 : idxadd = 1; break;
			}
			lineDDA(cpp[idx].getX1(), cpp[idx].getY1(), ccp[idx].getX2(), ccp[idx].getY2(), YELLOW);
			lineDDA(cpp[idx].getX1(), cpp[idx].getY1(), ccp[idxadd].getX2(), ccp[idxadd].getY2(), YELLOW);
			idx++;	
			}
			if(color_status) {
				floodfill(cpList[index].getXCenter(), cpList[index].getYCenter(),YELLOW);
			} 
	
		index += 2;
		idx = 0;
	}
}

void line_pattern(centerPoint cpList[]) {
//	lineDDA(cpList[])
}

void create_blinking_circle(int xCenter, int yCenter, int color) {
	int radius = 10;
	int YELLOW = 14;
	setfillstyle(SOLID_FILL, color);
	drawcircle(xCenter, yCenter, radius, color);
	floodfill(xCenter, yCenter, color);
}

void translationX_animation(centerPoint cpList[], int index) {
		int xCenter = cpList[index].getXCenter();
//	if(direction == 1) {
	if(cpList[index].getYCenter() <= 50 && cpList[index].getXCenter() <= getmaxx()-50) {
		cpList[index].setXCenter(cpList[index].getXCenter() + 2);
	} else if(cpList[index].getYCenter() >= getmaxy()-49 && cpList[index].getXCenter() >= 50) {
		cpList[index].setXCenter(cpList[index].getXCenter() - 2);	
	} else if(cpList[index].getXCenter() >= getmaxx()-50) {
		cpList[index].setYCenter(cpList[index].getYCenter() + 2);
	} else if(cpList[index].getXCenter() <= 50 ) {
		cpList[index].setYCenter(cpList[index].getYCenter() - 2);
	}
//	cpList[index].setYCenter(cpList[index].getYCenter() + translasiX);
}

int main() {
	int h, w, xCenter, yCenter, radius;
	
//	h=w=600;
	printf("masukan height : ");
	scanf("%d", &h);
	printf("masukan width : ");
	scanf("%d", &w);
	initwindow(h, w,"UTS Praktikum Komputer Grafik 171511036 - Alif Ramdani");
//	initgraph();
	
	setbkcolor(BLUE);
	
	int screenCount = calculate_screen(getmaxx(), getmaxy());
	
	centerPoint cpList[50];
	
	xCenter = yCenter = getmaxx()/12;
	radius = (getmaxx()+getmaxy())/40;
	
	create_ornamen_islam_pattern(xCenter,yCenter,cpList);
	
	ornamen_islam_animation(radius,cpList);
	
	
	getch();
	closegraph();

}



