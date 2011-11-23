//
//  main.cpp
//  SpongeBobWars
//
//  Created by Philip Dougherty on 11/23/11.
//  Copyright 2011 UW Madison. All rights reserved.
//

#include <iostream.h>
#include <stdlib.h>

#include "Model.h"

int numPlayers = 5;
int numNodes = 10;
Player ** playerArray;
Node ** nodeArray;

void initGame(int numPlayers, int numNodes)
{    
    //Make sure each player can have a starting node
    if(numNodes < numPlayers+1)
        throw new std::string("LESS NODES THAN PLAYERS");
    
    //Allocate space for all Players and Nodes
    Model::getSelf()->setNumPlayers(numPlayers);
    Model::getSelf()->setNumNodes(numNodes);
    
    //Copy pointers from model as it is likely they will be used often
    //**BE CAREFUL- DO NOT ABUSE THIS**
    playerArray = Model::getSelf()->playerArray;
    nodeArray = Model::getSelf()->nodeArray;

    //Create players and assign each a node
    for(int i = 0; i < numPlayers; i++)
    {
        playerArray[i] = new Player();
        nodeArray[i] = new Node(i%NUM_TYPES);
        playerArray[i]->conquerNode(nodeArray[i]);
    }
    
    //Create 'center' node (used in generating map
    Node * centerNode;
    centerNode = nodeArray[numPlayers] = new Node((int)Model::random()*NUM_TYPES);
    
    //Create neutral nodes
    for(int i = numPlayers+1; i < numNodes; i++)
    {
        nodeArray[i] = new Node((int)Model::random()*NUM_TYPES);
    }
    
    //Create map out of Nodes
    
}


int main (int argc, const char * argv[])
{
    initGame(numPlayers, numNodes);
    
    std::cout << "Hello, World!\n";
    return 0;
}

