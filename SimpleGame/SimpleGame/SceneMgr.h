#pragma once

#define MAX_OBJECTS_COUNT	10

class Renderer;
class Object;
class SceneMgr
{
public:
	SceneMgr();
	~SceneMgr();

	void CreateObject(float x, float y, float z, float r = 1.0f, float g = 1.0f, float b = 1.0f);

	void Update(float fTime);
	void Render();
	void Clear();
	void Delete(int index);
	Object* GetObj(int iIndex)
	{
		if (iIndex >= m_iObjectSize)
			return nullptr;
		return m_ObjectList[iIndex];
	}
	
	int GetSize() { return m_iObjectSize; }
private:
	Object*		m_ObjectList[MAX_OBJECTS_COUNT];
	int			m_iObjectSize;
	Renderer*	m_pRenderer;
	DWORD		m_dwTime;
};

