//
//  DrawableGeometry.h
//  MoshBall
//
//  Created by Philip Dougherty on 11/12/11.
//  Copyright 2011 UW Madison. All rights reserved.
//
#ifndef	DRAWABLEGEOMETRY_H
#define	DRAWABLEGEOMETRY_H

#import <OpenGL/OpenGL.h>
#import <GLUT/GLUT.h>

class DrawableGeometry
{
public:
    DrawableGeometry();         //Runs compile() if not already compiled
    virtual ~DrawableGeometry();
    
    int layer;
    
    static bool compiled;       //True iff displayList names a valid glDisplayList
    static GLuint displayList;  //Name of displaylist for object
    
    virtual void compileDL();   //Stores geometry in a displayList
    virtual void draw();        //draws geometry at current location
    
    //Sets specular, ambient, diffuse, and color arrays based on a color with weights on each
    virtual void setColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a, double sp, double di, double am);
    //Calls glMaterial on specular, ambient, diffuse, and glColor on color based on stored variables
    virtual void setGLColor();
    
protected:
    //Color data- format rgba (set with 'setColor(..)' for ease of use)
    GLfloat color[4];   
    GLfloat specular[4];
    GLfloat ambient[4];
    GLfloat diffuse[4];
};

#endif