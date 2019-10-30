//
//  Header.h
//  wasserbau
//
//  Created by Jessica Moll on 31.05.18.
//
#pragma once
#include "ofMain.h"
#include "aqua.h"
//#include "noise.h"
//#include "canals.h"

#ifndef _RIVERPARTICLE
#define _RIVERPARTICLE

//ofLogNotice() << "key: " << key;

class RiverParticle : public Aqua{
    int width;
    int height;

   
    float randomOffset;
    float partialRandomOffset;
    float strokeWidth;

    /*
    float minimalDistanceToCanal;
    float angleToCanal;
    bool nearestCanalSet;
    int numberOfNearestCanal;
     */
    
    
    
public:
    RiverParticle();
    ofVec2f p, pOld;
    ofPolyline line; //löschen, wie smooth?

    float angle;
    float angleToCanalSet;

    float left_of_screen;
    float right_of_screen;
    float top_of_screen;
    float bottom_of_screen;
    
    float stepSize;
    bool overSortingDistance;
    
    bool isOutside;
    bool outsideOfArray;
    bool hitCanalOrFlewOutsideBefore;
    bool testSuccessful;
    
    void setup();
    void updateAsRiver();
    void updateAsCanal();
    void draw();
    void setAngle(float a);
    //void checkIfOutside();
    

    float xPositionWhenCanalCalculated;
    float nearestCanal;
    float distanceToMyCanal; //test
    float distanceAfterOffset;
    
    //
    bool inRiver;
    bool inSorting;
    bool inCanal;
    
    //
    float noiseStrength;
    float noiseMedianOffset;
};

#endif
