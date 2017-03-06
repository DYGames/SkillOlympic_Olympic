#pragma once

#include "DXUT.h"
#include "Director.h"
#include "Sprite.h"

class SwimPlayer;
class Swim : public Scene
{
public:
	enum SWIMPLAYERSTATE
	{
		WAITFORDIVE,
		ONDIVE,
		DHPNKICK,
		SWIM,
		WAITFORTURN,
		TURN,
		GOALIN,

	};

	void init() override;
	void update() override;
	void exit() override;

	Sprite* _game;
	Sprite* _ui;

	Sprite* _zb;
	Sprite* _xb;

	Sprite* _spaceb;

	SwimPlayer* _player;
	SwimPlayer* _enemy[3];

	bool _end = false;
};