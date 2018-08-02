#pragma once

#define OFF		0
#define OVER	1
#define ON		2

class Button	//��ư!
{
public:
	Button() { }
	~Button() { }

private:
	int stateBtn = OFF;

	HDC hdcImg;
	HBITMAP hBitmap;
	HBITMAP hOnBitmap;
	HBITMAP hOverBitmap;
	COLORREF SpriteColor;
	POINT pos;
	int w;
	int h;

public:
	void Init(HWND hWnd, int x, int y, int w, int h, LPCWSTR FileName, LPCWSTR OnFileName, LPCWSTR OverFileName, COLORREF sprite = RGB(255, 0, 255));	//szFileName �� ��Ʈ�� ������ �̸�
	void Draw(HDC hMemDC);	//�׸���
	void Ternimate();		//����!

	void SetPosition(int x, int y);
	void SetSpriteColor(COLORREF color);

	POINT GetPosition();

	bool isOver(int x, int y);
	bool isClickDown(int x, int y);
	bool isClickUp(int x, int y);

};