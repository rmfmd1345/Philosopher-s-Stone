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

	int num;

public:
	void Init(LPCWSTR FileName, int end, bool Inf, int n);

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

	int GetNum();
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

	SKILL_ATK,
	SKILL_AGGRO,
	SKILL_PUSH,
	SKILL_BARRICADE,
};

class SoundList
{
public:
	SoundList() {};
	~SoundList() {};

private:
	vector<Sound> SoundPool;

public:
	void Push(int type, int num = 0);	//���� �߰�
	void Pop(int num);					//���� �����
	void ClearAll();					//��� �����
	void Pulse();						//���� �������� Ȯ��(���ѹݺ��̸� �ٽ� ���)

	bool Empty();						//����ִ��� Ȯ��

};