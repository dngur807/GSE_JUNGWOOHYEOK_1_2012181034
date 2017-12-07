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
	

	if (m_pRenderer == nullptr)
	{
		m_pRenderer = new Renderer(WINCX, WINCY);

		if (!m_pRenderer->IsInitialized())
		{
			std::cout << "Renderer could not be initialized.. \n";
		}
	}


	textureEnemyBulid =  m_pRenderer->CreatePngTexture("./Textures/test.png");
	textureNexus = m_pRenderer->CreatePngTexture("./Textures/nexus.png");

	textureSpark1 = m_pRenderer->CreatePngTexture("./Textures/Spark1.png");
	textureBack = m_pRenderer->CreatePngTexture("./Textures/test1.png");
	texturePlayer = m_pRenderer->CreatePngTexture("./Textures/player.png");

	textureEnemy = m_pRenderer->CreatePngTexture("./Textures/run_animation.png");


	int soundBG =m_Sound.CreateSound("./SoundSamples/MF-W-90.XM");
	m_Sound.PlaySoundW(soundBG, true, 0.2f);

	CreateObject(0, WINCY / 2  - 50, 0, OBJECT_BUILDING, TEAM_1, 1, 1, 1, nullptr, textureEnemyBulid);
	CreateObject(-160, WINCY / 2 - 80, 0, OBJECT_BUILDING, TEAM_1, 1, 1, 1, nullptr, textureEnemyBulid);
	CreateObject(160, WINCY / 2 - 80, 0, OBJECT_BUILDING, TEAM_1, 1, 1, 1, nullptr, textureEnemyBulid);


	CreateObject(0, -WINCY / 2 + 50, 0, OBJECT_BUILDING, TEAM_2, 1, 1, 1, nullptr, textureNexus);
	CreateObject(-160, -WINCY / 2 + 80, 0, OBJECT_BUILDING, TEAM_2, 1, 1, 1, nullptr, textureNexus);
	CreateObject(160, -WINCY / 2 + 80, 0, OBJECT_BUILDING, TEAM_2, 1, 1, 1, nullptr, textureNexus);




}

void SceneMgr::Update(float fTime)
{
	if (m_pRenderer)
		m_pRenderer->SetSceneTransform(0 , 0 , 1 , 1);

	m_fTimeUP += fTime * 0.001f;
	m_fTimeDOWN += fTime * 0.001f;
	if (m_fTimeUP > 3.00f)
	{
		m_fTimeUP = 0.0f;
		//북쪽 진영에 0.5초당 1개 캐릭터 생성
		CreateObject(rand() % WINCX  - WINCX / 2,  rand() % (WINCY / 2 - 200) , 0, OBJECT_CHARACTER, TEAM_1  , 1, 1 ,1 , nullptr , textureEnemy);
	}
	if (m_fTimeDOWN > 0.50f)
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
					m_vecObject[j]->CollisionCheck(m_vecObject[i]->GetInfo().vPos.x, m_vecObject[i]->GetInfo().vPos.y, (int)m_vecObject[i]->GetInfo().size, m_vecObject[i]->GetDamege());

					m_vecObject[i]->CollisionCheck(m_vecObject[j]->GetInfo().vPos.x, m_vecObject[j]->GetInfo().vPos.y, (int)m_vecObject[j]->GetInfo().size , m_vecObject[j]->GetDamege());
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

	m_pRenderer->DrawText(WINCX / 2 * -1, WINCY / 2 - 100, GLUT_BITMAP_8_BY_13, 1, 1, 1, "2012181034 JWH");

	//레벨은 큰값으로 주자 0.1~0.99
	m_pRenderer->DrawTexturedRect(0, 0, 0, 800 ,1, 1, 1, 1, textureBack, 0.99);//

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
					if (pobj->GetType() == OBJECT_BUILDING)
					{
						//printf("%f\n", pobj->GetLife());
					}
					m_pRenderer->DrawSolidRectGauge(pobj->GetInfo().vPos.x, pobj->GetInfo().vPos.y + pobj->GetInfo().size / 2, pobj->GetInfo().vPos.z, pobj->GetInfo().size, 5, 0, 0, 1, 1.0f, pobj->GetLife() / pobj->GetMaxLife(), pobj->GetRenderingLevel());
				}
			}
			if (pobj->GetTexture() != 0 )
			{
				if (pobj->GetIsAnimation() == true)
				{
					m_pRenderer->DrawTexturedRectSeq(pobj->GetInfo().vPos.x, pobj->GetInfo().vPos.y, 0, pobj->GetInfo().size, 1, 1, 1, 1, pobj->GetTexture(), pobj->GetCurAniNumber(), 0, pobj->GetMaxAniNumber(), 1, pobj->GetRenderingLevel());
				}
				else
					m_pRenderer->DrawTexturedRect(pobj->GetInfo().vPos.x, pobj->GetInfo().vPos.y, 0, pobj->GetInfo().size, 1, 1, 1, 1, pobj->GetTexture() , pobj->GetRenderingLevel());
			}
			else if (pobj->GetType() == OBJECT_BULLET  )
			{
				m_pRenderer->DrawParticle(pobj->GetInfo().vPos.x, pobj->GetInfo().vPos.y, pobj->GetInfo().vPos.z, pobj->GetInfo().size, 1, 1, 1 , 1, pobj->GetDir().x, pobj->GetDir().y, textureSpark1, pobj->GetParticleTime());
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
			

			CreateObject(x, y, 0, OBJECT_CHARACTER, TEAM_2, 1, 1, 1, nullptr, texturePlayer);
		}
		else
		{
			printf("적진영 입니다. \n");
		}
	}
	else
	{
		printf(" %.1f초 남았습니다\n", 0.50f - m_fTimeDOWN);
	}

}
