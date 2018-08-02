#include "stdafx.h"
#include "ButtonObj.h"

//깃허브 동기화 되는지 확인용으로 주석++
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
	SetRect({ x, y, x + w, y + h }); //LEFT와 RIGHT는 x값을 받고, TOP과 BOTTOM은 Y값을 받으므로
	pos.x = x; //그림을 띄울 좌표와
	pos.y = y;
	this->w = w; //그림의 너비, 높이를 지정
	this->h = h;

	SpriteColor = click; //마젠타 빼주기
}

void Button::Draw(HDC hMemDC)
{
	//hPen = CreatePen(PS_INSIDEFRAME, 2, PenColor);
	//OldPen = (HPEN)SelectObject(hMemDC, hPen);

	//if (!bIsOn)	//온 여부에 따라서 어떤 브러쉬를 적용 할 것인지 체크
	//{
	//	hBrush = CreateSolidBrush(BrushColor);
	//	OldBrush = (HBRUSH)SelectObject(hMemDC, hBrush);
	//}
	//else
	//{
	//	hBrush = CreateSolidBrush(ClickColor);
	//	OldBrush = (HBRUSH)SelectObject(hMemDC, hBrush);
	//}

	////받은 후면DC에 그린다
	//Rectangle(hMemDC, rect.left, rect.top, rect.right, rect.bottom);

	//if (hPen != NULL)
	//	DeleteObject(SelectObject(hMemDC, OldPen));
	//if (hBrush != NULL)
	//	DeleteObject(SelectObject(hMemDC, OldBrush));
	////잊지않게 지워주기
	Btn_Bitmap[Button_State_Num].Draw(hMemDC);
}

bool Button::isOver(int x, int y)	//마우스오버 체크
{
	if ((rect.left <= x) && (x <= rect.right) && (rect.top <= y) && (y <= rect.bottom))
	{
		Button_State_Num = Over;
		bIsOn = true;
		return true;
	}
	Button_State_Num = Up; //평상시엔 버튼이 올라간 상태
	bIsOn = false;
	return false;
}

bool Button::isClick(int x, int y)	//마우스오버와 같은 함수인데 또 만든이유는 함수의 이름을 다르게 하여 보기 편함을 위해
{									//아니면 마우스오버 색 외에 클릭 색도 추가하여 오버가 되었는지, 클릭이 되었는지 체크할 수 있음
	if (this->isOver(x, y))
	{
		Button_State_Num = Down;
		bIsOn = true;
		return true;
	}
	bIsOn = false;
	return false;
}