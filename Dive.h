#pragma once

#include "DXUT.h"
#include "Director.h"
#include "Sprite.h"
#include "Board.h"

typedef std::pair<std::wstring, int> intstr;

class Dive : public Scene
{
public:
	enum DIVEPLAYERSTATE
	{
		PAUSE,
		GOTODIVE,
		GOTOHANDUP,
		WAITFORHANDUP,
		GOTOJUMP,
		ONTHEJUMP,
		BEGINDIVE,
		ONDIVE,



	};

	void init() override;
	void update() override;
	void exit() override;

	void JumpOnce(int c);

	Sprite* _game;
	Sprite* _ui;

	bool _touch = false;

	Sprite* _jumpcheckback;
	Sprite* _jumpcheck;

	DIVEPLAYERSTATE _state;

	Board* _board;

	Sprite* _player;

	Sprite* _springboard;

	Sprite* _circlebig;
	Sprite* _circle;

	Sprite* _arrow[3];

	Sprite* _tn;
	Sprite* _fc;

	Sprite* _judgeback;

	void Count();

	void FiveCircle();

	int _score[3];
	int _gamescore[3];
	int _resultscore[3];

	int _key[3];

	int _jmpcnt = 3;

	int _divecnt = 0;
	int _gamecnt = 0;
	int _resultcnt = 0;

};