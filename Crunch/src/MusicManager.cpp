#include "MusicManager.hpp"
namespace crunch
{
const virtualIndex_t MusicManager::error = 50000;
MusicManager::MusicManager() : root(nullptr), count(0)
{
}

MusicManager::~MusicManager()
{
	node* cur = root;
	for (;cur != nullptr;cur = cur->nxt); //find the end
	while(cur->prv != nullptr)
	{
		node* temp;
		temp = cur->prv;
		delete(cur);
		cur = temp;
	}
	if(root != nullptr)
	{
		delete(root);
	}
}

unsigned int MusicManager::getCount()
{
	return(count);
}

virtualIndex_t MusicManager::play(AudioAsset asset, bool repeat, sf::Time offset)
{
	virtualIndex_t index = newNode();
	node* cur = new node();

	cur->prv->nxt = cur;	//set new next node on previous node

	cur->assetInfo = asset;
	cur->music = new sf::Music();

	if(!cur->music->openFromFile(asset.filePath))
	{
		delete (cur->music);
		cur->music = nullptr;
		std::cerr << "problem opening " << asset.filePath << std::endl;
		index = error;	//error index
	}
	else
	{
		cur->repeat = repeat;
		cur->music->setLoop(repeat);
		cur->music->setPlayingOffset(offset);
		cur->music->play();
		++count;
	}
	cur->offset = offset;
	cur->index = index;
	return (cur->index);
}

void MusicManager::play(virtualIndex_t nodeIndex)
{
	node* cur = getNodeByIndex(nodeIndex);

	if(cur != nullptr)
	{
		if(cur->music == nullptr)
		{
			cur->music = new sf::Music();
			if(!cur->music->openFromFile(cur->assetInfo.filePath))
			{
				delete (cur->music);
				cur->music = nullptr;
				std::cerr << "problem opening " << cur->assetInfo.filePath << std::endl;
			}
			else
			{
				cur->music->setLoop(cur->repeat);
				if(cur->paused)
					cur->music->setPlayingOffset(cur->pausedOffset);
				else
					cur->music->setPlayingOffset(cur->offset);
				cur->music->play();
				++count;
			}
		}
		else
		{
			std::cerr << "Failed to play paused streamed audio file with index " << nodeIndex << " because it is already playing" << "\n";
		}
	}
}

void MusicManager::setOffset(virtualIndex_t nodeIndex, sf::Time timeIndex)
{
	node* cur = getNodeByIndex(nodeIndex);

	if(cur != nullptr && cur->music != nullptr)
	{
		cur->music->setPlayingOffset(timeIndex);
	}
	cur->offset = timeIndex;
}

void MusicManager::pause(virtualIndex_t nodeIndex)
{
	node* cur = getNodeByIndex(nodeIndex);

	if(cur != nullptr)
	{
		if(cur->music != nullptr)
		{
			cur->paused = true;
			cur->pausedOffset = cur->music->getPlayingOffset();
			cur->music->stop();
			delete(cur->music);
			cur->music = nullptr;
			--count;
		}
		else
		{
			std::cerr << "Attempt to pause streamed audio file with index " << nodeIndex << " failed because it is already stopped or paused" << std::endl;
		}
		return;
	}
	else
	{
		std::cerr << "Attempt to pause streamed audio file with index " << nodeIndex << " failed because it does not exist" << std::endl;
	}
}

void MusicManager::stop(virtualIndex_t nodeIndex)
{
	node* cur = getNodeByIndex(nodeIndex);

	if(cur != nullptr)
	{
		if(cur->paused)
		{
			cur->paused = false;
			cur->pausedOffset = sf::Time::Zero;
		}
		else
			if(cur->music != nullptr)
			{
				cur->music->stop();
				delete(cur->music);
				cur->music = nullptr;
				--count;
			}
			else
				std::cerr << "Attempt to stop streamed audio file with index " << nodeIndex << " failed because it was already stopped" << std::endl;
		return;
	}
	std::cerr << "Attempt to stop streamed audio file with index " << nodeIndex << " failed because it does not exist" << std::endl;
}

void MusicManager::close(virtualIndex_t nodeIndex)
{
	node* cur = getNodeByIndex(nodeIndex);

	if(cur != nullptr)
	{
		if(cur == root)
		{
			root = root->nxt;
		}
		//return cur's index
		indexStore.returnIndex(cur->index);
		delete(cur);
		cur = nullptr; //not taking chances
		--count;
	}
}

void MusicManager::update()
{
	node* cur = root;
	while(cur != nullptr)
	{
		if(cur->music != nullptr)
		{
			if(cur->music->getStatus() == sf::Music::Status::Stopped)
			{
				delete (cur->music);
				cur->music = nullptr;
				--count;
			}
		}
		cur = cur->nxt;
	}
}

MusicManager::node* MusicManager::getNodeByIndex(virtualIndex_t nodeIndex)
{
	node* cur = root;
	while(cur->index != nodeIndex && cur != nullptr)
	{
		cur = cur->nxt;
	}
	return(cur);
}

virtualIndex_t MusicManager::newNode()
{
	node* cur = root;
	node* prv = nullptr;
	for(;cur != nullptr;cur = cur->nxt) //find the end
	{
		prv=cur;		//keep track of previous node to set it later
	}
	cur = new node();
	cur->prv = prv;			//set previous node on new currently visited node
	if(prv != nullptr)
	{
		cur->prv->nxt = cur;	//set new next node on previous node
	}
	else
	{
		root = cur;
	}
	return (indexStore.getIndex());

}
}//namespace crunch
