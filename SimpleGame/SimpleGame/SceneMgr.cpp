#include "stdafx.h"
#include "SceneMgr.h"
#include "Object.h"
#include "Renderer.h"
SceneMgr::SceneMgr()
{
	//ZeroMemory(m_ObjectList, 0);
	m_fTimeUP = 0.0f;
	m_fTimeDOWN = 0.0f;
	m_IsCreateColltime = false;
}


SceneMgr::~SceneMgr()
{
	delete m_pRenderer;

}

void SceneMgr::CreateObject(float x, float y, float z , int iType , int iTeam ,  float r, float g, float b , Object* pme , GLuint iTexture)
{
	Object* pobj = new Object(iType , iTeam);
	pobj->SetInfo(OBJ_INFO(x, y, z, 20, r, g, b, 1.0f));
	pobj->SetMe(pme);//미사일 발사 객체 알기위해서
	pobj->Initialize();
	pobj->SetTexture(iTexture);
	m_vecObject.push_back(pobj);
}

void SceneMgr::Initialize()
{
	m_vecObject.reserve(MAX_OBJECTS_COUNT);
	m_iObjectSize = 0;
	m_dwTime = 0;
	


	CreateObject(0, WINCY / 2  - 50, 0, OBJECT_BUILDING, TEAM_1, 1, 1, 1, nullptr, m_pRenderer->CreatePngTexture("./Textures/test.png"));
	CreateObject(-160, WINCY / 2 - 80, 0, OBJECT_BUILDING, TEAM_1, 1, 1, 1, nullptr, m_pRenderer->CreatePngTexture("./Textures/test.png"));
	CreateObject(160, WINCY / 2 - 80, 0, OBJECT_BUILDING, TEAM_1, 1, 1, 1, nullptr, m_pRenderer->CreatePngTexture("./Textures/test.png"));


	CreateObject(0, -WINCY / 2 + 50, 0, OBJECT_BUILDING, TEAM_2, 1, 1, 1, nullptr, m_pRenderer->CreatePngTexture("./Textures/nexus.png"));
	CreateObject(-160, -WINCY / 2 + 80, 0, OBJECT_BUILDING, TEAM_2, 1, 1, 1, nullptr, m_pRenderer->CreatePngTexture("./Textures/nexus.png"));
	CreateObject(160, -WINCY / 2 + 80, 0, OBJECT_BUILDING, TEAM_2, 1, 1, 1, nullptr, m_pRenderer->CreatePngTexture("./Textures/nexus.png"));


	if (m_pRenderer == nullptr)
	{
		m_pRenderer = new Renderer(WINCX, WINCY);

		if (!m_pRenderer->IsInitialized())
		{
			std::cout << "Renderer could not be initialized.. \n";
		}
	}

}

void SceneMgr::Update(float fTime)
{
	m_fTimeUP += fTime * 0.001f;
	m_fTimeDOWN += fTime * 0.001f;
	if (m_fTimeUP > 5.0f)
	{
		m_fTimeUP = 0.0f;
		//북쪽 진영에 5초당 1개 캐릭터 생성
		CreateObject(rand() % WINCX  - WINCX / 2,  rand() % (WINCY / 2 - 200) , 0, OBJECT_CHARACTER, TEAM_1  , 1, 1 ,1 , nullptr , m_pRenderer->CreatePngTexture("./Textures/corsair.png"));
	}
	if (m_fTimeDOWN > 7.0f)
	{
		m_IsCreateColltime = true;
		m_fTimeDOWN = 0.0f;
	//	CreateObject(rand() % WINCX - WINCX / 2, rand() % (WINCY / 2 - 200) * -1, 0, OBJECT_CHARACTER, TEAM_2);
	}

	for (int i = 0; i < m_vecObject.size(); ++i)
	{
		m_vecObject[i]->SetIsColl(false);

		for (int j = 0; j < m_vecObject.size(); ++j)
		{
			if (i != j)
			{
				if (m_vecObject[i]->GetIsDestory() == false &&
					m_vecObject[i]->GetPrevColl() == false && 
					m_vecObject[j]->GetIsDestory() == false && 
					m_vecObject[j] ->GetPrevColl() == false )
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
					else if (m_vecObject[i]->GetType() == OBJECT_ARROW
						&& m_vecObject[j]->GetType() == OBJECT_ARROW)
					{
						continue;
					}
					else if (m_vecObject[i]->GetType() == OBJECT_ARROW
						&& m_vecObject[j]->GetType() == OBJECT_BULLET)
					{
						continue;
					}

					else if (m_vecObject[i]->GetType() == OBJECT_BULLET
						&& m_vecObject[j]->GetType() == OBJECT_ARROW)
					{
						continue;
					}
					else if (m_vecObject[i]->GetType() == OBJECT_CHARACTER &&
						m_vecObject[j]->GetType() == OBJECT_ARROW
						&& m_vecObject[i] == m_vecObject[j]->GetMe())
					{
						continue;
					}
					else if (m_vecObject[i]->GetType() == OBJECT_ARROW
						&& m_vecObject[j] ->GetType() == OBJECT_CHARACTER
						&& m_vecObject[i]->GetMe() == m_vecObject[j])
					{
						continue;
					}
					else if (m_vecObject[i]->GetTeam() == m_vecObject[j]->GetTeam())
					{
						continue;
					}
					float fCurLife = m_vecObject[j]->GetLife();
					m_vecObject[j]->CollisionCheck(m_vecObject[i]->GetInfo().vPos.x, m_vecObject[i]->GetInfo().vPos.y, (int)m_vecObject[i]->GetInfo().size, m_vecObject[i]->GetLife());
					m_vecObject[i]->CollisionCheck(m_vecObject[j]->GetInfo().vPos.x, m_vecObject[j]->GetInfo().vPos.y, (int)m_vecObject[j]->GetInfo().size , fCurLife);
				}
			}
		}
		int iUpdate = 0;
		if ((iUpdate = m_vecObject[i]->Update(fTime)))
		{
			switch (iUpdate)
			{
			case UPDATE_RETURN_CREATE_BULLET:
				CreateObject(m_vecObject[i]->GetInfo().vPos.x, m_vecObject[i]->GetInfo().vPos.y, m_vecObject[i]->GetInfo().vPos.z, OBJECT_BULLET , m_vecObject[i] ->GetTeam());
				break;
			case UPDATE_RETURN_CREATE_ARROW:
				CreateObject(m_vecObject[i]->GetInfo().vPos.x, m_vecObject[i]->GetInfo().vPos.y, m_vecObject[i]->GetInfo().vPos.z, OBJECT_ARROW, m_vecObject[i]->GetTeam(), 1 , 1 , 1 , m_vecObject[i]);
				break;
			}
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

			if (pobj->GetType() == OBJECT_BUILDING || pobj->GetType() == OBJECT_CHARACTER)
			{
				//게이지 추가
				if (pobj->GetTeam() == TEAM_1)
				{
					m_pRenderer->DrawSolidRectGauge(pobj->GetInfo().vPos.x, pobj->GetInfo().vPos.y + pobj->GetInfo().size / 2, pobj->GetInfo().vPos.z, pobj->GetInfo().size , 5, 1.0f, 0, 0, 1.0f, pobj->GetLife() / pobj->GetMaxLife(), pobj->GetRenderingLevel());
				}
				else if (pobj->GetTeam() == TEAM_2)
				{
					m_pRenderer->DrawSolidRectGauge(pobj->GetInfo().vPos.x, pobj->GetInfo().vPos.y + pobj->GetInfo().size / 2, pobj->GetInfo().vPos.z, pobj->GetInfo().size, 5, 0, 0, 1, 1.0f, pobj->GetLife() / pobj->GetMaxLife(), pobj->GetRenderingLevel());
				}
			}
			if (pobj->GetTexture() != 0)
			{
				m_pRenderer->DrawTexturedRect(pobj->GetInfo().vPos.x, pobj->GetInfo().vPos.y, 0, pobj->GetInfo().size, 1, 1, 1, 1, pobj->GetTexture() , pobj->GetRenderingLevel());
			}
			else
			{
				
				m_pRenderer->DrawSolidRect(pobj->GetInfo().vPos.x, pobj->GetInfo().vPos.y, pobj->GetInfo().vPos.z
					, pobj->GetInfo().size
					, pobj->GetInfo().r, pobj->GetInfo().g, pobj->GetInfo().b, pobj->GetInfo().a , pobj->GetRenderingLevel());
			}
		}
	}

}
void SceneMgr::Clear()
{
	auto iter = remove_if(m_vecObject.begin(), m_vecObject.end(), [](const Object* pobj) {return pobj;});
	m_vecObject.erase(iter , m_vecObject.end());
}

void SceneMgr::Delete(int index)
{
	if (index < m_vecObject.size())
	{
		if (m_vecObject[index])
		{
			delete m_vecObject[index];
			m_vecObject[index] = nullptr;

			Object* temp = m_vecObject[index]; // 맨끝
			m_vecObject[index] = m_vecObject[m_vecObject.size() - 1];
			m_vecObject[m_vecObject.size() - 1] = temp;
			m_vecObject.pop_back();
		}
	}
}

void SceneMgr::MakeCharacter(int x, int y)
{
	if (GetCollTime())
	{
		if (y < 0)
		{
			m_IsCreateColltime = false;
			m_fTimeDOWN = 0.0f;
			CreateObject(x, y, 0, OBJECT_CHARACTER, TEAM_2, 1, 1, 1, nullptr, m_pRenderer->CreatePngTexture("./Textures/scout.png"));
		}
		else
		{
			printf("적진영 입니다. \n");
		}
	}
	else
	{
		printf(" %.1f초 남았습니다\n", 7 - m_fTimeDOWN);
	}

}
