// Βενιόπουλος Δημήτρης 3610
#include <GL/glut.h>
#include <GL/glu.h>
#include <stdlib.h>

int createNewFractal = 1;
int i[10000];
int rgb[10000][3];
int numberOfPoints = 10000;
float r = 1.0 / 3.0;
int old_x;
int old_y;
int new_x = 0;
int new_y = 0;


void initialize()
{
    glEnable(GL_BLEND);
    glClearColor(0, 0, 0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 500);
    glMatrixMode(GL_MODELVIEW);

}

void display()
{
   if (createNewFractal)
        glColor3ub( rand() % 255, rand() % 255, rand() % 255 );

    typedef GLfloat point2[2];
    point2 pentagon[5] = {{400.0,600.0},
                          {100.0, 400.0},
                          {200.0, 100.0},
                          {600.0, 100.0},
                          {700.0,400.0}};


    point2 p = { 300.0, 300.0};

    glClear(GL_COLOR_BUFFER_BIT);

    if (createNewFractal)
        for (int k = 0; k < numberOfPoints; k++){
            i[k] = rand() % 5;
            rgb[k][1] = rand() % 255;
            rgb[k][2] = rand() % 255;
            rgb[k][3] = rand() % 255;
        }

    for( int k = 0; k < numberOfPoints; k++)
    {
        p[0] = (p[0] + pentagon[i[k]][0]) * r;
        p[1] = (p[1] + pentagon[i[k]][1]) * r;
        glBegin(GL_POINTS);
        glVertex2fv(p);
        if (numberOfPoints == 10000){
            if (createNewFractal)
                glColor3ub( rand() % 255, rand() % 255, rand() % 255 );
            else
                glColor3ub(rgb[k][1], rgb[k][2], rgb[k][3] );
        }
        glEnd();
    }

    glFlush();
}

void menu(int id){

    createNewFractal = 1;
    if (id == 1)
        exit(0);
    else if (id == 2)
        numberOfPoints = 8000;
    else if (id == 3)
        numberOfPoints = 10000;
    else if (id == 4){
        r = 1.0 / 3.0;
        createNewFractal = 0;
    }
    else if (id == 5){
        r = 3.0 / 8.0;
        createNewFractal = 0;
    }

    display();
    glutSwapBuffers();
}

void mouseCallback(int button, int state, int x, int y){
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        old_x = x;
        old_y = y;
        createNewFractal = 0;
    }
}

void motionCallback(int x, int y){

    new_x += (x - old_x);
    new_y -= (y - old_y);
    glViewport(new_x, new_y, 500, 500);
    display();
    glutSwapBuffers();

    old_x = x;
    old_y = y;
}

int main(int argc, char** argv) {

    glutInit(&argc,argv);
    glutInitDisplayMode (GLUT_DOUBLE| GLUT_RGB);
    glutInitWindowSize(500,500); /* 500 x 500 pixel window */
    glutInitWindowPosition(600,300); /* place window top left on display */
    glutCreateWindow("Pentagon"); /* Window title */
    glutDisplayFunc(display); /* display callback invoked when window opened */
    initialize(); /* set attributes */
    display();
    glutSwapBuffers();

    glutCreateMenu(menu);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    glutAddMenuEntry("Quit", 1);
    glutAddMenuEntry("8000 points", 2);
    glutAddMenuEntry("10000 points", 3);
    glutAddMenuEntry("r = 1/3", 4);
    glutAddMenuEntry("r = 3/8", 5);

    glutMouseFunc(mouseCallback);
    glutMotionFunc(motionCallback);

    glutMainLoop();

    return 0;
}
