#include "AudioAsset.hpp"
namespace crunch
{
AudioAsset::assetType AudioAsset::getType()
{
	//we determine the type of audio asset by the state of the buffer pointer and filePath variables
	//notApplicable means that this audioAsset hasn't been set yet.
	if(buffer == nullptr)
	{
		if(filePath == "")
		{
			return(notApplicable);
		}
		else
			return(streamed);
	}
	else
		return(buffered);
}
}//namespace crunch
