/*
 * SpriteInfo.hpp
 *
 *  Created on: Feb 27, 2016
 *      Author: daniel
 */

#ifndef SPRITEINFO_HPP_
#define SPRITEINFO_HPP_
#include "Sprite.hpp"
#include "LayerManager.hpp"
namespace crunch
{

class SpriteInfo
{
public:
	Sprite sprite;			//Sprite data
	const int32_t& z = z;
private:
	int32_t z_level;				//z-level
	virtualIndex_t layer;	//index of layer

	SpriteInfo();
	virtual ~SpriteInfo();
	void setZ(int32_t level, LayerManager& layerManager, virtualIndex_t spriteIndex)
	{
		layerManager.removeSpriteFromLayer(z, layer);
		z_level = level;
		layer = layerManager.addSpriteToLayer(z, spriteIndex);
	}
};

} /* namespace crunch */

#endif /* SPRITEINFO_HPP_ */
