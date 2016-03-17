#include "SoundManager.hpp"

namespace crunch
{
SoundManager::SoundManager()
{
}

SoundManager::~SoundManager()
{
	sounds.begin();
	for(unsigned int i = 0;i < sounds.size();i++)
	{
		node& cur = sounds.current();
		if(cur.sound != nullptr)
			delete (cur.sound);
		cur.sound = nullptr;
	}
	sounds.end();
}

unsigned int SoundManager::getCount()
{
	return(count);
}

virtualIndex_t SoundManager::play(AudioAsset asset, bool repeat, sf::Time offset)
{
	node temp;
	virtualIndex_t index = sounds.newItem(temp);
	++count;

	node& cur = sounds[index];

	cur.assetInfo = asset;
	cur.offset = offset;
	cur.repeat = repeat;

	cur.sound = new sf::Sound();
	cur.sound->setBuffer(*asset.buffer);
	cur.sound->setPlayingOffset(offset);
	cur.sound->setLoop(repeat);
	cur.sound->play();

	return(index);
}

void SoundManager::play(virtualIndex_t index)
{
	if(sounds.exists(index))
	{
		node& cur = sounds[index];

		if(cur.sound == nullptr)
		{
			cur.sound = new sf::Sound();
			++count;
			cur.sound->setBuffer(*cur.assetInfo.buffer);	//dereferencing a pointer to turn it into a reference, funny :P

			if(cur.paused)
			{
				cur.sound->setPlayingOffset(cur.pausedOffset);
				cur.paused = false;
			}
			else
				cur.sound->setPlayingOffset(cur.offset);
			cur.sound->setLoop(cur.repeat);
			cur.sound->play();
		}
	}
	else
	{
		std::cerr << "Index " << index << " does not exist, so the sound cannot be played." << std::endl;
	}
}

void SoundManager::setOffset(virtualIndex_t index, sf::Time offset)
{
	node& cur = sounds[index];

	cur.offset = offset;
	if(cur.sound != nullptr)
	{
		cur.sound->setPlayingOffset(offset);
	}
}

void SoundManager::pause(virtualIndex_t index)
{
	if(sounds.exists(index))
	{
		node& cur = sounds[index];

		if(cur.sound != nullptr)
		{
			cur.pausedOffset = cur.sound->getPlayingOffset();
			cur.paused = true;
			cur.sound->stop();
			delete (cur.sound);
			--count;
			cur.sound = nullptr;
		}
	}
	else
	{
		std::cerr << "Index " << index << " does not exist, so the sound cannot be paused." << std::endl;
	}
}

void SoundManager::stop(virtualIndex_t index)
{
	if(sounds.exists(index))
	{
		node& cur = sounds[index];

		if(cur.sound != nullptr)
		{
			cur.sound->stop();
			delete (cur.sound);
			--count;
			cur.sound = nullptr;
		}
	}
	else
	{
		std::cerr << "Index " << index << " does not exist, so the sound cannot be stopped." << std::endl;
	}
}

void SoundManager::close(virtualIndex_t nodeIndex)
{
	if(sounds.exists(nodeIndex))
	{
		node& cur = sounds[nodeIndex];

		if(cur.sound != nullptr)
		{
			cur.sound->stop();
			delete (cur.sound);
			cur.sound = nullptr;
			--count;
		}
		sounds.erase(nodeIndex);
	}
	else
	{
		std::cerr << "Index " << nodeIndex << " does not exist, so the sound cannot be closed." << std::endl;
	}
}

void SoundManager::update()
{
	sounds.begin();
	for(unsigned int i = 0;i < sounds.size();i++)
	{
		node& cur = sounds.current();
		if(cur.sound != nullptr)
		{
			sf::Sound::Status status = cur.sound->getStatus();

			if(status == sf::Sound::Status::Stopped)
			{
				delete(cur.sound);
				--count;
			}
		}
	}
	sounds.end();

}
}//namespace crunch
