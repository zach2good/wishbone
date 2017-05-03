#pragma once

// From:
// http://gameprogrammingpatterns.com/service-locator.html

#include "IAudioSystem.h"
#include "NullAudioSystem.h"

class ServiceLocator
{
public:
	static void initialize() { service_ = &nullService_; }

	static IAudioSystem& getAudio() { return *service_; }

	static void provide(IAudioSystem* service)
	{
		if (service == nullptr)
		{
			// Revert to null service.
			service_ = &nullService_;
		}
		else
		{
			service_ = service;
		}
	}

private:
	static IAudioSystem* service_;
	static NullAudioSystem nullService_;
};