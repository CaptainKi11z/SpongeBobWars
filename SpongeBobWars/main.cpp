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

void linkNodeToNeighbors(Node * node)
{
    int col;
    int row;
    for(int i = 0; i < 6; i++)
    {
        switch (i) {
            case 0:
                col = node->column;
                row = node->row+2;
                break;
            case 1:
                col = node->column+1;
                row = node->row+1;
                break;
            case 2:
                col = node->column+1;
                row = node->row-1;
                break;
            case 3:
                col = node->column;
                row = node->row-2;
                break;
            case 4:
                col = node->column-1;
                row = node->row-1;
                break;
            case 5:
                col = node->column-1;
                row = node->row+1;
                break;
            default:
                throw new std::string("PICKED NEIGHBOR OUTSIDE BOUNDS");
                break;
        }

        for(int j = 0; j < Model::getSelf()->numNodes; j++)
        {
            if(nodeArray[j]->column == col && nodeArray[j]->row == row)
            {
                node->neighborNodes[i] = nodeArray[j];
                nodeArray[j]->neighborNodes[(i+3)%6] = node;
                node->numNeighborNodes++;
                nodeArray[j]->numNeighborNodes++;
            }
        }
    }
}

void createNodeMap(Node * centerNode, int numNodes)
{
    //THIS FUNCTION IS IN-COMPLETE:
    // it gets stuck looking for a source node that is eligible for a neighbor. 
    // Needs to be tweaked to allow it to break MAP_DENSITY rule if necessary.
    
    
    //NOTE: Two important nodes in this algorithm- sourceNode and newNeighbor. 
    //  sourceNode is the node currently looking to add a neighbor (and should already be assigned a location). 
    //  newNeighbor is the node that is looking to be placed, and will be placed next to sourceNode.
    Node* sourceNode;
    Node* newNeighbor;
    int nodesLeftToBeAssigned = numNodes;
    int rNode;
    int rNeighbor;
    
    //Holds all nodes yet to be assigned. Node gets removed as it is assigned a location
    //Starts with all nodes but 'centerNode', as it is by definition already assigned
    Node** copyArray = new Node*[numNodes];
    for(int i = 0; i < numNodes-1; i++)
    {
        if(i < Model::getSelf()->numPlayers) copyArray[i] = nodeArray[i];
        else copyArray[i] = nodeArray[i+1];
    }
    nodesLeftToBeAssigned--;
    
    centerNode->row = 0;
    centerNode->column = 0;
    sourceNode = centerNode;

    bool nodeAssigned = false;
    //Assign each node a location
    while(nodesLeftToBeAssigned > 0)
    {
        //Pick a random node from copyArray
        rNode = (int)(Model::random()*nodesLeftToBeAssigned);
        newNeighbor = copyArray[rNode];
        nodeAssigned = false;
        
        //Algorithm ensures node is assigned
        while(!nodeAssigned)
        {
            //If the current source node is eligible to have a neighbor
            if(sourceNode->numNeighborNodes < MAP_DENSITY && ((rNeighbor = sourceNode->getRandomFreeNeighbor()) != -1))
            {
                //Assign the new node a location coordinate
                switch (rNeighbor) {
                    case 0:
                        newNeighbor->row = sourceNode->row+2;
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
                        newNeighbor->row = sourceNode->row-2;
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
                
                //Uncomment for debugging info
                //std::cout << "SourceNode: " << sourceNode->column << "," << sourceNode->row << std::endl;
                //std::cout << "NeighborNode: " << newNeighbor->column << "," << newNeighbor->row << "\n" << std::endl;

                //Link new node to all other neighbors based on coordinate
                linkNodeToNeighbors(newNeighbor);
                
                //Remove node from copyArray
                for(int i = rNode; i < nodesLeftToBeAssigned-1; i++)
                {
                    copyArray[i] = copyArray[i+1];
                }
                nodesLeftToBeAssigned--;
                
                nodeAssigned = true;
            }
            //Otherwise assign a current neighbor of the source node as the new source node
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

