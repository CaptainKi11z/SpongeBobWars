//
//  Model.h
//  SpongeBobWars
//
//  Created by Philip Dougherty on 11/23/11.
//  Copyright 2011 UW Madison. All rights reserved.
//
#ifndef H_MODEL
#define H_MODEL

/**
 * CONSTANTS
 */

//Node/Unit Types
#define NUM_TYPES  4
#define TYPE_WATER 0
#define TYPE_EARTH 1
#define TYPE_WIND  2
#define TYPE_FIRE  3

//Ship Types
#define NUM_SHIP_TYPES     4
#define SHIP_TYPE_GENERIC  0
#define SHIP_TYPE_FLAGSHIP 1
#define SHIP_TYPE_CARRIER  2
#define SHIP_TYPE_BATTLE   3

/**
 * END_CONSTANTS
 */


//Forward declarations- everything has access to everything (woah)
class Player;
class Node;
class Unit;
class Ship;
class Flagship;
class Fleet;

#include "Player.h"
#include "Node.h"
#include "Unit.h"
#include "Ship.h"
#include "Flagship.h"
#include "Fleet.h"

//Singleton class
class Model
{
public:
    static Model * selfPtr;
    static Model * getSelf();
    
    Player * nullPlayer;
    Node * nullNode;
    Unit * nullUnit;
    
    Player ** playerArray;
    Node ** nodeArray;
    
    int numPlayers;
    int numNodes;
    
    void setNumPlayers(int numPlayers);
    void setNumNodes(int numNodes);
    
    Model();
    ~Model();
    
    //HELPER FUNCTIONS
    static double random();
};

#endif