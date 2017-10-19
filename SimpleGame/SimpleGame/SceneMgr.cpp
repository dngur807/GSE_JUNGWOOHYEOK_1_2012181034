#include "stdafx.h"
#include "SceneMgr.h"
#include "Object.h"

SceneMgr::SceneMgr()
{
	ZeroMemory(m_ObjectList, 0);
	m_iObjectSize = 0;

}


SceneMgr::~SceneMgr()
{
}

void SceneMgr::CreateObject(float x, float y, float z,  float r, float g, float b)
{
	if (m_iObjectSize < MAX_OBJECTS_COUNT)
	{
		Object* pobj = new Object;
		pobj->SetInfo(OBJ_INFO(x, y, z, 20 , r, g, b , 1.0f));
		if (m_ObjectList[m_iObjectSize])
		{
			delete m_ObjectList[m_iObjectSize];
			m_ObjectList[m_iObjectSize] = nullptr;
		}
		m_ObjectList[m_iObjectSize] = pobj;
		++m_iObjectSize;
	}
	else
	{
		cout << "Å©±â ²Ë Âü" << endl;
	}
		
}

void SceneMgr::Update()
{

	for (int i = 0; i < m_iObjectSize ; ++i)
	{
		m_ObjectList[i]->SetIsColl(false);

		for (int j = 0; j < m_iObjectSize; ++j)
		{
			if (i != j)
			{
				m_ObjectList[i]->CollisionCheck(m_ObjectList[j]->GetInfo().vPos.x, m_ObjectList[j]->GetInfo().vPos.y, m_ObjectList[j]->GetInfo().size);

			}
		}
		m_ObjectList[i]->Update();
	}
}
void SceneMgr::Render()
{
}
void SceneMgr::Clear()
{
	for (int i = 0; i < m_iObjectSize; ++i)
	{
		if (m_ObjectList[i])
		{
			delete m_ObjectList[i];
			m_ObjectList[i] = nullptr;
		}
	}
	m_iObjectSize = 0;
}