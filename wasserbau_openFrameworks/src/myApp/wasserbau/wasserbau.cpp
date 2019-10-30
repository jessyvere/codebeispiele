#include "wasserbau.h"


//--------------------------------------------------------------
Wasserbau::Wasserbau(){
    //muss aqua hier initen, damit vector nicht null ist
    init();
}



//--------------------------------------------------------------
void Wasserbau::setup(){
    
    //ofAddListener(ofEvents().keyPressed, this, &Wasserbau::keyReleased);
    
    gui.setup();
    gui.add(numberOfParticles.setup("particles", 5000, 0, 10000));
    gui.add(noiseScale.setup("noise scale",  8.0, 1.0, 20.0));
    gui.add(noiseStrength.setup("noise strenght * PI", 8, 0, 16));
    gui.add(shiftMedian.setup("shiftMedian * PI", 0.5, -1, 1));
    gui.add(octaves.setup("octaves: ", 8, 1, 16));
    
    
    noiseSuccessfulTested = false;
    numberOfMinSuccessfulTests = 50;
    
    
    fbo.allocate(m_size.x, m_size.y, GL_RGBA);
    fbo.begin();
    ofClear(0);
    ofClearAlpha();
    fbo.end();
    
    noise.setup();
    noise.setScale(noiseScale);
    
    ofSetBackgroundAuto(false);
    ofBackground(0,0,0);
    //ofSetFrameRate(150);
    
    maximumParticles = 10000;
    currentParticles = numberOfParticles; //should be 0-100% of agentsCountMax for controller
    
    canals.setNumberOfCanals(5);
    canals.setYPosition(846.75);
    canals.setWidth(10);
    canals.setSortingDistance(60);
    canals.setup();
    
    testNoise();
    
    
    
}

//--------------------------------------------------------------
void Wasserbau::setAngleWithPerlinNoise(RiverParticle& p){
    
    p.setAngle((noise.multiOctavePerlinNoise2D((p.p.x/noise.scale), (p.p.y/noise.scale), octaves) * p.noiseStrength) + p.noiseMedianOffset);
    
    //p.setAngle((noise.multiOctavePerlinNoise2D((p.p.x/noise.scale), (p.p.y/noise.scale), octaves) * (noiseStrength*PI)) + ((shiftMedian)*PI));
    
    
    // p.setAngle((noise.multiOctavePerlinNoise2D((p.p.x/noise.scale), (p.p.y/noise.scale), 8) * (3*PI)) + PI);
    
    // p.setAngle((noise.multiOctavePerlinNoise2D((p.p.x/noise.scale)-(m_size.x/noise.scale)/2, (p.p.y/noise.scale) - (m_size.y/noise.scale)/2, 8) + PI/3) * noise.strength);
}

//--------------------------------------------------------------
void Wasserbau::testNoise() {
    
    //cout << noise.shift << endl;
    //noise.setScale(noiseScale);
    
    int numberOfTestParticles = int(m_size.x/2);
    testNoiseParticles.resize(numberOfTestParticles);
    testNoiseParticles.assign(numberOfTestParticles, RiverParticle());
    
    //generateNewSeed for noise until enough testParticles hit canalYLocation on screen
    //loop would work, but im too scared
    while(true){
        testCounter = 0;
        testSuccessfulCounter = 0;
        
        for(int i = 0; i < testNoiseParticles.size(); i++){
            testNoiseParticles[i].setup();
            testNoiseParticles[i].noiseStrength = 8*PI;
            testNoiseParticles[i].noiseMedianOffset = +0.5*PI;
            testNoiseParticles[i].p.set(float(i+2), 0.0);
            testNoiseParticles[i].p += m_pos;
            testNoiseParticles[i].hitCanalOrFlewOutsideBefore = false;
        }
        
        //update testParticles until all flew outside or hit canalYPosition
        while (testCounter < testNoiseParticles.size()){
            
            for (int i = 0; i < testNoiseParticles.size(); i++){
                
                if(!(testNoiseParticles[i].hitCanalOrFlewOutsideBefore)){
                    
                    setAngleWithPerlinNoise(testNoiseParticles[i]);
                    
                    testNoiseParticles[i].updateAsRiver();
                    
                    if(testNoiseParticles[i].p.x < 0 || testNoiseParticles[i].p.x > m_size.x || testNoiseParticles[i].p.y < 0){
                        testCounter++;
                        testNoiseParticles[i].hitCanalOrFlewOutsideBefore = true;
                        
                    } else if (testNoiseParticles[i].p.y >= canals.yPosition){
                        testCounter++;
                        testSuccessfulCounter++;
                        
                        if(testSuccessfulCounter >= numberOfMinSuccessfulTests){
                            cout << "test successful!" << endl;
                            testNoiseParticles.clear();
                            return; //or stop if enough hit canalYLocation
                        }
                        testNoiseParticles[i].hitCanalOrFlewOutsideBefore = true;
                    }
                }
            }
        }
        cout << "generate new seed" << endl;
        noise.generateNewSeed();
    }
}

//--------------------------------------------------------------
//if outside and not in the current array anymore, kill it
bool checkDead( RiverParticle &p){
    
    return (p.p.x > p.right_of_screen || p.p.x < p.left_of_screen || p.p.y < p.top_of_screen || p.p.y > p.bottom_of_screen);
}


//--------------------------------------------------------------
void Wasserbau::update(){
    
    //noise.setScale(noiseScale);
    
    currentParticles = numberOfParticles;
    
    
    
    for(int i = 0; i < riverParticles.size(); i++){
        
        if(riverParticles[i].p.y < canals.yPosition-canals.sortingDistance){
            setAngleWithPerlinNoise(riverParticles[i]);
            
            riverParticles[i].updateAsRiver();
            
            
        } else {
            
            if(!riverParticles[i].angleToCanalSet){
                riverParticles[i].angleToCanalSet = true;
                
                canals.calculateNearestCanal(riverParticles[i].p.x);
                
                canals.minimalDistanceToCanal = abs(canals.minimalDistanceToCanal += (ofRandom(-5, 5)));
                
                if (riverParticles[i].p.x-canals.nearestCanalPosition < 0) {
                    
                    riverParticles[i].setAngle(atan(canals.sortingDistance/(canals.minimalDistanceToCanal)));
                    
                } else {
                    
                    riverParticles[i].setAngle(PI-atan(canals.sortingDistance/(canals.minimalDistanceToCanal)));
                }
            }
            
            riverParticles[i].updateAsCanal();
            //riverParticles[i].overSortingDistance = riverParticles[i].p.y > canals.yPosition;
            if(riverParticles[i].p.y > canals.yPosition && !riverParticles[i].overSortingDistance){
                riverParticles[i].overSortingDistance = true;
            }
        }
        
        
    }
    
    
    ofRemove(riverParticles,checkDead);
    
    if(currentParticles != 0){
        
        newNoiseGenerated = false;
        
        //int(ofMap(currentParticles, 1,maximumParticles,10,1)
        if (ofGetElapsedTimeMillis() % int(ofMap(currentParticles, 1,maximumParticles,10,1)) == 0) {
            for(int i = 0; i < int(ofMap(currentParticles, 1,maximumParticles,1,30)); i++){
                riverParticles.push_back(RiverParticle());
                riverParticles.back().setup();
                
                switch(levelOfRiverWidth){
                    case 1:
                        riverParticles.back().noiseStrength = noise.levelsOfNoiseStrength[0];
                        riverParticles.back().noiseMedianOffset = noise.fittingNoiseMedianOffset[0];
                        
                        if(currentParticles > maximumParticles/4) levelOfRiverWidth = 2;
                        break;
                        
                    case 2:
                        if(currentParticles < (maximumParticles/4)*1) levelOfRiverWidth = 1;
                        
                        riverParticles.back().noiseStrength = noise.levelsOfNoiseStrength[1];
                        riverParticles.back().noiseMedianOffset = noise.fittingNoiseMedianOffset[1];
                        
                        if(currentParticles > (maximumParticles/4)*2) levelOfRiverWidth = 3;
                        break;
                        
                    case 3:
                        if(currentParticles < (maximumParticles/4)*2) levelOfRiverWidth = 2;
                        
                        riverParticles.back().noiseStrength = noise.levelsOfNoiseStrength[2];
                        riverParticles.back().noiseMedianOffset = noise.fittingNoiseMedianOffset[2];
                        
                        if(currentParticles > (maximumParticles/4)*3) levelOfRiverWidth = 4;
                        break;
                        
                    case 4:
                        riverParticles.back().noiseStrength = noise.levelsOfNoiseStrength[3];
                        riverParticles.back().noiseMedianOffset = noise.fittingNoiseMedianOffset[3];
                        
                        if(currentParticles < (maximumParticles/4)*3) levelOfRiverWidth = 3;
                        
                }
            }
        }
    }
}

//--------------------------------------------------------------
void Wasserbau::draw(){
    
    ofClear(0);
    fbo.begin();
    //noise.reallyDraw();
    gui.draw();
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ONE);
    glBlendEquation(GL_FUNC_REVERSE_SUBTRACT);
    
    float fClearOpacity = 0.03f;
    ofSetColor(0, 255*fClearOpacity);
    ofFill();
    ofDrawRectangle(m_pos.x-10, m_pos.y-10, m_size.x+10, m_size.y+10);
    
    glDisable(GL_BLEND);
    glBlendEquation(GL_FUNC_ADD);
    glBlendFunc(GL_SRC_COLOR, GL_DST_COLOR);
    ofSetColor(236, 43, 0, 200);
    ofFill();
    
    
    for(int i = 0; i < riverParticles.size(); i++){
        riverParticles[i].draw();
    }
    
    
    fbo.end();
    fbo.draw(0,0);
    
    
}



