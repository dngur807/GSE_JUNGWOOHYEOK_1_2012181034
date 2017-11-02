#include "stdafx.h"
#include "SceneMgr.h"
#include "Object.h"
#include "Renderer.h"
SceneMgr::SceneMgr()
{
	//ZeroMemory(m_ObjectList, 0);
	m_vecObject.reserve(MAX_OBJECTS_COUNT);

	m_iObjectSize = 0;
	m_dwTime = 0;
}


SceneMgr::~SceneMgr()
{
	delete m_pRenderer;

}

void SceneMgr::CreateObject(float x, float y, float z , int iType ,  float r, float g, float b)
{
	if (m_pRenderer == nullptr)
	{
		m_pRenderer = new Renderer(500, 500);

		if (!m_pRenderer->IsInitialized())
		{
			std::cout << "Renderer could not be initialized.. \n";

		}
	}


	Object* pobj = new Object(iType);
	pobj->SetInfo(OBJ_INFO(x, y, z, 20, r, g, b, 1.0f));
	pobj->Initialize();
	m_vecObject.push_back(pobj);




	/*if (m_iObjectSize < MAX_OBJECTS_COUNT)
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
		*/
}

void SceneMgr::Update(float fTime)
{


	for (int i = 0; i < m_vecObject.size(); ++i)
	{
		m_vecObject[i]->SetIsColl(false);

		for (int j = 0; j < m_vecObject.size(); ++j)
		{
			if (i != j)
			{
				if (m_vecObject[i]->GetIsDestory() == false &&
					m_vecObject[j]->GetIsDestory() == false)
				{
					if (m_vecObject[i]->GetType() == OBJECT_CHARACTER
						&& m_vecObject[j]->GetType() == OBJECT_CHARACTER)
					{
						continue;
					}
					else if (m_vecObject[i]->GetType() == OBJECT_BUILDING
						&& m_vecObject[j]->GetType() == OBJECT_BULLET)
					{
						continue;
					}
					else if (m_vecObject[i]->GetType() == OBJECT_BULLET
						&& m_vecObject[j]->GetType() == OBJECT_BUILDING)
					{
						continue;
					}

					else if (m_vecObject[i]->GetType() == OBJECT_BULLET
						&& m_vecObject[j]->GetType() == OBJECT_BULLET)
					{
						continue;
					}


					m_vecObject[i]->CollisionCheck(m_vecObject[j]->GetInfo().vPos.x, m_vecObject[j]->GetInfo().vPos.y, m_vecObject[j]->GetInfo().size);
				}


			}
		}
		if (m_vecObject[i]->Update(fTime) == 2)
		{
			CreateObject(m_vecObject[i]->GetInfo().vPos.x, m_vecObject[i]->GetInfo().vPos.y, m_vecObject[i]->GetInfo().vPos.z, OBJECT_BULLET);

		}

		if (m_vecObject[i]->GetIsDestory() == true)
		{
			Delete(i);
		}
	}

	


	
}
void SceneMgr::Render()
{
	for (int i = 0; i < m_vecObject.size(); ++i)
	{
		Object* pobj = m_vecObject[i];

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
	/*for (int i = 0; i < m_iObjectSize; ++i)
	{
		if (m_ObjectList[i])
		{
			delete m_ObjectList[i];
			m_ObjectList[i] = nullptr;
		}
	}
	m_iObjectSize = 0;*/
	for (int i = 0; i < m_vecObject.size(); ++i)
	{
		delete m_vecObject[i];
	}
	m_vecObject.clear();
}

void SceneMgr::Delete(int index)
{
	if (index < m_vecObject.size())
	{
		if (m_vecObject[index])
		{
			delete m_vecObject[index];
			m_vecObject[index] = nullptr;

			Object* temp = m_vecObject[index]; // ¸Ç³¡
			m_vecObject[index] = m_vecObject[m_vecObject.size() - 1];
			m_vecObject[m_vecObject.size() - 1] = temp;
			m_vecObject.pop_back();
		}
	}
}
