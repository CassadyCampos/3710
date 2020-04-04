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

int recentfKey = 1; // camera angle starts at the '1' position. This position is
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
Robot robot;            // robot object to do most functions.
BuildingBuilder builder;

int eyeX = 0, eyeY = 4, eyeZ = -15;
int atX = 0, atY = 0, atZ = 0;
int GROUND_LEVEL = 0.5;
int frame_count = 0;
float rotateRect = 0.4;
float rotateCyil = 0.5;

static void PrintString(void *font, char *str)
{
    int i, len = strlen(str);

    for (i = 0; i < len; i++)
        glutBitmapCharacter(font, *str++);
}

void renderSphe(int x, int z) {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(eyeX, eyeY, eyeZ, atX, atY, atZ, 0, 1, 0);

    
    //* Move to building square
    float moveX = -40 + x * 60;
    float moveZ = -30 + x * 60;
    

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
    gluLookAt(eyeX, eyeY, eyeZ, atX, atY, atZ, 0, 1, 0);
   
    float cylXPos = -15 + x * 60;
    float cylZPos = -20 + z * 60;
    

    
    //* Draw rectangle ontop
    float rectXmin = -5 + x * 60;
    float rectXmax = -25 + x * 60;
    float rectZmax = -12 + x * 60;
    float rectZmin = -30 + x * 60;
    

    
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
    gluLookAt(eyeX, eyeY, eyeZ, atX, atY, atZ, 0, 1, 0);
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
//    glEnd();
    
    //* LEFT
    glColor3f(0.467, 0.533, 0.600);
//    glBegin(GL_QUADS);
    glVertex3f(buildingXmin, 30, buildingZmin); // top right
    glVertex3f(buildingXmin, 30, buildingZmax); // top left
    glVertex3f(buildingXmin, GROUND_LEVEL, buildingZmax); // bot left
    glVertex3f(buildingXmin, GROUND_LEVEL, buildingZmin); // bot right
//    glEnd();
    
    //* LEFT WINDOW -- Change z value to make window smaller
    //* building. Extend x value out so appears infront of building
    for (int i = 1; i < 4; i++) {
        if (i * 12 > 30) {
            break;
        } else {
            glColor3f(0.941, 1.000, 1.000); // Azure
//            glBegin(GL_QUADS);
            glVertex3f(buildingXmin+0.1, i*12, buildingZmin - 2); // top right
            glVertex3f(buildingXmin+0.1, i*12, buildingZmax + 2); // top left
            glVertex3f(buildingXmin+0.1, i*8, buildingZmax + 2); // bot left
            glVertex3f(buildingXmin+0.1, i*8, buildingZmin - 2); // bot right
//            glEnd();
        }
    }

    //*BACK
    glColor3f(0.467, 0.533, 0.600);
//    glBegin(GL_QUADS);
    glVertex3f(buildingXmax, 30, buildingZmin); // top right;
    glVertex3f(buildingXmin, 30, buildingZmin); // top left
    glVertex3f(buildingXmin, GROUND_LEVEL, buildingZmin); // bot left
    glVertex3f(buildingXmax, GROUND_LEVEL, buildingZmin); // bot right
//    glEnd();
    
    //* RIGHT
    glColor3d(0.467, 0.533, 0.600);
//    glBegin(GL_QUADS);
    glVertex3f(buildingXmax, 30, buildingZmin); // top right
    glVertex3f(buildingXmax, 30, buildingZmax); // top left
    glVertex3f(buildingXmax, GROUND_LEVEL, buildingZmax); // bot left
    glVertex3f(buildingXmax, GROUND_LEVEL, buildingZmin); // bot right
//    glEnd();
    
    //* TOP
    glColor3d(0.467, 0.533, 0.600);
//    glBegin(GL_QUADS);
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
    
    gluLookAt(eyeX, eyeY, eyeZ, atX, atY, atZ, 0, 1, 0);
    
    srand(time(NULL));
    int ran;
    
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            ran = 1 + rand() % 3;
                
            switch (ran) {
                case 1:
                    renderBuild(i,j);
                    renderCyli(i, j);
                    renderSphe(i, j);
                    break;
                case 2:
                    renderCyli(i, j);
                    renderBuild(i,j);
                    renderSphe(i, j);
                    break;
                case 3:
                    renderSphe(i, j);
                    renderCyli(i, j);
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

    gluLookAt(eyeX, eyeY, eyeZ, atX, atY, atZ, 0, 1, 0);

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
//    glEnd();
    
    //* VERTICLE ROAD STRIPES*
    glColor3f(1.0, 1.0 , 0.0); // Just yellow
//    glBegin(GL_QUADS);
    for (int i = 0; i < 20; i++) {
        glVertex3f(-54 + i * 60, GROUND_LEVEL + 0.05, 1150);
        glVertex3f(-56 + i * 60, GROUND_LEVEL + 0.05, 1150);
        //* BOTTOM VERTICES
        glVertex3d(-56 + i * 60, GROUND_LEVEL + 0.05, -50);
        glVertex3d(-54 + i * 60, GROUND_LEVEL + 0.05, -50);
    }
//    glEnd();


    //* HORIZONTAL ROADS
    glColor3f(0.412, 0.412, 0.412);

//    glBegin(GL_QUADS);
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
//    glEnd();

    //* HORIZONTAL ROAD STRIPES
    glColor3f(1.0, 1.0, 0.0); // Yellow
//    glfBegin(GL_QUADS);
    for (int i = 0; i < 20; i++) {
        glVertex3f(-60, GROUND_LEVEL + 0.05, -56 + i * 60);
        glVertex3f(-60, GROUND_LEVEL + 0.05, -54 + i * 60);
        glVertex3f(1150, GROUND_LEVEL + 0.05, -54 + i * 60);
        glVertex3f(1150, GROUND_LEVEL + 0.05, -56 + i * 60);
    }
    glEnd();
//    glFlush();
}

void CallBackRenderScene(void)
{
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
      robot.drawRobot(); // draw robot into the world
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

    //  robot.headRotate(headTurnR, headTurnL); // function for rotating head if head
    //                                          // is supposed to be rotating
    //
    //  robot.bodyRot(
    //      robRotR,
    //      robRotL); // function for rotating body if body is supposed to be rotating
    //  robot.moveCam(
    //      recentfKey); // passing an int to identify what the current camera angle
    //                   // should be, moving there if it already isn't
}
void processHits(GLint hits, GLuint buffer[])
{
    unsigned int i, j;
    GLuint names, *ptr, minZ, *ptrNames, numberOfNames;

    printf("hits = %d\n", hits);
    ptr = (GLuint *)buffer;
    minZ = 0xffffffff;
    for (i = 0; i < hits; i++)
    {
        names = *ptr;
        ptr++;
        if (*ptr < minZ)
        {
            numberOfNames = names;
            minZ = *ptr;
            ptrNames = ptr + 2;
        }

        ptr += names + 2;
    }
    printf("The closest hit names are:");
    ptr = ptrNames;
    if (hits == 0)
    { // if no building are hit, we get out of this function as nothing more is to
        // be done
        return;
    }
    for (j = 0; j < numberOfNames; j++, ptr++)
    {
        std::cout << *ptr % 400 << std::endl;
        if (buildHits[*ptr % 400] > 0)
        {                             // if we hit a building an the hit counter is still above 0
            buildHits[*ptr % 400]--; // subtract one from the hit counter
        }
        if (buildHits[*ptr % 400] == 0)
        { // if the hit counter is now 0, we destroy the building by setting the
            // number to generate it to a different value
            randNums[*ptr % 400] = 5; // this falls to a different case in our switch
                                      // statement and draws the building out of view
        }
    }
    printf("\n");
}

#define SIZE 10000

void mouse(int button, int state, int x, int y)
{
    GLuint selectBuf[SIZE]; // Selection buffer, which is an array of size 512.
    GLint hits;
    GLint viewport[4]; // Current viewport size. See below.
    if (!pausedState)
    {
        if (button == GLUT_LEFT_BUTTON &&
            state == GLUT_DOWN) // When the left mouse button is pressed, we start
                                // picking.
        {

            glGetIntegerv(GL_VIEWPORT, viewport); // Get the viewport size and put
                                                  // them into the array viewport.

            glSelectBuffer(
                SIZE,
                selectBuf);             // Create the selection buffer for preparing picking.
            glRenderMode(GL_SELECT); // Enter into the selection mode.

            glInitNames(); // Initialize the name stack. We need to push our objects
                           // into the stack.
            glPushName(-1);

            glMatrixMode(GL_PROJECTION); // Need to create a new projection matrix. We
                                         // select projection stack first.
            glPushMatrix();                 // Need to save the old one, which is our projection for
                                         // rendering on the screen.
            glLoadIdentity();             // Start a new projection matrix calculation.

            // Create 5x5 pixel picking region near the current mouse pointer location
            // This is where we need to pay attention to.
            //
            // Note the second parameter of gluPickMatrix. OpenGL has a different
            // origin for its window coordinates than the operation system. The second
            // parameter provides for the conversion between the two systems, i.e. it
            // transforms the origin from the upper left corner, as provided by GLUT
            // (related to the hardware, for this case, the mouse pointer's location),
            // into the bottom left corner, which is the one OpenGL uses.
            //
            // The picking region in this case is a 5x5 window. You may find that it
            // is not appropriate for your application. Do some tests to find an
            // appropriate value if you're finding it hard to pick the right objects.
            //
            gluPickMatrix((GLdouble)x, (GLdouble)(viewport[3] - y), 5.1, 5.1,
                          viewport);
            gluPerspective(45.0f, (GLfloat)Window_Width / (GLfloat)Window_Height, 1.0,
                           250.0f);
            glMatrixMode(GL_MODELVIEW);
            renderCity(GL_SELECT); // See below for the tricks we play here.

            glMatrixMode(GL_PROJECTION); // Now that the projection is done,
            glPopMatrix();                 // we don't need it any more. We have to
            glFlush();                     // retrieve the project matrix for displaying on the screen.

            hits = glRenderMode(GL_RENDER); // Leave the selection mode.

            processHits(hits, selectBuf); // To see which objects are hit. See below

            glutPostRedisplay();
        }
    }
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

        case 122:
                robot.cz += 1.0;
                robot.eyez += 1.0;
//                eyez += 1.0;
            
//            std::cout << "EyeZ: " << eyeZ << std::endl;

            // z key
            //      robot.cz +=
            //          offAddz; // move the robot forward, the offAddx and offAddz change
            //      robot.cx +=
            //          offAddx;           // based on the direction the robot is currently facing
            //      robot.eyez += offAddz; // to keep up with where the robot is
            //      robot.atz += offAddz;
            //      robot.atx += offAddx;
            //      robot.eyex += offAddx;
            //      robot.offx += offAddx;
            //      robot.offz += offAddz;
            //      switch (robot.cx)
            //      {
            //      case 545: // if at the boundary, we cannot go forward
            //        robot.cx -= 5;
            //        robot.offx -= 5;
            //        robot.atx -= 5;
            //        robot.eyex -= 5;
            //        break;
            //      case -665: // if at the boundary, we cannot go forward
            //        robot.cx += 5;
            //        robot.offx += 5;
            //        robot.atx += 5;
            //        robot.eyex += 5;
            //        break;
            //      default:
            //        break;
            //      }
            //      switch (robot.cz)
            //      { // if at the boundary, we cannot go forward
            //      case 545:
            //        robot.cz -= 5;
            //        robot.offz -= 5;
            //        robot.atz -= 5;
            //        robot.eyez -= 5;
            //        break;
            //      case -665: // if at the boundary, we cannot go forward
            //        robot.cz += 5;
            //        robot.offz += 5;
            //        robot.atz += 5;
            //        robot.eyez += 5;
            //        break;
            //      default:
            //        break;
            //      }
            break;
        case 97: // a key
            eyeY += 1.0;
                robot.eyey += 1.0;
            std::cout << "EyeY: " << eyeY << std::endl;
            break;
        case 115: // s key
            eyeY -= 1.0;
                robot.eyey -= 1.0;
            std::cout << "EyeY: " << eyeY << std::endl;
            break;
        case 113: // q key
            eyeX += 1.0;
                robot.eyex += 1.0;
            std::cout << "EyeX: " << eyeX << std::endl;

            break;
        case 119: // w key
            eyeX -= 1.0;
                robot.eyex -= 1.0;
            std::cout << "EyeX: " << eyeX << std::endl;
            break;
        case 114: // r key
            eyeZ += 1.0;
                robot.eyez += 1.0;
            std::cout << "EyeZ: " << eyeZ << std::endl;
            break;
        case 120: //x key
            eyeZ -= 1.0;
                robot.eyez -= 1.0;
            std::cout << "EyeZ " << eyeZ << std::endl;
            break;
        case 117: //u
            atX += 1.0;
                robot.atx += 1.0;
            std::cout << "atX: " << atX << std::endl;
            break;
        case 105: //i
            atX -= 1.0;
                robot.atx -= 1.0;
            std::cout << "atX: " << atX << std::endl;

            break;
        case 106: // j
            atY += 1.0;
                robot.aty += 1.0;
            std::cout << "atY: " << atY << std::endl;

            break;
        case 107: // k
            std::cout << "atY: " << atY << std::endl;

            atY -= 1.0;
                robot.aty -= 1.0;
            break;
        case 110: // n
            std::cout << "atZ: " << atZ << std::endl;

            atZ += 1.0;
                robot.atz += 1.0;
            break;
        case 109: //
            std::cout << "atZ: " << atZ << std::endl;
            atZ -= 1.0;
                robot.atz -= 1.0;
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

void speckeyboard(int key, int x, int y)
{
    if (!pausedState)
    {
        if (key == GLUT_KEY_F1)
        { // depending on what direction the robot is facing we set the camera
            // appropriately for the defined lookats
            if (robNorth)
            {
                recentfKey = 1; // recent fkey is simply a int specifying what camera
                                // angle to use relative to the robot
            }
            if (robEast)
            {
                recentfKey = 4;
            }
            if (robSouth)
            {
                recentfKey = 3;
            }
            if (robWest)
            {
                recentfKey = 2;
            }
        }

        if (key == GLUT_KEY_F2)
        { // if the f2 key is pressed we begin rotating the robots head to the right
            headTurnR = true;
        }

        if (key == GLUT_KEY_F3)
        { // if the f3 key is pressed we begin rotating the robots head to the left
            headTurnL = true;
        }

        if (key == GLUT_KEY_F4)
        {
            if (robNorth)
            {
                recentfKey = 1; // recent fkey is simply a int specifying what camera
                                // angle to use relative to the robot
            }
            if (robEast)
            {
                recentfKey = 4;
            }
            if (robSouth)
            {
                recentfKey = 3;
            }
            if (robWest)
            {
                recentfKey = 2;
            }
        }

        if (key == GLUT_KEY_F6)
        { // depending on what direction the robot is facing we set the camera
            // appropriately for the defined lookats
            if (robNorth)
            {
                recentfKey = 6;
            }
            if (robEast)
            {
                recentfKey = 5;
            }
            if (robSouth)
            {
                recentfKey = 8;
            }
            if (robWest)
            {
                recentfKey = 7;
            }
        }

        if (key == GLUT_KEY_F5)
        { // depending on what direction the robot is facing we set the camera
            // appropriately for the defined lookats
            if (robNorth)
            {
                recentfKey = 5;
            }
            if (robEast)
            {
                recentfKey = 8;
            }
            if (robSouth)
            {
                recentfKey = 7;
            }
            if (robWest)
            {
                recentfKey = 6;
            }
        }

        if (key == GLUT_KEY_F7)
        { // depending on what direction the robot is facing we set the camera
            // appropriately for the defined lookats
            if (robNorth)
            {
                recentfKey = 7;
            }
            if (robEast)
            {
                recentfKey = 6;
            }
            if (robSouth)
            {
                recentfKey = 5;
            }
            if (robWest)
            {
                recentfKey = 8;
            }
        }

        if (key == GLUT_KEY_F8)
        { // depending on what direction the robot is facing we set the camera
            // appropriately for the defined lookats
            if (robNorth)
            {
                recentfKey = 8;
            }
            if (robEast)
            {
                recentfKey = 7;
            }
            if (robSouth)
            {
                recentfKey = 6;
            }
            if (robWest)
            {
                recentfKey = 5;
            }
        }

        if (key == GLUT_KEY_F9)
        { // depending on what direction the robot is facing we set the camera
            // appropriately for the defined lookats
            if (robNorth)
            {
                recentfKey = 9;
            }
            if (robEast)
            {
                recentfKey = 12;
            }
            if (robSouth)
            {
                recentfKey = 11;
            }
            if (robWest)
            {
                recentfKey = 10;
            }
        }

        if (key == GLUT_KEY_F10)
        { // depending on what direction the robot is facing we set the camera
            // appropriately for the defined lookats
            if (robNorth)
            {
                recentfKey = 10;
            }
            if (robEast)
            {
                recentfKey = 9;
            }
            if (robSouth)
            {
                recentfKey = 12;
            }
            if (robWest)
            {
                recentfKey = 11;
            }
        }

        if (key == GLUT_KEY_F11)
        { // depending on what direction the robot is facing we set the camera
            // appropriately for the defined lookats
            if (robNorth)
            {
                recentfKey = 11;
            }
            if (robEast)
            {
                recentfKey = 10;
            }
            if (robSouth)
            {
                recentfKey = 9;
            }
            if (robWest)
            {
                recentfKey = 12;
            }
        }

        if (key == GLUT_KEY_F12)
        { // depending on what direction the robot is facing we set the camera
            // appropriately for the defined lookats
            if (robNorth)
            {
                recentfKey = 12;
            }
            if (robEast)
            {
                recentfKey = 11;
            }
            if (robSouth)
            {
                recentfKey = 10;
            }
            if (robWest)
            {
                recentfKey = 9;
            }
        }
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

int main(int argc, char **argv)
{
      // INITIALIZATION of class attributes of Robot
      robot.atx = 0;       // x position of lookat
      robot.aty = 0.0;     // y position of lookat
      robot.atz = 0;       // z position of lookat
      robot.eyex = 0;      // x position of camera eye
      robot.eyey = 4;      // y position of camera eye
      robot.eyez = -15;    // z position of camera eye
      robot.cx = 0;        // x position of robot
      robot.cy = -3.5;     // y position of robot
      robot.cz = 0;        // z position of robot
      robot.bodyAngle = 0; // the angle at which the robot is currently.
      robot.headAngle = 0; // angle the head is currently rotated
      robot.antRot = 0;    // angle of antenae rotating
      robot.offz = 0;      // x offset from the origin
      robot.offx = 0;      // z offset from the origin
      robot.nameCount = 0; // counter for naming the buildings for picking function

    // generate a random array of numbers 1-3 for our building generation. The
    // random seed is based on current system time so it should be different each
    // time you run it

    srand(time(NULL));
    for (int i = 0; i < 400; i++)
    {
        randNums[i] = rand() % 3 + 1;
    }

    /*using the previously generated array of random numbers, we associated a
   *sister array of hit values. building 1 is -1 for indestructible building 2
   *is 3 for strong building building 3 is 1 for weak building this array is
   *later accessed when a building is clicked on and the number is
   *de-incremented until it hits 0 which is then removed from the viewing area
   */

    for (int i = 0; i < 400; i++)
    {
        if (randNums[i] == 1)
        {
            buildHits[i] = -1;
        }
        if (randNums[i] == 2)
        {
            buildHits[i] = 3;
        }
        if (randNums[i] == 3)
        {
            buildHits[i] = 1;
        }
    }

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
