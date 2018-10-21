#include "stdafx.h"
#include "SoundObj.h"

void Sound::Init(LPCWSTR FileName, int end, bool Inf)
{
	wsprintf(fliename, FileName);

	endTime = end;

	isPlay = false;
	Infinite = Inf;
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

void Sounds::Init()
{
	for(int i = 0; ;i++)
	{
		Sound temp;

		switch (i)
		{
		case BGM_TITLE:
			temp.Init(L"./Sound/_title.wav", (60 * 1) + 37, true);
			break;
		case BGM_CAVE:
			temp.Init(L"./Sound/_cave.wav", (60 * 0) + 58, true);
			break;
		case EFFECT_WALLBREAK:
			temp.Init(L"./Sound/_wallbreak.wav", 1, false);
			break;
		case EFFECT_SELECT:
			temp.Init(L"./Sound/_select.wav", 1, false);
			break;
		case EFFECT_TRAPSET:
			temp.Init(L"./Sound/_trapset.wav", 1, false);
			break;
		case EFFECT_DISMANTLETRAP:
			temp.Init(L"./Sound/_dismantle.wav", 1, false);
			break;
		case EFFECT_STAB:
			temp.Init(L"./Sound/_stab.wav", 1, false);
			break;
		case EFFECT_SWORD:
			temp.Init(L"./Sound/_sword.wav", 1, false);
			break;
		case TRAP_NIDDLE:
			temp.Init(L"./Sound/_niddle.wav", 1, false);
			break;
		case TRAP_SCARECROW:
			temp.Init(L"./Sound/_scarecrow.wav", 1, false);
			break;
		case TRAP_GRAB:
			temp.Init(L"./Sound/_grab.wav", 1, false);
			break;
		case TRAP_CONFUSE:
			temp.Init(L"./Sound/_confuse.wav", 1, false);
			break;
		case TRAP_HOLE:
			temp.Init(L"./Sound/_hole.wav", 1, false);
			break;
		case TRAP_HOLESPIN:
			temp.Init(L"./Sound/_holespin.wav", 1, false);
			break;
		case TRAP_REROAD:
			temp.Init(L"./Sound/_reload.wav", 1, false);
			break;
		case SKILL_ATK:
			temp.Init(L"./Sound/_atk.wav", 1, false);
			break;
		case SKILL_AGGRO:
			temp.Init(L"./Sound/_scarecrow.wav", 1, false); //추가필요
			break;
		case SKILL_BARRICADE:
			temp.Init(L"./Sound/_barricade.wav", 1, false);
			break;
		case SKILL_PUSH:
			temp.Init(L"./Sound/_push.wav", 1, false);
			break;
		case BARRICADE_BREAK:
			temp.Init(L"./Sound/_break.wav", 1, false);
			break;
		default:
			return;
		}

		pool.push_back(temp);
	}
}

void Sounds::Terminate()
{
	pool.clear();
}

void Sounds::Play(int num)
{
	if (pool.empty()) return;

	vector<Sound>::iterator it;
	it = pool.begin();

	it += num;

	it->Restart();
}

void Sounds::Stop(int num)
{
	if (pool.empty()) return;

	vector<Sound>::iterator it;
	it = pool.begin();

	it += num;

	it->Stop();
}

void Sounds::Pulse()
{
	if (pool.empty()) return;

	vector<Sound>::iterator it;
	it = pool.begin();

	while (it != pool.end())
	{
		if (it->isSongEnd())
		{
			if (it->GetInfinite())
			{
				it->Restart();
			}
		}

		it++;
	}
}