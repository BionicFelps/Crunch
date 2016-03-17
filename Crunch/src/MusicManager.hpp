/*
 *	Created on: 03/13/2016
 *	Author:	Daniel G Billings Jr
*/
#ifndef MUSICMANAGER_HPP
#define MUSICMANAGER_HPP
#include <SFML/Audio.hpp>
#include <stack>
#include <iostream>
#include <vector>
#include <memory>
#include "IndexManager.hpp"
#include "AudioAsset.hpp"
#include "virtualIndexType.hpp"
namespace crunch
{
class MusicManager
{
public:
	struct node
	{
		//went with an old-school linked list here instead of std::unique_ptr for flexibility in creating and destroying sf::Music objects willy nilly, such as if it is "paused"
		//since it need not exist if it isn't playing, the playing offset is stored, and the music object in the node is deleted, another class will manage the total number of live sf::sound and sf::music
		//objects such that they are less than 256, an accurate count is kept for that class.
		virtualIndex_t index;
		AudioAsset assetInfo;
		sf::Time offset = sf::Time::Zero;
		sf::Time pausedOffset = sf::Time::Zero;
		bool paused = false;
		bool repeat = false;
		sf::Music* music = nullptr;
		node* nxt = nullptr;
		node* prv = nullptr;


		~node()
		{
			if(music != nullptr)
			{
				sf::Music::Status status = music->getStatus();
				if(status == sf::Music::Status::Paused || status == sf::Music::Status::Playing)
				{
					music->stop();
				}
				delete (music);
			}
			if(nxt != nullptr)
			{
				nxt->prv = prv;
			}
			if(prv != nullptr)
			{
				prv->nxt = nxt;
			}
		}
	};


	static const virtualIndex_t error;


	MusicManager();
	~MusicManager();
	unsigned int getCount();
	virtualIndex_t play(AudioAsset, bool repeat = true, sf::Time = sf::Time::Zero);	///<creates the music object and begins playing
	void play(virtualIndex_t);															///<Plays a previously paused instance
	void setOffset(virtualIndex_t nodeIndex, sf::Time);								///<sets the playing offset
	void pause(virtualIndex_t);														///<Pauses playing
	void stop(virtualIndex_t);															///<Stops playing and destroys the music object
	void close(virtualIndex_t);														///<Stops playing and destroys the entire node
	void update();			///<checks status of music and reacts accordingly (deletes sf::Music when it is stopped or paused)

private:
	node* root;
	IndexManager<virtualIndex_t> indexStore;
	unsigned int count;

	node* getNodeByIndex(virtualIndex_t);
	virtualIndex_t newNode();
};
}//namespace crunch
#endif // MUSICMANAGER_HPP
