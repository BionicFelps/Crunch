/* Author: Daniel G Billings Jr
 * Date: 3/10/2016
 * This class will hold information about an audio asset, its location on disk, and an identifier/index, uniquely identifying this sound
 * as well as a type (streamed or buffered), and the index of the buffer (in static memory) if applicable.
 *
 * This object is very simple, and does not manage its own memory
*/

#ifndef AUDIOASSET_HPP
#define AUDIOASSET_HPP

#include <SFML/Audio.hpp>
#include <string>

namespace crunch
{
class AudioAsset
{
public:
	enum assetType{buffered, streamed, notApplicable};

	assetType getType();

	std::string filePath;	///< File path to the sound
	int priority = 0;		///< A sound with higher priority will never be overridden by those with lower priority, default is 0 (may be negative)
	sf::SoundBuffer* buffer;	//if buffer == nullptr && filePath != "" AudioAsset should be streamed from disk.
};
}//namespace crunch
#endif // AUDIOASSET_HPP
