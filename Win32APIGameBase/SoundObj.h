#pragma once

class Sound
{
public:
	Sound() {};
	~Sound() {};

private:
	TCHAR fliename[128];
	int endTime;
	bool Infinite;

	bool isPlay;

public:
	void Init(LPCWSTR FileName, int end, bool Inf);

public:
	void Play();
	void Pause();
	void Stop();
	void Reset();
	void Restart();

	void SetPlaytime(int time);
	void SetVolume(int vol);
	void SetInfinite(bool b);

	bool isSongPlay();
	bool isSongEnd();

	int GetPlayTime();
	int GetEndTime();
	bool GetInfinite();
};

enum SoundNum
{
	BGM_TITLE,
	BGM_CAVE,

	EFFECT_WALLBREAK,
	TRAP_NIDDLE,
	TRAP_SCARECROW,
	TRAP_GRAB,
	TRAP_CONFUSE,
	TRAP_HOLE,
	TRAP_REROAD,

	SKILL_ATK,
	SKILL_AGGRO,
	SKILL_PUSH,
	SKILL_BARRICADE,

	BARRICADE_BREAK
};

class Sounds
{
public:
	Sounds() { }
	~Sounds() { }

private:
	vector<Sound> pool;

public:
	void Init();
	void Terminate();

	void Play(int num);
	void Stop(int num);

	void Pulse();

};