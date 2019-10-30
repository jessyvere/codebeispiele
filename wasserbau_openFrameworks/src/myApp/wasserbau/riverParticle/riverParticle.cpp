#include "riverParticle.h"
//ofLogNotice() << "key: " << key;

RiverParticle::RiverParticle(){
    init();
    width = m_size.x;
    height = m_size.y;
    left_of_screen = 0+m_pos.x;
    right_of_screen = m_size.x+m_pos.x;
    top_of_screen = 0+m_pos.y;
    bottom_of_screen = m_size.y + m_pos.y;
    
    
    angleToCanalSet = false; //evtl eins weg; hier oder setup
    strokeWidth = 0.3;
    isOutside = false;
    outsideOfArray = true;
    testSuccessful = false;
    //minimalDistanceToCanal = ofGetWidth();
    overSortingDistance = false;
    //nearestCanalSet = false;
    
    
    inRiver = true;
    inSorting = false;
    inCanal = false;
    
    
    
    //if offset & stepSize too similar the particle wont move
    while (abs(randomOffset + stepSize) <= 0.1 || abs(randomOffset - stepSize) <= 0.1) {
        randomOffset = ofRandom(-3, 3);
    }
}

void RiverParticle::setup(){
    isOutside = false;
    angleToCanalSet = false;
    p.set(ofRandom(width), 0);
    p += m_pos;
    pOld.set(p.x, p.y);
    
    stepSize = ofRandom(0.3, 3); //0.2, 3
    randomOffset = ofRandom(-2, 2);
    
    
    ofSetLineWidth(strokeWidth * stepSize + 1); //(strokeWidth * stepSize); 
    
    while (abs(randomOffset + stepSize) <= 0.1 || abs(randomOffset - stepSize) <= 0.1) {
        randomOffset = ofRandom(-3, 3);
    }
}



//--------------------------------------------------------------
void RiverParticle::updateAsRiver(){
    //noise with mouse
    //angle = (noise((p.x+mouseX)/noiseScale,(p.y+mouseY)/noiseScale) + PI/3) * noiseStrength;
    
    p.x += (cos(angle) * stepSize) + randomOffset;
    p.y += (sin(angle) * stepSize);
    
    //cout << "angle in updateAsRiver: " << angle << endl;
    
    //checkIfOutside();
    
}



//--------------------------------------------------------------
void RiverParticle::updateAsCanal(){
    
    if (!overSortingDistance){
        inRiver = false;
        inSorting = true;
        p.x += (cos(angle)*stepSize);
        p.y += (sin(angle)*stepSize);
    } else {
        inSorting = false;
        inCanal = true;
        p.y += stepSize;
    }
    
    //checkIfOutside();
}

//--------------------------------------------------------------
void RiverParticle::draw(){
    
    ofSetColor(240,240,240, 230); //, 60
    //line.getSmoothed(4,1);
    //ofEnableSmoothing();
    ofDrawLine(pOld.x, pOld.y, p.x, p.y);
    
    
    /*
     line.begin();
     line.addVertex(pOld.x, pOld.y);
     line.addVertex(p.x, p.y);
     line.end();
     
     
     //line.getSmoothed(4,1);
     line.draw();
     */
    pOld.set(p);
    
}

//--------------------------------------------------------------
void RiverParticle::setAngle(float a){
    angle = a;
}


/*
void RiverParticle::checkIfOutside() {
    
    
    if (isOutside) {
        if (!outsideOfArray) {
            p.x = ofRandom(width);
            p.y = 0;
            pOld.set(p);
            isOutside = false;
        }
        angleToCanalSet = false;
    }
 
}
 */
