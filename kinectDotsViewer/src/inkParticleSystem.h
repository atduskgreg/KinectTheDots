//
//  inkParticleSystem.h
//  emptyExample
//
//  Created by Gregory Borenstein on 2/23/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#pragma once
#include "ofxParticleSystem.h"
#include "inkParticle.h"
#include "ofMain.h"

class inkParticleSystem : public ofxParticleSystem {
public:
    //typedef ofxParticleSystem super;
	inkParticleSystem();
    virtual void addParticles( int amount );
    void seek();

    void setTarget(ofPoint p);
    void update();
    void draw();
    void addSprite(ofImage img);
    
    ofImage * sprite;
    
  std::list<inkParticle> particles;

};

