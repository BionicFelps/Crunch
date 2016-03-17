/*
 *	Created on: 03/13/2016
 *	Author:	Daniel G Billings Jr
*/
#ifndef AUDIOSYSTEM_HPP
#define AUDIOSYSTEM_HPP


#include <SFML/Audio.hpp>
#include <map>
#include <string>
#include "AudioAsset.hpp"
#include "VectIndexMap.hpp"
#include "virtualIndexType.hpp"
namespace crunch
{
class AudioSystem
{
public:
	AudioSystem();
	void loadFromFile(std::string, AudioAsset::assetType = AudioAsset::buffered);
	virtualIndex_t play(AudioAsset);
	void stop(virtualIndex_t);
	void pause(virtualIndex_t);
private:
VectIndexMap<AudioAsset> assets;
VectIndexMap<sf::SoundBuffer> buffers;

};
}//namespace crunch
#endif // AUDIOSYSTEM_HPP
