#pragma once

class Button	//버튼!
{
public:
	Button() { }
	~Button() { }

private:
	bool bIsOn = false;	//온이 되었는가?
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

	HDC hdcImg;				//미리 그려둘 비트맵의 DC
	COLORREF SpriteColor;	//투명화 컬러 (마젠타가 기본)
	POINT pos;				//좌표
	int w;					//너비
	int h;					//높이

public:
	void Init(int x, int y, int w, int h, COLORREF click = RGB(255, 0, 255));	//초기화
	void Draw(HDC hMemDC);	//그리기

	void SetRect(RECT rt);	//위치 변경
	void SetPenColor(COLORREF color);	//펜 색 변경
	void SetBrushColor(COLORREF color);	//브러쉬 색 변경
	//왜 오버마우스 색 변경이 없냐면 깜빡하고 안만들었음

	bool isOver(int x, int y);	//마우스가 올라왔는지
	bool isClick(int x, int y);	//클릭이 되었는지
};