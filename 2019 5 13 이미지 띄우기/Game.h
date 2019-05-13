#pragma once

extern void Init(); // 디바이스 불러오기?

extern void Term(); // 디바이스 종료같은 느낌 소멸자

extern void Update(float deltaTime); // 유니티에서 Time.deltaTime 과 비슷한 역활을 해줄 친구

extern void Render(); // 그리기

extern void MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam); // 마우스랑 키보드 입력 받는거 도와주는 친구