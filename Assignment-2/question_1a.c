//Aditya Badayalya, 510819056, Assignment 1
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<GL/glut.h>

int click = 0 , xa = 0,ya = 0,xb = 0,yb = 0;
int xc,yc,r,m=640; 
void bresenham_circle();
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
    drawAxes();
    bresenham_circle();
}
void plot_point(int x ,int y)
{
    //plotting 8 points at 45 degeree each
    glPointSize(4.0);
    glBegin(GL_POINTS);
    glVertex2i(xc+x, yc+y);
    glVertex2i(xc+x, yc-y);
    glVertex2i(xc+y, yc+x);
    glVertex2i(xc+y, yc-x);
    glVertex2i(xc-x, yc-y);
    glVertex2i(xc-y, yc-x);
    glVertex2i(xc-x, yc+y);
    glVertex2i(xc-y, yc+x);
    glEnd();
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

void bresenham_circle()
{
    //r = radius
    int x=0,y=r;//init
    float d=(5.0/4.0)-r;//decision parameter
    plot_point(x,y);
    while(x < y)
    {
        x = x + 1;
        if(d < 0)
        d += 2*x+1;
        else
        {
            y = y - 1;
            d = d + 2*(x - y) + 1;
        }
        plot_point(x,y);
    }
    glFlush();
}

void main(int argc ,char ** argv)
{
    printf("Enter the x and y co-ordinates of the center of the circle:\n");
    scanf("%d%d",&xc,&yc);
    printf("Enter the radius of the circle:\n");
    scanf("%d",&r);
    glutInit(&argc,argv);//initialises the GLUT library
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);//used to create a window of different typws as per teh provided flags
    glutInitWindowSize(m,m);//determines the size of the window
    glutInitWindowPosition(0,0);//determines the posirion of the window
    glutCreateWindow("Bressenham's Circle");//title of the window
    gpInit();
    glutMainLoop();
}