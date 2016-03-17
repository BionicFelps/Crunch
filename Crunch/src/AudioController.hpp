#ifndef AUDIOCONTROLLER_HPP
#define AUDIOCONTROLLER_HPP

#include <SFML/Audio.hpp>
#include "AudioAsset.hpp"
#include "MusicManager.hpp"
#include "SoundManager.hpp"
#include "VectIndexMap.hpp"

namespace crunch
{
class AudioController
{
	struct audioIndex
	{
		AudioAsset asset;
		virtualIndex_t index;
		AudioAsset::assetType lastKnownType;
		sf::SoundBuffer buffer;
	};

public:
	AudioController();
private:
	MusicManager music;
	SoundManager sound;
	VectIndexMap<virtualIndex_t> musicList;
};
}
#endif // AUDIOCONTROLLER_HPP
