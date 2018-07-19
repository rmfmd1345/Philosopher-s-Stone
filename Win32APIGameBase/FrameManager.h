#pragma once

class FrameManager
{
public:
	FrameManager() { }
	~FrameManager() { }
private:
	float SecPerFrame;

	float Timer;
	float AcculTime; //시간 누적
	float TimeStep;  //시간 간격
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

