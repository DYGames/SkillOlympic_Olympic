#pragma once

#include "DXUT.h"
#include "Director.h"
#include "Sprite.h"

class RunPlayer;

class Run : public Scene
{
public:
	void init() override;
	void update() override;
	void exit() override;

	Sprite* _game;
	Sprite* _ui;

	RunPlayer* _player;
	RunPlayer* _enemy[3];

	bool _btouch;

};