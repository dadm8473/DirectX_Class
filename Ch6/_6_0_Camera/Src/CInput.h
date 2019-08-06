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
	BYTE	m_KeyCur[256];	// 현재의 상태
	BYTE	m_KeyOld[256];	// 이전의 상태
	BYTE	m_KeyMap[256];	// 키보드 맵

public:
	int	Update();

	bool	KeyDown(int nKey);
	bool	KeyUp(int nKey);
	bool	KeyPress(int nKey);
};
