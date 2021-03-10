//Aditya Badayalya, 510819056, Assignment 1
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<GL/glut.h>


int xa = 0,ya = 0,xb = 0,yb = 0,m; 
void drawBRE();
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
    drawBRE();
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

void drawBRE()
{
    drawPoint(xa,ya,4.0);
    //unlike rounding off in the DDA algorithm in this algorithm we take the nearest pixel to the line
    //from the get go and then plot that 
    int diffy = yb - ya, diffx = xb - xa, sx = 1, sy = 1;
    if(diffx < 0)
    {
        sx = -1;//increment values depending upon the initial and terminal point
    }
    if(diffy < 0)
    {
        sy = -1;
    }
    diffy = abs(diffy);
    diffx = abs(diffx);
    int k = 2 * diffy - diffx;//decision variable initial state (always same)
    // the equation for the decision variable is as follows 
    //decision variable = 2*diffy(x) - 2*diffx(y)
    // difference in decision variable = 2*diffy(xnext - x) - 2*diffx(ynext -y);
    if((diffy - diffx) > 0)
    {
        //ie increments in y more than that of x 
        //or slope is greater than 1
        while(ya!=yb)//until the final point
        {
            drawPoint(xa,ya,2.0);
            ya+=sy;//since slope > 1 y will always be incremented unlike x
            if(k>0)
            {
                //if decision variable is > 0 i.e the next x point is closer than the cuurent one
                //for the line to be drawn then x is incremented and the decision variable is updated
                xa+=sx;
                k -= 2*diffy;
            }
            k += 2*diffx;//always
        }
    }
    else 
    {
        while(xa!=xb)
        {
            //slope is less than zero
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
    glutCreateWindow("Bresenham's Line Drawing Algorithm");//title of the window
    gpInit();
    glutMainLoop();
}