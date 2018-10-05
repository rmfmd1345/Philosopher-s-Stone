#pragma once

class SpriteHelper
{
private:

	HDC hdcImg;				//�̸� �׷��� ��Ʈ���� DC
	HBITMAP hBitmap;		//��Ʈ��
	COLORREF SpriteColor;	//����ȭ �÷� (����Ÿ�� �⺻)
	POINT pos;				//��ǥ
	RECT rtImg;				//ǥ�� �� �̹��� ũ��
	int w;					//�ʺ�
	int h;					//����
	int term;				//��������Ʈ ����
	int CurrentFrame;		//���� ��µǴ� �̹���	
	int LastFrame;			//��ü �̹��� ��	

public:
	void Init(HWND hWnd, int x, int y, int w, int h, int f, LPCWSTR szFileName, COLORREF sprite = RGB(255, 0, 255));
	void Draw(HDC hMemDC);
	void ReverseDraw(HDC hMemDC);
	void Ternimate();

	void SetPosition(int x, int y);
	void SetSpriteColor(COLORREF color);

	void NextFrameSprite();
	void SetFrameSprite(int f);
};