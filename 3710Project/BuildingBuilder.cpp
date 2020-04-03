

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
#include "BuildingBuilder.hpp"

void BuildingBuilder::renderRectBuilding(int x, int z) {
      glLoadIdentity();
        gluLookAt(0, 0, 0, 0, 0, 0, 0, 1, 0);
        glTranslatef(-655, -4.95, -655);
        // GREY X2 BUILDINGS
        glColor3f(0.5f, 0.5f, 0.5f);
        // Top Building
        // BACK
    //    if (modeV == GL_SELECT)
    //    {
    //      glLoadName(nameCount);
    //      nameCount++;
    //    }
        glBegin(GL_QUADS);
        glVertex3f(x + 16.5, 0, z + 45);
        glVertex3f(x + 16.5, 30, z + 45);
        glVertex3f(x + 34, 30, z + 45);
        glVertex3f(x + 34, 0, z + 45);

        // RIGHT

        glVertex3f(x + 34, 30, z + 45);
        glVertex3f(x + 34, 0, z + 45);
        glVertex3f(x + 34, 0, z + 27.5);
        glVertex3f(x + 34, 30, z + 27.5);

        // LEFT

        glVertex3f(x + 16.5, 30, z + 27.5);
        glVertex3f(x + 16.5, 30, z + 45);
        glVertex3f(x + 16.5, 0, z + 45);
        glVertex3f(x + 16.5, 0, z + 27.5);

        // TOP

        glVertex3f(x + 16.5, 30, z + 27.5);
        glVertex3f(x + 16.5, 30, z + 45);
        glVertex3f(x + 34, 30, z + 45);
        glVertex3f(x + 34, 30, z + 27.5);

        // BOTTOM

        glVertex3f(x + 16.5, 0, z + 27.5);
        glVertex3f(x + 16.5, 0, z + 45);
        glVertex3f(x + 34, 0, z + 45);
        glVertex3f(x + 34, 0, z + 27.5);
        glEnd();

        // Bottom Left Building
        // BACK
        glBegin(GL_QUADS);
        glVertex3f(x + 5, 0, z + 22.5);
        glVertex3f(x + 5, 20, z + 22.5);
        glVertex3f(x + 22.5, 20, z + 22.5);
        glVertex3f(x + 22.5, 0, z + 22.5);

        // RIGHT

        glVertex3f(x + 22.5, 0, z + 5);
        glVertex3f(x + 22.5, 20, z + 5);
        glVertex3f(x + 22.5, 20, z + 22.5);
        glVertex3f(x + 22.5, 0, z + 22.5);

        // LEFT

        glVertex3f(x + 5, 0, z + 5);
        glVertex3f(x + 5, 20, z + 5);
        glVertex3f(x + 5, 20, z + 22.5);
        glVertex3f(x + 5, 0, z + 22.5);

        // TOP

        glVertex3f(x + 5, 20, z + 5);
        glVertex3f(x + 5, 20, z + 22.5);
        glVertex3f(x + 22.5, 20, z + 22.5);
        glVertex3f(x + 22.5, 20, z + 5);

        // BOTTOM

        glVertex3f(x + 5, 0, z + 5);
        glVertex3f(x + 5, 0, z + 22.5);
        glVertex3f(x + 22.5, 0, z + 22.5);
        glVertex3f(x + 22.5, 0, z + 5);
        glEnd();

        // Reset current matrix to identity
        glLoadIdentity();
}


void BuildingBuilder::renderCubeBuilding(int x, int z) {
   // Draw the one cylindrical building on the block

   // BLACK CYLINDER
   glColor3f(0.0f, 0.0f, 0.0f);
   //  glTranslatef(-605 + x, 0, -605 + z);
   glLoadIdentity();
   gluLookAt(0, 0, 0, 0, 0, 0, 0, 1, 0);
   glTranslatef(-660, 0, -660);
   glTranslatef(x + 30, -4.95, z + 30);
   glRotatef(90, -1, 0, 0);
   // Draw the cylinder based on the current matrix so it's it the correct
   // position
//   if (modeV == GL_SELECT)
//   {
//     glLoadName(nameCount);
//     nameCount++;
//   }
   glBegin(GL_TRIANGLE_STRIP);
   GLUquadricObj *obj = gluNewQuadric();
   gluCylinder(obj, 15, 15, 30, 10, 10);
   glEnd();
   // Reset current matrix to identity
   glLoadIdentity();
 }

void BuildingBuilder::renderCyliBuilding(int x, int z) {
    glLoadIdentity();
      gluLookAt(0, 0, 0, 0, 0, 0, 0, 1, 0);
      glTranslatef(-655, -4.95, -655);
      glColor3f(0.1f, 0.2f, 0.0f);
      // BACK
//      if (modeV == GL_SELECT)
//      {
//        glLoadName(nameCount);
//        nameCount++;
//      }
      glBegin(GL_QUADS);
      glVertex3f(x + 5, 0, z + 45);
      glVertex3f(x + 5, 30, z + 45);
      glVertex3f(x + 45, 30, z + 45);
      glVertex3f(x + 45, 0, z + 45);

      // RIGHT

      glVertex3f(x + 45, 30, z + 45);
      glVertex3f(x + 45, 0, z + 45);
      glVertex3f(x + 45, 0, z + 5);
      glVertex3f(x + 45, 30, z + 5);

      // LEFT

      glVertex3f(x + 5, 0, z + 5);
      glVertex3f(x + 5, 30, z + 5);
      glVertex3f(x + 5, 30, z + 45);
      glVertex3f(x + 5, 0, z + 45);

      // TOP

      glVertex3f(x + 5, 30, z + 5);
      glVertex3f(x + 5, 30, z + 45);
      glVertex3f(x + 45, 30, z + 45);
      glVertex3f(x + 45, 30, z + 5);

      // BOTTOM

      glVertex3f(x + 5, 0, z + 5);
      glVertex3f(x + 5, 0, z + 45);
      glVertex3f(x + 45, 0, z + 45);
      glVertex3f(x + 45, 0, z + 5);
      glEnd();
}
