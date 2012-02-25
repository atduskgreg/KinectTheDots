//
//  ink.h
//  emptyExample
//
//  Created by Gregory Borenstein on 2/23/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#pragma once
#include "ofxParticle.h"
#include "ofMain.h"

class inkParticle : public ofxParticle {
public:
    typedef ofxParticle super;
	inkParticle();
        
    void update();
    
    void draw();

    void seek();
    void setLocation(ofVec2f l);
    void setTarget(ofPoint p);
    
    ofVec2f target;
    

};
