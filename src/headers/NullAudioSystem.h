#pragma once

#include "IAudioSystem.h"

class NullAudioSystem : public IAudioSystem
{
public:
	virtual void playSound(int soundID)
	{
		// Do Nothing
	}

	virtual void stopSound(int soundID)
	{
		// Do Nothing
	}

	virtual void stopAllSounds()
	{
		// Do Nothing
	}
};
