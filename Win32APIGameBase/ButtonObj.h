#pragma once

class Button	//��ư!
{
public:
	Button() { }
	~Button() { }

private:
	bool bIsOn = false;	//���� �Ǿ��°�?
	RECT rect;

	// GDI part
	HPEN hPen;
	HPEN OldPen;
	HBRUSH hBrush;
	HBRUSH OldBrush;

	COLORREF PenColor;
	COLORREF BrushColor;
	COLORREF ClickColor;

public:
	// Bitmap part
	Bitmap Btn_Bitmap[3]; // Up Over Down
	int Button_State_Num;

	enum Button_State
	{
		Up,
		Over,
		Down
	};

public:
	void Init(RECT rt, COLORREF pen, COLORREF brush, COLORREF click);	//�ʱ�ȭ
	void Draw(HDC hMemDC);	//�׸���

	void SetRect(RECT rt);	//��ġ ����
	void SetPenColor(COLORREF color);	//�� �� ����
	void SetBrushColor(COLORREF color);	//�귯�� �� ����
	//�� �������콺 �� ������ ���ĸ� �����ϰ� �ȸ������

	bool isOver(int x, int y);	//���콺�� �ö�Դ���
	bool isClick(int x, int y);	//Ŭ���� �Ǿ�����
};