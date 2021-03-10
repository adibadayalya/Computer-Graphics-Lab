//Aditya Badayalya, 510819056, Assignment 1
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<GL/glut.h>


int xa = 0,ya = 0,xb = 0,yb = 0,m; 
void drawDDA();
void drawAxes();
void gpInit()
{
    //setting up parameters in the window
	glClearColor(1.0, 1.0, 1.0, 0.0);//background color
	glColor3f(0.0f, 0.0f, 0.0f);//point color?
	glEnable(GL_POINT_SMOOTH);//eabling stuff here enabling to draw points with proper filtering
	glMatrixMode(GL_PROJECTION);//sets the current matrix mode here GL_PROJECTION applies subsequent matrix operations to project matrix stack
	glLoadIdentity();//replaces the current mateix with identity matrix
	gluOrtho2D(-m/2, m/2, -m/2,m/2);//sets 2 dimenstion orthographic region parameters as = (left, right, bottom ,top)
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
    drawDDA();
    drawAxes();
}

void drawPoint(int x, int y, float size)
{
    glPointSize(size);//setting point size
    glBegin(GL_POINTS);//specifies the way in which the vertex is to be interpretes i.e as point
    glVertex2i(x,y);//specifies the point
    glEnd();//end
}

void drawAxes()
{
    int k = -m/2;
    drawPoint(0,k,4.0);
    while(k<m/2)
    {
        k++;
        drawPoint(0,k,2.0);
    }
    drawPoint(0,m/2,4.0);
    glFlush();
    k = -m/2;
    drawPoint(k,0,4.0);
    while(k<m/2)
    {
        k++;
        drawPoint(k,0,2.0);
    }
    drawPoint(m/2,0,4.0);
    glFlush();
}
void drawDDA()
{
    drawPoint(xa,ya,4.0);
    int diffy = yb-ya, diffx = xb-xa, sx = 1, sy = 1;
    float slope = fabs(diffy)/fabs(diffx), dx = 0, dy = 0;
    //determing the proper increment as per the conditions
    if(diffx==0)
    {
        //line parallel to y axis
        dx = 0;
        dy = 1;
    }
    else if(diffy==0)
    {
        //line parallel to x axis
        dx = 1;
        dy = 0;
    }
    else if(slope < 1)
    {
        //difference between x greater than difference between y
        //making proper increment values
        dx = 1;
        dy = slope;
    }
    else 
    {
        //difference between y greater than difference between x
        //making proper increment values
        dy = 1;
        dx = 1/slope;
    }
    if(diffx < 0)
    {
        sx = -1;//determining the direction to head to ie left or right left being negative
    }
    if(diffy < 0)
    {
        sy = -1;//determining the direction to head to up or down down being negative(?)
    }
    float x = xa , y = ya;
    while(1)
    {
        //incremnting to the next point on the said line
        x += (sx * dx);
        y += (sy * dy);
        //drawing the next point on the line
        drawPoint(round(x),round(y),2.0);//drawing a point
        //checking if we have reached the end of line
        if((round(x)==xb)&&(round(y)==yb))//rounding off and checking for the end point
        break;
    }
    drawPoint(xb,yb,4.0);
    glFlush();
}

void main(int argc ,char ** argv)
{
    printf("Enter the window size:\n");
    scanf("%d",&m);
    printf("Enter the value of xa and ya:\n");
    scanf("%d%d",&xa,&ya);
    printf("Enter the value of xb and yb:\n");
    scanf("%d%d",&xb,&yb);
    glutInit(&argc,argv);//initialises the GLUT library
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);//used to create a window of different typws as per teh provided flags
    glutInitWindowSize(m,m);//determines the size of the window
    glutInitWindowPosition(0,0);//determines the posirion of the window
    glutCreateWindow("DDA Line Drawing Algorithm");//title of the window
    gpInit();
    glutMainLoop();
}