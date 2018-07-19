#include "stdafx.h"
#include "ButtonObj.h"

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

void Button::Init(RECT rt, COLORREF pen, COLORREF brush, COLORREF click)
{
	SetRect(rt);
	SetPenColor(pen);
	SetBrushColor(brush);
	ClickColor = click;
}

void Button::Draw(HDC hMemDC)
{
	hPen = CreatePen(PS_INSIDEFRAME, 2, PenColor);
	OldPen = (HPEN)SelectObject(hMemDC, hPen);

	if (!bIsOn)	//온 여부에 따라서 어떤 브러쉬를 적용 할 것인지 체크
	{
		hBrush = CreateSolidBrush(BrushColor);
		OldBrush = (HBRUSH)SelectObject(hMemDC, hBrush);
	}
	else
	{
		hBrush = CreateSolidBrush(ClickColor);
		OldBrush = (HBRUSH)SelectObject(hMemDC, hBrush);
	}

	//받은 후면DC에 그린다
	Rectangle(hMemDC, rect.left, rect.top, rect.right, rect.bottom);

	if (hPen != NULL)
		DeleteObject(SelectObject(hMemDC, OldPen));
	if (hBrush != NULL)
		DeleteObject(SelectObject(hMemDC, OldBrush));
	//잊지않게 지워주기
}

bool Button::isOver(int x, int y)	//마우스오버 체크
{
	if ((rect.left <= x) && (x <= rect.right) && (rect.top <= y) && (y <= rect.bottom))
	{
		bIsOn = true;
		return true;
	}
	bIsOn = false;
	return false;
}

bool Button::isClick(int x, int y)	//마우스오버와 같은 함수인데 또 만든이유는 함수의 이름을 다르게 하여 보기 편함을 위해
{									//아니면 마우스오버 색 외에 클릭 색도 추가하여 오버가 되었는지, 클릭이 되었는지 체크할 수 있음
	if (this->isOver(x, y))
	{
		bIsOn = true;
		return true;
	}
	bIsOn = false;
	return false;
}