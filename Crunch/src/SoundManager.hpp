/*
 *	Created on: 03/15/2016
 *	Author:	Daniel G Billings Jr
*/

#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H
#include <SFML/Audio.hpp>
#include <iostream>
#include "AudioAsset.hpp"
#include "VectIndexMap.hpp"
namespace crunch
{
class SoundManager
{
	//unlike sf::Music, sf::Sound may be copied, so we use our VectIndexMap instead of a linked list, the index map is a vector underneath but keeps track of a virtual index that never changes (even if the item moves inside the vector)
	struct node
	{
		AudioAsset assetInfo;
		sf::Time offset = sf::Time::Zero;
		sf::Time pausedOffset = sf::Time::Zero;
		bool paused = false;
		bool repeat = false;
		sf::Sound* sound;		//A pointer that can be created and destroyed willynilly to minimize the number of sound objects at any given moment
	};

public:
	SoundManager();
	~SoundManager();

	unsigned int getCount();
	virtualIndex_t play(AudioAsset, bool = true, sf::Time = sf::Time::Zero);	///<creates the sound object and begins playing
	void play(virtualIndex_t);															///<Plays a previously paused or stopped instance
	void setOffset(virtualIndex_t, sf::Time);								///<sets the playing offset
	void pause(virtualIndex_t);														///<Pauses playing
	void stop(virtualIndex_t);															///<Stops playing and destroys the sound object
	void close(virtualIndex_t);														///<Stops playing and destroys the entire node
	void update();			///<checks status of sounds and reacts accordingly (deletes sf::Music when it is stopped or paused)

private:
	unsigned int count;
	VectIndexMap<node> sounds;
};
}//namespace crunch
#endif // SOUNDMANAGER_H
