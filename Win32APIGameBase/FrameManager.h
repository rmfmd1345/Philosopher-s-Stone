#pragma once

class FrameManager
{
public:
	FrameManager() { }
	~FrameManager() { }
private:
	float SecPerFrame;

	float Timer;
	float AcculTime; //�ð� ����
	float TimeStep;  //�ð� ����
	int FrameCount;

	DWORD CurrentTime;
	DWORD OldTime;
	DWORD Tick;

private:
	float FPS;       //FPS

protected:
	void Initilaize();
	bool Update();
	void Terminate();

public:
	void SetFramePerSec(float fps);

};

