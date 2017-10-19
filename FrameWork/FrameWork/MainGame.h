#pragma once
class CRenderer;
class CMainGame
{
public:
	CMainGame();
	~CMainGame();

public:
	void Initialize();
	void Update();
	void Render();

private:
	CRenderer*		m_pRenderer;
};