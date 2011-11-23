//
//  Node.h
//  SpongeBobWars
//
//  Created by Philip Dougherty on 11/23/11.
//  Copyright 2011 UW Madison. All rights reserved.
//
#ifndef H_NODE
#define H_NODE

class Node
{
public:
    int type;
    
    //Neighboring Node ptrs
    Node * top;
    Node * topRight;
    Node * bottomRight;
    Node * bottom;
    Node * bottomLeft;
    Node * topLeft;
    
    Node();
    Node(int type);
    ~Node();
    void assignNeighbors(Node *top, Node *topRight, Node *bottomRight, Node *bottom, Node *bottomLeft, Node *topLeft);
    
    void tick(); //Do whatever needs to be done on the passing of a turn
};

#endif