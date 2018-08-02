#include "stdafx.h"
#include "ButtonObj.h"

//����� ����ȭ �Ǵ��� Ȯ�ο����� �ּ�++
void Button::SetRect(RECT rt)
{
	rect.left = rt.left;
	rect.top = rt.top;
	rect.right = rt.right;
	rect.bottom = rt.bottom;
}

void Button::SetPenColor(COLORREF color)
{
	PenColor = color;
}

void Button::SetBrushColor(COLORREF color)
{
	BrushColor = color;
}

void Button::Init(int x, int y, int w, int h, COLORREF click)
{
	SetRect({ x, y, x + w, y + h }); //LEFT�� RIGHT�� x���� �ް�, TOP�� BOTTOM�� Y���� �����Ƿ�
	pos.x = x; //�׸��� ��� ��ǥ��
	pos.y = y;
	this->w = w; //�׸��� �ʺ�, ���̸� ����
	this->h = h;

	SpriteColor = click; //����Ÿ ���ֱ�
}

void Button::Draw(HDC hMemDC)
{
	//hPen = CreatePen(PS_INSIDEFRAME, 2, PenColor);
	//OldPen = (HPEN)SelectObject(hMemDC, hPen);

	//if (!bIsOn)	//�� ���ο� ���� � �귯���� ���� �� ������ üũ
	//{
	//	hBrush = CreateSolidBrush(BrushColor);
	//	OldBrush = (HBRUSH)SelectObject(hMemDC, hBrush);
	//}
	//else
	//{
	//	hBrush = CreateSolidBrush(ClickColor);
	//	OldBrush = (HBRUSH)SelectObject(hMemDC, hBrush);
	//}

	////���� �ĸ�DC�� �׸���
	//Rectangle(hMemDC, rect.left, rect.top, rect.right, rect.bottom);

	//if (hPen != NULL)
	//	DeleteObject(SelectObject(hMemDC, OldPen));
	//if (hBrush != NULL)
	//	DeleteObject(SelectObject(hMemDC, OldBrush));
	////�����ʰ� �����ֱ�
	Btn_Bitmap[Button_State_Num].Draw(hMemDC);
}

bool Button::isOver(int x, int y)	//���콺���� üũ
{
	if ((rect.left <= x) && (x <= rect.right) && (rect.top <= y) && (y <= rect.bottom))
	{
		Button_State_Num = Over;
		bIsOn = true;
		return true;
	}
	Button_State_Num = Up; //���ÿ� ��ư�� �ö� ����
	bIsOn = false;
	return false;
}

bool Button::isClick(int x, int y)	//���콺������ ���� �Լ��ε� �� ���������� �Լ��� �̸��� �ٸ��� �Ͽ� ���� ������ ����
{									//�ƴϸ� ���콺���� �� �ܿ� Ŭ�� ���� �߰��Ͽ� ������ �Ǿ�����, Ŭ���� �Ǿ����� üũ�� �� ����
	if (this->isOver(x, y))
	{
		Button_State_Num = Down;
		bIsOn = true;
		return true;
	}
	bIsOn = false;
	return false;
}