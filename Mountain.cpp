#include "DXUT.h"
#include "Mountain.h"
#include "MountainPlayer.h"
#include "GameMng.h"

void Mountain::init()
{
	_game = new Sprite();
	_game->_active = true;
	this->addChild(_game);

	_ui = new Sprite();
	_ui->_active = true;
	this->addChild(_ui);

	WCHAR mapstr[256];
	swprintf(mapstr, L"stage%d-1.png", GameMng::getInstance()->_mtstage + 1);

	_map1 = new Sprite();
	_map1->initWithFile(mapstr);
	_map1->_position = Vec2(_map1->_texture->_info.Width / 2.f, 360);
	_game->addChild(_map1);

	swprintf(mapstr, L"stage%d-2.png", GameMng::getInstance()->_mtstage + 1);
	_map2 = new Sprite();
	_map2->initWithFile(mapstr);
	_map2->_position = Vec2(_map2->_texture->_info.Width / 2.f, 360);
	_game->addChild(_map2);

	swprintf(mapstr, L"stage%d-3.png", GameMng::getInstance()->_mtstage + 1);
	_map3 = new Sprite();
	_map3->initWithFile(mapstr);
	_map3->_position = Vec2(_map3->_texture->_info.Width / 2.f, 360);
	_game->addChild(_map3);

	swprintf(mapstr, L"mtmap%d.png", GameMng::getInstance()->_mtstage + 1);
	_mtmap = new Sprite();
	_mtmap->initWithFile(mapstr);
	_mtmap->_position = Vec2(_mtmap->_texture->_info.Width / 2.f, 360);
	_mtmap->update();
	_mtmap->_visible = false;
	_game->addChild(_mtmap);

	D3DLOCKED_RECT r1;
	_mtmap->_texture->_texture->LockRect(0, &r1, 0, 0);
	D3DCOLOR* px = (D3DCOLOR*)r1.pBits;

	for (int x = 0; x < _mtmap->_texture->_info.Width; x++)
	{
		for (int y = 0; y < _mtmap->_texture->_info.Height; y++)
		{
			BYTE a = (px[y * _mtmap->_texture->_info.Width + x] & 0xFF000000) >> 24;
			if (a != '\0')
			{
				_map[x] = y;
				break;
			}
		}
	}

	_mtmap->_texture->_texture->UnlockRect(0);

	_player = new MtPlayer();
	_player->initWithFile(L"bike/korea/1.png");
	_player->_position = Vec2(210, 0);
	_player->_map = _map;
	_player->setY();
	_player->setR();
	_player->_name = L"korea";
	_player->_isPlayer = true;
	_game->addChild(_player);

	_player->_flag = new Sprite();
	_player->_flag->initWithFile(_player->_name + L".png");
	_player->_flag->_zorder = 1234;
	_game->addChild(_player->_flag);

	for (int i = 0; i < 3; i++)
	{
		_enemy[i] = new MtPlayer();
		if (i == 0)
			_enemy[0]->_name = L"japan";
		else if (i == 1)
			_enemy[1]->_name = L"usa";
		else
			_enemy[2]->_name = L"china";
		_enemy[i]->initWithFile(L"bike/" + _enemy[i]->_name + L"/1.png");
		_enemy[i]->_position = Vec2(200 - (i * 10), 0);
		_enemy[i]->_map = _map;
		_enemy[i]->setY();
		_enemy[i]->_isPlayer = true;
		_enemy[i]->setR();
		_game->addChild(_enemy[i]);
	}


	for (int i = 0; i < 3; i++)
	{
		_enemy[i]->_flag = new Sprite();
		_enemy[i]->_flag->initWithFile(_enemy[i]->_name + L".png");
		_enemy[i]->_flag->_zorder = 1234;
		_game->addChild(_enemy[i]->_flag);
	}


	_pedal = new Sprite();
	_pedal->initWithFile(L"pedal1.png");
	_pedal->_position = Vec2(640, 600);
	_pedal->ani._run = false;
	_ui->addChild(_pedal);

}

void Mountain::update()
{
	Node::update();

	_map1->_position.x = 5000.f + (_game->_position.x * (0.07f));
	_map2->_position.x = 5000.f + (_game->_position.x * (0.14f));

	_game->_position = Vec2(640 - _player->_position.x, _game->_position.y);
	if (_game->_position.x > 0)
		_game->_position.x = 0;

	if (DXUTWasKeyPressed('X'))
	{
		if (_pedal->_texture->_name == L"Resource/pedal1.png" && !_btouch)
		{
			_player->_pspeed -= 0.075f;
			_pedal->ani.initAni(_pedal, _player->_pspeed / 4.f, false, false);
			_pedal->ani.addClip(L"pedal2.png");
			_pedal->ani.addClip(L"pedal3.png");
			_pedal->ani.addClip(L"pedal4.png");
			_btouch = true;
		}
	}
	if (DXUTWasKeyPressed('Z'))
	{
		if (_pedal->_texture->_name == L"Resource/pedal4.png" && _btouch)
		{
			_player->_pspeed -= 0.075f;
			_pedal->ani.initAni(_pedal, _player->_pspeed / 4.f, false, false);
			_pedal->ani.addClip(L"pedal3.png");
			_pedal->ani.addClip(L"pedal2.png");
			_pedal->ani.addClip(L"pedal1.png");
			_btouch = false;
		}
	}

	if (DXUTWasKeyPressed(VK_SPACE))
	{
		_player->Jump();
	}

	for (int i = 0; i < 3; i++)
		_enemy[i]->_speed += Time::dt * (rand() % 3 + 2);

	if (_pedal->ani._run)
		_player->_speed += Time::dt * 7.5f;
	else
		if (_player->_speed > 0)
			_player->_speed -= Time::dt * 2.5f;

	if (_player->_pspeed <= 0.075f)
		_player->_pspeed = 0.075f;
	if (_player->_pspeed >= 0.75f)
		_player->_pspeed = 0.75f;

	if (_player->_goalin && _enemy[0]->_goalin && _enemy[1]->_goalin && _enemy[2]->_goalin && !_end)
	{
		_end = true;
		Sprite* e = new Sprite();
		e->initWithFile(L"scoreboard/mt.png");
		e->_position = Vec2(1280 + 640, 360);
		e->MoveTo(Vec2(640, 360), 4);
		e->_movetocallback = [=](){
			e->Delay(2.15f, [=](){
				e->MoveTo(Vec2(-640, 360), 4);
				e->_movetocallback = [=]()
				{
					removeChild(e);
				};
			});

		};
		_ui->addChild(e);

		_game->Delay(3, [=]()
		{
			GameMng::getInstance()->_mtstage = 1;
			Director::getInstance()->replaceScene(new Mountain());
		});
	}

}

void Mountain::Score()
{

}

void Mountain::exit()
{
	for (auto it : _children)
		removeChild(it);
}