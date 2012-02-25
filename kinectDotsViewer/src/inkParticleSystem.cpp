//
//  inkParticleSystem.cpp
//  emptyExample
//
//  Created by Gregory Borenstein on 2/23/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "inkParticleSystem.h"

inkParticleSystem::inkParticleSystem(){
}

void inkParticleSystem::addParticles( int amount ) {
    cout << "adding ink particles" << endl;
	for (int i = 0; i < amount; i++) {
        inkParticle p = inkParticle();
		particles.push_back( p );
	}
}

void inkParticleSystem::addSprite(ofImage img){
}


void inkParticleSystem::seek(){
    for ( list<inkParticle>::iterator p = particles.begin(); p != particles.end(); ++p) {
		p->seek();
	}
}


void inkParticleSystem::setTarget(ofPoint t){
    for ( list<inkParticle>::iterator p = particles.begin(); p != particles.end(); ++p) {
        p->setTarget(t);
	}

}


void inkParticleSystem::update() {
	for ( list<inkParticle>::iterator p = particles.begin(); p != particles.end(); ++p) {
		p->update();
	}
}


void inkParticleSystem::draw() {
	for ( list<inkParticle>::iterator p = particles.begin(); p != particles.end(); ++p) {
		p->draw();
	}
}
