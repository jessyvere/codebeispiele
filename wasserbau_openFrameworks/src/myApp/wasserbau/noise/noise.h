#pragma once
#include "ofMain.h"
#include "aqua.h"

#ifndef _NOISE
#define _NOISE
//ofLogNotice() << "key: " << key;

class Noise : public Aqua{

    ofVec2f seed;
    ofImage img;
    ofColor color;
    
public:
    ofVec2f shift;

    float scale;
    float strength;
    
    float levelsOfNoiseStrength[4] = {8, 7, 6, 4};
    float noiseMedianOffsetValues[4] = {0.5, 0, -0.5, 1};
    //float noiseMedianOffsetValues[4] = {0.5, -1, -0.5, 1};
    float fittingNoiseMedianOffset[4];
    
    Noise();
    void setup();
    void update();
    void draw();
    void reallyDraw();
    //void keyReleased(int key);
    void generateNewSeed();
    float multiOctavePerlinNoise2D(float x, float y, int octaves);
    void setScale(float s);
    
};

#endif
