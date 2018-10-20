#include "stdafx.h"
#include "SoundObj.h"

void Sound::Init(LPCWSTR FileName, int end, bool Inf, int n)
{
	wsprintf(fliename, FileName);

	endTime = end;

	isPlay = false;
	Infinite = Inf;

	num = n;
}

void Sound::Play()
{
	TCHAR cmd[128];

	wsprintf(cmd, L"play %s", fliename);
	mciSendString(cmd, NULL, 0, NULL);

	isPlay = true;
}

void Sound::Pause()
{
	TCHAR cmd[128];

	wsprintf(cmd, L"pause %s", fliename);
	mciSendString(cmd, NULL, 0, NULL);

	isPlay = !(isPlay);
}

void Sound::Stop()
{
	TCHAR cmd[128];

	wsprintf(cmd, L"stop %s", fliename);
	mciSendString(cmd, NULL, 0, NULL);

	isPlay = false;
}

void Sound::Reset()
{
	TCHAR cmd[128];

	wsprintf(cmd, L"play %s from 0", fliename);
	mciSendString(cmd, NULL, 0, NULL);

	isPlay = true;
}

void Sound::Restart()
{
	Reset();
	Play();
}

void Sound::SetPlaytime(int time)
{
	TCHAR cmd[128];

	wsprintf(cmd, L"play %s from %d", fliename, time * 100);
	mciSendString(cmd, NULL, 0, NULL);

	isPlay = true;
}

void Sound::SetVolume(int vol)
{
	TCHAR cmd[128];
	wsprintf(cmd, L"setaudio %s volume from %d", fliename, vol);
	mciSendString(cmd, NULL, 0, NULL);
}

void Sound::SetInfinite(bool b)
{
	Infinite = b;
}

bool Sound::isSongPlay()
{
	return isPlay;
}

bool Sound::isSongEnd()
{
	if (GetPlayTime() >= endTime * 10)
		return true;
	else
		return false;
}

int Sound::GetNum()
{
	return num;
}

int Sound::GetPlayTime()
{
	TCHAR cmd[128];

	TCHAR bgmPosition[256];
	char bgmPos[256];
	float bgmCurrent;

	size_t getVal = 0;

	wsprintf(cmd, L"status %s position", fliename);
	mciSendString(cmd, bgmPosition, 256, NULL);

	wcstombs_s(&getVal, bgmPos, bgmPosition, 256);
	bgmCurrent = atoi(bgmPos) / 100.0;

	return (int)bgmCurrent;
}

int Sound::GetEndTime()
{
	return endTime;
}

bool Sound::GetInfinite()
{
	return Infinite;
}

void SoundList::Push(int type, int num)
{
	Sound temp;

	switch (type)
	{
	case BGM_TITLE:
		temp.Init(L"./Sound/_title.wav", (60 * 1) + 37, true, num);
		break;
	case BGM_CAVE:
		temp.Init(L"./Sound/_cave.wav", (60 * 0) + 58, true, num);
		break;
	case EFFECT_WALLBREAK:
		temp.Init(L"./Sound/_wallbreak.wav", 1, false, num);
		break;
	default:
		return;
	}
	SoundPool.push_back(temp);

	vector<Sound>::iterator it;
	it = SoundPool.end() - 1;
	it->Restart();
}

void SoundList::Pop(int num)
{
	if (SoundPool.empty()) return;

	vector<Sound>::iterator it;
	it = SoundPool.begin();

	while (it != SoundPool.end())
	{
		if (it->GetNum() == num)
		{
			it->Stop();
			it = SoundPool.erase(it);
		}
		else
		{
			it++;
		}
	}
}

void SoundList::ClearAll()
{
	SoundPool.clear();
}

void SoundList::Pulse()
{
	if (SoundPool.empty()) return;

	vector<Sound>::iterator it;
	it = SoundPool.begin();

	while (it != SoundPool.end())
	{
		if (it->isSongEnd())
		{
			if (it->GetInfinite())
			{
				it->Restart();
			}
			else
			{
				it = SoundPool.erase(it);
			}
		}
		else
		{
			it++;
		}
	}
}

bool SoundList::Empty()
{
	return (SoundPool.empty());
}
