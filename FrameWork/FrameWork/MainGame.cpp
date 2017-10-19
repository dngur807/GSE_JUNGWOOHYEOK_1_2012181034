#include "stdafx.h"
#include "MainGame.h"
#include "Value.h"
#include "Renderer.h"

CMainGame::CMainGame()
	: m_pRenderer(nullptr)
{
}
CMainGame::~CMainGame()
{
	if (m_pRenderer)
	{
		delete m_pRenderer;
		m_pRenderer = nullptr;
	}
}
void CMainGame::Initialize()
{
	if (m_pRenderer == nullptr)
	{
		m_pRenderer = new CRenderer;
		m_pRenderer->Initialize();
	}
}

void CMainGame::Update()
{
}

void CMainGame::Render()
{
	if (m_pRenderer)
	{
		m_pRenderer->DrawSolidRect(-400, 0, 0, 100, 1, 0, 1, 1);
	}
}
