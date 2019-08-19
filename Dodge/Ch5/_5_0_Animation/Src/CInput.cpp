#include "DXUT.h"
#include "CInput.h"

CInput::CInput()
{
	memset(m_KeyCur, 0, sizeof(m_KeyCur));
	memset(m_KeyOld, 0, sizeof(m_KeyOld));
	memset(m_KeyMap, 0, sizeof(m_KeyMap));

	SetKeyboardState(m_KeyCur);
}


CInput::~CInput()
{
}

int CInput::Update()
{
	int i = 0;

	memcpy(m_KeyOld, m_KeyCur, sizeof(m_KeyOld));

	memset(m_KeyCur, 0, sizeof(m_KeyCur));
	memset(m_KeyMap, 0, sizeof(m_KeyMap));

	GetKeyboardState(m_KeyCur);


	for (i = 0; i < 256; ++i)
	{
		BYTE	vKey = m_KeyCur[i] & 0x80;	// 현재의 키보드 상태를 읽어온다.
		m_KeyCur[i] = (vKey) ? 1 : 0;		// 키보드 상태를 0과 1로 정한다.

		INT nOld = m_KeyOld[i];
		INT nCur = m_KeyCur[i];

		if (0 == nOld && 1 == nCur)	m_KeyMap[i] = EINPUT_DOWN;	// Down
		else if (1 == nOld && 0 == nCur)	m_KeyMap[i] = EINPUT_UP;	// Up
		else if (1 == nOld && 1 == nCur)	m_KeyMap[i] = EINPUT_PRESS;	// Press
		else				m_KeyMap[i] = EINPUT_NONE;	// NONE
	}

	return 0;
}

bool CInput::KeyDown(int nKey)
{
	return (m_KeyMap[nKey] == EINPUT_DOWN);
}

bool CInput::KeyUp(int nKey)
{
	return (m_KeyMap[nKey] == EINPUT_UP);
}

bool CInput::KeyPress(int nKey)
{
	return (m_KeyMap[nKey] == EINPUT_PRESS);
}
