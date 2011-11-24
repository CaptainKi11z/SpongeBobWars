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
    //Water, Earth, Wind, Fire
    int type;
    
    //Used for information in linking/positioning
    int row;
    int column;
    
    int numNeighborNodes;
    Node ** neighborNodes; 
    //Mapping of array to neighbor:
    //neighborNodes[0] = top;
    //neighborNodes[1] = topRight;
    //neighborNodes[2] = bottomRight;
    //neighborNodes[3] = bottom;
    //neighborNodes[4] = bottomLeft;
    //neighborNodes[5] = topLeft;
    
    void initStuff();
    Node();
    Node(int type);
    ~Node();
    int getRandomFreeNeighbor();
    int getRandomNeighbor();
    void assignNeighbors(Node *top, Node *topRight, Node *bottomRight, Node *bottom, Node *bottomLeft, Node *topLeft);
    
    void tick(); //Do whatever needs to be done on the passing of a turn
};

#endif