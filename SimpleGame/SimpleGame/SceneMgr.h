#pragma once

#define MAX_OBJECTS_COUNT	50

class Object;
class SceneMgr
{
public:
	SceneMgr();
	~SceneMgr();

	void CreateObject(float x, float y, float z, float r = 1.0f, float g = 1.0f, float b = 1.0f);

	void Update();
	void Render();
	void Clear();
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
};

