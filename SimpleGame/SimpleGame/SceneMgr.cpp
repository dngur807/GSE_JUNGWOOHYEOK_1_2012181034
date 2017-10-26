#include "stdafx.h"
#include "SceneMgr.h"
#include "Object.h"
#include "Renderer.h"
SceneMgr::SceneMgr()
{
	ZeroMemory(m_ObjectList, 0);
	m_iObjectSize = 0;
	m_dwTime = 0;
}


SceneMgr::~SceneMgr()
{
	delete m_pRenderer;

}

void SceneMgr::CreateObject(float x, float y, float z,  float r, float g, float b)
{
	if (m_pRenderer == nullptr)
	{
		m_pRenderer = new Renderer(500, 500);

		if (!m_pRenderer->IsInitialized())
		{
			std::cout << "Renderer could not be initialized.. \n";

		}
	}
	


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
		
}

void SceneMgr::Update(float fTime)
{


	for (int i = 0; i < m_iObjectSize; ++i)
	{
		m_ObjectList[i]->SetIsColl(false);

		for (int j = 0; j < m_iObjectSize; ++j)
		{
			if (i != j)
			{
				if (m_ObjectList[i]->GetIsDestory() == false &&
					m_ObjectList[j]->GetIsDestory() == false)
				{
					m_ObjectList[i]->CollisionCheck(m_ObjectList[j]->GetInfo().vPos.x, m_ObjectList[j]->GetInfo().vPos.y, m_ObjectList[j]->GetInfo().size);
				}


			}
		}
		m_ObjectList[i]->Update(fTime);

		if (m_ObjectList[i]->GetIsDestory() == true)
		{
			Delete(i);
		}
	}

	


	
}
void SceneMgr::Render()
{
	for (int i = 0; i < m_iObjectSize; ++i)
	{
		Object* pobj = GetObj(i);

		if (pobj && pobj ->GetIsDestory() == false)
		{
			m_pRenderer->DrawSolidRect(pobj->GetInfo().vPos.x, pobj->GetInfo().vPos.y, pobj->GetInfo().vPos.z
				, pobj->GetInfo().size
				, pobj->GetInfo().r, pobj->GetInfo().g, pobj->GetInfo().b, pobj->GetInfo().a);
		}
	}

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

void SceneMgr::Delete(int index)
{
	if (index < m_iObjectSize)
	{
		if (m_ObjectList[index])
		{
			delete m_ObjectList[index];
			m_ObjectList[index] = nullptr;

			//¶¯±â±â

			for (int i = index; i < m_iObjectSize - 1; ++i)
			{
				m_ObjectList[i] = m_ObjectList[i + 1];
				m_ObjectList[i + 1] = nullptr;
			}
			--m_iObjectSize;
		}
	}
}
