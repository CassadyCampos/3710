//**********//**********//**********//**********//**********//**********//**********//**********//
//*                                                                                            *//
//*     CPSC 3710 Computer Graphics Spring 2020                                                *//
//*                                                                                            *//
//*     Cassady Campos                                                                         *//
//*     Prosper Ibhamawu                                                                       *//
//*                                                                                            *//
//*                                                                                            *//
//*                                                                                            *//
//**********//**********//**********//**********//**********//**********//**********//**********//

#define PROGRAM_TITLE "Cass Pros Battle Hummer"
#define DISPLAY_INFO "CPSC 3710"

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

int BLOCK_SIZE = 20;

int Window_ID;
int Window_Width = 1280;
int Window_Height = 720;
int locationZ = 2;
int locationX = 4;

//* DEFAULT FUNCTION KEY PRESSED IS 1
int fkey = 1;

//* FLAG FOR PAUSE GAME
bool isPaused =  false;

//* CONSTANTS FOR CAMERA
int eyeX = 5, eyeY = 8,eyeZ = 25;
int atX = 0, atY = 0, atZ = 0;
float upX = 0, upY = 1, upZ = 0;

int offsetX, offsetY, offsetZ;
int carOffX, carOffY, carOffZ;

int GROUND_LEVEL = 0.5;
int frame_count = 0;
float rotateRect = 0.4;
float rotateCyil = 0.5;
float antRot = 30;
float bodyAngle = 90;

//* CONSTANTS FOR CAR
int cx = 0.0;
int cy = 0.0;
int cz = 0.0;

bool isNorth = true;
bool isWest = false;
bool isSouth = false;
bool isEast = false;

// function for drawing the Car into the world
void renderCar() {
    float theta,angle;
    int frame_count=0;

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
    glTranslatef(1, 1, 1); // 3.
    glRotatef(rotateCyil , 0, 1, 0); //2.
    glTranslatef(1, 1, 1); // 1.
    
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

    glColor3f(0.000, 0.000, 0.000); // black
    glBegin(GL_QUADS);

    int neg50 = -50;
    int pos60 = 60;
    //* BUILDING SQUARES
    // Amount of columns = 20
    // Every column x offset is changed
    for (int x = 0; x < 20; x++)
    {
        // Amount of rows = 20
        // Every row z offset is changed
        for (int z = 0; z < 20; z++)
        {
            //bottom left
            glVertex3f(neg50 + x * pos60, GROUND_LEVEL, 0.0 + z * pos60);

            glTexCoord2f(0.0, 1.0);
            //bottom right
            glVertex3f(0.0 + x * pos60, GROUND_LEVEL, 0.0 + z * pos60);

            glTexCoord2f(0.0, 0.0);
            glVertex3f(0.0 + x * pos60, GROUND_LEVEL, neg50 + z * pos60);

            glTexCoord2f(1.0, 0.0);
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
    int baseY = 5;
    //* WHEN FACING NORTH;
    int nX = 0, nZ = -15;
    //* WHEN FACING WEST;
    int wX = -15, wZ = 1;
    switch (fkey) {
        case 1:
            if (isNorth) {
                eyeX = nX;
                eyeY = baseY;
                eyeZ = nZ;
                break;
            } else if (isWest) {
                eyeX = wX;
                eyeY = baseY;
                eyeZ = wZ;
                break;
            } else if (isSouth) {
                eyeX = -nX;
                eyeY = baseY;
                eyeZ = -nZ;
                break;
            } else if (isEast) {
                eyeX = -wX;
                eyeY = baseY;
                eyeZ = -wZ;
                break;
            }
            break;
        case 2: //* LOOKAT f2
            if (isNorth) {
                eyeX = 14;
                eyeZ = 0;
            } else if (isSouth) {
                eyeX = -14;
                eyeZ = 0;
            } else if (isWest) {
                eyeX = 0;
                eyeZ = -14;
            } else if (isEast) {
                eyeX = 0;
                eyeZ = 14;
            }
            break;
        case 3: //* LOOKAT f3
            if (isNorth) {
                eyeX = -14;
                eyeZ = 0;
            } else if (isSouth) {
                eyeX = 14;
                eyeZ = 0;
            } else if (isWest) {
                eyeX = 0;
                eyeZ = 14;
            } else if (isEast) {
                eyeX = 0;
                eyeZ = -14;
            }

            break;
        case 4: //* LOOKAT F4 - original position
            if (isNorth) {
                eyeX = nX; eyeY = baseY; eyeZ = nZ;
                break;
            } else if (isWest) {
                eyeX = wX;
                eyeY = baseY;
                eyeZ = wZ;
                break;
            } else if (isSouth) {
                eyeX = -nX;
                eyeY = baseY;
                eyeZ = -nZ;
                break;
            } else if (isEast) {
                eyeX = -wX;
                eyeY = baseY;
                eyeZ = -wZ;
                break;
            }
            break;
        case 5: //* LOOKAT f5
            if (isNorth) {
                eyeX = nX;
                eyeY = baseY + 2;
                eyeZ = nZ - 20;
            } else if (isSouth) {
                eyeX = -nX;
                eyeY = baseY + 2;
                eyeZ = -(nZ - 20);
            } else if (isWest) {
                eyeX = nZ - 20;
                eyeY = baseY + 2;
                eyeZ = nX;
            } else if (isEast) {
                eyeX = -(nZ - 20);
                eyeY = baseY + 2;
                eyeZ = nX;
            }
            break;
        case 8: //* LOOKAT f8
            if (isNorth) {
                eyeX = nX;
                eyeY = baseY + 6;
                eyeZ = nZ - 15;
            } else if (isSouth) {
                eyeX = -nX;
                eyeY = baseY + 6;
                eyeZ = -nZ - 15;
            } else if (isWest) {
                eyeX = (nZ - 15);
                eyeY = baseY + 6;
                eyeZ = nX;
            } else if (isEast) {
                eyeX = -(nZ - 15);
                eyeY = baseY + 6;
                eyeZ = -nX;
            }
            break;
        case 6: //* LOOKAT f6
            if (isNorth) {
                eyeX = nX;
                eyeY = baseY + 2;
                eyeZ = nZ * - 1;
            } else if (isSouth) {
                eyeX = -nX;
                eyeY = baseY + 2;
                eyeZ = - (nZ * -1);
            } else if (isWest) {
                eyeX = nZ * - 1;
                eyeY = baseY + 2;
                eyeZ = nX;
            } else if (isSouth) {
                eyeX = -(nZ * - 1);
                eyeY = baseY + 2;
                eyeZ = -nX;
            }
            break;
        case 7: //* LOOKAT f7
            if (isNorth) {
                eyeX = nX;
                eyeY = baseY + 4;
                eyeZ = (nZ * - 1) + 10;
            } else if (isSouth) {
                eyeX = -nX;
                eyeY = baseY + 4;
                eyeZ = (-nZ * -1) + 10;
            } else if (isWest) {
                eyeX = (nZ * - 1) + 10;
                eyeY = baseY + 4;
                eyeZ = nX;
            } else if (isEast) {
                eyeX = -(nZ * - 1) + 10;
                eyeY = baseY + 4;
                eyeZ = -nX;
            }
            break;
        case 9: //* LOOKAT F9 -- further than f5
            if (isNorth) {
                eyeX = nX;
                eyeY = baseY + 4;
                eyeZ = nZ - 40;
            } else if (isSouth) {
                eyeX = -nX;
                eyeY = baseY + 4;
                eyeZ = -nZ - 40;
            } else if (isWest) {
                eyeX = nZ - 40;
                eyeY = baseY + 4;
                eyeZ = nX;
            } else if (isEast) {
                eyeX = -(nZ - 40);
                eyeY = baseY + 4;
                eyeZ = -nX;
            }
            break;
        case 10: //* LOOKAT F10 -- further than f6
            if (isNorth) {
                eyeX = nX;
                eyeY = baseY + 4;
                eyeZ = (nZ * - 1) + 20;
            } else if (isSouth) {
                eyeX = -nX;
                eyeY = baseY + 4;
                eyeZ = (nZ * -1) + 20;
            } else if (isWest) {
                eyeX = (nZ * - 1) + 20;
                eyeY = baseY + 4;
                eyeZ = nX;
            } else if (isEast) {
                eyeX = -(nZ * - 1) + 20;
                eyeY = baseY + 4;
                eyeZ = -nX;
            }
            break;
        case 11: //* LOOKAT F11 -- further than f7
            if (isNorth) {
                eyeX = nX;
                eyeY = baseY + 8;
                eyeZ = (nZ * -1) + 20;
            } else if (isSouth) {
                eyeX = -nX;
                eyeY = baseY +8;
                eyeZ = (-nZ * -1) + 20;
            } else if (isWest) {
                eyeX = (nZ * -1) + 20;
                eyeY = baseY + 8;
                eyeZ = nX;
            } else if (isEast) {
                eyeX = -(nZ * -1) + 20;
                eyeY = baseY + 8;
                eyeZ = -nX;
            }
            break;
        case 12: //* LOOKAT F12 -- further than f8
            if (isNorth) {
                eyeX = nX;
                eyeY = baseY + 12;
                eyeZ = nZ - 30;
            } else if (isSouth) {
                eyeX = -nX;
                eyeX = baseY + 12;
                eyeZ = -nZ - 30;
            } else if (isWest) {
                eyeX = nZ - 30;
                eyeY = baseY + 12;
                eyeZ = nX;
            } else if (isEast) {
                eyeX = -(nZ - 30);
                eyeY = baseY + 12;
                eyeZ = -nX;
            }
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
    renderGround();
    glPopMatrix();

    glPushMatrix();
    renderCity(GL_RENDER);
    glPopMatrix();
    
    glPushMatrix();
    glLoadIdentity();
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



bool isIntersectionZ(int carZ){
    if(carZ % 60 == 0){
        return true;
    } else {
        return false;
    }
}

bool isIntersectionX(int carX){
    if(carX % 60 == 0){
        return true;
    } else {
        return false;
    }
}


void keyboard(unsigned char key, int x, int y)
{
    if (key == 112) {
        std::cout << "pause: " << isPaused << std::endl;
        isPaused = !isPaused;
    }
    if (isPaused == 0) {
        switch (key)
        {
        case 122: // z key
                if (isNorth) {
                    //* Check boundary
                    if (cz == -60) break;
                    offsetZ -= 1.0;
                    atZ -= 1.0;
                    cz -= 1.0;
  
                    std::cout << "NORTH: cz: " << cz << " cx: " << cx << std::endl;
                    break;
                } else if (isWest) {
                    //* Check boundary
                    if (cx == -60) break;
                    offsetX -= 1.0;
                    atX -= 1.0;
                    cx -= 1.0;
                    std::cout << "WEST: cz: " << cz << " cx: " << cx << std::endl;
                    break;
                } else if (isEast) {
                    //* Check boundary
                    if (cx >= 1160) break;
                    offsetX += 1.0;
                    atX += 1.0;
                    cx += 1.0;
                    std::cout << "EAST: cz: " << cz << " cx: " << cx << std::endl;

                    break;
                } else if (isSouth) {
                    //* Check boundary
                    if (cz >= 1160) break;
                    offsetZ += 1.0;
                    atZ += 1.0;
                    cz += 1.0;
                    std::cout << "SOUTH: cz: " << cz << " cx: " << cx << std::endl;
                    break;
                }
            break;
        case 97: // a key
                if (isNorth) {
                    //* Check boundary
                    if (cz >= 1160) break;
                    offsetZ += 1.0;
                    atZ += 1.0;
                    cz += 1.0;
                    std::cout << "NORTH: cz: " << cz << " cx: " << cx << std::endl;
                    break;
                } else if (isWest) {
                    //* Check boundary
                    if (cx >= 1160) break;
                    offsetX += 1.0;
                    atX += 1.0;
                    cx += 1.0;
                    std::cout << "WEST: cz: " << cz << " cx: " << cx << std::endl;

                    break;
                } else if (isEast) {
                    if (cx == -60) break;
                    offsetX -= 1.0;
                    atX -= 1.0;
                    cx -= 1.0;
                    std::cout << "EAST: cz: " << cz << " cx: " << cx << std::endl;

                    break;
                } else if (isSouth) {
                    //* Check boundary
                    if (cz == -54) break;
                    offsetZ -= 1.0;
                    atZ -= 1.0;
                    cz -= 1.0;
                    std::cout << "SOUTH: cz: " << cz << " cx: " << cx << std::endl;
                    break;
                }
            break;
        case 113: // q key
                if (isNorth && isIntersectionZ(cz) && isIntersectionX(cx)) {
                    bodyAngle += 90;
                    isWest = true;
                    isNorth = false;
                    std::cout << "NORTH: cz: " << cz << " cx: " << cx << std::endl;
                    break;
                } else if (isWest && isIntersectionZ(cz) && isIntersectionX(cx)) {
                    bodyAngle += 90;
                    isSouth = true;
                    isWest = false;
                    std::cout << "WEST: cz: " << cz << " cx: " << cx << std::endl;
                    break;
                } else if (isSouth && isIntersectionZ(cz) && isIntersectionX(cx)) {
                    bodyAngle += 90;
                    isEast = true;
                    isSouth = false;
                    std::cout << "SOUTH: cz: " << cz << " cx: " << cx << std::endl;
                    break;
                } else if (isEast && isIntersectionZ(cz) && isIntersectionX(cx)) {
                    bodyAngle = 90;
                    isNorth = true;
                    isEast = false;
                    std::cout << "EAST: cz: " << cz << " cx: " << cx << std::endl;

                    break;
                }
            break;
        case 119: // w key
                if (isNorth && isIntersectionZ(cz) && isIntersectionX(cx)) {
                    bodyAngle -= 90;
                    isEast = true;
                    isNorth = false;
                } else if (isEast && isIntersectionZ(cz) && isIntersectionX(cx)) {
                    bodyAngle -= 90;
                    isSouth = true;
                    isEast = false;
                } else if (isSouth && isIntersectionZ(cz) && isIntersectionX(cx)) {
                    bodyAngle -= 90;
                    isWest = true;
                    isSouth = false;
                } else if (isWest && isIntersectionZ(cz) && isIntersectionX(cx)) {
                    bodyAngle = 90;
                    isNorth = true;
                    isWest = false;
                }
            break;


        case 117: //u
            eyeX += 1.0;
            std::cout << "eyeX: " << eyeX << std::endl;
            break;
        case 105: //i key
            eyeX -= 1.0;
            std::cout << "eyeX: " << eyeX << std::endl;

            break;
        case 106: // j key
            eyeY += 1.0;
            std::cout << "eyeY: " << eyeY << std::endl;
            break;
        case 107: // k key
            std::cout << "eyeY: " << eyeY << std::endl;
            eyeY -= 1.0;
            break;
        case 110: // n key

            eyeZ += 1.0;
            std::cout << "eyeZ: " << eyeZ << std::endl;

            break;
        case 109: //
            eyeZ -= 1.0;
            std::cout << "eyeZ: " << eyeZ << std::endl;
            break;

        default:
            printf("No case assigned for %d.\n", key);
            break;
        }
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

void CallBackResizeScene(int Width, int Height)
{
    if (Height == 0)
    {
        Height = 1;
    }

    glViewport(0, 0, Width, Height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

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

    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

    glutInitWindowSize(Window_Width, Window_Height);
    Window_ID = glutCreateWindow(PROGRAM_TITLE);

    glutDisplayFunc(&CallBackRenderScene);

    glutIdleFunc(&CallBackRenderScene);

    glutReshapeFunc(&CallBackResizeScene);

    glutMouseFunc(&mouse);

    glutSpecialFunc(&speckeyboard);
    glutKeyboardFunc(&keyboard);

    MyInit(Window_Width, Window_Height);

    printf("\n%s\n\n", PROGRAM_TITLE);
    glutMainLoop();
    return 1;
}
