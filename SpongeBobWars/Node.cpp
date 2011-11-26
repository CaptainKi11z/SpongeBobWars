//
//  Node.cpp
//  SpongeBobWars
//
//  Created by Philip Dougherty on 11/23/11.
//  Copyright 2011 UW Madison. All rights reserved.
//

#include <math.h>
#include "Node.h"
#include "Model.h"

void Node::initStuff()
{
    this->neighborNodes = new Node*[6];
    Node *  nN = Model::getSelf()->nullNode;
    assignNeighbors(nN, nN, nN, nN, nN, nN);
    this->numNeighborNodes = 0;
    row = NULL_LOCATION;
    column = NULL_LOCATION;
    layer = 0;
    
    if(!Node::compiled) Node::compileDL();
}

Node::Node()
{
    initStuff();
}

Node::Node(int type)
{
    this->type = type;
    initStuff();
}

Node::~Node()
{
    delete neighborNodes;
}

int Node::getRandomFreeNeighbor()
{
    int r = (int)(Model::random()*6);
    for(int i = 0; i < 6; i++)
    {
        if(this->neighborNodes[(r+i)%6] == Model::getSelf()->nullNode)
            return ((r+i)%6);
    }
    return -1;
}

int Node::getRandomNeighbor()
{
    int r = (int)(Model::random()*6);
    for(int i = 0; i < 6; i++)
    {
        if(this->neighborNodes[(r+i)%6] != Model::getSelf()->nullNode)
            return ((r+i)%6);
    }
    return -1;
}

void Node::assignNeighbors(Node *top, Node *topRight, Node *bottomRight, Node *bottom, Node *bottomLeft, Node *topLeft)
{
    this->neighborNodes[0] = top;
    this->neighborNodes[1] = topRight;
    this->neighborNodes[2] = bottomRight;
    this->neighborNodes[3] = bottom;
    this->neighborNodes[4] = bottomLeft;
    this->neighborNodes[5] = topLeft;
}

void Node::tick()
{
    
}


//DRAWABLE GEO FUNCTIONS
bool Node::compiled = false;
GLuint Node::displayList;

void Node::compileDL()
{
    //Sample compilation of a simple sphere 
    if(compiled) return;
    displayList = glGenLists(1);
    glNewList(displayList, GL_COMPILE);
    double sqrtOfThreeOverTwo = sqrt(3)/2;
    glBegin(GL_TRIANGLE_FAN);
    glVertex3d(1, layer, 0);
    glVertex3d(1/2, layer, sqrtOfThreeOverTwo);
    glVertex3d(-1/2, layer, sqrtOfThreeOverTwo);
    glVertex3d(-1, layer, 0);
    glVertex3d(-1/2, layer, -1*sqrtOfThreeOverTwo);
    glVertex3d(1/2, layer, -1*sqrtOfThreeOverTwo);    
    glEnd();
    gluSphere(gluNewQuadric(),50,50,50);
    glEndList();
    compiled = true;
}

void Node::draw()
{
    if(!Node::compiled) return;
    setColor(1.0, 0.0, 0.0, 0.0, 0.5, 1.0, 1.0);
    setGLColor();
    glCallList(Node::displayList);
}
