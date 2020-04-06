#define PROGRAM_TITLE "Cass Pros Battle Humm"
#define DISPLAY_INFO "CPSC 3710"
#include "objects.cpp"

#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <GLUT/GLUT.h>
#include <OpenGL/glu.h>
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#include <GL/glut.h>
#include <GL/glu.h>
#endif

#include <iostream>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "BuildingBuilder.hpp"

#define PI 3.1415927

int BLOCK_SIZE = 20;

int Window_ID;
int Window_Width = 1280;
int Window_Height = 720;

int fkey = 1; // camera angle starts at the '1' position. This position is
                    // behind the robots head

bool pausedState; // game starts unpaused and is controlled by 'p' key to change
                  // this state

void moveCam(int); // forward declaration of moveCam function.

bool headTurnR = false; // can head turn right
bool headTurnL = false; // can head turn left
bool robRotR = false;    // is robot rotating right
bool robRotL = false;    // is robot rotating left
bool robNorth = true;    // is robot facing north (starts off north)
bool robEast = false;    // is robot facing east
bool robSouth = false;    // is robot facing south
bool robWest = false;    // is robot facing west
int offAddz = 5;        // we start off facing north so we want to be able to move that
                        // direction, this is used for movement/camera on z key
int offAddx = 0;        // same as offAddz
int randNums[400];        // array to hold random numbers generated for building
                        // generation
int buildHits[400];        // sister array to hold hit values of buildings so they can
                        // be destroyed.
Car car;            // robot object to do most functions.
BuildingBuilder builder;

int eyeX = 5, eyeY = 8,eyeZ = -45;
int atX = 0, atY = 0, atZ = 0;
float upX = 0, upY = 1, upZ = 0;

int offsetX, offsetY, offsetZ;
int GROUND_LEVEL = 0.5;
int frame_count = 0;
float rotateRect = 0.4;
float rotateCyil = 0.5;
float antRot = 90;
float bodyAngle = 90;
int cx = 4.0;
int cy = 0.0;
int  cz = -20.0;

bool isNorth = true;
bool isWest = false;
bool isSouth = false;
bool isEast = false;

static void PrintString(void *font, char *str)
{
    int i, len = strlen(str);

    for (i = 0; i < len; i++)
        glutBitmapCharacter(font, *str++);
}

void renderCar() { // function for drawing the Car into the world
    float theta,angle;
    int frame_count;

    // cube begin
    glLoadIdentity();
    gluLookAt(eyeX + offsetX, eyeY + offsetY, eyeZ + offsetZ, atX, atY, atZ, upX, upY, upZ);

    glTranslatef(GROUND_LEVEL+cx,GROUND_LEVEL,GROUND_LEVEL+cz);      // translate to Cars current position
    glRotatef(bodyAngle, 0, 1, 0); // for when Car is turning to left or right
    glTranslatef(0,0,0);         // translate to 0, 0, 0 first for if Car is turning
    glScalef(3.0,3.0,3.0);
    glEnable(GL_COLOR_MATERIAL);

    // begin the body of the Car
    glBegin(GL_QUADS);
    /* top of cube*/
    //************************FRONT BODY****************************************
    glColor3f(0.1,1.0,0.5);
    glVertex3f( 0.2, 0.4,0.6);
    glVertex3f(0.6, 0.5,0.6);
    glVertex3f(0.6, 0.5,0.2);
    glVertex3f( 0.2,0.4,0.2);
    /* bottom of cube*/
    glVertex3f( 0.2,0.4,0.6);
    glVertex3f(0.6,0.2,0.6);
    glVertex3f(0.6,0.2,0.2);
    glVertex3f( 0.2,0.2,0.2);
    /* front of cube*/
    glVertex3f( 0.2,0.2,0.6);
    glVertex3f(0.2, 0.4,0.6);
    glVertex3f(0.2,0.4,0.2);
    glVertex3f( 0.2,0.2,0.2);
    /* back of cube.*/
    glVertex3f(0.6,0.2,0.6);
    glVertex3f(0.6,0.5,0.6);
    glVertex3f(0.6,0.5,0.2);
    glVertex3f( 0.6,0.2,0.2);
    /* left of cube*/
    glVertex3f(0.2,0.2,0.6);
    glVertex3f(0.6,0.2,0.6);
    glVertex3f(0.6,0.5,0.6);
    glVertex3f(0.2,0.4,0.6);
    /* Right of cube */
    glVertex3f(0.2,0.2,0.2);
    glVertex3f( 0.6,0.2,0.2);
    glVertex3f( 0.6,0.5,0.2);
    glVertex3f( 0.2,0.4,0.2);

    //****************************************************************************
    glVertex3f(0.7,0.65,0.6);
    glVertex3f(0.7,0.65,0.2);
    glVertex3f(1.7,0.65,0.2);
    glVertex3f(1.7,0.65,0.6);

    //***************************back guard******************************
    // You can change r, g, b to different colors.
    glColor3f(0.1,1.0,0.5);
    glVertex3f( 1.8, 0.5,0.6);
    glVertex3f(1.8, 0.5,0.2);
    glVertex3f(2.1, 0.4, 0.2);
    glVertex3f(2.1,0.4,0.6);
    /* bottom of cube*/
    glVertex3f( 2.1,0.2,0.6);
    glVertex3f(2.1,0.2,0.2);
    glVertex3f(1.8,0.2,0.6);
    glVertex3f( 1.8,0.2,0.6);
    /* back of cube.*/
    glVertex3f(2.1,0.4,0.6);
    glVertex3f(2.1,0.4,0.2);
    glVertex3f(2.1,0.2,0.2);
    glVertex3f(2.1,0.2,0.6);
    /* left of cube*/
    glVertex3f(1.8,0.2,0.2);
    glVertex3f(1.8,0.5,0.2);
    glVertex3f(2.1,0.4,0.2);
    glVertex3f(2.1,0.2,0.2);
    /* Right of cube */
    glVertex3f(1.8,0.2,0.6);
    glVertex3f(1.8,0.5,0.6);
    glVertex3f(2.1,0.4,0.6);
    glVertex3f(2.1,0.2,0.6);

    //******************MIDDLE BODY************************************
    glVertex3f( 0.6, 0.5,0.6);
    glVertex3f(0.6, 0.2,0.6);
    glVertex3f(1.8, 0.2, 0.6);
    glVertex3f(1.8,0.5,0.6);
    

    /* bottom of cube*/
    glVertex3f( 0.6,0.2,0.6);
    glVertex3f(0.6,0.2,0.2);
    glVertex3f(1.8,0.2,0.2);
    glVertex3f( 1.8,0.2,0.6);

    /* back of cube.*/
    glVertex3f(0.6,0.5,0.2);
    glVertex3f(0.6,0.2,0.2);
    glVertex3f(1.8,0.2,0.2);
    glVertex3f(1.8,0.5,0.2);

    //*********************ENTER WINDOW**********************************
    glColor3f(0.3,0.3,0.3);
    glVertex3f( 0.77, 0.63,0.2);
    glVertex3f(0.75, 0.5,0.2);        //quad front window
    glVertex3f(1.2, 0.5, 0.2);
    glVertex3f( 1.22,0.63,0.2);

    glVertex3f(1.27,0.63,.2);
    glVertex3f(1.25,0.5,0.2);        //quad back window
    glVertex3f(1.65,0.5,0.2);
    glVertex3f(1.67,0.63,0.2);

    glColor3f(0.1,1.0,0.5);
    glVertex3f(0.7,0.65,0.2);
    glVertex3f(0.7,0.5,.2);       //first separation
    glVertex3f(0.75,0.5,0.2);
    glVertex3f(0.77,0.65,0.2);

    glVertex3f(1.2,0.65,0.2);
    glVertex3f(1.2,0.5,.2);       //second separation
    glVertex3f(1.25,0.5,0.2);
    glVertex3f(1.27,0.65,0.2);

    glVertex3f(1.65,0.65,0.2);
    glVertex3f(1.65,0.5,.2);     //3d separation
    glVertex3f(1.7,0.5,0.2);
    glVertex3f(1.7,0.65,0.2);

    glVertex3f( 0.75, 0.65,0.2);
    glVertex3f(0.75, 0.63,0.2);        //line strip
    glVertex3f(1.7, 0.63, 0.2);
    glVertex3f( 1.7,0.65,0.2);

    glVertex3f( 0.75, 0.65,0.6);
    glVertex3f(0.75, 0.63,0.6);        //line strip
    glVertex3f(1.7, 0.63, 0.6);
    glVertex3f( 1.7,0.65,0.6);

    glColor3f(0.3,0.3,0.3);
    glVertex3f( 0.77, 0.63,0.6);
    glVertex3f(0.75, 0.5,0.6);        //quad front window
    glVertex3f(1.2, 0.5, 0.6);
    glVertex3f( 1.22,0.63,0.6);

    glVertex3f(1.27,0.63,.6);
    glVertex3f(1.25,0.5,0.6);        //quad back window
    glVertex3f(1.65,0.5,0.6);
    glVertex3f(1.67,0.63,0.6);

    glColor3f(0.1,1.0,0.5);
    glVertex3f(0.7,0.65,0.6);
    glVertex3f(0.7,0.5,.6);       //first separation
    glVertex3f(0.75,0.5,0.6);
    glVertex3f(0.77,0.65,0.6);

    glVertex3f(1.2,0.65,0.6);
    glVertex3f(1.2,0.5,.6);       //second separation
    glVertex3f(1.25,0.5,0.6);
    glVertex3f(1.27,0.65,0.6);

    glVertex3f(1.65,0.65,0.6);
    glVertex3f(1.65,0.5,.6);
    glVertex3f(1.7,0.5,0.6);
    glVertex3f(1.7,0.65,0.6);
    glEnd();


    //**************************************************************
    glBegin(GL_QUADS);

    /* top of cube*/
    glColor3f(0.3,0.3,0.3);
    glVertex3f( 0.6, 0.5,0.6);
    glVertex3f(0.6, 0.5,0.2);        //quad front window
    glVertex3f(0.7, 0.65, 0.2);
    glVertex3f( 0.7,0.65,0.6);

    glVertex3f(1.7,0.65,.6);
    glVertex3f(1.7,0.65,0.2);        //quad back window
    glVertex3f(1.8,0.5,0.2);
    glVertex3f(1.8,0.5,0.6);

    glEnd();

    glBegin(GL_TRIANGLES);                /* start drawing the cube.*/
    /* top of cube*/
    glColor3f(0.3,0.3,0.3);
    glVertex3f( 0.6, 0.5,0.6);
    glVertex3f( 0.7,0.65,0.6);       //tri front window
    glVertex3f(0.7,0.5,0.6);

    glVertex3f( 0.6, 0.5,0.2);
    glVertex3f( 0.7,0.65,0.2);       //tri front window
    glVertex3f(0.7,0.5,0.2);

    glVertex3f( 1.7, 0.65,0.2);
    glVertex3f( 1.8,0.5,0.2);       //tri back window
    glVertex3f( 1.7,0.5,0.2);

    glVertex3f( 1.7, 0.65,0.6);
    glVertex3f( 1.8,0.5,0.6);       //tri back window
    glVertex3f(1.7,0.5,0.6);
    glEnd();

    //******************ATENNA BODY************************************
    glPushMatrix();
    glColor3f(0.3,0.3,0.7);
    glTranslatef(1.5,0.8,0.45);
    glRotatef(90.0,1.0,0,0);
    gluCylinder(gluNewQuadric(),0.02,0.03,.5,10,10);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.0,0.3,0.3);
    glTranslatef(1.5,1.0,0.45);
    glRotatef(antRot,0.0f,1.0f,0.0f);
    glutWireSphere(0.2,25,25);
    glPopMatrix();
    //*****************************************************************

    glColor3f(0.7,0.7,0.7);
    glPushMatrix();
    glBegin(GL_LINE_STRIP);
    
    for(theta=0;theta<360;theta=theta+40) {
        glVertex3f(0.6,0.2,0.62);
        glVertex3f(0.6+(0.08*(cos(((theta+angle)*3.14)/180))),0.2+(0.08*(sin(((theta+angle)*3.14)/180))),0.62);
    }
    glEnd();

    glBegin(GL_LINE_STRIP);
    
    for(theta=0;theta<360;theta=theta+40) {
        glVertex3f(0.6,0.2,0.18);
        glVertex3f(0.6+(0.08*(cos(((theta+angle)*3.14)/180))),0.2+(0.08*(sin(((theta+angle)*3.14)/180))),0.18);
    }
    glEnd();

    glBegin(GL_LINE_STRIP);
    
    for(theta=0;theta<360;theta=theta+40) {
        glVertex3f(1.7,0.2,0.18);
        glVertex3f(1.7+(0.08*(cos(((theta+angle)*3.14)/180))),0.2+(0.08*(sin(((theta+angle)*3.14)/180))),0.18);
    }
    glEnd();

    glBegin(GL_LINE_STRIP);
    
    for(theta=0;theta<360;theta=theta+40) {
        glVertex3f(1.7,0.2,0.62);
        glVertex3f(1.7+(0.08*(cos(((theta+angle)*3.14)/180))),0.2+(0.08*(sin(((theta+angle)*3.14)/180))),0.62);
    }
    glEnd();

    glTranslatef(0.6,0.2,0.6);
    glColor3f(0,0,0);
    glutSolidTorus(0.025,0.07,10,25);

    glTranslatef(0,0,-0.4);
    glutSolidTorus(0.025,0.07,10,25);

    glTranslatef(1.1,0,0);
    glutSolidTorus(0.025,0.07,10,25);

    glTranslatef(0,0,0.4);
    glutSolidTorus(0.025,0.07,10,25);
    //*************************************************************
    glPopMatrix();
    glEnable(GL_DEPTH_TEST);
    glutPostRedisplay();

    frame_count++;
    if (frame_count % 10 == 0) {
        antRot += 30;
        frame_count = 0;
        if (antRot > 360) {
            antRot = 0;
        }
    }
  }

void renderSphe(int x, int z) {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(eyeX + offsetX, eyeY + offsetY, eyeZ + offsetZ, atX, atY, atZ, upX, upY, upZ);

    
    //* Move to building square
    float moveX = -40 + x * 60;
    float moveZ = -30 + z * 60;
    

    // 2nd cylinder
    glPushMatrix();
    glTranslatef(moveX, GROUND_LEVEL+12, moveZ);
    //* 1. Translate to origin (center of cylinder
    //* 2. Rotate on y
    //* 3. Rotate back to original spot
    glTranslatef(1, 1, 1); // 3
    glRotatef(rotateCyil , 0, 1, 0); //2
    glTranslatef(1, 1, 1); // 1
    
    glRotatef(70, -1, 0, 0);
    glColor3f(0.753, 0.753, 0.753); // grey
    glBegin(GL_TRIANGLE_STRIP);;
    GLUquadricObj *obj = gluNewQuadric();
    gluCylinder(obj, 2.5, 2.5, 2, 5, 5);
    glEnd();
    glPopMatrix();
    

    // Wick part
    glPushMatrix();
    //* Moves ontop of sphere
    glTranslatef(moveX - 2, GROUND_LEVEL+13, moveZ);

    //* 1. Translate to origin (center of cylinder
    //* 2. Rotate on y
    //* 3. Rotate back to original spot
    glTranslatef(5/2, 5/2, 5/2); // 3
    glRotatef(rotateCyil, 0, 1, 0); //2
    glTranslatef(5/2, -(5/2), -5/2); // 1
    
    //* Rotate it standing
    glRotatef(70, -1, 0, 0);
    //* Draw Cylinder
    glColor3f(0.871, 0.722, 0.529); // wood color
    glBegin(GL_TRIANGLE_STRIP);
    GLUquadricObj *obj2 = gluNewQuadric();
    gluCylinder(obj2, 2, 2, 5, 5, 5);
    glEnd();
    glPopMatrix();
    
    //* Draw Sphere
    glPushMatrix();
    glTranslatef(moveX, GROUND_LEVEL+5, moveZ);
    glColor3f(0.098, 0.098, 0.439);
    glutSolidSphere(10, 10, 10);
    glPopMatrix();
    
    frame_count++;
    if (frame_count % 10 == 0) {
        rotateCyil += 0.3;
        frame_count = 0;
        if(rotateCyil > 360.0) rotateCyil = 0;
    }
}

void renderCyli(int x, int z) {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(eyeX + offsetX, eyeY + offsetY, eyeZ + offsetZ, atX, atY, atZ, upX, upY, upZ);
   
    float cylXPos = -15 + x * 60;
    float cylZPos = -20 + z * 60;
    

    
    //* Draw rectangle ontop
    float rectXmin = -5 + x * 60;
    float rectXmax = -25 + x * 60;
    float rectZmax = -12 + z * 60;
    float rectZmin = -30 + z * 60;
    

    
    glPushMatrix();
    // Move to origin, rotate then move back
    glTranslatef((rectXmax + rectXmin)/2, 21.5, (rectZmax + rectZmin)/2);
    glRotatef(rotateRect, 0, 1, 0);
    glTranslatef(-(rectXmax + rectXmin)/2, -21.5, -(rectZmax + rectZmin)/2);

    //* Front
    glColor3f(0.502, 0.000, 0.000);
    glBegin(GL_QUADS);
    glVertex3f(rectXmax, 25, rectZmin);
    glVertex3f(rectXmin, 25, rectZmin);
    glVertex3f(rectXmin, 18, rectZmin);
    glVertex3f(rectXmax, 18, rectZmin);

    //* Left
    glColor3f(0.184, 0.310, 0.310);
    glVertex3f(rectXmin, 25, rectZmin);
    glVertex3f(rectXmin, 25, rectZmax);
    glVertex3f(rectXmin, 18, rectZmax);
    glVertex3f(rectXmin, 18, rectZmin);

    //* Back
    glColor3f(0.980, 0.922, 0.843);
    glVertex3f(rectXmax, 25, rectZmax);
    glVertex3f(rectXmin, 25, rectZmax);
    glVertex3f(rectXmin, 18, rectZmax);
    glVertex3f(rectXmax, 18, rectZmax);
    
    //* Right
    glColor3f(0.255, 0.412, 0.882);
    glVertex3f(rectXmax, 25, rectZmin);
    glVertex3f(rectXmax, 25, rectZmax);
    glVertex3f(rectXmax, 18, rectZmax);
    glVertex3f(rectXmax, 18, rectZmin);
    
    //* Bottom
    glColor3f(0.000, 1.000, 1.000);
    glVertex3f(rectXmin, 18, rectZmin);
    glVertex3f(rectXmax, 18, rectZmin);
    glVertex3f(rectXmax, 18, rectZmax);
    glVertex3f(rectXmin, 18, rectZmax);
    
    //* Top
    glColor3f(0.604, 0.804, 0.196);
    glVertex3f(rectXmin, 25, rectZmin);
    glVertex3f(rectXmax, 25, rectZmin);
    glVertex3f(rectXmax, 25, rectZmax);
    glVertex3f(rectXmin, 25, rectZmax);
    glEnd();
    glPopMatrix();
    
    
    glPushMatrix();
    // Move it within building square
    glTranslatef(cylXPos, GROUND_LEVEL, cylZPos);
    //* Rotate it standing
    glRotatef(90, -1, 0, 0);

    //* Draw cylinder
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_TRIANGLE_STRIP);
    GLUquadricObj *obj = gluNewQuadric();
    gluCylinder(obj, 8, 8, 20, 10, 10);
    glEnd();
    glFlush();
    glPopMatrix();
    
    // Rotate cube 30 degrees every 10 frames
    frame_count++;
    if (frame_count % 10 == 0) {
        rotateRect += 0.5;
        frame_count = 0;
        if (rotateRect > 360.0) rotateRect = 0;
    }
    
}

void renderBuild(int x, int z) {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(eyeX + offsetX, eyeY + offsetY, eyeZ + offsetZ, atX, atY, atZ, upX, upY, upZ);
//    gluLookAt(eyeX, 40, 60, atX, atY, atZ, 0, 1, 0);

    
    // These floats are calcualted from the viewpoint of looking at the *FRONT
    // Of the building.
    float buildingXmin = -10 + x * 60;
    float buildingXmax = -20 + x * 60;
    float buildingZmax = -50 + z * 60;
    float buildingZmin = -40 + z * 60;
    
    //* FRONT
    // more pos <- x+ -x -> more neg,
    // more neg -z push aways, more pos +z push towards me
    glColor3f(0.467, 0.533, 0.600);
    glBegin(GL_QUADS);
    glVertex3f(buildingXmax, 30, buildingZmax); // top right
    glVertex3f(buildingXmin, 30, buildingZmax); // top left
    glVertex3f(buildingXmin, GROUND_LEVEL, buildingZmax); // bot left
    glVertex3f(buildingXmax, GROUND_LEVEL, buildingZmax); // bot right
    
    //* FRONT WINDOW
    glColor3f(0.941, 1.000, 1.000); // Azure
    glVertex3f(buildingXmax + 2, 16, buildingZmax -0.1); // top right
    glVertex3f(buildingXmin - 2, 16, buildingZmax - 0.1); // top left
    glVertex3f(buildingXmin - 2, 12, buildingZmax -0.1); // bot left
    glVertex3f(buildingXmax + 2, 12, buildingZmax -0.1); // bot right
    
    //* LEFT
    glColor3f(0.467, 0.533, 0.600);
    glVertex3f(buildingXmin, 30, buildingZmin); // top right
    glVertex3f(buildingXmin, 30, buildingZmax); // top left
    glVertex3f(buildingXmin, GROUND_LEVEL, buildingZmax); // bot left
    glVertex3f(buildingXmin, GROUND_LEVEL, buildingZmin); // bot right
    
    //* LEFT WINDOW
    glColor3f(0.941, 1.000, 1.000); // Azure
    glVertex3f(buildingXmin+0.1, 12, buildingZmin - 2); // top right
    glVertex3f(buildingXmin+0.1, 12, buildingZmax + 2); // top left
    glVertex3f(buildingXmin+0.1, 8, buildingZmax + 2); // bot left
    glVertex3f(buildingXmin+0.1, 8, buildingZmin - 2); // bot right


    //*BACK
    glColor3f(0.467, 0.533, 0.600);
    glVertex3f(buildingXmax, 30, buildingZmin); // top right;
    glVertex3f(buildingXmin, 30, buildingZmin); // top left
    glVertex3f(buildingXmin, GROUND_LEVEL, buildingZmin); // bot left
    glVertex3f(buildingXmax, GROUND_LEVEL, buildingZmin); // bot right
    
    //* RIGHT
    glColor3d(0.467, 0.533, 0.600);
    glVertex3f(buildingXmax, 30, buildingZmin); // top right
    glVertex3f(buildingXmax, 30, buildingZmax); // top left
    glVertex3f(buildingXmax, GROUND_LEVEL, buildingZmax); // bot left
    glVertex3f(buildingXmax, GROUND_LEVEL, buildingZmin); // bot right
    
    //* TOP
    glColor3d(0.467, 0.533, 0.600);
    glVertex3f(buildingXmin, 30, buildingZmin);
    glVertex3f(buildingXmax, 30, buildingZmin);
    glVertex3f(buildingXmax, 30, buildingZmax);
    glVertex3f(buildingXmin, 30, buildingZmax);
    glEnd();

}

void renderCity(GLenum mode)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    gluLookAt(eyeX + offsetX, eyeY + offsetY, eyeZ + offsetZ, atX, atY, atZ, upX, upY, upZ);
    
    srand(time(NULL));
    int ran;
    
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            ran = 1 + rand() % 3;
                
            switch (ran) {
                case 1:
                    renderBuild(i,j);
                    renderCyli(i,j);
                    renderSphe(i,j);
                    break;
                case 2:
                    renderCyli(i,j);
                    renderBuild(i,j);
                    renderSphe(i,j);
                    break;
                case 3:
                    renderSphe(i,j);
                    renderCyli(i,j);
                    renderBuild(i,j);
                    break;
                default:
                    break;
                }
            }
            
            glFlush();
    }

    
}

void renderGround() {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(eyeX + offsetX, eyeY + offsetY, eyeZ + offsetZ, atX, atY, atZ, upX, upY, upZ);

    // Render blocks for building sections
    glColor3f(0.000, 0.000, 0.000); // black
    glBegin(GL_QUADS);

    int neg50 = -50;
    int pos60 = 60;

    // Amount of columns = 20
    // Every column x offset is changed
    for (int x = 0; x < 20; x++)
    {
        // Amount of rows = 20
        // Every row z offset is changed
        for (int z = 0; z < 20; z++)
        {
            //bottom left
//            std::cout << "V1: x:" <<neg50 + x * pos60 << " z: " << 0.0 +x z * pos60 << std::endl;
            glVertex3f(neg50 + x * pos60, GROUND_LEVEL, 0.0 + z * pos60);

            glTexCoord2f(0.0, 1.0);
            //bottom right
//            std::cout << "V2: x:" << 0.0 + x * pos60 << " z: " << 0.0 + z * pos60 << std::endl;
            glVertex3f(0.0 + x * pos60, GROUND_LEVEL, 0.0 + z * pos60);

            glTexCoord2f(0.0, 0.0);
            // top right
//            std::cout << "V3: x:" << 0.0 + x * pos60 << " z: " << neg50 + z * pos60 << std::endl;
            glVertex3f(0.0 + x * pos60, GROUND_LEVEL, neg50 + z * pos60);

            glTexCoord2f(1.0, 0.0);
            // top left
//            std::cout << "V4: x:" << neg50 + x * pos60 << " z: " << neg50 + z * pos60 << std::endl;
            glVertex3f(neg50 + x * pos60, GROUND_LEVEL, neg50 + z * pos60);
        }
    }
    glEnd();

    // VERTICLE ROADS
    glColor3f(0.412, 0.412, 0.412);
    glBegin(GL_QUADS);

    for (int i = 0; i < 21; i++)
    {
        //* TOP VERTICES
        glTexCoord2f(1.0, 1.0);
        glVertex3f(-60 + i * 60, GROUND_LEVEL, 1150);
        glTexCoord2f(0.0, 1.0);
        glVertex3f(-50 + i * 60, GROUND_LEVEL, 1150);

        //* BOTTOM VERTICES
        glTexCoord2f(0.0, 0.0);
        glVertex3f(-50 + i * 60, GROUND_LEVEL, -50);
        glTexCoord2f(1.0, 0.0);
        glVertex3f(-60 + i * 60, GROUND_LEVEL, -50);

    }
    
    //* VERTICLE ROAD STRIPES*
    glColor3f(1.0, 1.0 , 0.0); // Just yellow
    for (int i = 0; i < 20; i++) {
        glVertex3f(-54 + i * 60, GROUND_LEVEL + 0.05, 1150);
        glVertex3f(-56 + i * 60, GROUND_LEVEL + 0.05, 1150);
        //* BOTTOM VERTICES
        glVertex3d(-56 + i * 60, GROUND_LEVEL + 0.05, -50);
        glVertex3d(-54 + i * 60, GROUND_LEVEL + 0.05, -50);
    }


    //* HORIZONTAL ROADS
    glColor3f(0.412, 0.412, 0.412);
    for (int i = 0; i < 20; i++) {
        glTexCoord2f(1.0, 0.0);
        glVertex3f(-60, GROUND_LEVEL, -60 + i * 60);
        glTexCoord2f(0.0, 0.0);
        glVertex3f(-60, GROUND_LEVEL, -50 + i * 60);
        glTexCoord2f(0.0, 1.0);
        glVertex3f(1150, GROUND_LEVEL, -50 + i * 60);
        glTexCoord2f(1.0, 1.0);
        glVertex3f(1150, GROUND_LEVEL, -60 + i * 60);
    }

    //* HORIZONTAL ROAD STRIPES
    glColor3f(1.0, 1.0, 0.0); // Yellow
    for (int i = 0; i < 20; i++) {
        glVertex3f(-60, GROUND_LEVEL + 0.05, -56 + i * 60);
        glVertex3f(-60, GROUND_LEVEL + 0.05, -54 + i * 60);
        glVertex3f(1150, GROUND_LEVEL + 0.05, -54 + i * 60);
        glVertex3f(1150, GROUND_LEVEL + 0.05, -56 + i * 60);
    }
    glEnd();
}

void moveCam() {
    int originX = 5, originY = 8, originZ = -45;
    switch (fkey) {
        case 1:
            if (isNorth) {
                eyeX = originX, eyeY = originY, eyeZ = originZ;
            } else if (isWest) {
//                eyeX = -40, eyeY = 8, eyeZ = -25;
                upZ = 1;
                upX = 1;

            }
            break;
        case 2: //* LOOKAT f2
            if (isNorth) {
                eyeX = 12;
                eyeY = GROUND_LEVEL + 1;
                eyeZ = -25;
            } else if (isWest) {
                eyeX = -25;
                eyeY = GROUND_LEVEL + 1;
                eyeZ = -35;
            }

            
            break;
        case 3: //* LOOKAT f3
            eyeX = -12;
            eyeY = GROUND_LEVEL + 1;
            eyeZ = -25;
            break;
        case 4: //* LOOKAT F4 - original position
            eyeX = originX;
            eyeY = originY;
            eyeZ = originZ;
            break;
        case 5: //* LOOKAT f5
            eyeX = originX;
            eyeY = originY + 2;
            eyeZ = originZ - 20;

            break;
        case 8: //* LOOKAT f8
            eyeX = originX;
            eyeY = originY + 6;
            eyeZ = originZ - 15;
            break;
        case 6: //* LOOKAT f6
            eyeX = originX;
            eyeY = originY + 2;
            eyeZ = originZ * - 1;
            break;
        case 7: //* LOOKAT f7
            eyeX = originX;
            eyeY = originY + 4;
            eyeZ = (originZ * - 1) + 10;
            break;
        case 9: //* LOOKAT F9 -- further than f5
            eyeX = originX;
            eyeY = originY + 4;
            eyeZ = originZ - 40;
            break;
        case 10: //* LOOKAT F10 -- further than f6
            eyeX = originX;
            eyeY = originY + 4;
            eyeZ = (originZ * - 1) + 20;
            break;
        case 11: //* LOOKAT F11 -- further than f7
            eyeX = originX;
            eyeY = originY + 8;
            eyeZ = (originZ * -1) + 20;
            break;
        case 12: //* LOOKAT F12 -- further than f8
            eyeX = originX;
            eyeY = originY + 12;
            eyeZ = originZ - 30;
            
            break;
        default:
            break;
    }
}

void CallBackRenderScene(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    glPushMatrix();
    //  robot.draw_environment(GL_RENDER); // draw the ground/blocks
    renderGround();
    glPopMatrix();

    glPushMatrix();
    renderCity(GL_RENDER); // draw buildings into the world
    glPopMatrix();
    
    glPushMatrix();
    glLoadIdentity();
    //car.renderCar(); // draw robot into the world
    renderCar();
    glPopMatrix();

    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();

    glLoadIdentity();
    glOrtho(0, Window_Width, 0, Window_Height, -1.0, 1.0);
    glColor4f(0.6, 1.0, 0.6, 1.00);

    glTranslatef(6.0f, Window_Height - 14, 0.0f);

    glPopMatrix();
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

    glutSwapBuffers();

    moveCam();
}

void mouse(int button, int state, int x, int y)
{
}


void keyboard(unsigned char key, int x, int y)
{

    if (!pausedState)
    {

        switch (key)
        {
        case 112: // p key

            glutDisplayFunc(CallBackRenderScene);
            glutIdleFunc(NULL);
            pausedState = true;
            break;

        case 122: // z key
                if (isNorth) {
                    //* Check boundary
                    if (cz == -54) break;
                    
                    if (bodyAngle == 90)
                    {
                        offsetZ -= 1.0;
                        atZ -= 1.0;
                        cz -= 1.0;
                        if (cz % 6 == 0) std::cout << "can turn" << std::endl;
                        std::cout << "atX: " << atX << std::endl << " AtZ: " << atZ << std::endl;
                    } else{
                        offsetX -= 1.0;
                        atX -= 1.0;
                        cx -= 1.0;
                    }
                } else if (isWest) {
                    offsetX -= 1.0;
                    atX -= 1.0;
                    if (bodyAngle == 180) {
                        cx -= 1.0;
                    } else {
                        cz += 1.0;
                    }
                }

                
            break;
        case 97: // a key
                if (isNorth) {
                    //* Check boundary
                    if (cz >= 1154) break;

                    if (cz % 6 == 0) std::cout << "can turn" << std::endl;
                    std::cout << "atX: " << atX << std::endl << " AtZ: " << atZ << std::endl;
                    offsetZ += 1.0;
                    atZ += 1.0;
                    std::cout << "cz: " << cz << " cx: " << cx << std::endl;
                    if (bodyAngle == 90)
                    {
                        cz += 1.0;
                    } else{
                        cx += 1.0;
                    }
                } else if (isWest) {
                    offsetX += 1.0;
                    atX += 1.0;
                    if (bodyAngle == 180) {
                        cx += 1.0;
                    } else {
                        cz += 1.0;
                    }
                }
            break;
        case 115: // s key
            eyeY -= 1.0;
            std::cout << "EyeY: " << eyeY << std::endl;
            break;
        case 113: // q key
            eyeX = -8, eyeY = 5, eyeZ = -45;
            bodyAngle += 90;
                if (isNorth) {
                    upX = 1;
                    isWest = true;
                    isNorth = false;
                }
            break;
        case 119: // w key
            eyeX = 5, eyeY = -8, eyeZ = -45;
            bodyAngle -= 90;
                if (isWest) {
                    isNorth = true;
                    isWest = false;
                }
            break;
        case 114: // r key
            eyeZ += 1.0;
//                car.eyez += 1.0;
            std::cout << "EyeZ: " << eyeZ << std::endl;
            break;
        case 120: //x key
            eyeZ -= 1.0;
//                car.eyez -= 1.0;
            std::cout << "EyeZ " << eyeZ << std::endl;
            break;
        case 117: //u
            atX += 1.0;
//                car.atx += 1.0;
            std::cout << "atX: " << atX << std::endl;
            break;
        case 105: //i
            atX -= 1.0;
//                car.atx -= 1.0;
            std::cout << "atX: " << atX << std::endl;

            break;
        case 106: // j
            atY += 1.0;
//                car.aty += 1.0;
            std::cout << "atY: " << atY << std::endl;

            break;
        case 107: // k
            std::cout << "atY: " << atY << std::endl;

            atY -= 1.0;
//                car.aty -= 1.0;
            break;
        case 110: // n
            std::cout << "atZ: " << atZ << std::endl;

            atZ += 1.0;
//                car.atz += 1.0;
            break;
        case 109: //
            std::cout << "atZ: " << atZ << std::endl;
            atZ -= 1.0;
//                car.atz -= 1.0;
            break;

        default:
            printf("No case assigned for %d.\n", key);
            break;
        }
    }
    else if (key = 112)
    {
        glutIdleFunc(CallBackRenderScene);
        pausedState = false;
    }
}

void speckeyboard(int key, int x, int y) {
    if (key == GLUT_KEY_F1) {
        fkey = 1;
    } else if (key == GLUT_KEY_F2) {
        fkey = 2;
    } else if (key == GLUT_KEY_F3) {
        fkey = 3;
    } else if (key == GLUT_KEY_F4) {
        fkey = 4;
    } else if (key == GLUT_KEY_F5) {
        fkey = 5;
    } else if (key == GLUT_KEY_F8) {
        fkey = 8;
    } else if (key == GLUT_KEY_F6) {
        fkey = 6;
    } else if (key == GLUT_KEY_F7) {
        fkey = 7;
    } else if (key == GLUT_KEY_F8) {
        fkey = 8;
    } else if (key == GLUT_KEY_F9) {
        fkey = 9;
    } else if (key == GLUT_KEY_F10) {
        fkey = 10;
    } else if (key == GLUT_KEY_F11) {
        fkey = 11;
    } else if (key == GLUT_KEY_F12) {
        fkey = 12;
    }
    
}

void speckeyboarddown(int key, int x, int y)
{

    if (GLUT_KEY_F2)
    { // case for when the F2 key is released and the robots head should no longer
        // be rotating
        headTurnR = false;
    }
    if (GLUT_KEY_F3)
    { // case for when the F3 key is released and the robots head should no longer
        // be rotating
        headTurnL = false;
    }
}

void CallBackResizeScene(int Width, int Height)
{
    if (Height == 0)
    {
        Height = 1;
    }

    glViewport(0, 0, Width, Height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // glOrtho(-200, 200, -200, 200, 0, 50);
    // Buildings come into view in distance
    gluPerspective(45.0f, (GLfloat)Width / (GLfloat)Height, 0.1f, 300.0f);

    glMatrixMode(GL_MODELVIEW);

    Window_Width = Width;
    Window_Height = Height;
}

void MyInit(int Width, int Height)
{
    glClearColor(0.1f, 0.1f, 0.1f, 0.0f);

    glClearDepth(1.0);
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);

    glShadeModel(GL_SMOOTH);

    CallBackResizeScene(Width, Height);
}

int main(int argc, char **argv) {
    car.atx = 0.0;       // x position of lookat
    car.aty = 0.0;     // y position of lookat
    car.atz = 0;       // z position of lookat
    car.eyex = 0.0;      // x position of camera eye
    car.eyey = 4;      // y position of camera eye
    car.eyez = -10 ;    // z position of camera eye
    car.cx = -3;        // x position of robot
    car.cy = -5;     // y position of robot
    car.cz = 4;        // z position of robot
    car.bodyAngle = 95; // the angle at which the robot is currently.
//    car.headAngle = 0; // angle the head is currently rotated
//    car.antRot = 0;    // angle of antenae rotating
//    car.offz = 0;      // x offset from the origin
//    car.offx = 0;      // z offset from the origin
//    car.nameCount = 0; // counter for naming the buildings for picking function



    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

    glutInitWindowSize(Window_Width, Window_Height);
    Window_ID = glutCreateWindow(PROGRAM_TITLE);

    glutDisplayFunc(&CallBackRenderScene);

    glutIdleFunc(&CallBackRenderScene);

    glutReshapeFunc(&CallBackResizeScene);

    glutMouseFunc(&mouse);

    glutSpecialFunc(&speckeyboard);
    glutSpecialUpFunc(&speckeyboarddown);
    glutKeyboardFunc(&keyboard);

    MyInit(Window_Width, Window_Height);

    printf("\n%s\n\n", PROGRAM_TITLE);
    glutMainLoop();
    return 1;
}
