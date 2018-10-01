#pragma once

class Gdi //그리기 도구 (폰트부분 관련 텍스트를 제외하고 설명 생략)
{
public:
	Gdi(void) { 
	}
	~Gdi(void) {
	}

private:
	HPEN hPen;
	HPEN OldPen;
	HBRUSH hBrush;
	HBRUSH OldBrush;
	HFONT hFont;
	HFONT OldFont;

	COLORREF PenColor;
	COLORREF BrushColor;
	COLORREF TextColor;

public:
	void SetPenColor(COLORREF color);
	void SetBrushColor(COLORREF color);
	void SetTextsColor(COLORREF color);

public:
	void Rect(HDC hMemDC, RECT rt);
	void Circle(HDC hMemDC, int x, int y, int r);
	void Text(HDC hMemDC, int x, int y, const TCHAR* text, int s = 12);
	void Dot(HDC hMemDC, int x, int y, COLORREF color);
	void Line(HDC hMemDC, int x1, int y1, int x2, int y2);

};

