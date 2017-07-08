#pragma once

#include <string>

#ifdef _WIN32
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

enum PlayerState {
	Stand,
	Walk,
	Crouch,
	Jump,
	Fall,
	GrabLedge,
	Celebrate,
	Dead

};
class Player : public Component {
public:
    // NOTE: Remember that these component classes are meant to act as data containers
    // There should be no logic in here really
    Player()
    {
        type = "player";
    }
    //~Player();
	
	// https://gamedevelopment.tutsplus.com/tutorials/basic-2d-platformer-physics-part-1--cms-25799
	// State Management
	PlayerState playerState = PlayerState::Stand;
	const char* getStateString() {
		switch (playerState)
		{
		case PlayerState::Stand:
			return "Stand";
			break;
		case PlayerState::Crouch:
			return "Crouch";
			break;
		case PlayerState::Walk:
			return "Walk";
			break;
		case PlayerState::Jump:
			return "Jump";
			break;
		case PlayerState::Fall:
			return "Fall";
			break;
		case PlayerState::GrabLedge:
			return "GrabLedge";
			break;
		case PlayerState::Celebrate:
			return "Celebrate";
			break;
		case PlayerState::Dead:
			return "Dead";
			break;
		default:
			return "Unknown";
			break;
		}
	}
	bool wasOnGround;
	bool isOnGround;

	bool wasPushingRightWall;
	bool isPushingRightWall;

	bool wasPushingLeftWall;
	bool isPushingLeftWall;

	bool wasPushingCeiling;
	bool isPushingCeiling;
	
	float walkSpeed = 1.0f;
	float jumpPower = 3.0f;

	unsigned int health = 100;
    
private:
};
