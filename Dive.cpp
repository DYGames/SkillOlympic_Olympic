#include "DXUT.h"
#include "Dive.h"

void Dive::init()
{
	_game = new Sprite();
	_game->_active = true;
	this->addChild(_game);

	_ui = new Sprite();
	_ui->_active = true;
	this->addChild(_ui);

	_game->MoveTo(Vec2(1280, -340), 1);

	_board = new Board();
	_board->_sfinals[0] = L"korea";
	_board->_sfinals[1] = L"japan";
	_board->_sfinals[2] = L"brazil";
	_board->_sfinals[3] = L"china";
	_board->_sfinals[4] = L"russia";
	_board->_sfinals[5] = L"usa";
	_board->_sfinals[6] = L"aus";
	_board->_sfinals[7] = L"ukr";
	_board->init(_ui);
	_board->FadeOn();
	_board->update();
	_board->Delay(2, [=](){
		_board->FadeOff();
	});

	Sprite* back = new Sprite();
	back->initWithFile(L"diveback/1.png");
	back->_position = Vec2(-1280 + 640, back->_texture->_info.Height / 2.f);
	back->_zorder = -5;
	_game->addChild(back);

	Sprite* fback = new Sprite();
	fback->initWithFile(L"diveback/2.png");
	fback->_position = Vec2(-1280 + 640, fback->_texture->_info.Height / 2.f);
	fback->_zorder = -3;
	_game->addChild(fback);

	Sprite* crowd = new Sprite();
	crowd->initWithFile(L"diveback/c1.png");
	crowd->_position = Vec2(-1280 + 640, 750);
	crowd->ani.initAni(crowd, 0.13f);
	crowd->ani.addClip(L"diveback/c2.png");
	crowd->ani.addClip(L"diveback/c3.png");
	crowd->_zorder = -2;
	_game->addChild(crowd);

	Sprite* st2 = new Sprite();
	st2->initWithFile(L"diveback/st2.png");
	st2->_position = Vec2(-1280 + 960, 740);
	st2->_zorder = -1;
	_game->addChild(st2);

	Sprite* pilar = new Sprite();
	pilar->initWithFile(L"diveback/pilar.png");
	pilar->_position = Vec2(-1280 + 960, 520);
	pilar->_zorder = 1;
	_game->addChild(pilar);

	Sprite* st1 = new Sprite();
	st1->initWithFile(L"diveback/st1.png");
	st1->_position = Vec2(-1280 + 960, 740);
	st1->_zorder = 2;
	_game->addChild(st1);

	Sprite* top = new Sprite();
	top->initWithFile(L"diveback/top.png");
	top->_position = Vec2(-1280 + 640, (top->_texture->_info.Height / 2.f));
	top->_zorder = 4;
	_game->addChild(top);

	_player = new Sprite();
	_player->initWithFile(L"playersprite/pose/1.png");
	_player->_position = Vec2(-1280 + 120, 960 - (_player->_texture->_info.Height / 2.f));
	_player->_zorder = 3;
	_player->_name = L"player";
	_player->ani.initAni(_player, 0.25f);
	_player->ani.addClip(L"playersprite/pose/1.png");
	_player->ani.addClip(L"playersprite/pose/2.png");
	_game->addChild(_player);

	_jumpcheckback = new Sprite();
	_jumpcheckback->initWithFile(L"jumpcheckback.png");
	_jumpcheckback->_position = Vec2(640, 560);
	_jumpcheckback->_visible = false;
	_ui->addChild(_jumpcheckback);

	_jumpcheck = new Sprite();
	_jumpcheck->initWithFile(L"jumpcheck.png");
	_jumpcheck->_position = Vec2(490, 560);
	_jumpcheck->_visible = false;
	_ui->addChild(_jumpcheck);

	Sprite* inback = new Sprite();
	inback->initWithFile(L"indiveback/bg.png");
	inback->_position = Vec2(640, inback->_texture->_info.Height / 2.f);
	_game->addChild(inback);

	for (int i = 0; i < 4; i++)
	{
		Sprite* light = new Sprite();
		light->initWithFile(L"indiveback/light/1.png");
		light->ani.initAni(light);
		light->ani.addClip(L"indiveback/light/1.png");
		light->ani.addClip(L"indiveback/light/2.png");
		light->ani.addClip(L"indiveback/light/3.png");
		light->ani.addClip(L"indiveback/light/4.png");
		light->ani.addClip(L"indiveback/light/5.png");
		light->ani.addClip(L"indiveback/light/6.png");
		light->_position = Vec2(180 + (i * (510 - 180)), 670);
		_game->addChild(light);
	}
	
	Sprite* crowd1 = new Sprite();
	crowd1->initWithFile(L"diveback/c1.png");
	crowd1->_position = Vec2(640, 750 + 450);
	crowd1->ani.initAni(crowd1);
	crowd1->ani.addClip(L"diveback/c2.png");
	crowd1->ani.addClip(L"diveback/c3.png");
	_game->addChild(crowd1);

	Sprite* crowd2 = new Sprite();
	crowd2->initWithFile(L"diveback/c1.png");
	crowd2->_position = Vec2(640, crowd1->_position.y + 450);
	crowd2->ani.initAni(crowd2);
	crowd2->ani.addClip(L"diveback/c2.png");
	crowd2->ani.addClip(L"diveback/c3.png");
	_game->addChild(crowd2);

	Sprite* crowd3 = new Sprite();
	crowd3->initWithFile(L"diveback/c1.png");
	crowd3->_position = Vec2(640, crowd2->_position.y + 450);
	crowd3->ani.initAni(crowd3);
	crowd3->ani.addClip(L"diveback/c2.png");
	crowd3->ani.addClip(L"diveback/c3.png");
	_game->addChild(crowd3);

	Sprite* inback2 = new Sprite();
	inback2->initWithFile(L"indiveback/undertop.png");
	inback2->_position = Vec2(640, inback2->_texture->_info.Height / 2.f + (509));
	_game->addChild(inback2);

	Sprite* intop = new Sprite();
	intop->initWithFile(L"indiveback/top.png");
	intop->_position = Vec2(1280 - (intop->_texture->_info.Width / 2.f), (intop->_texture->_info.Height / 2.f));
	intop->_zorder = 7;
	_game->addChild(intop);


	_springboard = new Sprite();
	_springboard->initWithFile(L"indiveback/floor/1.png");
	_springboard->_position = Vec2(510, 500);
	_game->addChild(_springboard);

	_circlebig = new Sprite();
	_circlebig->initWithFile(L"circlebig.png");
	_circlebig->_position = Vec2(640, 600);
	_circlebig->_visible = false;
	_circlebig->_tag = -1;
	_ui->addChild(_circlebig);

	_circle = new Sprite();
	_circle->initWithFile(L"circle.png");
	_circle->_position = Vec2(640, 600);
	_circle->_visible = false;
	_ui->addChild(_circle);

	for (int i = 0; i < 3; i++)
	{
		_arrow[i] = new Sprite();
		_arrow[i]->initWithFile(L"left.png");
		_arrow[i]->_position = Vec2(640, 450 + i * 75);
		_arrow[i]->_visible = false;
		_arrow[i]->_zorder = 123;
		_ui->addChild(_arrow[i]);
	}

	_tn = new Sprite();
	_tn->initWithFile(L"playersprite/tornado/1.png");
	_tn->ani.initAni(_tn, 0.15f, false, true);
	_tn->ani._run = false;
	_tn->_visible = false;
	_tn->ani.addClip(L"playersprite/tornado/1.png");
	_tn->ani.addClip(L"playersprite/tornado/2.png");
	_tn->ani.addClip(L"playersprite/tornado/1.png");
	_tn->ani.addClip(L"playersprite/tornado/2.png");
	_tn->_position = _player->_position;
	_game->addChild(_tn);

	_fc = new Sprite();
	_fc->initWithFile(L"fc1.png");
	_fc->_position = Vec2(640, 360);
	_fc->ani.initAni(_fc, 0.1f, false, false);
	_fc->ani._run = false;
	_fc->_visible = false;
	_ui->addChild(_fc);
	_fc->ani.addClip(L"fc2.png");
	_fc->ani.addClip(L"fc3.png");
	_fc->ani.addClip(L"fc4.png");
	_fc->ani.addClip(L"fc5.png");
	_fc->ani.addClip(L"fc6.png");
	_fc->ani.addClip(L"fc7.png");
	_fc->ani._callback = [=](){_fc->ani._idx = 0; _fc->ani._delay = 0; _fc->_visible = false; _fc->ani._run = false; };

	_judgeback = new Sprite();
	_judgeback->initWithFile(L"judgeboard.png");
	_judgeback->_position = Vec2(640, 360);
	_judgeback->_scale = Vec2(0, 0);
	_ui->addChild(_judgeback);

	memset(_score, 0, sizeof(_score));
	memset(_gamescore, 0, sizeof(_score));
	memset(_key, 0, sizeof(_key));
	_jmpcnt = 3;
	_divecnt = 0;
	_gamecnt = 0;

	Sprite* wv = new Sprite();
	inback->update();
	wv->initWithFile(L"indiveback/wave/1.png");
	wv->_position = Vec2(640, inback->_rect.bottom - (wv->_texture->_info.Height / 2));
	wv->ani.initAni(wv);
	wv->_zorder = 99999;
	wv->ani.addClip(L"indiveback/wave/2.png");
	wv->ani.addClip(L"indiveback/wave/3.png");
	wv->ani.addClip(L"indiveback/wave/4.png");
	wv->ani.addClip(L"indiveback/wave/5.png");
	wv->ani.addClip(L"indiveback/wave/6.png");
	_game->addChild(wv);

	_state = DIVEPLAYERSTATE::PAUSE;
}

void Dive::update()
{
	Node::update();

	printf("%f %f\n", Input::mouseLocation().x, Input::mouseLocation().y);

	if (_state != DIVEPLAYERSTATE::PAUSE)
	{
		_game->MoveTo(Vec2((_player->_position.x * -1) + 640, (_player->_position.y * -1) + 360), 2);

		if (_state == DIVEPLAYERSTATE::GOTODIVE)
			_game->_position.x = 1280;
		if (_state == DIVEPLAYERSTATE::GOTODIVE && _game->_position.y < -340)
			_game->_position.y = -340;
		if (_state == DIVEPLAYERSTATE::GOTODIVE && _game->_position.x > 1280)
			_game->_position.x = 1280;

		if (_game->_position.y > 0)
			_game->_position.y = 0;
		if (_game->_position.x < 0)
			_game->_position.x = 0;

		if (_game->_position.y < -(2662 - 720))
			_game->_position.y = -(2662 - 720);
	}

	if (DXUTWasKeyPressed(VK_SPACE))
	{
		if (_state == DIVEPLAYERSTATE::PAUSE)
		{
			_tn->_visible = true;
			_tn->ani._run = true;

			_player->ani.removeAllClip();
			_player->ani._maxdelay = 0.1f;
			_player->ani._run = true;
			_player->ani.addClip(L"playersprite/walk/1.png");
			_player->ani.addClip(L"playersprite/walk/2.png");
			_player->ani.addClip(L"playersprite/walk/3.png");
			_player->ani.addClip(L"playersprite/walk/4.png");

			_state = DIVEPLAYERSTATE::GOTODIVE;

			_player->MoveTo(_player->_position + Vec2(570, 0), 6, false);
			_player->_movetocallback = [=]()
			{
				_player->MoveTo(_player->_position + Vec2(560, -150), 5, false);
				_player->_movetocallback = [=]()
				{
					_player->_scale.x = -1;
					_player->_zorder = 0;
					_player->MoveTo(_player->_position + Vec2(-560, -150), 5, false);
					_player->_movetocallback = [=]()
					{
						_player->_scale.x = 1;
						_player->_zorder = 3;
						_player->MoveTo(_player->_position + Vec2(560, -150), 5, false);
						_player->_movetocallback = [=]()
						{
							_state = DIVEPLAYERSTATE::GOTOHANDUP;
							FiveCircle();
							_player->MoveTo(_player->_position + Vec2(270, 0), 5, false);
							_player->_movetocallback = [=](){_state = DIVEPLAYERSTATE::WAITFORHANDUP; _player->ani.removeAllClip(); };
						};
					};
				};
			};
		}

		if (_state == DIVEPLAYERSTATE::WAITFORHANDUP)
		{
			_player->ani.initAni(_player, 0.1f, false, false);
			_player->ani.removeAllClip();
			_player->ani._run = true;
			_player->_texture = TextureMng::getInstance()->getTexture(L"playersprite/ready/1.png");
			_player->ani.addClip(L"playersprite/ready/1.png");
			_player->ani.addClip(L"playersprite/ready/2.png");
			_player->ani.addClip(L"playersprite/ready/3.png");
			_player->ani.addClip(L"playersprite/ready/3.png");
			_player->ani.addClip(L"playersprite/ready/3.png");
			_player->ani.addClip(L"playersprite/ready/3.png");
			_player->ani.addClip(L"playersprite/ready/3.png");
			_player->ani.addClip(L"playersprite/ready/2.png");
			_player->ani.addClip(L"playersprite/ready/1.png");
			_player->ani.addClip(L"playersprite/walk/2.png");
			_player->ani._callback = [=](){
				_state = DIVEPLAYERSTATE::GOTOJUMP;
				_player->ani._callback = nullptr;
				_player->ani.removeAllClip();
				_player->ani._run = true;
				_player->ani._loop = true;
				_player->_texture = TextureMng::getInstance()->getTexture(L"playersprite/walk/1.png");
				_player->ani.addClip(L"playersprite/walk/1.png");
				_player->ani.addClip(L"playersprite/walk/2.png");
				_player->ani.addClip(L"playersprite/walk/3.png");
				_player->ani.addClip(L"playersprite/walk/4.png");
				
				_player->MoveTo(_player->_position + Vec2(30, -20), 3, false);
				_player->_movetocallback = [=](){
					_player->MoveTo(_player->_position + Vec2(420, 0), 3, false);
					_player->_movetocallback = [=]()
					{
						_player->ani.removeAllClip();
						_player->ani._run = false;
						_player->Delay(1.5f, [=]()
						{
							_state = DIVEPLAYERSTATE::ONTHEJUMP;

							_jumpcheckback->_visible = true;
							_jumpcheck->_visible = true;

							_jumpcheck->_position = Vec2(490, 560);
							_jumpcheck->MoveTo(_jumpcheck->_position + Vec2(150, 50), 7, false);
							_jumpcheck->_tag = 1;
							_jumpcheck->_movetocallback = [=]()
							{
								if (_jumpcheck->_tag == 0)
									_jumpcheck->MoveTo(_jumpcheck->_position + Vec2(150, 50), 7, false), _jumpcheck->_tag = 1;
								else if (_jumpcheck->_tag == 1)
									_jumpcheck->MoveTo(_jumpcheck->_position + Vec2(150, -50), 7, false), _jumpcheck->_tag = 2;
								else if (_jumpcheck->_tag == 2)
									_jumpcheck->MoveTo(_jumpcheck->_position + Vec2(-150, 50), 7, false), _jumpcheck->_tag = 3;
								else if (_jumpcheck->_tag == 3)
									_jumpcheck->MoveTo(_jumpcheck->_position + Vec2(-150, -50), 7, false), _jumpcheck->_tag = 0;
							};
						});
					};
				};
			};
		}
		if (_state == DIVEPLAYERSTATE::ONTHEJUMP)
		{
			float dis = _jumpcheck->_position.distance(Vec2(490 + 150, 560 + 50));
			if (dis < 30)
			{
				if (_jmpcnt > 0)
					_jmpcnt--, JumpOnce(_jmpcnt);
				if (_jmpcnt == 0)
				{
					_jumpcheckback->_visible = false;
					_jumpcheck->_visible = false;
					_jumpcheck->_position = Vec2(490, 560);
					_state = DIVEPLAYERSTATE::BEGINDIVE;

					_player->ani.removeAllClip();
					_player->MoveTo(_player->_position + Vec2(0, 100), 4);
					_springboard->_texture = TextureMng::getInstance()->getTexture(L"indiveback/floor/3.png");
					_player->_movetocallback = [=]()
					{
						_player->MoveTo(_player->_position + Vec2(90, -200), 10, false);
						_player->_texture = TextureMng::getInstance()->getTexture(L"playersprite/dive/1.png");
						_player->_movetocallback = [=]()
						{
							_player->_texture = TextureMng::getInstance()->getTexture(L"playersprite/dive/2.png");
							_player->MoveTo(_player->_position + Vec2(80, 150), 10, false);
							_player->_movetocallback = [=]()
							{
								_player->_texture = TextureMng::getInstance()->getTexture(L"playersprite/dive/3.png");
								_player->MoveTo(_player->_position + Vec2(0, 75), 4, false);
								_player->_movetocallback = [=]()
								{
									_player->_texture = TextureMng::getInstance()->getTexture(L"playersprite/dive/4.png");
									_player->MoveTo(_player->_position + Vec2(0, 500), 25, false);
									_player->_movetocallback = [=]()
									{
										_springboard->_texture = TextureMng::getInstance()->getTexture(L"indiveback/floor/1.png");
										_state = DIVEPLAYERSTATE::ONDIVE;
										Count();
									};
								};
							};
						};
					};
				}
			}
			else
				_jmpcnt = 3;
		}

		
	}

	BYTE key;
	switch (_key[_circlebig->_tag])
	{
	case 0:
		key = VK_LEFT;
		break;
	case 1:
		key = VK_RIGHT;
		break;
	case 2:
		key = VK_UP;
		break;
	case 3:
		key = VK_DOWN;
		break;
	default:
		key = VK_F15;
		break;
	}

	if (DXUTWasKeyPressed(key) && _arrow[_circlebig->_tag]->_color.a == 1)
	{
		if (_state == DIVEPLAYERSTATE::ONDIVE)
		{
			if (_circlebig->_scale.x > 3.f / 4)
				if (_circlebig->_scale.distance(Vec2(3.f / 4, 3.f / 4)) < 0.1f)
					_score[0] = (0.15f - _circlebig->_scale.distance(Vec2(3.f / 4, 3.f / 4))) * 100, _arrow[0]->AlphaTo(0, Time::dt * 4, nullptr);
				else
					_score[0] = 0;
			else if (_circlebig->_scale.x > 2.f / 4)
				if (_circlebig->_scale.distance(Vec2(2.f / 4, 2.f / 4)) < 0.1f)
					_score[1] = (0.15f - _circlebig->_scale.distance(Vec2(2.f / 4, 2.f / 4))) * 100, _arrow[1]->AlphaTo(0, Time::dt * 4, nullptr);
				else
					_score[1] = 0;
			else if (_circlebig->_scale.x > 1.f / 4)
				if (_circlebig->_scale.distance(Vec2(1.f / 4, 1.f / 4)) < 0.1f)
					_score[2] = (0.15f - _circlebig->_scale.distance(Vec2(1.f / 4, 1.f / 4))) * 100, _arrow[2]->AlphaTo(0, Time::dt * 4, nullptr);
				else
					_score[2] = 0;

			if (_score[0] > 10)
				_score[0] = 10;
			if (_score[1] > 10)
				_score[1] = 10;
			if (_score[2] > 10)
				_score[2] = 10;

			WCHAR str[256];

			swprintf(str, L"%d.png", _score[_divecnt]);
			Sprite* n = new Sprite();
			n->initWithFile(str);
			n->_position = _arrow[_divecnt]->_position;
			_ui->addChild(n);
			n->ScaleTo(Vec2(1.4f, 1.4f), 2, [=](){ n->AlphaTo(0, Time::dt * 2, [=](){removeChild(n); });});
		}
	}
}

void Dive::Count()
{
	if (_gamecnt >= 2)
	{
		_player->Delay(1.5f, [=](){
			_judgeback->ScaleTo(Vec2(1, 1), 4, [=]()
			{
				_judgeback->Delay(4, [=]()
				{
					if (_resultcnt >= 2)
					{
						intstr score[4];
						score[0] = std::make_pair(_board->_sfinals[0], (_resultscore[0] + _resultscore[1] + _resultscore[2]) / 3.f);
						score[1] = std::make_pair(_board->_sfinals[1], rand() % 5 + 5);
						score[2] = std::make_pair(_board->_sfinals[2], rand() % 5 + 5);
						score[3] = std::make_pair(_board->_sfinals[3], rand() % 5 + 5);

						for (int i = 0; i < 4; i++)
						{
							if (score[i].second < score[i + 1].second)
							{
								std::swap(score[i], score[i + 1]);
							}
						}

						for (int i = 0; i < 4; i++)
						{
							if (score[i].second < score[i + 1].second)
							{
								std::swap(score[i], score[i + 1]);
							}
						}

						_board->_finals[0] = score[0].first;
						_board->_finals[1] = score[1].first;
						_board->_finals[2] = L"russia";
						_board->_finals[3] = L"usa";
						_board->FadeOn();
						_board->Delay(2, [=](){
							_board->FadeOff();
						});

						_judgeback->ScaleTo(Vec2(), 4, nullptr);
						_state = DIVEPLAYERSTATE::WAITFORHANDUP;
						_player->_position = Vec2(240, 310);
						_player->_texture = TextureMng::getInstance()->getTexture(L"playersprite/walk/2.png");
						memset(_score, 0, sizeof(_score));
						memset(_resultscore, 0, sizeof(_resultscore));
						memset(_gamescore, 0, sizeof(_gamescore));
						memset(_key, 0, sizeof(_key));
						_jmpcnt = 3;
						_divecnt = 0;
						_gamecnt = 0;
						_resultcnt = 0;
					}
					else
					{
						_judgeback->ScaleTo(Vec2(), 4, nullptr);
						_state = DIVEPLAYERSTATE::WAITFORHANDUP;
						_player->_position = Vec2(240, 310);
						_player->_texture = TextureMng::getInstance()->getTexture(L"playersprite/walk/2.png");
						memset(_score, 0, sizeof(_score));
						_resultscore[_resultcnt] = (_gamescore[0] + _gamescore[1] + _gamescore[2]) / 3.f;
						memset(_gamescore, 0, sizeof(_gamescore));
						memset(_key, 0, sizeof(_key));
						_jmpcnt = 3;
						_divecnt = 0;
						_gamecnt = 0;
						_resultcnt++;
					}
				});
			});
		});

		return;
	}

	_circlebig->_visible = true;
	_circle->_visible = true;
	_arrow[0]->_visible = true;
	_arrow[1]->_visible = true;
	_arrow[2]->_visible = true;


	for (int i = 0; i < 3; i++)
	{
		_key[i] = rand() % 4;
		switch (_key[i])
		{
		case 0:
			_arrow[i]->_texture = TextureMng::getInstance()->getTexture(L"left.png");
			break;
		case 1:
			_arrow[i]->_texture = TextureMng::getInstance()->getTexture(L"right.png");
			break;
		case 2:
			_arrow[i]->_texture = TextureMng::getInstance()->getTexture(L"up.png");
			break;
		case 3:
			_arrow[i]->_texture = TextureMng::getInstance()->getTexture(L"down.png");
			break;
		}

	}
	_circlebig->_tag = 0;
	_circlebig->ScaleTo(Vec2(3.f / 4, 3.f / 4), 0.75f, nullptr);
	_circlebig->_scaletocallback = [=]()
	{
		_circlebig->_tag = 1;
		_divecnt++;
		_circlebig->ScaleTo(Vec2(2.f / 4, 2.f / 4), 0.75f, nullptr);
		_circlebig->_scaletocallback = [=]()
		{
			_circlebig->_tag = 2;
			_divecnt++;
			_circlebig->ScaleTo(Vec2(1.f / 4, 1.f / 4), 0.75f, nullptr);
			_circlebig->_scaletocallback = [=]()
			{
				if (((_score[0] + _score[1] + _score[2]) / 3.f) > 5)
				{
					_gamescore[_gamecnt] = ((_score[0] + _score[1] + _score[2]) / 3.f);

					if (_gamecnt == 1)
						_player->MoveTo(_player->_position + Vec2(0, 1450), 25, false);
					else
						_player->MoveTo(_player->_position + Vec2(0, 700), 25, false);

					_player->_movetocallback = [=]()
					{
						_circlebig->_scale = { 1, 1 };
						_arrow[0]->_alphatospeed = 0;
						_arrow[1]->_alphatospeed = 0;
						_arrow[2]->_alphatospeed = 0;
						_arrow[0]->_color.a = 1;
						_arrow[1]->_color.a = 1;
						_arrow[2]->_color.a = 1;

						Count();
					};
				}
				else
				{
					_gamescore[_gamecnt] = 0;
				}
				_gamecnt++;
				_divecnt = 0;
				_circlebig->_visible = false;
				_circle->_visible = false;
				_arrow[0]->_visible = false;
				_arrow[1]->_visible = false;
				_arrow[2]->_visible = false;

				
			};
		};
	};

}

void Dive::JumpOnce(int c)
{
	_springboard->_texture = TextureMng::getInstance()->getTexture(L"indiveback/floor/2.png");
	_player->MoveTo(_player->_position + Vec2(0, 30 * (3 - c)), 3);
	_player->_movetocallback = [=]()
	{
		_springboard->_texture = TextureMng::getInstance()->getTexture(L"indiveback/floor/3.png");
		_player->MoveTo(_player->_position + Vec2(0, -(80 * (3 - c))), 6);
		_player->_movetocallback = [=]()
		{
			_springboard->_texture = TextureMng::getInstance()->getTexture(L"indiveback/floor/4.png");
			_player->MoveTo(_player->_position + Vec2(0, (50 * (3 - c))), 5);
			_player->_movetocallback = [=]()
			{
				_springboard->_texture = TextureMng::getInstance()->getTexture(L"indiveback/floor/1.png");
				_player->_movetocallback = nullptr;
			};
		};
	};
}

void Dive::FiveCircle()
{
	_fc->_visible = true;
	_fc->ani._run = true;
}

void Dive::exit()
{
	for (auto it : _children)
		removeChild(it);
}