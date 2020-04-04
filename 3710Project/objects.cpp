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
static GLuint skybox;
static GLuint hor;

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
  int antRot;
  float offz;
  float offx;
  int nameCount;
  GLenum modeV; // current GL_MODE (either GL_RENDER or GL_SELECT)

  void drawRobot()
  { // function for drawing the robot into the world
  float theta,angle,i;
  int frame_count;

    // cube begin
    glLoadIdentity();
    gluLookAt(eyex, eyey, eyez, atx, aty, atz, 0, 1,
              0); // lookat view for the robot

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
    glBegin(GL_TRIANGLE_STRIP);
    GLUquadricObj *quadratic;
    quadratic = gluNewQuadric();
    gluQuadricTexture(quadratic, true);
    glTranslatef(3.0, 3.0, 3.0); 
    glRotatef(antRot, 0.0f, 1.0f, 0.0f);
    gluCylinder(quadratic,0.1f,0.1f,1.0f,32,32);
    glEnd();
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

    //*************************************************************
    glPopMatrix();
    glEnable(GL_DEPTH_TEST);
    glutPostRedisplay();
    glutSwapBuffers();

    frame_count++;
    if (frame_count % 10 == 0) {
        antRot += 30;
        frame_count = 0;
        if (antRot > 360) {
            antRot = 0;
        }
    }
  }

  void moveCam(int fKey)
  { // function that handles the camera angles.
    switch (fKey)
    {
    case 1:
      if (eyex > (offx + 0))
      { // this is default view of robot
        eyex--;
      }
      if (eyex < (offx + 0))
      { // each on of these if statements basically is checking if the eye is in
        // the right position
        eyex++; // relative to the robots offset for the desired camera angle.
      }         // this is standard across all cases (1-12) for every camera angle
      // required
      if (eyey > 5)
      { // 1-4 are the behind view of the robot (depending on what direction he
        // is facing)
        eyey--; // 5-8 are the angled camera views of the robot
      }         // 9-12 are the farther out angled camera views of the robot
      if (eyey < 5)
      { // All of these use offx and offz to determine how far offset the robot
        // currently is from the origin
        eyey++;
      }
      if (eyez > (offz + -15))
      {
        eyez--;
      }
      if (eyez < (offz + -15))
      {
        eyez++;
      }
      break;
    case 2:
      if (eyex > (offx + -15))
      {
        eyex--;
      }
      if (eyex < (offx + -15))
      {
        eyex++;
      }
      if (eyey > 5)
      {
        eyey--;
      }
      if (eyey < 5)
      {
        eyey++;
      }
      if (eyez > (offz + 0))
      {
        eyez--;
      }
      if (eyez < (offz + 0))
      {
        eyez++;
      }
      break;
    case 3:
      if (eyex > (offx + 0))
      {
        eyex--;
      }
      if (eyex < (offx + 0))
      {
        eyex++;
      }
      if (eyey > 5)
      {
        eyey--;
      }
      if (eyey < 5)
      {
        eyey++;
      }
      if (eyez > (offz + 15))
      {
        eyez--;
      }
      if (eyez < (offz + 15))
      {
        eyez++;
      }
      break;
    case 4:
      if (eyex > (offx + 15))
      {
        eyex--;
      }
      if (eyex < (offx + 15))
      {
        eyex++;
      }
      if (eyey > 5)
      {
        eyey--;
      }
      if (eyey < 5)
      {
        eyey++;
      }
      if (eyez > (offz + 0))
      {
        eyez--;
      }
      if (eyez < (offz + 0))
      {
        eyez++;
      }
      break;
    case 5:
      if (eyex > (offx + 10))
      {
        eyex--;
      }
      if (eyex < (offx + 10))
      {
        eyex++;
      }
      if (eyey > 10)
      {
        eyey--;
      }
      if (eyey < 10)
      {
        eyey++;
      }
      if (eyez > (offz + -10))
      {
        eyez--;
      }
      if (eyez < (offz + -10))
      {
        eyez++;
      }
      break;
    case 6:
      if (eyex > (offx + -10))
      {
        eyex--;
      }
      if (eyex < (offx + -10))
      {
        eyex++;
      }
      if (eyey > 10)
      {
        eyey--;
      }
      if (eyey < 10)
      {
        eyey++;
      }
      if (eyez > (offz + -10))
      {
        eyez--;
      }
      if (eyez < (offz + -10))
      {
        eyez++;
      }
      break;
    case 7:
      if (eyex > (offx + -10))
      {
        eyex--;
      }
      if (eyex < (offx + -10))
      {
        eyex++;
      }
      if (eyey > 10)
      {
        eyey--;
      }
      if (eyey < 10)
      {
        eyey++;
      }
      if (eyez > (offz + 10))
      {
        eyez--;
      }
      if (eyez < (offz + 10))
      {
        eyez++;
      }
      break;
    case 8:
      if (eyex > (offx + 10))
      {
        eyex--;
      }
      if (eyex < (offx + 10))
      {
        eyex++;
      }
      if (eyey > 10)
      {
        eyey--;
      }
      if (eyey < 10)
      {
        eyey++;
      }
      if (eyez > (offz + 10))
      {
        eyez--;
      }
      if (eyez < (offz + 10))
      {
        eyez++;
      }
      break;
    case 9:
      if (eyex > (offx + 50))
      {
        eyex--;
      }
      if (eyex < (offx + 50))
      {
        eyex++;
      }
      if (eyey > 50)
      {
        eyey--;
      }
      if (eyey < 50)
      {
        eyey++;
      }
      if (eyez > (offz + -50))
      {
        eyez--;
      }
      if (eyez < (offz + -50))
      {
        eyez++;
      }
      break;
    case 10:
      if (eyex > (offx + -50))
      {
        eyex--;
      }
      if (eyex < (offx + -50))
      {
        eyex++;
      }
      if (eyey > 50)
      {
        eyey--;
      }
      if (eyey < 50)
      {
        eyey++;
      }
      if (eyez > (offz + -50))
      {
        eyez--;
      }
      if (eyez < (offz + -50))
      {
        eyez++;
      }
      break;
    case 11:
      if (eyex > (offx + -50))
      {
        eyex--;
      }
      if (eyex < (offx + -50))
      {
        eyex++;
      }
      if (eyey > 50)
      {
        eyey--;
      }
      if (eyey < 50)
      {
        eyey++;
      }
      if (eyez > (offz + 50))
      {
        eyez--;
      }
      if (eyez < (offz + 50))
      {
        eyez++;
      }
      break;
    case 12:
      if (eyex > (offx + 50))
      {
        eyex--;
      }
      if (eyex < (offx + 50))
      {
        eyex++;
      }
      if (eyey > 50)
      {
        eyey--;
      }
      if (eyey < 50)
      {
        eyey++;
      }
      if (eyez > (offz + 50))
      {
        eyez--;
      }
      if (eyez < (offz + 50))
      {
        eyez++;
      }
      break;
    }
  }

  void bodyRot(bool &robRotR, bool &robRotL)
  {
    if (robRotR)
    {
      bodyAngle +=
          3; // if the robot is supposed to be rotating right, we add 3 until we
             // hit a 90 degree angle (which is north/east/south/west)
      if ((bodyAngle == 90) || (bodyAngle == 180) || (bodyAngle == 270) ||
          (bodyAngle == 360) || (bodyAngle == 0))
      { // we only want to rotate to a 90 degree direction
        if (bodyAngle == 360)
        { // to prevent overflow we reset to 0 when we hit 360
          bodyAngle = 0;
        }
        robRotR = false; // when we hit a 90 degree angle we set it to no longer
                         // be rotating
      }
      if ((bodyAngle == -90) || (bodyAngle == -180) || (bodyAngle == -270) ||
          (bodyAngle == -360) || (bodyAngle == 0))
      {
        if (bodyAngle == -360)
        { // still must account for if the robot was previously rotated to the
          // left, checking for 90 degree angles in the negative direction as
          // well
          bodyAngle = 0;
        }
        robRotR = false;
      }
    }
    if (robRotL)
    {
      bodyAngle -= 3; // identical to previous if statement but reversed for
                      // rotating to the left instead
      if ((bodyAngle == -90) || (bodyAngle == -180) || (bodyAngle == -270) ||
          (bodyAngle == -360) || (bodyAngle == 0))
      {
        if (bodyAngle == -360)
        {
          bodyAngle = 0;
        }
        robRotL = false;
      }
      if ((bodyAngle == 90) || (bodyAngle == 180) || (bodyAngle == 270) ||
          (bodyAngle == 360) || (bodyAngle == 0))
      {
        if (bodyAngle == -360)
        {
          bodyAngle = 0;
        }
        robRotL = false;
      }
    }
  }

  void headRotate(bool headTurnR, bool headTurnL)
  {
    if (headAngle == 360)
    { // if the angle rotates a full 360 we reset it to prevent overflow
      headAngle = 0;
    }
    if (headAngle == -360)
    { // if the angle rotates a full 360 we reset it to prevent overflow
      headAngle = 0;
    }
    if (headTurnR == true)
    { // if the head turn right key is pressed down we rotate the head until it
      // no longer is
      headAngle -= 2;
    }

    if (headTurnL == true)
    { // if the head turn left key is pressed down we rotate the head until it
      // no longer is
      headAngle += 2;
    }

    if ((headAngle != 0) && (headTurnL == false) && (headTurnR == false))
    { // when we are no longer turning we reset the head to forward position
      if (headAngle > 0)
      {
        headAngle -= 2;
      }
      if (headAngle < 0)
      {
        headAngle += 2;
      }
    }
  }
};
#endif
