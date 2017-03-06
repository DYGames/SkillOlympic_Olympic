#include "DXUT.h"
#include "Mountain.h"
#include "MountainPlayer.h"

void MtPlayer::update()
{
	Sprite::update();

	_flag->_position = _position - Vec2(0, 150);

	if (_jumpstate == 1)
		_jumpv += Time::dt * 500;

	if (_jumpv > 150)
		_jumpstate = 2;

	if (_jumpstate == 2)
		_jumpv -= Time::dt * 400;
	
	if (_jumpstate == 2)
		if (_jumpv <= 0)
			_jumpv = 0, _jumpstate = 0;

	if (_map[(int)_position.x - _cdis] > _map[(int)_position.x + _cdis])
	{
		_speed -= Time::dt * ((_map[(int)_position.x - _cdis] - _map[(int)_position.x + _cdis]) / 15.f);
	}
	else if (_map[(int)_position.x - _cdis] < _map[(int)_position.x + _cdis])
	{
		_speed += Time::dt * ((_map[(int)_position.x + _cdis] - _map[(int)_position.x - _cdis]) / 15.f);
	}
	else if (_isPlayer)
	{
		if (_speed > 0)
			_speed -= Time::dt * 2;
		if (_speed < 0)
			_speed += Time::dt * 2;
	}

	if (_isPlayer)
	{
		if (_speed > 14)
			_speed = 14;
	}
	else
	{
		if (_speed > 12)
			_speed = 12;
	}

	_position.x += _speed;

	if (_position.x < -_cdis)
		_position.x = -_cdis;
	if (_position.x > 9900 - _cdis)
		_position.x = 9900 - _cdis, _goalin = true;

	for (auto it : ((Mountain*)_parent->_parent)->_children)
	{
		if (it->_name == L"obs" && _jumpstate == 0)
		{
			if ((it->_position.x - _position.x) < 50)
			{
				Jump();
			}
		}
	}

	setY();
	setR();

	_position.y -= _jumpv;
}