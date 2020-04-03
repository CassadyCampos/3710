#ifndef BUILDINGBUILDER_H
#define BUILDINGBUILDER_H


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

class BuildingBuilder {
    public:
    void renderRectBuilding(int x, int z);
    void renderCyliBuilding(int x, int z);
    void renderCubeBuilding(int x, int z);
};

#endif
