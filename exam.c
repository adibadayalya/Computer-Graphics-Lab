//Aditya Badayalya, 510819056
#include <stdio.h>
#include <GL/glut.h>

#define WW 800
#define WH 800

void mouse(int button, int state, int x, int y);
void gppDisplay();
void gpDisplay();
void gpInit();
int main(int argc, char *argv[]){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(WW, WH);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("FOOTBALL FIELD");
	glutDisplayFunc(gpDisplay);
    glutMouseFunc(mouse);
	gpInit();
	glutMainLoop();
}
void gpDisplay()
{
    gppDisplay();
}
void gpInit(){
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glColor3f(0.0, 0.35, 0.45);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-WW/2, WW/2, -WW/2,WW/2);
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
}
int xc,yc,r;
void plot_point(int x ,int y)
{
    //plotting 8 points at 45 degeree each
    glPointSize(2.0);
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

void semi_circle(int x, int y)
{
    glPointSize(2.0);
    glBegin(GL_POINTS);
    glVertex2i(xc+x, yc+y);
    glVertex2i(xc+x, yc-y);
    glVertex2i(xc+y, yc+x);
    glVertex2i(xc+y, yc-x);
    glEnd();
}
void semi_circle2(int x, int y)
{
    glPointSize(2.0);
    glBegin(GL_POINTS);
    glVertex2i(xc-x, yc-y);
    glVertex2i(xc-y, yc-x);
    glVertex2i(xc-x, yc+y);
    glVertex2i(xc-y, yc+x);
    glEnd();
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

void bre_semi()
{
    int x=0,y=r;//init
    float d=(5.0/4.0)-r;//decision parameter
    semi_circle(x,y);
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
        semi_circle(x,y);
    }
    glFlush();   
}
void bre_semi2()
{
    int x=0,y=r;//init
    float d=(5.0/4.0)-r;//decision parameter
    semi_circle2(x,y);
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
        semi_circle2(x,y);
    }
    glFlush();   
}

int ya,xa;
void playerR()
{
    glBegin(GL_POLYGON);
    glVertex2i(278,-4);
    glVertex2i(275,-4);
    glVertex2i(275,4);
    glVertex2i(278,4);
	glEnd();
    glBegin(GL_POLYGON);
    glVertex2i(220,-20);
    glVertex2i(215,-20);
    glVertex2i(215,-16);
    glVertex2i(220,-16);
	glEnd();
    glBegin(GL_POLYGON);
    glVertex2i(220,-50);
    glVertex2i(215,-50);
    glVertex2i(215,-44);
    glVertex2i(220,-44);
	glEnd();
    glBegin(GL_POLYGON);
    glVertex2i(220,20);
    glVertex2i(215,20);
    glVertex2i(215,16);
    glVertex2i(220,16);
	glEnd();
    glBegin(GL_POLYGON);
    glVertex2i(220,50);
    glVertex2i(215,50);
    glVertex2i(215,44);
    glVertex2i(220,44);
	glEnd();
      glBegin(GL_POLYGON);
    glVertex2i(120,-20);
    glVertex2i(115,-20);
    glVertex2i(115,-16);
    glVertex2i(120,-16);
	glEnd();
    glBegin(GL_POLYGON);
    glVertex2i(120,-50);
    glVertex2i(115,-50);
    glVertex2i(115,-44);
    glVertex2i(120,-44);
	glEnd();
    glBegin(GL_POLYGON);
    glVertex2i(120,20);
    glVertex2i(115,20);
    glVertex2i(115,16);
    glVertex2i(120,16);
	glEnd();
    glBegin(GL_POLYGON);
    glVertex2i(120,50);
    glVertex2i(115,50);
    glVertex2i(115,44);
    glVertex2i(120,44);
	glEnd();
    glBegin(GL_POLYGON);
    glVertex2i(40,20);
    glVertex2i(45,20);
    glVertex2i(45,16);
    glVertex2i(40,16);
	glEnd();
    glBegin(GL_POLYGON);
    glVertex2i(40,-20);
    glVertex2i(45,-20);
    glVertex2i(45,-16);
    glVertex2i(40,-16);
	glEnd();
}

void playerL()
{
    glBegin(GL_POLYGON);
    glVertex2i(-278,-4);
    glVertex2i(-275,-4);
    glVertex2i(-275,4);
    glVertex2i(-278,4);
	glEnd();
    glBegin(GL_POLYGON);
    glVertex2i(-220,-20);
    glVertex2i(-215,-20);
    glVertex2i(-215,-16);
    glVertex2i(-220,-16);
	glEnd();
    glBegin(GL_POLYGON);
    glVertex2i(-220,-50);
    glVertex2i(-215,-50);
    glVertex2i(-215,-44);
    glVertex2i(-220,-44);
	glEnd();
    glBegin(GL_POLYGON);
    glVertex2i(-220,20);
    glVertex2i(-215,20);
    glVertex2i(-215,16);
    glVertex2i(-220,16);
	glEnd();
    glBegin(GL_POLYGON);
    glVertex2i(-220,50);
    glVertex2i(-215,50);
    glVertex2i(-215,44);
    glVertex2i(-220,44);
	glEnd();
      glBegin(GL_POLYGON);
    glVertex2i(-120,-20);
    glVertex2i(-115,-20);
    glVertex2i(-115,-16);
    glVertex2i(-120,-16);
	glEnd();
    glBegin(GL_POLYGON);
    glVertex2i(-120,-50);
    glVertex2i(-115,-50);
    glVertex2i(-115,-44);
    glVertex2i(-120,-44);
	glEnd();
    glBegin(GL_POLYGON);
    glVertex2i(-120,20);
    glVertex2i(-115,20);
    glVertex2i(-115,16);
    glVertex2i(-120,16);
	glEnd();
    glBegin(GL_POLYGON);
    glVertex2i(-120,50);
    glVertex2i(-115,50);
    glVertex2i(-115,44);
    glVertex2i(-120,44);
	glEnd();
    glBegin(GL_POLYGON);
    glVertex2i(-40,20);
    glVertex2i(-45,20);
    glVertex2i(-45,16);
    glVertex2i(-40,16);
	glEnd();
    glBegin(GL_POLYGON);
    glVertex2i(-40,-20);
    glVertex2i(-45,-20);
    glVertex2i(-45,-16);
    glVertex2i(-40,-16);
	glEnd();
}

void gppDisplay(){
    glColor3f(0.6,0.4,0.12);
	glBegin(GL_POLYGON);
    glVertex2i(-350,-300);
    glVertex2i(350,-300);
    glVertex2i(350,300);    
    glVertex2i(-350,300);
	glEnd();
	glFlush();
    glColor3f(0.0, 0.35, 0.0);
	glBegin(GL_POLYGON);
    glVertex2i(-300,-140);
    glVertex2i(300,-140);
    glVertex2i(300,140);
    glVertex2i(-300,140);
	glEnd();
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINES);
    glVertex2f(0, -140);
    glVertex2f(0, 140);
    glEnd();
    xc=0,yc=0,r=20;
    bresenham_circle();
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINES);
    glVertex2i(-300,-110);
    glVertex2i(-250,-110);
    glVertex2i(-250,110);
    glVertex2i(-300,110);
	glEnd();
    glBegin(GL_LINES);
    glVertex2i(-250,-110);
    glVertex2i(-250,110);
    glEnd();
    glBegin(GL_LINES);
    glVertex2i(300,-110);
    glVertex2i(250,-110);
    glVertex2i(250,110);
    glVertex2i(300,110);
	glEnd();
    glBegin(GL_LINES);
    glVertex2i(250,-110);
    glVertex2i(250,110);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2i(-300,-35);
    glVertex2i(-280,-35);
    glVertex2i(-280,35);
    glVertex2i(-300,35);
	glEnd();
    glBegin(GL_POLYGON);
    glVertex2i(300,-35);
    glVertex2i(280,-35);
    glVertex2i(280,35);
    glVertex2i(300,35);
	glEnd();
    yc=0,xc=-250,r=20;
    bre_semi();
    yc=0,xc=250,r=20;
    bre_semi2();
    yc=0,xc=-265,r=1;
    bresenham_circle();
    yc=0,xc=265,r=1;
    bresenham_circle();
    glColor3f(1.0, 1.0, 0.0);
    playerR();
    glColor3f(0.0, 0.0, 0.0);
    playerL();
    glColor3f(1.0, 1.0, 1.0);
    xc=0,yc=0,r=2;
    bresenham_circle();
    glFlush();
}
int click=0,m=800,xb,yb;
void moveBall();
void drawPoint(int x, int y, float size)
{
    glColor3f(1.0,1.0, 0.0);
    glPointSize(size);//setting point size
    glBegin(GL_POINTS);//specifies the way in which the vertex is to be interpretes i.e as point
    glVertex2i(x,y);//specifies the point
    glEnd();//end
}
void mouse(int button, int state, int x, int y)
{
    y = glutGet(GLUT_WINDOW_HEIGHT) - y;
    if((button == GLUT_RIGHT_BUTTON)&&(state == GLUT_DOWN))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        gppDisplay();
        click = 0;
    }
    if((button == GLUT_LEFT_BUTTON)&&(state == GLUT_DOWN))
    {
        if(click%2 != 0)
        {
            xb = x-m/2;
            yb = y-m/2;
            moveBall();
            //gppDisplay();
            bresenham_circle();
        }
        else 
        {
            //last or the end point of the line to be drawn
            glColor3f(0.0, 0.35, 0.0);
            bresenham_circle();
            xa = x-m/2;
            ya = y-m/2;
            xc=xa,yc=ya;
            r=2;
            glColor3f(1.0, 1.0, 1.0);
            bresenham_circle();//Bresenham's line drawing algorithm
        }
        click++;
    }

    glFlush();//flushes the buffer stream
}
void moveBall()
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
            glColor3f(1.0, 0.0, 0.0);
            drawPoint(xa,ya,4.0);
            xc=xa,yc=ya;
            glColor3f(1.0, 1.0, 1.0);
            bresenham_circle();
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
            //slope is less than zero
            glColor3f(1.0, 0.0, 0.0);
            drawPoint(xa,ya,4.0);
            xc=xa,yc=ya;
            glColor3f(1.0, 1.0, 1.0);
            bresenham_circle();
            xa+=sx;
            if(k > 0)
            {
                ya+=sy;
                k -= 2*diffx;
            }
            k += 2*diffy;
        }
    }
    glColor3f(1.0, 0.0, 0.0);
    drawPoint(xa,ya,4.0);
    xc=xb,yc=yb;
    glColor3f(1.0, 1.0, 1.0);
    bresenham_circle();
}