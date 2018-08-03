#pragma once

#define MAX_SCENENUM	16

enum eSCENE	//씬 이넘
{
	SCENE_TITLE,
	SCENE_INGAME,
	SCENE_CREDIT,
	SCENE_OPTION,

	SCENE_NULL = MAX_SCENENUM
};

class Scene
{
public:
	Scene() { }
	~Scene() { }

private:
	eSCENE scene;	//씬 넘버
	int evnt;		//이벤트 넘버

public:
	virtual void SetScene(eSCENE num) {
		scene = num;
	}

	virtual eSCENE GetScene() {
		return scene;
	}

	virtual void SetEvent(int num) {
		evnt = num;
	}

	virtual int GetEvent() {
		return evnt;
	}
};