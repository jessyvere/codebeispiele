//
//  canal.h
//  wasserbau_1
//
//  Created by Jessica Moll on 01.06.18.
//

#pragma once
#include "ofMain.h"
#include "aqua.h"

#ifndef _CANALS
#define _CANALS

class Canals : public Aqua{
    int numberOfCanals;
    
public:
    Canals();
    void setup();
    void update();
    void draw();
    float cwidth;
    float yPosition;
    float sortingDistance;
    vector<float> xPositions;
    void setNumberOfCanals(int x);
    void setYPosition(float x);
    void setWidth(float x);


    void setSortingDistance(float x);
    float calculateNearestCanal(float x);

    float nearestCanalPosition;
    float minimalDistanceToCanal;
    
};

#endif
