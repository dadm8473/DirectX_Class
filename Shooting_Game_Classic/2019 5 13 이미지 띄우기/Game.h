#pragma once

extern void Init(); // ����̽� �ҷ�����?

extern void Term(); // ����̽� ���ᰰ�� ���� �Ҹ���

extern void Update(float deltaTime); // ����Ƽ���� Time.deltaTime �� ����� ��Ȱ�� ���� ģ��

extern void Render(); // �׸���

extern void MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam); // ���콺�� Ű���� �Է� �޴°� �����ִ� ģ��