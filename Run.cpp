#include "DXUT.h"
#include "Run.h"
#include "RunPlayer.h"

void Run::init()
{
	_game = new Sprite();
	_game->_active = true;
	this->addChild(_game);

	_ui = new Sprite();
	_ui->_active = true;
	this->addChild(_ui);

	Sprite* bg = new Sprite();
	bg->initWithFile(L"runback.png");
	bg->_position = Vec2(bg->_texture->_info.Width / 2.f, 360);
	_game->addChild(bg);

	_player = new RunPlayer();
	_player->initWithFile(L"runplayer.png");
	_player->_position = Vec2(130, 80);
	_player->_isPlayer = true;
	_game->addChild(_player);

	for (int i = 0; i < 3; i++)
	{
		_enemy[i] = new RunPlayer();
		_enemy[i]->initWithFile(L"runplayer.png");
		_enemy[i]->_position = Vec2(130, 210 + ((i + 1) * 110));
		_enemy[i]->_isPlayer = false;
		_game->addChild(_enemy[i]);
	}

	_btouch = true;
}

void Run::update()
{
	Node::update();

	_game->MoveTo(Vec2(640 - _player->_position.x, 0), 2);

	if (_game->_position.x > 0)
		_game->_position.x = 0;

	if (DXUTWasKeyPressed('Z'))
	{
		if (_btouch && !_player->_isGoal)
		{
			_player->_speed += Time::dt * 31;
			_btouch = false;
		}
	}
	if (DXUTWasKeyPressed('X'))
	{
		if (!_btouch && !_player->_isGoal)
		{
			_player->_speed += Time::dt * 31;
			_btouch = true;
		}
	}


}

void Run::exit()
{
	for (auto it : _children)
		removeChild(it);
}