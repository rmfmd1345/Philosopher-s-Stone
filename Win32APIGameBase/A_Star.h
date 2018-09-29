#pragma once
using namespace std;

// 타일 속성을 관리하기 위한 열거형
enum Tile
{
	T_N, /* 빈곳 */
	T_B, /* 벽 */
	T_S, /* 시작지점 */
	T_E, /* 목적지 */
	T_O, /* 열린목록*/
	T_C, /* 닫힌목록*/
	T_P, /* 확정된 길*/
	T_End
};

// 각 타일의 정보를 관리하기 위한 구조체
struct TileNode
{
	//	타일 좌표
	POINT		m_pos = {};

	//	F,G,H
	int m_F = 0;
	int m_G = 0;
	int m_H = 0;

	//	부모 노드
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
	POINT m_tileMapSize = { MAX_TILE_Y, MAX_TILE_X }; // 맵의 가로(or 세로) 갯수

	vector<Tile>	m_tileMap;		// 맵 데이터 리스트
	list<TileNode>	m_openList;		// 이동이 가능한 오픈리스트
	list<TileNode>	m_closeList;	// 임시로 이동을 확정한 닫힌리스트

protected:
	list<POINT>		m_pathList;		// 이동경로 리스트

public:
	A_Star();
	~A_Star();

protected:
	bool PathFind(POINT MonsterPos, POINT PlayerPos); //길찾기 시작

private:
	void SetBlock(POINT pt, Tile isTile = T_End, bool Drag = false);

	int GetPosTileNum(POINT pt);
	Tile GetPosTile(POINT pt);
	vector<Tile> GetTileList();
	void SetTileMap();

private:
	void clear();
	
};


