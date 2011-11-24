//
//  Model.cpp
//  SpongeBobWars
//
//  Created by Philip Dougherty on 11/23/11.
//  Copyright 2011 UW Madison. All rights reserved.
//
#include <iostream>
#include <string>

#include "Model.h"

Model * Model::selfPtr = NULL;

Model::Model()
{
    if(Model::selfPtr)
        throw (new std::string("DO NOT CALL CONSTRUCTOR DIRECTLY. USE Model::getSelf()"));
    
    this->nullNode = NULL;
    this->nullPlayer = NULL;
    this->nullUnit = NULL;
    
    //HELPER STUFF
    srand(0);
}

Model * Model::getSelf()
{
    if(!Model::selfPtr)
        Model::selfPtr = new Model();
    return selfPtr;
}

Model::~Model()
{
    delete playerArray;
    delete nodeArray;
    delete selfPtr;
}

void Model::setNumPlayers(int numPlayers)
{
    Model::getSelf()->numPlayers = numPlayers;
    Model::getSelf()->playerArray = new Player*[numPlayers];
}

void Model::setNumNodes(int numNodes)
{
    Model::getSelf()->numNodes = numNodes;
    Model::getSelf()->nodeArray = new Node*[numNodes];
}


/**
 * HELPER FUNCTIONS
 * Need not do anything specific towards model. Just a universal hub to put useful stuff.
 */

//Generates a value from 0-1. Just makes code cleaner.
double Model::random()
{
    return rand()/(double)RAND_MAX;
}

