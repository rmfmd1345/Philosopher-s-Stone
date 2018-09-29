#pragma once
using namespace std;

// Ÿ�� �Ӽ��� �����ϱ� ���� ������
enum Tile
{
	T_N, /* ��� */
	T_B, /* �� */
	T_S, /* �������� */
	T_E, /* ������ */
	T_O, /* �������*/
	T_C, /* �������*/
	T_P, /* Ȯ���� ��*/
	T_End
};

// �� Ÿ���� ������ �����ϱ� ���� ����ü
struct TileNode
{
	//	Ÿ�� ��ǥ
	POINT		m_pos = {};

	//	F,G,H
	int m_F = 0;
	int m_G = 0;
	int m_H = 0;

	//	�θ� ���
	TileNode	*p_parentNode = nullptr;

	bool	operator < (TileNode &_right)
	{
		return m_F < _right.m_F;
	}
};

class A_Star
{
protected:
	POINT m_monsterPos = { 5, 5 };
	POINT m_playerPos = { 10, 5 };

private:
	Tile m_last_Tile = T_End;
	POINT m_tileMapSize = { MAX_TILE_Y, MAX_TILE_X }; // ���� ����(or ����) ����

	vector<Tile>	m_tileMap;		// �� ������ ����Ʈ
	list<TileNode>	m_openList;		// �̵��� ������ ���¸���Ʈ
	list<TileNode>	m_closeList;	// �ӽ÷� �̵��� Ȯ���� ��������Ʈ

protected:
	list<POINT>		m_pathList;		// �̵���� ����Ʈ

public:
	A_Star();
	~A_Star();

protected:
	bool PathFind(POINT MonsterPos, POINT PlayerPos); //��ã�� ����

private:
	void SetBlock(POINT pt, Tile isTile = T_End, bool Drag = false);

	int GetPosTileNum(POINT pt);
	Tile GetPosTile(POINT pt);
	vector<Tile> GetTileList();
	void SetTileMap();

private:
	void clear();
	
};


