#include "DXUT.h"
#include "Title.h"


Title::Title()
{
}


Title::~Title()
{
}

void Title::Init()
{
	// ��������Ʈ ������ �߰�
	m_Renderer = new CSpriteRenderer();
	m_Renderer->Create(L"Title.png");

	CTitleControl * TitleControl = new CTitleControl(this);
	Components.push_front(TitleControl);

	position = { 512,384 };
	pivot = { m_Renderer->GetTextureInfo()->GetImageWidth() * 0.5f , m_Renderer->GetTextureInfo()->GetImageHeight() * 0.5f };
}
