#pragma once
#include "SceneManager.h"
#include "DrawManager.h"

class System
{
public:
	System() { }
	~System() { } 

private:
	Scene nowScene;	//씬 인터페이스
	float fps;		//fps

public:
	virtual void SetScene(eSCENE scene) {
		nowScene.SetScene(scene);
	}

	virtual eSCENE GetScene() {
		return nowScene.GetScene();
	}

	virtual void SetEvent(int evnt) {
		nowScene.SetEvent(evnt);
	}

	virtual int GetEvent() {
		return nowScene.GetEvent();
	}

	virtual void SetFPS(float f) {
		fps = f;
	}

	virtual float GetFPS() {
		return fps;
	}
};