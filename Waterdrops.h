/*
 * Waterdrops.h
 *
 *  Created on: 18.11.2016
 *      Author: jannis
 */

#ifndef WATERDROPS_H_
#define WATERDROPS_H_

#include <vector>

#include "GlassPanel.h"
#include "Waterdrop.h"

class Waterdrops {
public:
	Waterdrops();
	virtual ~Waterdrops();
	void update();

	const std::vector<Waterdrop>& getWaterdrops() const {
		return waterdrops;
	}

	void setWaterdrops(const std::vector<Waterdrop>& waterdrops) {
		this->waterdrops = waterdrops;
	}

private:
	std::vector<Waterdrop> waterdrops;
	GlassPanel glassPanel;
};

#endif /* WATERDROPS_H_ */
