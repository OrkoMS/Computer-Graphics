#include<stdio.h>
#include <stdlib.h>
#include<windows.h>
#include<GL/gl.h>
#include <GL/glut.h>
#include<math.h>
#include<cstring>

void road();
void signal();
void car();
void car2();
void mydisplay();
void display();
void frontsreen();
void drawstring();
void setFont();
void myMouse();
void myinit();
void update(int);
void control();
void controlsScreen();
GLint a=-300,b=300,flag=0,traffic_regulator=1,control_keyl,control_keyr;
GLfloat red=0,blue=1,green=.3;
GLfloat p=0,q=0,r=1;
GLfloat distance=0, btnvalue=0;
//-----------
void *currentfont;

void setFont(void *font)
{
	currentfont=font;
}

void drawstring(float x,float y,float z,char *string)
{
	char *c;
	glRasterPos3f(x,y,z);

	for(c=string;*c!='\0';c++)
	{
		glutBitmapCharacter(currentfont,*c);
	}
}

void startscreen(void)
{
    setFont(GLUT_BITMAP_TIMES_ROMAN_24);
    glClearColor(0.000, 0.000, 0.804,0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1,0,0);
    drawstring(350.0,700.0,0.0,"AMERICAN INTERNATIONAL UNIVERSITY-BANGLADESH");
    glColor3f(0.7,0,1);
    drawstring(330,650,0.0,"DEPARTMENT OF COMPUTER SCIENCE AND ENGINEERING");
    glColor3f(1,0.5,0);
    drawstring(600,530,0.0,"PROJECT ON");
    glColor3f(1,0,0);
    drawstring(340,500,0.0,"COMPUTER GRAPHICS: TRAFFIC SIGNALS MANAGEMENT");
    glColor3f(1,0.5,0);
    drawstring(270,400,0.0,"SUBMITTED BY:");
    glColor3f(1,1,1);
    drawstring(100,370,0.0,"ORKO, MAHABUB SOBHAN  (13-25055-3)");
    glColor3f(1,0.5,0);
    drawstring(950,400,0.0,"SUBMITTED TO:");
    glColor3f(1,1,1);
    drawstring(980,370,0.0,"NO ONE");
    glColor3f(1,0.1,1);
    drawstring(543,100,0.0,"PRESS ENTER TO START");
    glFlush();
}

void controlsScreen()
{
    setFont(GLUT_BITMAP_TIMES_ROMAN_24);
    glClearColor(0.000, 0.392, 0.000,0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.596, 0.984, 0.596);
    drawstring(600.0,700.0,0.0,"TIPS");
    glColor3f(1.000, 0.980, 0.941);
    drawstring(250.0,640.0,0.0,"Stop the traffic (Red Light)                                  MOUSE LEFT CLICK");
    glColor3f(1.000, 0.980, 0.941);
    drawstring(250.0,600.0,0.0,"Yellow Signal                                                        MOUSE RIGHT BUTTON (HOLD ON)");
    glColor3f(1.000, 0.980, 0.941);
    drawstring(250.0,560.0,0.0,"Green Signal                                                         MOUSE RIGHT BUTTON (RELEASE)");
    glColor3f(1.000, 0.980, 0.941);
    drawstring(250.0,520.0,0.0,"Allow vehicles to MOVE left to right                  PRESS 'L'");
    glColor3f(1.000, 0.980, 0.941);
    drawstring(250.0,480.0,0.0,"Allow vehicles to MOVE right to left                  PRESS 'R'");
    glColor3f(1.000, 0.980, 0.941);
    drawstring(250.0,440.0,0.0,"Speed up the vehicles                                           PRESS 'S'");
    glColor3f(1.000, 0.980, 0.941);
    drawstring(250.0,400.0,0.0,"Help                                                                      PRESS 'H'");
    glColor3f(1.000, 0.980, 0.941);
    drawstring(250.0,360.0,0.0,"Escape                                                                  PRESS 'ESC'");
    glColor3f(0.596, 0.984, 0.596);
    glColor3f(1.000, 0.980, 0.941);
    drawstring(250.0,320.0,0.0,"Return to Start Screen                                         PRESS 'O'");
    drawstring(400.0,200.0,0.0,"NOW PRESS ENTER TO START THE SYSTEM");
    glFlush();
}

void control()
{
	if(control_keyl!='l'||control_keyr!='r')
	{
	if(control_keyl=='l')
        a=a-6;
	if(control_keyr=='r')
        b=b+6;
	}

}

void myKeyboard( unsigned char key, int x, int y )
{
    switch(key)
    {
        case 27:
            exit(0);
        break;
        case 13:
            if(flag==1)
            {
                flag=2;
                mydisplay();
            }
            if(flag==0)
            {
                flag=1;
                mydisplay();
            }
        break;
        case 'l':
            control_keyl=key;
            p=0;q=0;r=1;
        break;
        case 'r':
            control_keyr=key;
            p=0;q=0;r=1;
        break;
        case 's':
            mydisplay();
        break;
        case 'h':
            flag=1;
            mydisplay();
        break;
        case 'o':
            flag=0;
            mydisplay();
        break;

        default:
        break;
    }
}

void myMouse(int button,int state,int x,int y)
{
	if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
	{
	    btnvalue=1.0;
	    p=1;
        q=0;
        r=0;
	}

	if(button==GLUT_RIGHT_BUTTON && state==GLUT_DOWN)
	{
        traffic_regulator=0;
        p=0;
        q=1;
        r=0;
	}
	if(button==GLUT_RIGHT_BUTTON && state==GLUT_UP)
	{
        traffic_regulator=1;
        p=0;
        q=0;
        r=1;
	}

	glutPostRedisplay();
}

void mydisplay(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    if(flag==0)
        startscreen();
    if(flag==1)
        controlsScreen();
    if(flag==2)
        display();
    glutSwapBuffers();
}

void update(int value)
{
    a=a+10;
    control();
    if(blue!=0&&green!=0)
    {
        blue-=.004;green-=.004;
    }
    glutPostRedisplay();
}

void display(void)
{
	if(traffic_regulator)
        glutTimerFunc(50,update,0);
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(red,green,blue,0);
    road();
    signal();
    car();
    car2();

    glFlush();
}

void road()
{
    glPushMatrix();
    glScaled(40.0,40.0,0.0);
    glColor3f(0.1,0.1,0.1);
    glBegin(GL_POLYGON);
    //straight road
        glVertex2f(0,5);
        glVertex2f(40,5);
        glVertex2f(40,10);
        glVertex2f(0,10);
    glEnd();
    //gray edge
    glBegin(GL_POLYGON);
    glColor3f(0.412, 0.412, 0.412);
        glVertex2f(0,5);
        glVertex2f(40,5);
        glVertex2f(40,4);
        glVertex2f(0,4);
    glEnd();
    //strip road
    glLineWidth(10);
    glColor3f(1.0, 1.0, 1.0);
    glLineStipple(15, 0xAAAA);
    glEnable(GL_LINE_STIPPLE);
    glBegin(GL_LINES);
        glVertex2f(0, 7.5);
        glVertex2f(40, 7.5);
    glEnd();
    glDisable(GL_LINE_STIPPLE);

    glPopMatrix();
}

void signal()
{
    glPushMatrix();
    glScaled(40.0,40.0,0.0);
    //stand
    //glColor3f(0.612, 0.612, 0.412);
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
        glVertex2f(15,7);
        glVertex2f(15,8);
        glVertex2f(18,8);
        glVertex2f(18,7);
    glEnd();
    //pole
    glBegin(GL_POLYGON);
        glVertex2f(16,7);
        glVertex2f(17,8);
        glVertex2f(17,15);
        glVertex2f(16,15);
    glEnd();
    //board
    glBegin(GL_POLYGON);
        glVertex2f(15.5,15);
        glVertex2f(17.5,15);
        glVertex2f(17.5,10);
        glVertex2f(15.5,10);
    glEnd();
    //red
    glColor3f(p,0.0,0.0);
    glBegin(GL_POLYGON);
        glVertex2f(16,14.5);
        glVertex2f(17,14.5);
        glVertex2f(17,14);
        glVertex2f(16,14);
    glEnd();
    //yellow
    glColor3f(q,q,0.0);
    glBegin(GL_POLYGON);
        glVertex2f(16,13.5);
        glVertex2f(17,13.5);
        glVertex2f(17,13);
        glVertex2f(16,13);
    glEnd();
    //green
    glColor3f(0.0,r,0.0);
    glBegin(GL_POLYGON);
        glVertex2f(16,12.5);
        glVertex2f(17,12.5);
        glVertex2f(17,12);
        glVertex2f(16,12);
    glEnd();
    //test collide box
    glColor3f(0.0,0.0,0.0);
    glBegin(GL_POINT);
        glVertex2f(16,8);
        //glVertex2f(17,8.5);
        //glVertex2f(17,8);
        //glVertex2f(16,8);
    glEnd();
    glPopMatrix();
}

void car()
{
    GLfloat x1=a-160,y1=7;
    glLineWidth(2);
    glPushMatrix();
    glTranslated(a,190.0,0.0);
    glScaled(20.0,20.0,0.0);
    glColor3f(1.0,1.0,1.0);
    //making color for outer line

    glBegin(GL_POINT);
        glVertex2f(x1,y1);
    glEnd();
    distance = sqrt((x1-16.0)*(x1-16.0)+(y1-8.0)*(y1-8.0));
    printf("%f\n",distance);
    if(distance<6 && distance>3 && btnvalue==1.0)
        {
            traffic_regulator=0;
        }
    glColor3f(1.0,0.0,0.0);
    glBegin(GL_POLYGON);
        glVertex2f(2.5,2.5);
        glVertex2f(3.0,3.5);
        glVertex2f(3.5,3.75);
        glVertex2f(4.0,4.0);
        glVertex2f(4.5,4.0);
        glVertex2f(5.0,3.75);
        glVertex2f(5.5,3.5);
        glVertex2f(5.75,3.0);
        glVertex2f(6.0,2.5);
        glVertex2f(16.5,2.5);
        glVertex2f(16.75,3.0);
        glVertex2f(17.0,3.5);
        glVertex2f(17.5,3.75);
        glVertex2f(18.0,4.0);
        glVertex2f(18.5,4.0);
        glVertex2f(19.0,3.75);
        glVertex2f(19.5,3.5);
        glVertex2f(19.75,3.0);
        glVertex2f(20.0,2.5);
        glVertex2f(21.0,2.5);
        glVertex2f(21.1,4.0);
        glVertex2f(21.2,4.0);
        glVertex2f(21.0,4.5);
        glVertex2f(20.0,5.0);
        glVertex2f(15.0,5.0);
        glVertex2f(14.0,5.5);
        glVertex2f(13.0,6.0);
        glVertex2f(12.0,6.5);
        glVertex2f(11.0,7.0);
        glVertex2f(6.0,7.0);
        glVertex2f(5.0,6.5);
        glVertex2f(4.5,6.25);
        glVertex2f(4.25,6.0);
        glVertex2f(4.0,5.75);
        glVertex2f(3.5,5.5);
        glVertex2f(3.0,5.5);
        glVertex2f(1.9,5.45);
        glVertex2f(1.8,5.4);
        glVertex2f(1.7,5.35);
        glVertex2f(1.6,5.3);
        glVertex2f(1.5,5.25);
        glVertex2f(1.4,5.15);
        glVertex2f(1.3,5.0);
        glVertex2f(1.2,4.85);
        glVertex2f(1.1,4.7);
        glVertex2f(1.0,4.3);
        glVertex2f(1.0,3.2);
        glVertex2f(1.1,3.05);
        glVertex2f(1.2,2.9);
        glVertex2f(1.3,2.9);
        glVertex2f(1.4,2.75);
        glVertex2f(1.5,2.65);
        glVertex2f(1.6,2.6);
        glVertex2f(1.7,2.55);
        glVertex2f(1.8,2.5);
        glVertex2f(1.9,2.45);
        glVertex2f(2.0,2.5);
    glEnd();
    //color for outer window
    glColor3f(1.0,1.0,1.0);
    glBegin(GL_POLYGON);
        glVertex2f(5.0,5.0);
        glVertex2f(14.0,5.0);
        glVertex2f(11.5,6.5);
        glVertex2f(10.5,6.75);
        glVertex2f(7.0,6.75);
    glEnd();
    //making outer line for car
    glColor3f(0.0,0.0,0.0);
    glBegin(GL_LINE_LOOP);
        glVertex2f(2.5,2.5);
        glVertex2f(3.0,3.5);
        glVertex2f(3.5,3.75);
        glVertex2f(4.0,4.0);
        glVertex2f(4.5,4.0);
        glVertex2f(5.0,3.75);
        glVertex2f(5.5,3.5);
        glVertex2f(5.75,3.0);
        glVertex2f(6.0,2.5);
        glVertex2f(16.5,2.5);
        glVertex2f(16.75,3.0);
        glVertex2f(17.0,3.5);
        glVertex2f(17.5,3.75);
        glVertex2f(18.0,4.0);
        glVertex2f(18.5,4.0);
        glVertex2f(19.0,3.75);
        glVertex2f(19.5,3.5);
        glVertex2f(19.75,3.0);
        glVertex2f(20.0,2.5);
        glVertex2f(21.0,2.5);
        glVertex2f(21.1,4.0);
        glVertex2f(21.2,4.0);
        glVertex2f(21.0,4.5);
        glVertex2f(20.0,5.0);
        glVertex2f(15.0,5.0);
        glVertex2f(14.0,5.5);
        glVertex2f(13.0,6.0);
        glVertex2f(12.0,6.5);
        glVertex2f(11.0,7.0);
        glVertex2f(6.0,7.0);
        glVertex2f(5.0,6.5);
        glVertex2f(4.5,6.25);
        glVertex2f(4.25,6.0);
        glVertex2f(4.0,5.75);
        glVertex2f(3.5,5.5);
        glVertex2f(3.0,5.5);
        glVertex2f(1.9,5.45);
        glVertex2f(1.8,5.4);
        glVertex2f(1.7,5.35);
        glVertex2f(1.6,5.3);
        glVertex2f(1.5,5.25);
        glVertex2f(1.4,5.15);
        glVertex2f(1.3,5.0);
        glVertex2f(1.2,4.85);
        glVertex2f(1.1,4.7);
        glVertex2f(1.0,4.3);
        glVertex2f(1.0,3.2);
        glVertex2f(1.1,3.05);
        glVertex2f(1.2,2.9);
        glVertex2f(1.3,2.9);
        glVertex2f(1.4,2.75);
        glVertex2f(1.5,2.65);
        glVertex2f(1.6,2.6);
        glVertex2f(1.7,2.55);
        glVertex2f(1.8,2.5);
        glVertex2f(1.9,2.45);
        glVertex2f(2.0,2.5);
    glEnd();
    //outer line for design the car
    glColor3f(0.0,0.0,0.0);
    glBegin(GL_LINE_LOOP);
        glVertex2f(8.0,3.0);
        glVertex2f(16.0,3.0);
        glVertex2f(16.5,3.5);
        glVertex2f(17.0,4.0);
        glVertex2f(16.5,4.25);
        glVertex2f(16.0,4.5);
        glVertex2f(15.0,4.5);
        glVertex2f(15.0,5.0);
        glVertex2f(14.0,5.0);
        glVertex2f(11.5,6.5);
        glVertex2f(10.5,6.75);
        glVertex2f(7.0,6.75);
        glVertex2f(5.0,5.0);
        glVertex2f(7.0,5.0);
        glVertex2f(6.5,4.5);
    glEnd();

    //connecting outer line
    glBegin(GL_LINES);
        glVertex2d(7.0,5.0);
        glVertex2d(15.0,5.0);
    glEnd();
    //connecting outer line
    glColor3f(0.0,0.0,0.0);
    glBegin(GL_LINES);
        glVertex2d(15.0,4.0);
        glVertex2d(17.0,4.0);
    glEnd();
    //connecting outer line
    glColor3f(0.0,0.0,0.0);
    glBegin(GL_LINES);
        glVertex2d(15.0,3.5);
        glVertex2d(16.5,3.5);
    glEnd();
    //connecting outer line
    glColor3f(0.0,0.0,0.0);
    glBegin(GL_LINES);
        glVertex2d(15.0,5.0);
        glVertex2d(14.0,3.0);
    glEnd();

    //connecting outer line
    glColor3f(0.0,0.0,0.0);
    glBegin(GL_LINES);
        glVertex2d(12.0,5.0);
        glVertex2d(12.0,6.2);
    glEnd();
    //connecting outer line
    glColor3f(0.0,0.0,0.0);
    glBegin(GL_LINES);
        glVertex2d(7.0,5.0);
        glVertex2d(7.0,6.7);
    glEnd();
    //Head Light
    glColor3f(1.0,1.0,0.0);
    glBegin(GL_POLYGON);
        glVertex2d(19.5,4.3);
        glVertex2d(20.5,4.3);
        glVertex2d(20.5,3.8);
    glEnd();
    if(q>0)
    {
        glLineWidth(2);
        glColor3f(1.0, 1.0, 1.0);
        glLineStipple(2, 0xAAAA);
        glEnable(GL_LINE_STIPPLE);
        glBegin(GL_LINES);
            glVertex2f(0.8, 3.2);
            glVertex2f(0.0, 3.2);
        glEnd();
        glBegin(GL_LINES);
            glVertex2f(0.8, 3.5);
            glVertex2f(0.2, 3.5);
        glEnd();
        glBegin(GL_LINES);
            glVertex2f(0.8, 3.8);
            glVertex2f(0.4, 3.8);
        glEnd();
        glBegin(GL_LINES);
            glVertex2f(-0.2, 3.2);
            glVertex2f(-0.8, 3.2);
        glEnd();
        glBegin(GL_LINES);
            glVertex2f(0.0, 3.5);
            glVertex2f(-0.6, 3.5);
        glEnd();
        glBegin(GL_LINES);
            glVertex2f(0.2, 3.8);
            glVertex2f(-0.4, 3.8);
        glEnd();
        glDisable(GL_LINE_STIPPLE);
    }
    //drawing a back wheel
    glColor3f(0.0,0.0,0.0);
    glTranslatef(4.2, 2.3, 0.0);
    glBegin(GL_POLYGON);
        for(int i=0;i<200;i++)
	{
		float pi=3.1416;
		float A=(i*2*pi)/50 ;
		float r=1.3;
		float x = r * cos(A);
		float y = r * sin(A);
		glVertex2f(x,y );
	}
    glEnd();

    //drawing front wheel
    glTranslatef(14.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
        for(int i=0;i<200;i++)
	{
		float pi=3.1416;
		float A=(i*2*pi)/50 ;
		float r=1.3;
		float x = r * cos(A);
		float y = r * sin(A);
		glVertex2f(x,y );
	}
    glEnd();

    glPopMatrix();
}
void car2()
{
    GLfloat x1=a-1660,y1=7;
    glPushMatrix();
    glTranslated(a-1500,190.0,0.0);
    glScaled(20.0,20.0,0.0);
    //making color for outer line
    glColor3f(0.000, 0.000, 0.0);
    glBegin(GL_POLYGON);
    glVertex2f(x1,y1);
    glEnd();
    distance = sqrt((x1-16.0)*(x1-16.0)+(y1-8.0)*(y1-8.0));
    printf("%f\n",distance);
    if(distance<6 && distance>3 && btnvalue==1.0)
    {
        traffic_regulator=0;
    }
    glColor3f(0.000, 0.000, 0.804);
    glBegin(GL_POLYGON);
        glVertex2f(2.5,2.5);
        glVertex2f(3.0,3.5);
        glVertex2f(3.5,3.75);
        glVertex2f(4.0,4.0);
        glVertex2f(4.5,4.0);
        glVertex2f(5.0,3.75);
        glVertex2f(5.5,3.5);
        glVertex2f(5.75,3.0);
        glVertex2f(6.0,2.5);
        glVertex2f(16.5,2.5);
        glVertex2f(16.75,3.0);
        glVertex2f(17.0,3.5);
        glVertex2f(17.5,3.75);
        glVertex2f(18.0,4.0);
        glVertex2f(18.5,4.0);
        glVertex2f(19.0,3.75);
        glVertex2f(19.5,3.5);
        glVertex2f(19.75,3.0);
        glVertex2f(20.0,2.5);
        glVertex2f(21.0,2.5);
        glVertex2f(21.1,4.0);
        glVertex2f(21.2,4.0);
        glVertex2f(21.0,4.5);
        glVertex2f(20.0,5.0);
        glVertex2f(15.0,5.0);
        glVertex2f(14.0,5.5);
        glVertex2f(13.0,6.0);
        glVertex2f(12.0,6.5);
        glVertex2f(11.0,7.0);
        glVertex2f(6.0,7.0);
        glVertex2f(5.0,6.5);
        glVertex2f(4.5,6.25);
        glVertex2f(4.25,6.0);
        glVertex2f(4.0,5.75);
        glVertex2f(3.5,5.5);
        glVertex2f(3.0,5.5);
        glVertex2f(1.9,5.45);
        glVertex2f(1.8,5.4);
        glVertex2f(1.7,5.35);
        glVertex2f(1.6,5.3);
        glVertex2f(1.5,5.25);
        glVertex2f(1.4,5.15);
        glVertex2f(1.3,5.0);
        glVertex2f(1.2,4.85);
        glVertex2f(1.1,4.7);
        glVertex2f(1.0,4.3);
        glVertex2f(1.0,3.2);
        glVertex2f(1.1,3.05);
        glVertex2f(1.2,2.9);
        glVertex2f(1.3,2.9);
        glVertex2f(1.4,2.75);
        glVertex2f(1.5,2.65);
        glVertex2f(1.6,2.6);
        glVertex2f(1.7,2.55);
        glVertex2f(1.8,2.5);
        glVertex2f(1.9,2.45);
        glVertex2f(2.0,2.5);
    glEnd();
    //color for outer window
    glColor3f(1.0,1.0,1.0);
    glBegin(GL_POLYGON);
        glVertex2f(5.0,5.0);
        glVertex2f(14.0,5.0);
        glVertex2f(11.5,6.5);
        glVertex2f(10.5,6.75);
        glVertex2f(7.0,6.75);
    glEnd();
    //making outer line for car
    glColor3f(0.0,0.0,0.0);
    glBegin(GL_LINE_LOOP);
        glVertex2f(2.5,2.5);
        glVertex2f(3.0,3.5);
        glVertex2f(3.5,3.75);
        glVertex2f(4.0,4.0);
        glVertex2f(4.5,4.0);
        glVertex2f(5.0,3.75);
        glVertex2f(5.5,3.5);
        glVertex2f(5.75,3.0);
        glVertex2f(6.0,2.5);
        glVertex2f(16.5,2.5);
        glVertex2f(16.75,3.0);
        glVertex2f(17.0,3.5);
        glVertex2f(17.5,3.75);
        glVertex2f(18.0,4.0);
        glVertex2f(18.5,4.0);
        glVertex2f(19.0,3.75);
        glVertex2f(19.5,3.5);
        glVertex2f(19.75,3.0);
        glVertex2f(20.0,2.5);
        glVertex2f(21.0,2.5);
        glVertex2f(21.1,4.0);
        glVertex2f(21.2,4.0);
        glVertex2f(21.0,4.5);
        glVertex2f(20.0,5.0);
        glVertex2f(15.0,5.0);
        glVertex2f(14.0,5.5);
        glVertex2f(13.0,6.0);
        glVertex2f(12.0,6.5);
        glVertex2f(11.0,7.0);
        glVertex2f(6.0,7.0);
        glVertex2f(5.0,6.5);
        glVertex2f(4.5,6.25);
        glVertex2f(4.25,6.0);
        glVertex2f(4.0,5.75);
        glVertex2f(3.5,5.5);
        glVertex2f(3.0,5.5);
        glVertex2f(1.9,5.45);
        glVertex2f(1.8,5.4);
        glVertex2f(1.7,5.35);
        glVertex2f(1.6,5.3);
        glVertex2f(1.5,5.25);
        glVertex2f(1.4,5.15);
        glVertex2f(1.3,5.0);
        glVertex2f(1.2,4.85);
        glVertex2f(1.1,4.7);
        glVertex2f(1.0,4.3);
        glVertex2f(1.0,3.2);
        glVertex2f(1.1,3.05);
        glVertex2f(1.2,2.9);
        glVertex2f(1.3,2.9);
        glVertex2f(1.4,2.75);
        glVertex2f(1.5,2.65);
        glVertex2f(1.6,2.6);
        glVertex2f(1.7,2.55);
        glVertex2f(1.8,2.5);
        glVertex2f(1.9,2.45);
        glVertex2f(2.0,2.5);
    glEnd();
    //outer line for design the second car
    glColor3f(0.0,0.0,0.0);
    glBegin(GL_LINE_LOOP);
        glVertex2f(8.0,3.0);
        glVertex2f(16.0,3.0);
        glVertex2f(16.5,3.5);
        glVertex2f(17.0,4.0);
        glVertex2f(16.5,4.25);
        glVertex2f(16.0,4.5);
        glVertex2f(15.0,4.5);
        glVertex2f(15.0,5.0);
        glVertex2f(14.0,5.0);
        glVertex2f(11.5,6.5);
        glVertex2f(10.5,6.75);
        glVertex2f(7.0,6.75);
        glVertex2f(5.0,5.0);
        glVertex2f(7.0,5.0);
        glVertex2f(6.5,4.5);
    glEnd();

    //connecting outer line
    glBegin(GL_LINES);
        glVertex2d(7.0,5.0);
        glVertex2d(15.0,5.0);
    glEnd();
    //connecting outer line
    glColor3f(0.0,0.0,0.0);
    glBegin(GL_LINES);
        glVertex2d(15.0,4.0);
        glVertex2d(17.0,4.0);
    glEnd();
    //connecting outer line
    glColor3f(0.0,0.0,0.0);
    glBegin(GL_LINES);
        glVertex2d(15.0,3.5);
        glVertex2d(16.5,3.5);
    glEnd();
    //connecting outer line
    glColor3f(0.0,0.0,0.0);
    glBegin(GL_LINES);
        glVertex2d(15.0,5.0);
        glVertex2d(14.0,3.0);
    glEnd();
    //connecting outer line
    glColor3f(0.0,0.0,0.0);
    glBegin(GL_LINES);
        glVertex2d(12.0,5.0);
        glVertex2d(12.0,6.2);
    glEnd();
    //connecting outer line
    glColor3f(0.0,0.0,0.0);
    glBegin(GL_LINES);
        glVertex2d(7.0,5.0);
        glVertex2d(7.0,6.7);
    glEnd();
    //Head Light
    glColor3f(1.0,1.0,0.0);
    glBegin(GL_POLYGON);
        glVertex2d(19.5,4.3);
        glVertex2d(20.5,4.3);
        glVertex2d(20.5,3.8);
    glEnd();
    if(q>0)
    {
        glLineWidth(2);
        glColor3f(1.0, 1.0, 1.0);
        glLineStipple(2, 0xAAAA);
        glEnable(GL_LINE_STIPPLE);
        glBegin(GL_LINES);
            glVertex2f(0.8, 3.2);
            glVertex2f(0.0, 3.2);
        glEnd();
        glBegin(GL_LINES);
            glVertex2f(0.8, 3.5);
            glVertex2f(0.2, 3.5);
        glEnd();
        glBegin(GL_LINES);
            glVertex2f(0.8, 3.8);
            glVertex2f(0.4, 3.8);
        glEnd();
        glBegin(GL_LINES);
            glVertex2f(-0.2, 3.2);
            glVertex2f(-0.8, 3.2);
        glEnd();
        glBegin(GL_LINES);
            glVertex2f(0.0, 3.5);
            glVertex2f(-0.6, 3.5);
        glEnd();
        glBegin(GL_LINES);
            glVertex2f(0.2, 3.8);
            glVertex2f(-0.4, 3.8);
        glEnd();
        glDisable(GL_LINE_STIPPLE);
    }
    //drawing a back wheel
    glColor3f(0.0,0.0,0.0);
    glTranslatef(4.2, 2.3, 0.0);
    glBegin(GL_POLYGON);
        for(int i=0;i<200;i++)
	{
		float pi=3.1416;
		float A=(i*2*pi)/50 ;
		float r=1.3;
		float x = r * cos(A);
		float y = r * sin(A);
		glVertex2f(x,y );
	}
    glEnd();

    //drawing front wheel
    glTranslatef(14.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
        for(int i=0;i<200;i++)
	{
		float pi=3.1416;
		float A=(i*2*pi)/50 ;
		float r=1.3;
		float x = r * cos(A);
		float y = r * sin(A);
		glVertex2f(x,y );
	}
    glEnd();

    glPopMatrix();
}

void myinit()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0,1346.0,0.0,728.0);

}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1346,728);
    glutInitWindowPosition(0,0);
    glutCreateWindow("SHOHAIL TAMIM's APP");
    glutDisplayFunc(mydisplay);
    glutKeyboardFunc(myKeyboard);
    glutMouseFunc(myMouse);
    myinit();
    glutMainLoop();
}
