#pragma once
#include "ofMain.h"
#include "ofxGui.h"
#include "ofEvents.h"
#include "aqua.h"


#include "noise.h"
#include "canals.h"
#include "riverParticle.h"




#ifndef _WASSERBAU
#define _WASSERBAU
//ofLogNotice() << "key: " << key;
//cout << names[0] << end;




class Wasserbau : public Aqua { // : public ofBaseApp
    
    
    
    ofxIntSlider numberOfParticles;
    ofxIntSlider noiseScale;
    ofxIntSlider noiseStrength;
    ofxFloatSlider shiftMedian;
    ofxIntSlider octaves;
    
    ofxPanel gui;
    
    ofFbo fbo;
    
    bool noiseSuccessfulTested;
    int testCounter;
    int testSuccessfulCounter;
    int numberOfMinSuccessfulTests;
    
    int levelOfRiverWidth = 1;
    
    Canals canals;
    
    bool newNoiseGenerated;

    
public:
    //ofEvent<ofVec2f> clickedInside;

    int maximumParticles;
    int currentParticles;
    vector<RiverParticle> testNoiseParticles;
    vector<RiverParticle> riverParticles;
    
    
    Noise noise;
    
    int particlesInRiver;
    int particlesInSorting;
    int particlesInCanal;
    
    Wasserbau();
    void setup();
    void update();
    void draw();
    void setAngleWithPerlinNoise(RiverParticle& p);
    //void mousePressed(int x, int y, int button);
    void testNoise();
    void keyReleased(int key);
    void keyPressed(int key);


};

#endif
