#pragma once

class SpriteHelper
{
private:

	HDC hdcImg;				//�̸� �׷��� ��Ʈ���� DC

	HDC AlphaDC;				//����ȭ�� ���� �׷��� ��Ʈ���� DC
	HDC TransparentDC;				//����ȭ�� ���� �׷��� ��Ʈ���� DC
	HBITMAP TempDC;				//����ȭ�� ���� �׷��� ��Ʈ���� DC
	BLENDFUNCTION bf;		//����ȭó���� �ʿ�

	HBITMAP hBitmap;		//��Ʈ��
	//HBITMAP h0Bitmap;		//��Ʈ��

	//HBITMAP hBitmap2;		//��Ʈ��
	//HBITMAP h0Bitmap2;		//��Ʈ��

	COLORREF SpriteColor;	//����ȭ �÷� (����Ÿ�� �⺻)
	POINT pos;				//��ǥ
	RECT rtImg;				//ǥ�� �� �̹��� ũ��
	int term;				//��������Ʈ ����
	int CurrentFrame;		//���� ��µǴ� �̹���	
	int LastFrame;			//��ü �̹��� ��	

public:
	int w;					//�ʺ�
	int h;					//����
public:
	void Init(HWND hWnd, int x, int y, int w, int h, int f, LPCWSTR szFileName, COLORREF sprite = RGB(255, 0, 255));
	void Draw(HDC hMemDC);
	void AlphaDraw(HDC hMemDC);
	void ReverseDraw(HDC hMemDC);
	void Ternimate();

	void SetPosition(int x, int y);
	void SetSpriteColor(COLORREF color);
	void SetCurrentFrame(int f);

	int GetCurrentFrame();
	int GetLastFrame();

	void NextFrameSprite(bool replay);
	void NextFrameSprite_Trap();
	void SetFrameSprite(int f);
};