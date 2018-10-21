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
	BGM_SAFE,
	BGM_DANGER,
	BGM_BAD,
	BGM_HAPPY,

	EFFECT_WALLBREAK,
	EFFECT_SELECT,
	EFFECT_TRAPSET,
	EFFECT_DISMANTLETRAP,
	EFFECT_STAB,
	EFFECT_SWORD,

	TRAP_NIDDLE,
	TRAP_SCARECROW,
	TRAP_GRAB,
	TRAP_CONFUSE,
	TRAP_HOLE,
	TRAP_HOLESPIN,
	TRAP_REROAD,

	SKILL_ATK,
	SKILL_AGGRO,
	SKILL_PUSH,
	SKILL_BARRICADE,

	BARRICADE_BREAK,

	ENDING_ALTAR
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