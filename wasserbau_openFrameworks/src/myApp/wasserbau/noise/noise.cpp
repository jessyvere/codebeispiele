#include "noise.h"

//--------------------------------------------------------------
Noise::Noise(){
    init();
}

//--------------------------------------------------------------
void Noise::setup(){
    scale = 0.1f;
    strength = 3*PI;
    shift.set(ofRandom(10000), ofRandom(10000));
    
    //berechnung der 4 Level der Flussbreite
    for(int i = 0; i < sizeof(levelsOfNoiseStrength) / sizeof(float); i++){
        fittingNoiseMedianOffset[i] = noiseMedianOffsetValues[int(levelsOfNoiseStrength[i])%4];
        levelsOfNoiseStrength[i] *= PI;
        fittingNoiseMedianOffset[i] *= PI;
    }
}

//z verschieben für neuen noise, scaling nicht beeinflusst
float Noise::multiOctavePerlinNoise2D(float x, float y, int octaves){
    
    float total = 0.0;
    float frequency = 0.01;
    float amplitude = 1.0;
    float maxValue = 0.0; //used for normalizing result to 0.0 - 1.0
    for (int i = 0; i < octaves; i++){
        total += ofNoise((x * frequency + shift.x), (y * frequency + shift.y)) * amplitude;
        maxValue += amplitude;
        frequency *= 2.0;
        amplitude *= 0.5;
    }
    return total/maxValue;
}

void Noise::reallyDraw(){
    img.allocate(m_size.x, m_size.y, OF_IMAGE_COLOR);
    img.setColor(ofColor::white);
    
    for (int w = 0; w < m_size.x; w++) {
        for (int h = 0; h < m_size.y; h++) {
            
            float noise = multiOctavePerlinNoise2D(w, h, 8);
            
            ofColor color = ofColor(noise * 255);
            img.setColor(w, h, color);
        }
    }
    
    img.update();
    img.draw(m_pos.x, m_pos.y);
}


//--------------------------------------------------------------
void Noise::update(){

}

//--------------------------------------------------------------
void Noise::draw(){
    
}


void Noise::generateNewSeed(){
    shift.set(ofRandom(10000), ofRandom(10000));
}

void Noise::setScale(float s){
    
    scale = s;
}



/*
 scale:
 verschieben um -shift
 scalieren
 verschieben um +shift
 */
