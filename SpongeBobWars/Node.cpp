//
//  Node.cpp
//  SpongeBobWars
//
//  Created by Philip Dougherty on 11/23/11.
//  Copyright 2011 UW Madison. All rights reserved.
//

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
    int r = (int)Model::random()*6;
    for(int i = 0; i < 6; i++)
    {
        if(this->neighborNodes[(r+i)%6] == Model::getSelf()->nullNode)
            return ((r+i)%6);
    }
    return -1;
}

int Node::getRandomNeighbor()
{
    int r = (int)Model::random()*6;
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
