#pragma once

class IAudioSystem
{
public:
	virtual ~IAudioSystem() {}
	virtual void playSound(int soundID) = 0;
	virtual void stopSound(int soundID) = 0;
	virtual void stopAllSounds() = 0;
};