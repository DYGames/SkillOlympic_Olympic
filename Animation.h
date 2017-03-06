#pragma once

#include <functional>
#include <vector>

class Texture;
class Sprite;
class Animation
{
public:
	Sprite* _target;
	bool _run;
	bool _loop;
	bool _erase;

	float _maxdelay;
	float _delay;

	int _idx;

	std::vector<Texture*> _clips;

	std::function<void()> _callback;

	void initAni(Sprite*, float delay = 0.1f, bool loop = true, bool erase = false);

	void setDelay(float delay)
	{
		_maxdelay = delay;
		if (_delay > _maxdelay)
			_delay = 0;
	}

	void addClip(std::wstring);

	void removeAllClip();

	void update();
};