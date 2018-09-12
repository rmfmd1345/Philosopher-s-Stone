#include "stdafx.h"
#include "SoundObj.h"

void Song::Init(LPCWSTR FileName, int end, int combo)
{
	wsprintf(fliename, FileName);

	endTime = end;
}

void Song::Play()
{
	TCHAR cmd[128];

	wsprintf(cmd, L"play %s", fliename);
	mciSendString(cmd, NULL, 0, NULL);

	isPlay = true;
}

void Song::Pause()
{
	TCHAR cmd[128];

	wsprintf(cmd, L"pause %s", fliename);
	mciSendString(cmd, NULL, 0, NULL);

	isPlay = !(isPlay);
}

void Song::Stop()
{
	TCHAR cmd[128];

	wsprintf(cmd, L"stop %s", fliename);
	mciSendString(cmd, NULL, 0, NULL);

	isPlay = false;
}

void Song::Reset()
{
	TCHAR cmd[128];

	wsprintf(cmd, L"play %s from 0", fliename);
	mciSendString(cmd, NULL, 0, NULL);
}

void Song::Restart()
{
	Reset();
	Play();
}

void Song::SetPlaytime(int time)
{
	TCHAR cmd[128];

	wsprintf(cmd, L"play %s from %d", fliename, time * 100);
	mciSendString(cmd, NULL, 0, NULL);

	isPlay = true;
}

void Song::SetVolume(int vol)
{
	TCHAR cmd[128];
	wsprintf(cmd, L"setaudio %s volume from %d", fliename, vol);
	mciSendString(cmd, NULL, 0, NULL);
}

bool Song::isSongPlay()
{
	return isPlay;
}

bool Song::isSongEnd()
{
	if (GetPlayTime() >= endTime * 10)
		return true;
	else
		return false;
}

int Song::GetPlayTime()
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

int Song::GetEndTime()
{
	return endTime;
}