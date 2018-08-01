#pragma once

class Bitmap	//��Ʈ�� ��ü ����
{
public:
	Bitmap() { }
	~Bitmap() { }

private:
	HDC hdcImg;				//�̸� �׷��� ��Ʈ���� DC
	HBITMAP hBitmap;		//��Ʈ��
	COLORREF SpriteColor;	//����ȭ �÷� (����Ÿ�� �⺻)
	POINT pos;				//��ǥ

public:
	int w;					//�ʺ�
	int h;					//����

public:
	void Init(HWND hWnd, int x, int y, int w, int h, LPCWSTR szFileName, COLORREF sprite = RGB(255, 0, 255));	//szFileName �� ��Ʈ�� ������ �̸�
	void Draw(HDC hMemDC);	//�׸���
	void Ternimate();		//����!

	void SetPosition(int x, int y);
	void SetSpriteColor(COLORREF color);
};