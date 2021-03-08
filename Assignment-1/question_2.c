//Aditya Badayalya, 510819056, Assignment 1
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<GL/glut.h>


int click = 0 , xa = 0,ya = 0,xb = 0,yb = 0; 

void gpInit()
{
    //setting up parameters in the window
	glClearColor(1.0, 1.0, 1.0, 0.0);//background color
	glColor3f(0.0f, 0.0f, 0.0f);//point color?
	glEnable(GL_POINT_SMOOTH);//eabling stuff here enabling to draw points with proper filtering
	glMatrixMode(GL_PROJECTION);//sets the current matrix mode here GL_PROJECTION applies subsequent matrix operations to project matrix stack
	glLoadIdentity();//replaces the current mateix with identity matrix
	gluOrtho2D(0.0, 640.0, 0.0, 480.0);//sets 2 dimenstion orthographic region parameters as = (left, right, bottom ,top)
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
}

void drawPoint(int x, int y, float size)
{
    glPointSize(size);//setting point size
    glBegin(GL_POINTS);//specifies the way in which the vertex is to be interpretes i.e as point
    glVertex2i(x,y);//specifies the point
    glEnd();//end 
}

void drawBRE()
{
    int diffy = yb - ya, diffx = xb - xa, sx = 1, sy = 1;
    if(diffx < 0)
    {
        sx = -1;
    }
    if(diffy < 0)
    {
        sy = -1;
    }
    diffy = abs(diffy);
    diffx = abs(diffx);
    int k = 2 * diffy - diffx;
    if((diffy - diffx) > 0)
    {
        while(ya!=yb)
        {
            drawPoint(xa,ya,2.0);
            ya+=sy;
            if(k>0)
            {
                xa+=sx;
                k -= 2*diffy;
            }
            k += 2*diffx;
        }
    }
    else 
    {
        while(xa!=xb)
        {
            drawPoint(xa,ya,2.0);
            xa+=sx;
            if(k > 0)
            {
                ya+=sy;
                k -= 2*diffx;
            }
            k += 2*diffy;
        }
    }
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
        click = 0;
    }
    if((button == GLUT_LEFT_BUTTON)&&(state == GLUT_DOWN))
    {
        if(click % 2 == 0)
        {
            //staring  or the first point of the line to be drawn
            xa = x;
            ya = y;
        }
        else 
        {
            //last or the end point of the line to be drawn
            xb = x;
            yb = y;
            drawBRE();//DDA line drawing algorithm
        }
        drawPoint(x,y,4.0);//drawing a point
        click++;
    }
    glFlush();//flushes the buffer stream
}

void main(int argc ,char ** argv)
{
    glutInit(&argc,argv);//initialises the GLUT library
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);//used to create a window of different typws as per teh provided flags
    glutInitWindowSize(640, 480);//determines the size of the window
    glutInitWindowPosition(0,0);//determines the posirion of the window
    glutCreateWindow("Bresenham's Line Drawing Algorithm");//title of the window
    glutMouseFunc(mouse);//function to record data from the mouse
    gpInit();
    glutMainLoop();
}