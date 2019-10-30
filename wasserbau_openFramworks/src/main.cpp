//
//  main.cpp
//  wasserbau_1
//
//  Created by Jessica Moll on 03.06.18.
//

#include <stdio.h>

#include "ofMain.h"
#include "ofApp.h"


//========================================================================




int main( ){
    Aqua aqua;
    aqua.init();
    ofSetupOpenGL(aqua.m_size.x, aqua.m_size.y ,OF_WINDOW);
    
    ofRunApp(new ofApp);

    
    
    
}
