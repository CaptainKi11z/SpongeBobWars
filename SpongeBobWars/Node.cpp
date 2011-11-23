//
//  Node.cpp
//  SpongeBobWars
//
//  Created by Philip Dougherty on 11/23/11.
//  Copyright 2011 UW Madison. All rights reserved.
//

#include "Node.h"
#include "Model.h"

Node::Node()
{
    
}

Node::Node(int type)
{
    this->type = type;
}

Node::~Node()
{
    
}

void Node::assignNeighbors(Node *top, Node *topRight, Node *bottomRight, Node *bottom, Node *bottomLeft, Node *topLeft)
{
    this->top = top;
    this->topRight = topRight;
    this->bottomRight = bottomRight;
    this->bottom = bottom;
    this->bottomLeft = bottomLeft;
    this->topLeft = topLeft;
}

void Node::tick()
{
    
}
