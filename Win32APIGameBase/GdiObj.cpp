#include "stdafx.h"
#include "GdiObj.h"

void Gdi::SetPenColor(COLORREF color)
{
	this->PenColor = color;
}

void Gdi::SetBrushColor(COLORREF color)
{
	this->BrushColor = color;
}

void Gdi::SetTextsColor(COLORREF color)
{
	this->TextColor = color;
}

void Gdi::Rect(HDC hMemDC, RECT rt)
{
	hPen = CreatePen(PS_INSIDEFRAME, 2, PenColor);
	OldPen = (HPEN)SelectObject(hMemDC, hPen);
	hBrush = CreateSolidBrush(BrushColor);
	OldBrush = (HBRUSH)SelectObject(hMemDC, hBrush);

	// 그리기
	Rectangle(hMemDC, rt.left, rt.top, rt.right, rt.bottom);

	if (hPen != NULL)
		DeleteObject(SelectObject(hMemDC, OldPen));
	if (hBrush != NULL)
		DeleteObject(SelectObject(hMemDC, OldBrush));
}

void Gdi::Circle(HDC hMemDC, int x, int y, int r)
{
	hPen = CreatePen(PS_INSIDEFRAME, 2, PenColor);
	OldPen = (HPEN)SelectObject(hMemDC, hPen);
	hBrush = CreateSolidBrush(BrushColor);
	OldBrush = (HBRUSH)SelectObject(hMemDC, hBrush);

	// 그리기
	Ellipse(hMemDC, x, y, x + r, y + r);

	if (hPen != NULL)
		DeleteObject(SelectObject(hMemDC, OldPen));
	if (hBrush != NULL)
		DeleteObject(SelectObject(hMemDC, OldBrush));
}

void Gdi::Text(HDC hMemDC, int x, int y, const TCHAR* text, int s) //텍스트 그리기
{
	hFont = CreateFont(s, 0, 0, 0, FW_NORMAL, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, 0, TEXT(FONT));
	OldFont = (HFONT)SelectObject(hMemDC, hFont);
	//폰트를 저장 PEN과 BRUSH와 동일하게 선택하고 해제하여서 사용함
	//s는 사이즈 FONT는 폰트를 저장해둔 매크로 

	SetBkMode(hMemDC, TRANSPARENT);		//배경을 투명하게
	SetTextColor(hMemDC, TextColor);	//색 변경
	TextOut(hMemDC, x, y, text, lstrlen(text));	//그리기

	if (hFont != NULL)
		DeleteObject(SelectObject(hMemDC, OldFont));
	//폰트 해제
}

void Gdi::Dot(HDC hMemDC, int x, int y, COLORREF color)
{
	SetPixel(hMemDC, x, y, color);
}

void Gdi::Line(HDC hMemDC, int x1, int y1, int x2, int y2)
{
	hPen = CreatePen(PS_INSIDEFRAME, 2, PenColor);
	OldPen = (HPEN)SelectObject(hMemDC, hPen);

	MoveToEx(hMemDC, x1, y1, NULL);
	LineTo(hMemDC, x2, y2);

	if (hPen != NULL)
		DeleteObject(SelectObject(hMemDC, OldPen));
}