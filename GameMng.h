#pragma once

class GameMng
{
public:
	static GameMng* _ginstance;
	static GameMng* getInstance()
	{
		if (!_ginstance)
			_ginstance = new GameMng();
		return _ginstance;
	}

	GameMng()
	{
		reset();
	}

	void reset()
	{
		_divestage = 0;
		_mtstage = 0;
		_swimstage = 0;
		_runstage = 0;
	}
	
	int _divestage;
	int _mtstage;
	int _swimstage;
	int _runstage;


};