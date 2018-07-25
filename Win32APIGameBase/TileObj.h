#pragma once

class CTile
{
public:
	int Tile_ID; // Ÿ�� �ĺ� ��ȣ
	bool Tile_On; // ���� ������ ����

	Bitmap Tile_Bitmap;

	std::function<void()> Tile_Func; // ���ٽ�

	void InitTile(HWND hwnd, int ID, LPCWSTR szFileName, std::function<void()> Tile_Function); //Ÿ�� �ʱ�ȭ
	void DestroyTile(CTile Tile); // Ÿ�� �̹��� �ı�
};

class CMap
{
public:
	CTile Map[20][20]; // ��

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
	void ActiveTile(/*���� �÷��̾��� ��ǥ*/); // �ش� Ÿ���� ����� ���� (���� ���)
	void SetTileOnMap(CTile Tile, int x, int y); // Ÿ���� �ʿ� ��ġ
	void DrawMap(); // ���� �׷��� (ȭ�� ��ũ�Ѹ� ����)
	void DrawBrick(); // ���� �׷���
	void DestroyMap(); // �� Ÿ�� �ı�
};