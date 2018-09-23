#include "stdafx.h"
#include "FrameManager.h"

void FrameManager::Initilaize()
{
	srand((unsigned)time(NULL));
	CurrentTime = timeGetTime();
	OldTime = timeGetTime();

	AcculTime = 0.0f;
	FrameCount = 0;
	TimeStep = 0.0f;
}

void FrameManager::Terminate()
{

}

void FrameManager::SetFramePerSec(float fps)
{
	SecPerFrame = 1.0f / fps;
}

bool FrameManager::Update()
{
	CurrentTime = timeGetTime();
	Tick = CurrentTime - OldTime;
	OldTime = CurrentTime;

	TimeStep = (float)Tick * 0.001f;

	Timer += TimeStep;
	AcculTime += TimeStep;

	if (Timer < 0)
	{
		if ((float)FrameCount / AcculTime > 0.0f)
		{
			ObjPool->System.SetFPS((float)FrameCount / AcculTime);	//오브젝트풀에 있는 fps변수에 저장
			AcculTime = 0;
			FrameCount = 0;
		}
		return false;
	}

	Timer -= SecPerFrame;
	FrameCount += 1;

	return true;
}
