#pragma once
#include "EntityObj.h"

class CTile
{
public:
	int Tile_ID; // Ÿ�� �ĺ� ��ȣ
	bool Tile_On; // ���� ������ ����
	bool Tile_isCanMove; //������ �� �ִ� Ÿ���ΰ�

	bool GrabArea_Row; //����
	bool GrabArea_Column; //����
	bool Brick_Up;
	bool Brick_Down;
	bool Brick_Left;
	bool Brick_Right;
	bool SubWall_Left;
	bool SubWall_Right;

	SpriteHelper Tile_Sprite; // �ִϸ��̼� ��������Ʈ (������ ��� �� : �ߵ� �ִϸ��̼� / ������ ��� �� : ������ �ִϸ��̼�)
	SpriteHelper Ani_Trap[4]; // �ִϸ��̼� ��������Ʈ (������ ��� �� : �ߵ� �ִϸ��̼� / ������ ��� �� : ������ �ִϸ��̼�)

	std::function<void(Entity* ent)> Tile_Func; // ���ٽ� (���� �ߵ� �� ������ ����)

	void InitTile(HWND hwnd, int Frame, int ID, int MoveID, std::function<void(Entity* ent)> Tile_Function); //Ÿ�� �ʱ�ȭ
	void DestroyTile(CTile Tile); // Ÿ�� �̹��� �ı�

public:
	//���� ����
	float TrapHp; //���� ü�� (���������� �ִ�ġ) //�ӽ÷� ���⼭ �ʱ�ȭ��
	int repairGage; //���� ���൵ ������
	int stateFrame; //���� �ִϸ��̼� �����ӻ���
	int nowTrapDirection; //���� �ִϸ��̼� ����
	//��������
	float damgeDelay; //���� ����� �� �����ؼ� �Լ��� �ߵ��Ǳ������ ����
	float SpinSpeed; //������������ ��ƼƼ�� ���� �ӵ�

	//��������
	POINT Grab_POS; //���� ������ ������ ������ ��ġ
	int movingGrab_x; //������ ������ �� ������ �׷����� ��ġ�� �ٲٱ� ����
	int movingGrab_y;
};

class CMap
{

public:
	CTile Map[MAX_TILE_Y][MAX_TILE_X]; // ��

	CTile None; // �ƹ��͵� ����
	CTile Floor; // �ٴ�
	CTile Wall; // ��
	CTile Trap_Niddle; // ���� ����
	CTile Trap_Hole; // ���� ����
	CTile Trap_ScareCrow; // ����ƺ� ����
	CTile Trap_Cunfusion; // ȥ�� ����
	CTile Trap_Grab; // ��������
	CTile Trap_GrabArea; // �������� �����


	Bitmap Brick[6]; // ���� �̹���
	Bitmap ingameUI_TrapHpBar; //���� ü�¹�
	Bitmap Trap_GrabArea_row; // �������� ����� (����)
	Bitmap Trap_GrabArea_column; // �������� ����� (����)

	enum Brick_ID_List
	{
		B_UP,
		B_LEFT,
		B_RIGHT,
		B_DOWN,
		SW_LEFT,
		SW_RIGHT
	};

	void InitMap(HWND hwnd); // Ÿ�� �̹��� �ʱ�ȭ
	void NiddleActive(Entity* ent);
	void ScareCrowActive(Entity* ent);
	void GrabActive(Entity* ent);
	void ConfusionActive(Entity* ent);
	void HoleActive(Entity* ent);
	void ResetMap(int Character_x, int Character_y); // �������� �Ѿ �� ���� �ʱ�ȭ
	void ActiveTile(Entity* ent); // �ش� Ÿ���� ����� ���� (���� ���)
	void SetTileOnMap(CTile Tile, int x, int y); // Ÿ���� �ʿ� ��ġ
	void SetTrapOnMap(CTile Tile, int x, int y); // ������ �ʿ� ��ġ
	void DrawMap(HDC hMemDC, int x, int y); //  �÷��̾ �������� ȭ�鿡 ������ Ÿ���� ����Ͽ� ���
	void DrawTrapHpBar(HDC hMemDC, int x, int y); //���� ������ �� hp������ ���

	void SetBrick(int x, int y); // ���� ��ġ�� ����
	void DrawBrick(HDC hMemDC, int x, int y); // ������ �׷���
	void DestroyMap(); // �� Ÿ�� �ı�

	int GetTileID(int x, int y);
	int GetTileMoveID(int x, int y);
	bool CheckTrap(int diraction, POINT pos);
};