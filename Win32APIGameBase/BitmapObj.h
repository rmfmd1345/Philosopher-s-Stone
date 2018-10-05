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
	int w;					//�ʺ�
	int h;					//����

public:
	void Init(HWND hWnd, int x, int y, int w, int h, LPCWSTR szFileName, COLORREF sprite = RGB(255, 0, 255));	//szFileName �� ��Ʈ�� ������ �̸�
	void Draw(HDC hMemDC);	//�׸���
	void Ternimate();		//����!

	void SetPosition(int _x, int _y);
	void SetDrawArea(int _w, int _h);
	void SetSpriteColor(COLORREF color);
};