#pragma once

#define MAX_OBJECTS_COUNT	10



class Renderer;
class Object;
class SceneMgr
{
public:
	SceneMgr();
	~SceneMgr();

	void CreateObject(float x, float y, float z, int iType, int iTeam, float r = 1.0f, float g = 1.0f, float b = 1.0f, Object* pme = nullptr , GLuint iTexture = 0);
	void Initialize();
	void Update(float fTime);
	void Render();
	void Clear();
	void Delete(int index);
	//Object* GetObj(int iIndex)
	//{
	//	if (iIndex >= m_iObjectSize)
	//		return nullptr;
	//	return m_ObjectList[iIndex];
	//}
	
	int GetSize() { return m_iObjectSize; }
	bool GetCollTime() { return m_IsCreateColltime; }
	void MakeCharacter(int x , int y);
private:
//	Object*		m_ObjectList[MAX_OBJECTS_COUNT];
	vector<Object*>			m_vecObject;
	int			m_iObjectSize;
	Renderer*	m_pRenderer;
	DWORD		m_dwTime;
	float		m_fTimeUP;
	float		m_fTimeDOWN;
	bool		m_IsCreateColltime;
};

