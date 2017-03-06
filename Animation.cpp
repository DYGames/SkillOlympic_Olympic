#include "DXUT.h"
#include "Animation.h"
#include "Sprite.h"

void Animation::initAni(Sprite* target, float delay, bool loop, bool erase)
{
	_run = true;
	_target = target;
	_delay = 0;
	_loop = loop;
	_idx = 0;
	_maxdelay = delay;
	_erase = erase;
	_clips.clear();
	_clips.push_back(target->_texture);
}

void Animation::addClip(std::wstring str)
{
	_clips.push_back(TextureMng::getInstance()->getTexture(str));
}

void Animation::removeAllClip()
{
	_delay = 0;
	_idx = 0;
	_clips.clear();
}

void Animation::update()
{
	if (!_clips.size() || !_run)
		return;

	_delay += Time::dt;
	if (_delay >= _maxdelay)
	{
		_delay = 0;
		_idx++;
		if (_idx >= _clips.size())
		{
			if (_loop)
				_idx = 0;
			else
			{
				if (_erase)
					_target->removeChild(_target);
				else
					_run = false;	
				
				if (_callback)
					_callback();

				return;
			}
		}

		_target->_texture = _clips.at(_idx);
	}

}