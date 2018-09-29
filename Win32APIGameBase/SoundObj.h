#pragma once

class Song
{
public:
	Song() {};
	~Song() {};

private:
	TCHAR fliename[128];
	int endTime;

	bool isPlay;

public:
	void Init(LPCWSTR FileName, int end, int combo);

public:
	void Play();
	void Pause();
	void Stop();
	void Reset();
	void Restart();

	void SetPlaytime(int time);
	void SetVolume(int vol);

	bool isSongPlay();
	bool isSongEnd();

	int GetPlayTime();
	int GetEndTime();

};
