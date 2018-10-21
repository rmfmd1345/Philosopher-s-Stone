#include "stdafx.h"
#include "A_Star.h"

//	POINT 자료형의 == 연산을 하기 위해서
bool operator==(POINT _pos1, POINT _pos2)
{
	return (_pos1.x == _pos2.x && _pos1.y == _pos2.y);
}
// POINT 자료형의 - 연산을 하기 위해서(절대값으로 계산 후 리던)
int operator-(POINT _pos1, POINT _pos2)
{
	return (abs(_pos1.x - _pos2.x) + abs(_pos1.y - _pos2.y));
}

A_Star::A_Star()
{
	SetTileMap();
}


A_Star::~A_Star()
{
}

bool A_Star::PathFind(POINT MonsterPos, POINT PlayerPos)
{
	// 검색을 시작할때 오픈, 닫힌 리스트를 초기화 후 시작
	m_openList.clear();
	m_closeList.clear();

	// 시작 및 목표지점 저장
	m_monsterPos = MonsterPos;
	m_playerPos = PlayerPos;
	
	//벽부분 제외시키기
	for (int i = 0; i < MAX_TILE_Y; i++)
	{
		for (int j = 0; j < MAX_TILE_X; j++)
		{
			if (!ObjPool->Maps.GetTileMoveID(j, i))
				SetBlock({ j,i });
		}
	}

	// 검색을 시작하기 위한 첫번째 노드를 생성 및 시작위치를 대입
	TileNode t_startNode;
	t_startNode.m_pos = MonsterPos;

	// 오픈리스트의 첫번째에 시작 노드를 대입
	m_openList.push_back(t_startNode);

	// 시작 지점부터 목표 지점까지 검색을 위한 반복
	while (true)
	{
		// 오픈리스트를 F 값 오름순으로 정렬 (첫번째 노드의 F 값이 가장 작음)
		// 구조체 비교 정렬이 가능하도록 TileNode 구조체 내부에 bool	operator < (TileNode &_right) 생성 
		m_openList.sort();

		// 오픈리스트에서 F 값이 가장 작은 Node 를 닫힌리스트 가장 뒤에 추가
		m_closeList.push_back(m_openList.front());
		// 닫힌리스트에 추가한 Node 를 오픈리스트에서 제거
		m_openList.pop_front();

		// 주변 계산을 위헤 닫힌리스트 가장 뒤에 있는 Node 를 레퍼런스 변수로 가져옴
		TileNode &t_selectNode = m_closeList.back();

		// 닫힌리스트 가장 마지막 노드와 목표 지점이 동일한 위치인지 확인
		if (t_selectNode.m_pos == PlayerPos)
		{
			//이동경로 리스트를 초기화 후 시작
			m_pathList.clear();
			// 마지막 노드를 기준으로 부모 노드를 확인하면서 대상 노드를 변경하기 위하여 
			// 포인터 변수 생성 및 대입
			TileNode *t_node = &t_selectNode;

			while (t_node != nullptr)
			{
				// 경로 리스트 가장 앞에 이번 노드의 좌표를 입력
				// (반복되면 시작 지점이 가장 마지막에 입력되지만 가장 앞에 위치함
				m_pathList.push_front(t_node->m_pos);

				// 현재 노드의 부모 좌표를 가져와서 현재 노드를 부모노드로 변경하고 다시 순회
				t_node = t_node->p_parentNode;
			}

			list<POINT>::iterator it;
			it = m_pathList.begin();
			while (it != m_pathList.end())
			{
				if (MonsterPos.x == it->x && MonsterPos.y == it->y)
				{
					it = m_pathList.erase(it);
				}
				/*
				else if (PlayerPos.x == it->x && PlayerPos.y == it->y)
				{
					it = m_pathList.erase(it);
				}
				*/
				else
				{
					it++;
				}
			}

			return true;
		}

		// 현재 위치 주변의 8곳을 검사 (위지 주변을 검색시 계산을 편하게 하기 위해 -1 ~ 1 까지 검색)
		for (int y = -1; y <= 1; y++)
		{
			for (int x = -1; x <= 1; x++)
			{
				// 대상 위치가 중앙인 경우 제외
				if (x == 0 && y == 0) continue;

				// 대상위치가 대각선인 경우 제외
				if ((x == -1 && (y == 1 || y == -1)) || (x == 1 && (y == 1 || y == -1))) continue;

				// 확인할 대상 노드 좌표 준비 (for 문 조건을 -1 ~ 1 해서 그냥 더하면 됨
				POINT t_pos = { t_selectNode.m_pos.x + x, t_selectNode.m_pos.y + y };

				// 대상 위치가 맵을 벗어난 경우 제외
				if (t_pos.x < 0 || t_pos.y < 0 ||
					t_pos.x >= MAX_TILE_X || t_pos.y >= MAX_TILE_Y) continue;

				// 대상 위치가 이동 불가 지역인 경우 제외
				int t_tilePos = MAX_TILE_X * t_pos.y + t_pos.x;
				Tile t_thisTile = m_tileMap[t_tilePos];
				// 값이 블럭으로 확인되면 검색에서 제외
				if (t_thisTile == T_B) continue;

				// 블럭 사이를 대각선으로 들어간 위치인 경우 제외
				if (x*y != 0) //  대각선 이동인 경우
				{
					// x 를 0 고정한 좌표
					POINT t_pos_1 = { t_selectNode.m_pos.x + 0, t_selectNode.m_pos.y + y };
					// y 를 0 고정한 좌표
					POINT t_pos_2 = { t_selectNode.m_pos.x + x, t_selectNode.m_pos.y + 0 };

					// 인접 타일 2개가 모두 블럭인 경우 중단
					if (m_tileMap[GetPosTileNum(t_pos_1)] == T_B && m_tileMap[GetPosTileNum(t_pos_2)] == T_B)
						continue;
				}

				// 대상 위치가 닫힌리스트에 추가된 상태인지 확인하고 있다면 중단
				// 확인 후 중단 처리를 위한 bool 변수 준비
				bool t_isCloseList = false;

				// 닫힌리스트를 순회하면서 확인
				for (auto &i : m_closeList)
				{
					if (i.m_pos == t_pos)
					{
						// 닫힌리스트에 있음으로 변경 하고 for 문 중단
						t_isCloseList = true;
						break;
					}
				}

				// 닫힌리스트에 있다면 제외
				if (t_isCloseList) continue;

				// 대상 위치가 열린목록에 있는지 확인하여 조건에 따른 처리
				// 열린리스트에 있다면 대상의 메모리 주소를 받아오기 위한 변수 선언(리스트에 있는 값을 바로 변경하기 위해)
				TileNode *t_o_node;
				t_o_node = nullptr;

				//대상위치 의 F, G, H 를 미리 계산함(나중에 노드에 대입시 사용하기 위해)
				// G : 누적으로 계산해야 되서 기준이되는 시작 노드의 G 값을 가져오고 위치에 따른 추가 계산값을 더함
				int t_thisG = t_selectNode.m_G + ((x*y == 0) ? 10 : 14);
				// H : 대상 위치에서 목적지 까지의 거리를 단순 계산(int operator-(POINT _pos1, POINT _pos2) 사용)
				int t_thisH = (t_pos - m_playerPos) * 10;
				int t_thisF = t_thisG + t_thisH;

				// 열린리스트 순회하면 있는지 확인 후 있다면 받아 둠
				for (auto &i : m_openList)
				{
					// 열림리스트에 동일한 좌표를 가진 Node 가 있다면 해당 노드의 메모리주소를 받아옴
					if (i.m_pos == t_pos)
					{
						t_o_node = &i;
						break;
					}
				}

				// 열림리스트에 없다면(nullptr)
				if (t_o_node == nullptr)
				{
					TileNode t_newNode;

					// 부모노드 설정
					t_newNode.p_parentNode = &t_selectNode;
					// F, G, H 설정
					t_newNode.m_F = t_thisF;
					t_newNode.m_G = t_thisG;
					t_newNode.m_H = t_thisH;

					// 좌표 설정
					t_newNode.m_pos = t_pos;
					// 오픈리스트에 추가 (반복문 시작시 정렬하기 때문에 순서는 무관
					m_openList.push_back(t_newNode);
				}
				// 열림리스트에 있다면
				else
				{
					// 이번에 계산한 노드의 G 값이 열린리스트의 G 보다 작다면 이번 노드 기준으로 대입
					if (t_o_node->m_G > t_thisG)
					{
						// 현재 기준 노드를 부모 노드로 설정
						t_o_node->p_parentNode = &t_selectNode;
						//F,G,H 를 변경
						t_o_node->m_F = t_thisF;
						t_o_node->m_G = t_thisG;
						t_o_node->m_H = t_thisH;
					}
				}
			}
		}

		// 열린목록이 비어 있는 경우 중단 (검색 가능한 곳이 없음)
		if (m_openList.empty() == true)
		{
			return false;
		}

		// 열림몰록에 있는 노드 갯수(사이즈)가 전체 맵 사이즈 보다 커지는 경우 중단 (오류 예외 처리)
		if (m_openList.size() > m_tileMap.size())
		{
			return false;
		}


	}

	return false;
}

void A_Star::SetBlock(POINT pos, Tile isTile, bool Drag)
{
	// 대상 위치가 맵을 벗어난 경우 제외
	if (pos.x < 0 || pos.y < 0 ||
		pos.x >= MAX_TILE_X || pos.y >= MAX_TILE_Y) return;

	int t_TileNum = MAX_TILE_X * pos.y + pos.x;
	Tile t_Tile = m_tileMap[t_TileNum];
	if (Drag == false)
	{
		if (t_Tile == T_N)
		{
			m_tileMap[t_TileNum] = T_B;
		}
		else if(t_Tile == T_B)
		{
			m_tileMap[t_TileNum] = T_N;
		}

		m_last_Tile = T_End;
	}
	else if(m_last_Tile != t_Tile)
	{
		if (m_last_Tile == T_N)
		{
			if (t_Tile == T_B)
			{
				m_tileMap[t_TileNum] = T_N;
				//return;
			}
		}
		else if (m_last_Tile == T_B)
		{
			if (t_Tile == T_N)
			{
				m_tileMap[t_TileNum] = T_B;
				//return;
			}
		}

		if (m_last_Tile == T_End)
		{
			m_last_Tile = t_Tile;
		}
	}

	clear();
}

void A_Star::clear()
{
	m_pathList.clear();
	m_openList.clear();
	m_closeList.clear();
}

int A_Star::GetPosTileNum(POINT pos)
{
	return (MAX_TILE_X * pos.y + pos.x);
}

Tile A_Star::GetPosTile(POINT pos)
{
	return m_tileMap[(MAX_TILE_X * pos.y + pos.x)];
}

vector<Tile> A_Star::GetTileList()
{
	// 현재 맵 데이터 백업
	vector<Tile>t_tileList = m_tileMap;

	// 이동 경로에 따른 tile 상태 변경
	for (auto i : m_pathList)
	{
		t_tileList[GetPosTileNum(i)] = T_P;
	}

	// 도착 지점의 상태 변경
	t_tileList[GetPosTileNum(m_playerPos)] = T_E;

	// 시작 지점의 상태 변경
	t_tileList[GetPosTileNum(m_monsterPos)] = T_S;


	return t_tileList;
}

void A_Star::SetTileMap()
{
	for (int i = 0; i < (MAX_TILE_X * MAX_TILE_Y); i++)
	{
		m_tileMap.push_back(T_N);
	}
}
