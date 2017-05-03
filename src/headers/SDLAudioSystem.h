#pragma once

#include "IAudioSystem.h"

class SDLAudioSystem : public IAudioSystem
{
public:
	virtual void playSound(int soundID)
	{
		// Play sound using audio api...
	}

	virtual void stopSound(int soundID)
	{
		// Stop sound using audio api...
	}

	virtual void stopAllSounds()
	{
		// Stop all sounds using audio api...
	}
};
