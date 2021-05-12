//Aditya Badayalya,510819056
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#define WW 640
#define WH 480
#define maxVer 10000
  
FILE *fp;
//start from lower left corner
//edgebucket structure
typedef struct edgebucket 
{
    int ymax;   //max y-coordinate of edge
    float xofymin;  //x-coordinate of lowest edge point updated only in aet
    float slopeinverse;
}EdgeBucket;
  
typedef struct edgetabletup
{
    // the array will give the scanline number
    // The edge table (ET) with edges entries sorted 
    // in increasing y and x of the lower end
      
    int countEdgeBucket;    //no. of edgebuckets
    EdgeBucket buckets[maxVer];
}EdgeTableTuple;

  
EdgeTableTuple EdgeTable[WH], ActiveEdgeTuple;
void initEdgeTable()
{
    int i;
    for (i=0;i<WH; i++)
    {
        EdgeTable[i].countEdgeBucket = 0;
    }
      
    ActiveEdgeTuple.countEdgeBucket = 0;
}
void insertionSort(EdgeTableTuple *ett)
{
    int i,j;
    EdgeBucket temp; 
  
    for (i = 1; i < ett->countEdgeBucket; i++) 
    {
        temp.ymax = ett->buckets[i].ymax;
        temp.xofymin = ett->buckets[i].xofymin;
        temp.slopeinverse = ett->buckets[i].slopeinverse;
        j = i - 1;
  
    while ((temp.xofymin < ett->buckets[j].xofymin) && (j >= 0)) 
    {
        ett->buckets[j + 1].ymax = ett->buckets[j].ymax;
        ett->buckets[j + 1].xofymin = ett->buckets[j].xofymin;
        ett->buckets[j + 1].slopeinverse = ett->buckets[j].slopeinverse;
        j = j - 1;
    }
    ett->buckets[j + 1].ymax = temp.ymax;
    ett->buckets[j + 1].xofymin = temp.xofymin;
    ett->buckets[j + 1].slopeinverse = temp.slopeinverse;
    }
}
  
  
void storeEdgeInTuple (EdgeTableTuple *receiver,int ym,int xm,float slopInv)
{
    //adding new edge
    (receiver->buckets[(receiver)->countEdgeBucket]).ymax = ym;
    (receiver->buckets[(receiver)->countEdgeBucket]).xofymin = (float)xm;
    (receiver->buckets[(receiver)->countEdgeBucket]).slopeinverse = slopInv;
    //sorting acc to y
    insertionSort(receiver);
    (receiver->countEdgeBucket)++; 
}
  
void storeEdgeInTable (int x1,int y1, int x2, int y2)
{
    float m,minv;//minv is slope inverse
    int ymaxTS,xwithyminTS, scanline; //ts stands for to store
    //working out the edge details
    if (x2==x1)
    {
        minv=0.000000;
    }
    else
    {
    m = ((float)(y2-y1))/((float)(x2-x1));
    //horizontal lines are not stored in edge table
    if (y2==y1)
        return;          
    minv = (float)1.0/m;
    }
      
    if (y1>y2)
    {
        scanline=y2;
        ymaxTS=y1;
        xwithyminTS=x2;
    }
    else
    {
        scanline=y1;
        ymaxTS=y2;
        xwithyminTS=x1;     
    }
    storeEdgeInTuple(&EdgeTable[scanline],ymaxTS,xwithyminTS,minv);      
}
  
void removeEdgeByYmax(EdgeTableTuple *Tup,int yy)
{
    int i,j;
    for (i=0; i< Tup->countEdgeBucket; i++)
    {
        if (Tup->buckets[i].ymax == yy)
        {              
            for ( j = i ; j < Tup->countEdgeBucket -1 ; j++ )
                {
                Tup->buckets[j].ymax =Tup->buckets[j+1].ymax;
                Tup->buckets[j].xofymin =Tup->buckets[j+1].xofymin;
                Tup->buckets[j].slopeinverse = Tup->buckets[j+1].slopeinverse;
                }
                Tup->countEdgeBucket--;
            i--;
        }
    }
}     
  
  
void updatexbyslopeinv(EdgeTableTuple *Tup)
{
    int i;
      
    for (i=0; i<Tup->countEdgeBucket; i++)
    {
        (Tup->buckets[i]).xofymin =(Tup->buckets[i]).xofymin + (Tup->buckets[i]).slopeinverse;
    }
}
  
  
void ScanlineFill()
{
    //horizontal edges not included in the edge table
    //horizontal edges drawn at the bottom or at the top
    //vertices: if local max or min then they are ti be counted twice else once is enough
    //either vertices at local minima or local maxima are drawn

    int i, j, x1, ymax1, x2, ymax2, FillFlag = 0, coordCount;
    //starting from 0 (here the bottom as per the window dimenstions)
    for (i=0; i<WH; i++)//4. Increment y by 1 (next scan line)
    {
        //1. Move from ET bucket y to the AET those edges whose ymin = y(entering adges)
        for (j=0; j<EdgeTable[i].countEdgeBucket; j++)
        {
            storeEdgeInTuple(&ActiveEdgeTuple,EdgeTable[i].buckets[j].ymax,EdgeTable[i].buckets[j].xofymin,
                    EdgeTable[i].buckets[j].slopeinverse);
        }
        // 2. Remove from AET those edges for which y=ymax (not involved in next scan line)
        removeEdgeByYmax(&ActiveEdgeTuple, i);
        //sort AET (ET is not presorted)
        insertionSort(&ActiveEdgeTuple);
        //3. Fill lines on scan line y by using pairs of x-coords from AET
        j = 0; 
        FillFlag = 0;
        coordCount = 0;
        x1 = 0;
        x2 = 0;
        ymax1 = 0;
        ymax2 = 0;
        while (j<ActiveEdgeTuple.countEdgeBucket)
        {
            if (coordCount%2==0)
            {
                x1 = (int)(ActiveEdgeTuple.buckets[j].xofymin);
                ymax1 = ActiveEdgeTuple.buckets[j].ymax;
                if (x1==x2)
                {
                    /* three cases can arrive-
                    1. lines are towards top of the intersection
                    2. lines are towards bottom
                    3. one line is towards top and other is towards bottom
                */
                    if (((x1==ymax1)&&(x2!=ymax2))||((x1!=ymax1)&&(x2==ymax2)))
                    {
                        x2 = x1;
                        ymax2 = ymax1;
                    }
                  
                    else
                    {
                        coordCount++;
                    }
                }
                  
                else
                {
                        coordCount++;
                }
            }
            else
            {
                x2 = (int)ActiveEdgeTuple.buckets[j].xofymin;
                ymax2 = ActiveEdgeTuple.buckets[j].ymax; 
                FillFlag = 0;
                if (x1==x2)
                {
                    if (((x1==ymax1)&&(x2!=ymax2))||((x1!=ymax1)&&(x2==ymax2)))
                    {
                        x1 = x2;
                        ymax1 = ymax2;
                    }
                    else
                    {
                        coordCount++;
                        FillFlag = 1;
                    }
                }
                else
                {
                        coordCount++;
                        FillFlag = 1;
                } 
              
              
            if(FillFlag)
            {
                glColor3f(0.00f, 0.35f, 0.45f);
                glBegin(GL_LINES);
                glVertex2i(x1,i);
                glVertex2i(x2,i);
                glEnd();
                glFlush();         
            }
        }
        j++;
    } 
    updatexbyslopeinv(&ActiveEdgeTuple);
}
printf("Scanline filling complete\n");
}
  
  
void myInit(void)
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
	glColor3f(0.0, 0.35, 0.45);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, WW, 0, WH);
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
}
  
void drawPolygon()
{
    glColor3f(0.0f,0.0f,0.0f);
    int count = 0,x1,y1,x2,y2;
    rewind(fp);
    while(!feof(fp) )
    {
        count++;
        if (count>2)
        {
            x1 = x2;
            y1 = y2;
            count=2;
        }
        if (count==1)
        {
            fscanf(fp, "%d %d", &x1, &y1);
            //printf("%d %d\n",x1,y1);
        }
        else
        {
            fscanf(fp, "%d %d", &x2, &y2);
            if(x2==-1)
            {
                x2=x1;
                y2=y1;
                count =0;
            }
            //printf("%d %d\n",x2,y2);
            glBegin(GL_LINES);
                glVertex2i(x1, y1);
                glVertex2i(x2, y2);
            glEnd();
            storeEdgeInTable(x1, y1, x2, y2);//storage of edges in edge table.  
            glFlush();
        }
    }         
}
  
void drawFigure(void)
{
    initEdgeTable();
    drawPolygon();
    ScanlineFill();
}
  
void main(int argc, char** argv)
{
    char fname[64];
    printf("Enter File Name : ");
	scanf("%s", fname);
    fp=fopen (fname,"r");
    if ( fp == NULL )
    {
        printf( "Could not open file" ) ;
        return;
    }
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(WW, WH);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Scan Line Filling");
	myInit();
    glutDisplayFunc(drawFigure);
	glutMainLoop();
	fclose(fp);
}