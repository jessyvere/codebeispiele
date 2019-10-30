//
//  main.cpp
//  wasserbau_1
//
//  Created by Jessica Moll on 03.06.18.
//

#include <stdio.h>

#include "ofMain.h"
#include "ofApp.h"
/*
#include "aqua.h"

#include "noise.h"
#include "canals.h"
#include "riverParticle.h"
#include "wasserbau.h"
 */

//========================================================================




int main( ){
    Aqua aqua;
    aqua.init();
    ofSetupOpenGL(aqua.m_size.x, aqua.m_size.y ,OF_WINDOW);
    
    //706;
    //1129;
    //width auf m_width, same height
    //m_pos vector(0,0); verschiebung
    
    //565, 903
    // <-------- setup the GL context
    
    // this kicks off the running of my app
    // can be OF_WINDOW or OF_FULLSCREEN
    // pass in width and height too:
    // number of canals = 5
    
    //ofRunApp(new Wasserbau);
    ofRunApp(new ofApp);

    
    
    
}
