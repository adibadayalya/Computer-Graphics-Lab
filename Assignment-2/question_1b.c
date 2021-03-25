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
    int a = xc-xb;
    int b = yc-yb;
    r=a*a+b*b;
    r=sqrt(r);
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

void mouse(int button, int state, int x, int y)
{
    //this function detemines the mouse button that was clicked and performs certain actions accordingly
    y = glutGet(GLUT_WINDOW_HEIGHT) - y;
    //GLUT_RIGHT_BUTTON means the event in case the righ mous ebutton ins pressed
    //GLUT_DOWN means keydown
    if((button == GLUT_RIGHT_BUTTON)&&(state == GLUT_DOWN))
    {
        //clearing the entire window in case of a right click
        glClear(GL_COLOR_BUFFER_BIT);
        drawAxes();
        click = 0;
    }
    if((button == GLUT_LEFT_BUTTON)&&(state == GLUT_DOWN))
    {
        if(click % 2 == 0)
        {
            xc = x-m/2;
            yc = y-m/2;
            //printf("%d %d\n",xc,yc);
        }
        else 
        {
            //last or the end point of the line to be drawn
            xb = x-m/2;
            yb = y-m/2;
            bresenham_circle();//Bresenham's line drawing algorithm
        }
        click++;
    }
    glFlush();//flushes the buffer stream
}

void main(int argc ,char ** argv)
{
    glutInit(&argc,argv);//initialises the GLUT library
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);//used to create a window of different typws as per teh provided flags
    glutInitWindowSize(m, m);//determines the size of the window
    glutInitWindowPosition(0,0);//determines the posirion of the window
    glutCreateWindow("Bresenham's Circle Mouse");//title of the window
    glutMouseFunc(mouse);//function to record data from the mouse
    gpInit();
    glutMainLoop();
}