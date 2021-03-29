#include<stdio.h>
#include<math.h>
#include<GL/glut.h>

int m = 640,click = 0;
int xa=0,ya=0,xb=0,yb=0,xc=0,yc=0;
float radius = 0;


void drawAxes();
void drawPoint(int x, int y, float size);

void drawEllipse(int rx, int ry)
{
   int x = 0, y= ry;
   int xn, yn;
   float parR1 = (ry*ry)-(rx*rx*ry)+0.25*rx*rx;//decision parameter
   float slope = (-2*x*ry*ry)/(2*y*rx*rx);
   while(slope>-1)//R1
   {
       drawPoint(x+xc,y+yc,2.0);
       drawPoint(-x+xc,y+yc,2.0);
       drawPoint(x+xc,-y+yc,2.0);
       drawPoint(-x+xc,-y+yc,2.0);
       xn = x+1;
       if(parR1>0)
       {
           yn = y-1; 
       }
       else 
       {
           yn = y;
       }
       parR1 = parR1 + 2*ry*ry*(x+1) + ry*ry + (rx*rx)*((yn - 0.5)*(yn - 0.5) - (y-0.5)*(y-0.5));
       x = xn;
       y = yn;
       slope = (-2*x*ry*ry)/(2*y*rx*rx);
   }
   //now for R2
   float parR2 = parR1;
   while(y>=0)
   {
       drawPoint(x+xc,y+yc,2.0);
       drawPoint(-x+xc,y+yc,2.0);
       drawPoint(x+xc,-y+yc,2.0);
       drawPoint(-x+xc,-y+yc,2.0);
       yn = y-1;
       if(parR2<=0)
       {
           xn = x+1;
       }
       else 
       {
           xn = x;
       }
       parR2 = parR2 - 2*rx*rx*(y-1) + rx*rx + ry*ry*((xn+0.5)*(xn+0.5)-(x+0.5)*(x+0.5));
       x= xn;
       y= yn;
   }
   glFlush();
}

void mouse(int button, int state, int x, int y)
{
    y = glutGet(GLUT_WINDOW_HEIGHT) - y;
    if((button == GLUT_RIGHT_BUTTON)&&(state == GLUT_DOWN))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        drawAxes();
        click = 0;
    }
    if((button == GLUT_LEFT_BUTTON)&&(state == GLUT_DOWN))
    {
        if(click%2 == 0)
        {
            xc = x-m/2;
            yc = y-m/2;
            drawPoint(xc,yc,4.0);
        }
        else
        {
            int dx = x-m/2 - xc;
            int dy = y-m/2 - yc;
            int f = dx*dx + dy*dy;
            int radius = sqrt(f);
            drawEllipse(2*radius,radius);
        }
        click++;
    }
    glFlush();
}

void gpInit()
{
    glClearColor(1.0,1.0,1.0,0.0);
    glColor3f(0.0f,0.0f,0.0f);
    glEnable(GL_POINT_SMOOTH);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-m/2,m/2,-m/2,m/2);
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
    drawAxes();
}

void drawPoint(int x, int y, float size)
{
    glPointSize(size);
    glBegin(GL_POINTS);
    glVertex2i(x,y);
    glEnd();
}

void drawAxes()
{
    int k =-m/2;
    drawPoint(0,k,2.0);
    while(k<m/2)
    {
        k++;
        drawPoint(0,k,2.0);
    }
    drawPoint(0,m/2,2.0);
    glFlush();
    k = -m/2;
    drawPoint(k,0,2.0);
    while(k<m/2)
    {
        k++;
        drawPoint(k,0,2.0);
    }
    drawPoint(m/2,0,2.0);
    glFlush();
}

void main(int argc, char ** argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(m,m);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Ellipse (rx=2*ry)");
    glutMouseFunc(mouse);
    gpInit();
    glutMainLoop();
}