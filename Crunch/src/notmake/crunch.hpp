/*
 * Filename: crunch.hpp
 * Date: 2/29/2016 2:21PM
 * Author: Daniel G Billings Jr
 *
 * This file will declare primary engine functions and necessary variables
 */
#ifndef CRUNCH_HPP
#define CRUNCH_HPP

#include <string>
#include <SFML/Graphics.hpp>
#include "ASManager.hpp"
#include "LayerManager.hpp"
#include "DrawManager.hpp"
#include "virtualIndexType.hpp"

namespace crunch
{
ASManager angelScript;
LayerManager layers;
DrawManager drawManager;
drawObjects objects;

void init(void);							///< Call once, initializes engine (registers functions in angelScript, creates a rendering context)
void reset(void);							///< Call to reset engine, will unload everything, and reload as if first run
void resetObjects(void);					///< Call to reset objects, will clear all game objects from memory, but scripts will continue where they are now (useful for changing levels, will need to reload all textures and sprites)


//These structs will help guard different types of indexes.
enum indexType {sprite, texture};
struct objIndex
{
	virtualIndex_t index;
	virtual indexType ident() = 0;
};

struct spriteIndex : objIndex
{
	drawType type;			//< The plan is to have several types of draw objects, here collectively refferred to as sprites, but not all of them will be.
	virtual indexType ident()
	{
		return (sprite);
	}
};
struct textureIndex : objIndex
{
	virtual indexType ident()
	{
		return (texture);
	}
};

}	//namespace crunch
#endif // CRUNCH_HPP
