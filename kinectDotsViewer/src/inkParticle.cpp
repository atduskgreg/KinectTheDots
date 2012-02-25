//
//  inkSystem.cpp
//  emptyExample
//
//  Created by Gregory Borenstein on 2/23/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "inkParticle.h"

inkParticle::inkParticle() {
    radius = rand() % 2 + 1;
    mass = rand() % 2 + 1;
    topSpeed = rand() % 6 + 20;
    
    float c = 255 - rand() % 30;
    
    color = ofColor(0, 0, 0,c);
}

void inkParticle::update(){
    seek();
    super::update();
}

void inkParticle::draw() {
	ofSetColor(color.r, color.g, color.b, color.a);
    float spread = ofMap(vel.length(), 0, 25, 3, 0);
    
    ofPushStyle();
    ofEnableAlphaBlending();
    ofSetColor(0, color.a);
    
    
    //ink.draw(loc.x, loc.y, radius + spread, radius + spread);
    
    ofCircle(loc.x, loc.y, radius + spread);

    ofPopStyle();
}


void inkParticle::setTarget(ofPoint p){
    target = ofVec2f(p.x, p.y); 
}

void inkParticle::setLocation(ofVec2f l){
    loc = l;
}



void inkParticle::seek(){
    ofVec2f desired = target - loc;
    
    float distance = desired.length();
    
    ofVec2f force = desired.normalized();
    
    
    if (distance < 50) {
        float m = ofMap(distance,0,50,0,topSpeed);

        force *= m;
    } else {
        force *= topSpeed;
    }
        
    ofVec2f steer = force - vel;
    
    addForce(steer);
}
