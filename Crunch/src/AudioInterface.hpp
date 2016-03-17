/* Date: 3/6/2016
 * Author: Daniel G Billings Jr
 *
 * This file will serve as the interface to the audio system in crunch.
 *
*/

#ifndef AUDIOINTERFACE_H
#define AUDIOINTERFACE_H
#include <SFML/Audio.hpp>
#include "IndexManager.hpp"
#include "indexType.hpp"
namespace crunch
{
struct soundIndex
{
	enum {buffered, streamed} type;
	index_t index;
};

class AudioInterface
{
public:
	AudioInterface(){}
	virtual void play(soundIndex)=0;
	virtual void stop(soundIndex)=0;
	virtual void pause(soundIndex)=0;
	virtual sf::Time getDuration(soundIndex)=0;
	virtual sf::Time getOffset(soundIndex)=0;
	virtual sf::Vector3f getPosition(soundIndex)=0;
	virtual bool getLoop()=0;
	virtual float getVolume()=0;
	virtual void setVolume(float)=0;
	virtual void setLoop()=0;
	virtual void setOffset(soundIndex, sf::Time)=0;
	virtual void setPitch(soundIndex, float)=0;
	virtual void setPosition(soundIndex, sf::Vector3f)=0;
};
} //namespace crunch

#endif // AUDIOINTERFACE_H
