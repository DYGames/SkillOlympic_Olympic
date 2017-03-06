#pragma once

#include "DXUT.h"
#include "Director.h"
#include "Sprite.h"

class MtPlayer;

class Mountain : public Scene
{
public:
	void init() override;
	void update() override;
	void exit() override;

	void Score();

	Sprite* _map1;
	Sprite* _map2;
	Sprite* _map3;

	Sprite* _game;
	Sprite* _ui;

	Sprite* _mtmap;

	MtPlayer* _player;
	MtPlayer* _enemy[3];

	Sprite* _pedal;

	bool _btouch = false;

	int _map[10000];

	bool _end = false;
};