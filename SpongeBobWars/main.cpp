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

void createNodeMap(Node * centerNode, int numNodes)
{
    Node* sourceNode;
    Node* newNeighbor;
    int nodesLeftToBeAssigned = numNodes;
    int rNode;
    int rNeighbor;
    
    Node** copyArray = new Node*[numNodes];
    for(int i = 0; i < numNodes; i++)
    {
        copyArray[i] = nodeArray[i];
    }
    
    centerNode->row = 0;
    centerNode->column = 0;
    sourceNode = centerNode;
    
    bool nodeAssigned = false;
    while(nodesLeftToBeAssigned > 0)
    {
        rNode = (int)Model::random()*nodesLeftToBeAssigned;
        newNeighbor = copyArray[rNode];
        nodeAssigned = false;
        while(!nodeAssigned)
        {
            if(sourceNode->numNeighborNodes < MAP_DENSITY && ((rNeighbor = newNeighbor->getRandomFreeNeighbor()) != -1))
            {
                sourceNode->neighborNodes[rNeighbor] = newNeighbor;
                newNeighbor->neighborNodes[(rNeighbor+3)%6] = sourceNode;
                sourceNode->numNeighborNodes++;
                newNeighbor->numNeighborNodes++;
                switch (rNeighbor) {
                    case 0:
                        newNeighbor->row = sourceNode->row+1;
                        newNeighbor->column = sourceNode->column;
                        break;
                    case 1:
                        newNeighbor->row = sourceNode->row+1;
                        newNeighbor->column = sourceNode->column+1;
                        break;
                    case 2:
                        newNeighbor->row = sourceNode->row-1;
                        newNeighbor->column = sourceNode->column+1;
                        break;
                    case 3:
                        newNeighbor->row = sourceNode->row-1;
                        newNeighbor->column = sourceNode->column;
                        break;
                    case 4:
                        newNeighbor->row = sourceNode->row-1;
                        newNeighbor->column = sourceNode->column-1;
                        break;
                    case 5:
                        newNeighbor->row = sourceNode->row+1;
                        newNeighbor->column = sourceNode->column-1;
                        break;
                    default:
                        throw new std::string("PICKED NEIGHBOR OUTSIDE BOUNDS");
                        break;
                }
                for(int i = rNode; i < nodesLeftToBeAssigned-1; i++)
                {
                    copyArray[i] = copyArray[i+1];
                }
                nodesLeftToBeAssigned--;
                nodeAssigned = true;
            }
            else
            {
                sourceNode = sourceNode->neighborNodes[sourceNode->getRandomNeighbor()];
            }
        }
    }
    
    delete copyArray;
}

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
    createNodeMap(centerNode, numNodes);
}


int main (int argc, const char * argv[])
{
    initGame(numPlayers, numNodes);
    
    std::cout << "Hello, World!\n";
    return 0;
}

