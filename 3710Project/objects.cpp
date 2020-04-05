#ifndef ROBOT_H
#define ROBOT_H


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

#define PI 3.1415927

void moveCam(int);
void headRotate(bool, bool);

class Robot
{
public:
  // all explained in main where we initialize them in the main function
  float atx;
  float aty;
  float atz;
  float eyex;
  float eyey;
  float eyez;
  int cx;
  int cy;
  int cz;
  int bodyAngle;
  int headAngle;
  float antRot = 0.5f;
  float offz;
  float offx;
  int nameCount;
  GLenum modeV; // current GL_MODE (either GL_RENDER or GL_SELECT)

  void drawRobot()
  { // function for drawing the robot into the world
  float theta,angle;
  int frame_count;

    // cube begin
    glLoadIdentity();
    gluLookAt(eyex, eyey, eyez, atx, aty, atz, 0, 1,0); // lookat view for the robot

    glTranslatef(cx, cy, cz);      // translate to robots current position
    glRotatef(bodyAngle, 0, 1, 0); // for when robot is turning to left or right
    glTranslatef(3.0, 3.0, 3.0);         // translate to 0, 0, 0 first for if robot is turning
    glScalef(3.0,3.0,3.0);
    glEnable(GL_COLOR_MATERIAL);

    // begin the body of the robot
    glBegin(GL_QUADS);

    // frontdesign
    glColor3f(1.0f, 0.0f, 1.0f);
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
    glVertex3f(0.7,0.65,0.6);
    glVertex3f(0.7,0.65,0.2);
    glVertex3f(1.7,0.65,0.2);
    glVertex3f(1.7,0.65,0.6);

    //***************************back guard******************************
    glColor3f(1.0f, 0.0f, 1.0f);
    glVertex3f(1.8,0.5,0.6);
    glVertex3f(1.8,0.5,0.2);
    glVertex3f(2.1,0.4,0.2);
    glVertex3f(2.1,0.4,0.6);
    /* bottom of cube*/
    glVertex3f(2.1,0.2,0.6);
    glVertex3f(2.1,0.2,0.2);
    glVertex3f(1.8,0.2,0.6);
    glVertex3f(1.8,0.2,0.6);
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
    glVertex3f(0.6,0.5,0.6);
    glVertex3f(0.6,0.2,0.6);
    glVertex3f(1.8,0.2,0.6);
    glVertex3f(1.8,0.5,0.6);
    //******************Top Antenna************************************
    /*side of antenna*/
    glVertex3f(1.35,1.3,0.4);
    glVertex3f(1.35,0.63,0.4);
    glVertex3f(1.6,0.63,0.4);
    glVertex3f(1.6,1.3,0.4);
    /*side of antenna*/
    glVertex3f(1.6,1.3,0.5);
    glVertex3f(1.6,0.63,0.5);
    glVertex3f(1.35,0.63,0.5);
    glVertex3f(1.35,1.3,0.5);

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

    glColor3f(1.0f,1.0f,1.0f);
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

    glColor3f(1.0f,1.0f,1.0f);
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

    //******************ATENNA BODY************************************
    glPushMatrix();
    glColor3f(0.0,0.3,0.3);
    glTranslatef(1.5,1.5,0.45);
    glRotatef(antRot,0.0f,1.0f,0.0f);
    glutWireSphere(0.25,25,25);
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
};
#endif

