//
//  ofApp.h
//  wasserbau_1
//
//  Created by Jessica Moll on 03.06.18.
//
#pragma once

#ifndef ofApp_h
#define ofApp_h
#include "ofMain.h"
#include "ofEvents.h"
#include "wasserbau.h"


class ofApp : public ofBaseApp{
    
    float generalVolume;
    float particleMax = wasserbau.maximumParticles;
    float currentParticlesOnScreen = wasserbau.riverParticles.size();
    
    ofSoundPlayer audioBigRiver;
    ofSoundPlayer audioMediumRiver;
    ofSoundPlayer audioSmallRiver;
    
    bool playSoundSmallRiver;
    bool playSoundMediumRiver;
    bool playSoundBigRiver;
    
    float minParticlesForSmallRiverSound = 0;
    float maxParticlesForSmallRiverSound = particleMax/4;
    float minParticlesForMediumRiverSound = particleMax/3;
    float maxParticlesForMediumRiverSound = (particleMax/3)*2;
    float minParticlesForBigRiver = (particleMax/3*2)-3000;
    float maxParticlesForBigRiver = wasserbau.maximumParticles;
    
    float volumeSmallRiver;
    float volumeMediumRiver;
    float volumeBigRiver;
    
    
    ofImage img;
    Wasserbau wasserbau;
    int number;
    std::string numberOfShot;
    
    
    
    
public:
    void setup(){
        
        generalVolume = 1;
        
        audioSmallRiver.setLoop(true);
        audioSmallRiver.load("phase_3_innenhifbrunnen3.wav");
        audioMediumRiver.setLoop(true);
        audioMediumRiver.load("phase_2_handwerksbrunnen2.wav");
        audioBigRiver.setLoop(true);
        audioBigRiver.load("phase_1_stadtbad.wav");
        
        
        wasserbau.setup();
        particleMax = wasserbau.maximumParticles;
        currentParticlesOnScreen = wasserbau.riverParticles.size();
        
        minParticlesForSmallRiverSound = 0;
        maxParticlesForSmallRiverSound = particleMax/4;
        minParticlesForMediumRiverSound = particleMax/4;
        maxParticlesForMediumRiverSound = (particleMax/3)*2;
        minParticlesForBigRiver = (particleMax/3*2)-5000;
        maxParticlesForBigRiver = wasserbau.maximumParticles;
        
        audioSmallRiver.play();
        audioMediumRiver.play();
        audioBigRiver.play();
        
        audioSmallRiver.setVolume(0);
        audioMediumRiver.setVolume(0);
        audioBigRiver.setVolume(0);
        
        
        number = 0;
    };
    
    void update(){
        wasserbau.update();
        currentParticlesOnScreen = wasserbau.riverParticles.size();
        
        playSoundSmallRiver = currentParticlesOnScreen <= maxParticlesForSmallRiverSound;
        playSoundMediumRiver = currentParticlesOnScreen >= minParticlesForMediumRiverSound && currentParticlesOnScreen <= maxParticlesForMediumRiverSound;
        playSoundBigRiver = currentParticlesOnScreen >= minParticlesForBigRiver;
        
        if(playSoundSmallRiver){
            volumeSmallRiver = ofMap(currentParticlesOnScreen, minParticlesForSmallRiverSound, maxParticlesForSmallRiverSound, 0, 1, true);
            audioSmallRiver.setVolume(volumeSmallRiver);
            
            if (volumeSmallRiver < 0){
                audioSmallRiver.setVolume(0);
            }
        }
        
        if (playSoundMediumRiver){
            volumeMediumRiver = ofMap(currentParticlesOnScreen, minParticlesForMediumRiverSound, maxParticlesForMediumRiverSound, 0, 0.7, true);
            audioMediumRiver.setVolume(volumeMediumRiver);
            
        }
        
        if (playSoundBigRiver){
            volumeBigRiver = ofMap(currentParticlesOnScreen, minParticlesForBigRiver, maxParticlesForBigRiver, 0, 0.8, true);
            audioBigRiver.setVolume(volumeBigRiver);
        }
        
        
    };
    
    void draw(){
        wasserbau.draw();
    };
    
    void keyPressed(int key){
        if (key == 110){ //n
            wasserbau.noise.generateNewSeed();
            
        }
        
        if(key == 's'){
            numberOfShot = "screenshot_";
            numberOfShot += std::to_string(number);
            numberOfShot += ".jpg";
            
            img.grabScreen(0, 0 , ofGetWidth(), ofGetHeight());
            img.save(numberOfShot);
            number++;
        }
    };
};



#endif /* ofApp_h */


