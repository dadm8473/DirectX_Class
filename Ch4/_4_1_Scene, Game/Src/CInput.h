#pragma once

enum EInputState
{
	EINPUT_NONE = 0,
	EINPUT_DOWN,
	EINPUT_UP,
	EINPUT_PRESS
};

class CInput
{
public:
	CInput();
	~CInput();

protected:
	BYTE	m_KeyCur[256];	// ������ ����
	BYTE	m_KeyOld[256];	// ������ ����
	BYTE	m_KeyMap[256];	// Ű���� ��

public:
	int	Update();

	bool	KeyDown(int nKey);
	bool	KeyUp(int nKey);
	bool	KeyPress(int nKey);
};
