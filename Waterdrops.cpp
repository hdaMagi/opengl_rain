/*
 * Waterdrops.cpp
 *
 *  Created on: 18.11.2016
 *      Author: jannis
 */

#include "Waterdrops.h"
#include "Waterdrop.h"


Waterdrops::Waterdrops() {
	// TODO Auto-generated constructor stub
	//glassPanel = GlassPanel();
	for (int idx = 0; idx < 75; idx++) {
		Waterdrop drop;
		waterdrops.push_back(drop);
		this->glassPanel.addMassAtPoint((int)drop.getXpos(), (int)drop.getYpos(), drop.getMass());
	}
}

Waterdrops::~Waterdrops() {
	// TODO Auto-generated destructor stub
}


void Waterdrops::update(){
	for (std::vector<Waterdrop>::iterator it = waterdrops.begin();
			it != waterdrops.end(); ++it) {
		Waterdrop & drop = *it;
		if (drop.isIsActive() == true) {
			glassPanel.addMassAtPoint((int)drop.getXpos(), (int)drop.getYpos(), -1*drop.getMass());
			GLfloat speed = glassPanel.calcSpeed(drop.getMass(), (int)drop.getXpos(), (int)drop.getYpos()) / 10;
			drop.setXSpeed(drop.getXSpeed() + speed);
			drop.setYSpeed(drop.getYSpeed() + speed);
			drop.updatePosition();
			glassPanel.addMassAtPoint((int)drop.getXpos(), (int)drop.getYpos(), drop.getMass());
			/* collision dectection could be in own method*/
			for (std::vector<Waterdrop>::iterator it2 = waterdrops.begin();
					it2 != waterdrops.end(); ++it2) {
				if (it != it2) {
//				printf("%i <--> %i - ", it,  it2);
					Waterdrop & drop1 = *it;
					Waterdrop & drop2 = *it2;
					if (drop1.isIsActive() == true
							&& drop2.isIsActive() == true) {
						bool x = drop1.detectCollision(&drop2);
						if (x == true) {
							drop1.joinDrops(&drop2);
						}
					}
				}
			}
		}
	}
}



