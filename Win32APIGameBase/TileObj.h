#pragma once

class CTile
{
public:
	int Tile_ID; // Ÿ�� �ĺ� ��ȣ
	bool Tile_On; // ���� ������ ����

	SpriteHelper Tile_Sprite; // �ִϸ��̼� ��������Ʈ (������ ��� �� : �ߵ� �ִϸ��̼� / ������ ��� �� : ������ �ִϸ��̼�)

	std::function<void()> Tile_Func; // ���ٽ� (���� �ߵ� �� ������ ����)

	void InitTile(HWND hwnd, int Frame, int ID, LPCWSTR szFileName, std::function<void()> Tile_Function); //Ÿ�� �ʱ�ȭ
	void DestroyTile(CTile Tile); // Ÿ�� �̹��� �ı�
};

class CMap
{
public:
	CTile Map[32][18]; // ��

	CTile None; // �ƹ��͵� ����
	CTile Floor; // �ٴ�
	CTile Wall; // ��
	CTile Trap_Niddle; // ���� ����
	CTile Trap_Hole; // ���� ����
	CTile Trap_ScareCrow; // ����ƺ� ����
	CTile Trap_Cunfution; // ȥ�� ����
	CTile Trap_Grap; // ���� ����

	Bitmap Brick[4]; // ���� �̹���

	enum Tile_ID_List  // �ĺ� ��ȣ ����Ʈ
	{
		NONE,
		FLOOR,
		WALL,
		TRAP_Niddle,
		TRAP_Hole,
		TRAP_ScareCrow,
		TRAP_Cunfution,
		TRAP_Grap
	};

	enum Brick_ID_List
	{
		UP,
		DOWN,
		LEFT,
		RIGHT
	};

	void InitMap(HWND hwnd); // Ÿ�� �̹��� �ʱ�ȭ
	void ResetMap(); // �������� �Ѿ �� ���� �ʱ�ȭ
	void ActiveTile(int Character_x, int Character_y); // �ش� Ÿ���� ����� ���� (���� ���)
	void SetTileOnMap(CTile Tile, int x, int y); // Ÿ���� �ʿ� ��ġ
	void DrawMap(HDC hMemDC); //  �÷��̾ �������� ȭ�鿡 ������ Ÿ���� ����Ͽ� ���
	void DrawBrick(HDC hMemDC); // ���� �׷���
	void DestroyMap(); // �� Ÿ�� �ı�
};