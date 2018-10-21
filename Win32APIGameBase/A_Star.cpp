#include "stdafx.h"
#include "A_Star.h"

//	POINT �ڷ����� == ������ �ϱ� ���ؼ�
bool operator==(POINT _pos1, POINT _pos2)
{
	return (_pos1.x == _pos2.x && _pos1.y == _pos2.y);
}
// POINT �ڷ����� - ������ �ϱ� ���ؼ�(���밪���� ��� �� ����)
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
	// �˻��� �����Ҷ� ����, ���� ����Ʈ�� �ʱ�ȭ �� ����
	m_openList.clear();
	m_closeList.clear();

	// ���� �� ��ǥ���� ����
	m_monsterPos = MonsterPos;
	m_playerPos = PlayerPos;
	
	//���κ� ���ܽ�Ű��
	for (int i = 0; i < MAX_TILE_Y; i++)
	{
		for (int j = 0; j < MAX_TILE_X; j++)
		{
			if (!ObjPool->Maps.GetTileMoveID(j, i))
				SetBlock({ j,i });
		}
	}

	// �˻��� �����ϱ� ���� ù��° ��带 ���� �� ������ġ�� ����
	TileNode t_startNode;
	t_startNode.m_pos = MonsterPos;

	// ���¸���Ʈ�� ù��°�� ���� ��带 ����
	m_openList.push_back(t_startNode);

	// ���� �������� ��ǥ �������� �˻��� ���� �ݺ�
	while (true)
	{
		// ���¸���Ʈ�� F �� ���������� ���� (ù��° ����� F ���� ���� ����)
		// ����ü �� ������ �����ϵ��� TileNode ����ü ���ο� bool	operator < (TileNode &_right) ���� 
		m_openList.sort();

		// ���¸���Ʈ���� F ���� ���� ���� Node �� ��������Ʈ ���� �ڿ� �߰�
		m_closeList.push_back(m_openList.front());
		// ��������Ʈ�� �߰��� Node �� ���¸���Ʈ���� ����
		m_openList.pop_front();

		// �ֺ� ����� ���� ��������Ʈ ���� �ڿ� �ִ� Node �� ���۷��� ������ ������
		TileNode &t_selectNode = m_closeList.back();

		// ��������Ʈ ���� ������ ���� ��ǥ ������ ������ ��ġ���� Ȯ��
		if (t_selectNode.m_pos == PlayerPos)
		{
			//�̵���� ����Ʈ�� �ʱ�ȭ �� ����
			m_pathList.clear();
			// ������ ��带 �������� �θ� ��带 Ȯ���ϸ鼭 ��� ��带 �����ϱ� ���Ͽ� 
			// ������ ���� ���� �� ����
			TileNode *t_node = &t_selectNode;

			while (t_node != nullptr)
			{
				// ��� ����Ʈ ���� �տ� �̹� ����� ��ǥ�� �Է�
				// (�ݺ��Ǹ� ���� ������ ���� �������� �Էµ����� ���� �տ� ��ġ��
				m_pathList.push_front(t_node->m_pos);

				// ���� ����� �θ� ��ǥ�� �����ͼ� ���� ��带 �θ���� �����ϰ� �ٽ� ��ȸ
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

		// ���� ��ġ �ֺ��� 8���� �˻� (���� �ֺ��� �˻��� ����� ���ϰ� �ϱ� ���� -1 ~ 1 ���� �˻�)
		for (int y = -1; y <= 1; y++)
		{
			for (int x = -1; x <= 1; x++)
			{
				// ��� ��ġ�� �߾��� ��� ����
				if (x == 0 && y == 0) continue;

				// �����ġ�� �밢���� ��� ����
				if ((x == -1 && (y == 1 || y == -1)) || (x == 1 && (y == 1 || y == -1))) continue;

				// Ȯ���� ��� ��� ��ǥ �غ� (for �� ������ -1 ~ 1 �ؼ� �׳� ���ϸ� ��
				POINT t_pos = { t_selectNode.m_pos.x + x, t_selectNode.m_pos.y + y };

				// ��� ��ġ�� ���� ��� ��� ����
				if (t_pos.x < 0 || t_pos.y < 0 ||
					t_pos.x >= MAX_TILE_X || t_pos.y >= MAX_TILE_Y) continue;

				// ��� ��ġ�� �̵� �Ұ� ������ ��� ����
				int t_tilePos = MAX_TILE_X * t_pos.y + t_pos.x;
				Tile t_thisTile = m_tileMap[t_tilePos];
				// ���� ������ Ȯ�εǸ� �˻����� ����
				if (t_thisTile == T_B) continue;

				// �� ���̸� �밢������ �� ��ġ�� ��� ����
				if (x*y != 0) //  �밢�� �̵��� ���
				{
					// x �� 0 ������ ��ǥ
					POINT t_pos_1 = { t_selectNode.m_pos.x + 0, t_selectNode.m_pos.y + y };
					// y �� 0 ������ ��ǥ
					POINT t_pos_2 = { t_selectNode.m_pos.x + x, t_selectNode.m_pos.y + 0 };

					// ���� Ÿ�� 2���� ��� ���� ��� �ߴ�
					if (m_tileMap[GetPosTileNum(t_pos_1)] == T_B && m_tileMap[GetPosTileNum(t_pos_2)] == T_B)
						continue;
				}

				// ��� ��ġ�� ��������Ʈ�� �߰��� �������� Ȯ���ϰ� �ִٸ� �ߴ�
				// Ȯ�� �� �ߴ� ó���� ���� bool ���� �غ�
				bool t_isCloseList = false;

				// ��������Ʈ�� ��ȸ�ϸ鼭 Ȯ��
				for (auto &i : m_closeList)
				{
					if (i.m_pos == t_pos)
					{
						// ��������Ʈ�� �������� ���� �ϰ� for �� �ߴ�
						t_isCloseList = true;
						break;
					}
				}

				// ��������Ʈ�� �ִٸ� ����
				if (t_isCloseList) continue;

				// ��� ��ġ�� ������Ͽ� �ִ��� Ȯ���Ͽ� ���ǿ� ���� ó��
				// ��������Ʈ�� �ִٸ� ����� �޸� �ּҸ� �޾ƿ��� ���� ���� ����(����Ʈ�� �ִ� ���� �ٷ� �����ϱ� ����)
				TileNode *t_o_node;
				t_o_node = nullptr;

				//�����ġ �� F, G, H �� �̸� �����(���߿� ��忡 ���Խ� ����ϱ� ����)
				// G : �������� ����ؾ� �Ǽ� �����̵Ǵ� ���� ����� G ���� �������� ��ġ�� ���� �߰� ��갪�� ����
				int t_thisG = t_selectNode.m_G + ((x*y == 0) ? 10 : 14);
				// H : ��� ��ġ���� ������ ������ �Ÿ��� �ܼ� ���(int operator-(POINT _pos1, POINT _pos2) ���)
				int t_thisH = (t_pos - m_playerPos) * 10;
				int t_thisF = t_thisG + t_thisH;

				// ��������Ʈ ��ȸ�ϸ� �ִ��� Ȯ�� �� �ִٸ� �޾� ��
				for (auto &i : m_openList)
				{
					// ��������Ʈ�� ������ ��ǥ�� ���� Node �� �ִٸ� �ش� ����� �޸��ּҸ� �޾ƿ�
					if (i.m_pos == t_pos)
					{
						t_o_node = &i;
						break;
					}
				}

				// ��������Ʈ�� ���ٸ�(nullptr)
				if (t_o_node == nullptr)
				{
					TileNode t_newNode;

					// �θ��� ����
					t_newNode.p_parentNode = &t_selectNode;
					// F, G, H ����
					t_newNode.m_F = t_thisF;
					t_newNode.m_G = t_thisG;
					t_newNode.m_H = t_thisH;

					// ��ǥ ����
					t_newNode.m_pos = t_pos;
					// ���¸���Ʈ�� �߰� (�ݺ��� ���۽� �����ϱ� ������ ������ ����
					m_openList.push_back(t_newNode);
				}
				// ��������Ʈ�� �ִٸ�
				else
				{
					// �̹��� ����� ����� G ���� ��������Ʈ�� G ���� �۴ٸ� �̹� ��� �������� ����
					if (t_o_node->m_G > t_thisG)
					{
						// ���� ���� ��带 �θ� ���� ����
						t_o_node->p_parentNode = &t_selectNode;
						//F,G,H �� ����
						t_o_node->m_F = t_thisF;
						t_o_node->m_G = t_thisG;
						t_o_node->m_H = t_thisH;
					}
				}
			}
		}

		// ��������� ��� �ִ� ��� �ߴ� (�˻� ������ ���� ����)
		if (m_openList.empty() == true)
		{
			return false;
		}

		// �������Ͽ� �ִ� ��� ����(������)�� ��ü �� ������ ���� Ŀ���� ��� �ߴ� (���� ���� ó��)
		if (m_openList.size() > m_tileMap.size())
		{
			return false;
		}


	}

	return false;
}

void A_Star::SetBlock(POINT pos, Tile isTile, bool Drag)
{
	// ��� ��ġ�� ���� ��� ��� ����
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
	// ���� �� ������ ���
	vector<Tile>t_tileList = m_tileMap;

	// �̵� ��ο� ���� tile ���� ����
	for (auto i : m_pathList)
	{
		t_tileList[GetPosTileNum(i)] = T_P;
	}

	// ���� ������ ���� ����
	t_tileList[GetPosTileNum(m_playerPos)] = T_E;

	// ���� ������ ���� ����
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
