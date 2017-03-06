#pragma once

#include "DXUT.h"
#include "Sprite.h"

class MtPlayer : public Sprite
{
public:
	int* _map;

	float _speed;
	float _pspeed;

	int _jumpstate;
	float _jumpv;

	int _cdis = 100;

	bool _isPlayer;

	Sprite* _flag;

	bool _goalin;

	MtPlayer()
	{
		_speed = 0;
		_pspeed = 0.75f;
		_jumpstate = 0;
		_jumpv = 0;
		_goalin = false;
	}

	void Jump()
	{
		if (_jumpstate == 0)
			_jumpstate = 1;
	}

	void update() override;

	void setY()
	{
		float maxx = max(_map[(int)_position.x - _cdis], _map[(int)_position.x + _cdis]);
		float minn = min(_map[(int)_position.x - _cdis], _map[(int)_position.x + _cdis]);

		_position.y = ((((maxx - minn) / 2) + minn) - (_texture->_info.Height / 2.f));
	}
	void setR()
	{
		Vec2 front, back;
		front = Vec2(_position.x + _cdis, _map[(int)_position.x + _cdis] - (_texture->_info.Height / 2.f));
		back = Vec2(_position.x - _cdis, _map[(int)_position.x - _cdis] - (_texture->_info.Height / 2.f));

		_rotation = atan2f(front.y - back.y, front.x - back.x);
	}

};