#include "stdafx.h"
#include "Object.h"


Object::Object()
{
	m_iType = OBJECT_CHARACTER;
	m_iTeam = TEAM_NEUTRAL;
	m_pME = nullptr;
}
Object::Object(int type , int iTeam)
{
	m_iType = type;
	m_iTeam = iTeam;
	m_pME = nullptr;
}

Object::~Object()
{
}

void Object::Initialize()
{
	m_texCharacter = 0;
	m_IsVisible = true;
	m_IsCollision = false;
	m_IsDestory = false;
	m_PrevColl = false;
	m_IsVisible = true;
	m_fCollTime = 0.0f;

	m_fTime = 0.0f;
	m_vPrevDir.x = (rand() % 10 + 1) * 0.1f;
	m_vPrevDir.y = (rand() % 10 + 1) * 0.1f;
	m_vDir.x = (rand() % 10 + 1) * 0.1f;
	m_vDir.y = (rand() % 10 + 1) * 0.1f;
	m_fTarget = 250.0f;
	m_fTargetY = 250.0f;
	m_fLifeTime = 10000.0f;

	int i = rand() % 4;
	if (i == 0)
		m_vDir.x *= -1;
	else if (i == 1)
	{
		m_vDir.y *= -1;
	}
	else if (i == 2)
	{
		m_vDir.x *= -1;
		m_vDir.y *= -1;
	}


	switch (m_iType)
	{
	case OBJECT_BUILDING:
		m_fLife = 500;
		m_fSpeed = 0;
		m_tInfo.size = 100;
		m_CurR = 1.0f;
		m_CurG = 1.0f;
		m_CurB = 0.0f;
		m_tInfo.a = 1.0f;
		m_fDamage = 30.0f;
		break;
	case OBJECT_CHARACTER:
	{
		m_fLife = 10;
		m_fSpeed = 300;
		m_tInfo.size = 10;
		m_tInfo.a = 1.0f;
		m_fDamage = 30.0f;

		if (m_iTeam == TEAM_1)
		{
			m_tInfo.r = m_CurR = 1.0f;
			m_tInfo.g = m_CurG = 0.0f;
			m_tInfo.b = m_CurB = 0.0f;
		}
		else
		{
			m_tInfo.r = m_CurR = 0.0f;
			m_tInfo.g = m_CurG = 0.0f;
			m_tInfo.b = m_CurB = 1.0f;
		}
	}
		break;
	case OBJECT_BULLET:
	{
		m_fLife = 20;
		m_fSpeed = 600;
		m_tInfo.size = 4;

		if (m_iTeam == TEAM_1)
		{
			m_tInfo.r = m_CurR = 1.0f;
			m_tInfo.g = m_CurG = 0.0f;
			m_tInfo.b = m_CurB = 0.0f;
			m_vDir.y = -1.0f;
		}
		else
		{
			m_tInfo.r = m_CurR = 0.0f;
			m_tInfo.g = m_CurG = 0.0f;
			m_tInfo.b = m_CurB = 1.0f;
			m_vDir.y = 1.0f;
		}
			
		m_tInfo.a = 1.0f;
		m_fDamage = 10.0f;
	}
		break;
	case OBJECT_ARROW:
	{
		m_fLife = 10;
		m_fSpeed = 100;
		m_tInfo.size = 4;
		if (m_iTeam == TEAM_1)
		{
			m_tInfo.r = m_CurR = 0.5f;
			m_tInfo.g = m_CurG = 0.2f;
			m_tInfo.b = m_CurB = 0.7f;
			m_vDir.y = -1.0f;
		}
		else
		{
			m_tInfo.r = m_CurR = 1.0f;
			m_tInfo.g = m_CurG = 1.0f;
			m_tInfo.b = m_CurB = 0.0f;
			m_vDir.y = 1.0f;
		}
		m_tInfo.a = 1.0f;
		m_fDamage = 10.0f;
		break;
	}
	}
}

int Object::Update(float fTime)
{
	if (m_fLife <= 0 || m_fLifeTime <= 0)
		m_IsDestory = true;

	if (m_IsDestory == true)
		return 1;

	if (m_pME && m_pME ->GetIsDestory())
	{
		m_pME = nullptr;
	}

	int CreateBullet = 0;//2이면 생성

	if (m_iType == OBJECT_BUILDING)
	{
		m_fTime += fTime * 0.001f;
		if (m_fTime > 10.0f)
		{
			m_fTime = 0;
			CreateBullet = UPDATE_RETURN_CREATE_BULLET;
		}
		//총알 0.5초마다 생성
	}
	else if (m_iType == OBJECT_CHARACTER)
	{
		m_fTime += fTime * 0.001f;
		if (m_fTime > 3.0f)
		{
			m_fTime = 0;
			CreateBullet = UPDATE_RETURN_CREATE_ARROW;
		}
	}


	//m_fLifeTime -= 0.01f;

	if (m_IsCollision == true)
	{
		m_PrevColl = true;
	}

	if (m_PrevColl)
	{
		m_fCollTime += fTime * 0.001f;
		if (m_fCollTime < 0.05f)
		{
			//빨간색
			m_tInfo.r = 1.0f;
			m_tInfo.g = 0.0f;
			m_tInfo.b = 1.0f;
			m_tInfo.a = 1.0f;
		}
		else
		{
			m_PrevColl = false;
			m_fCollTime = 0.0f;
		}
	}
	if (m_iType != OBJECT_BULLET && m_iType != OBJECT_ARROW)
	{
		Move(fTime);
	}
	
	else
	{
		float Time = fTime * 0.001f;
		m_vDir.Normalize();
		m_tInfo.vPos += m_vDir * (m_fSpeed * Time);
		if (m_tInfo.vPos.x >= WINCX / 2
			|| m_tInfo.vPos.x < -WINCX / 2
			|| m_tInfo.vPos.y >= WINCY / 2
			|| m_tInfo.vPos.y < -WINCY / 2
			)
		{
			m_IsDestory = true;
			return UPDATE_RETURN_DELETE;
		}
	}
	if (m_PrevColl)
	{
	}
	else
	{
		m_tInfo.r = m_CurR;
		m_tInfo.g = m_CurG;
		m_tInfo.b = m_CurB;
		m_tInfo.a = 1.0f;
	}
	return CreateBullet;
}
void Object::Move(float fTime)
{
	if (m_tInfo.vPos.x <= m_fTarget)
	{
		m_vDir.x = m_vPrevDir.x;
		if (m_fTarget - m_tInfo.vPos.x <= 20)
		{
			m_vPrevDir.x = -1.0f;
			//m_vPrevDir.y = (rand() % 10 + 1) * 0.1f;
			m_fTarget = -WINCX /2;
		}
	}
	else if (m_tInfo.vPos.x >= m_fTarget)
	{
		m_vDir.x = m_vPrevDir.x;
		if (m_tInfo.vPos.x - m_fTarget <= 20)
		{
			m_vPrevDir.x = 1.0f;
			//m_vPrevDir.y = (rand() % 10 + 1) * 0.1f;
			m_fTarget = WINCX / 2;
		}
	}

	if (m_tInfo.vPos.y <= m_fTargetY)
	{
		m_vDir.y = m_vPrevDir.y;
		if (m_fTargetY - m_tInfo.vPos.y <= 20)
		{
			m_fTargetY = -WINCY / 2;
		//	m_vPrevDir.x = (rand() % 10 + 1) * 0.1f;
			m_vPrevDir.y = -1.0f;
		}
	}
	else if (m_tInfo.vPos.y >= m_fTargetY)
	{
		m_vDir.y = m_vPrevDir.y;
		if (m_tInfo.vPos.y - m_fTargetY <= 20)
		{
			m_vPrevDir.y = 1.0f;
	//		m_vPrevDir.x = (rand() % 10 + 1) * 0.1f ;
			m_fTargetY = WINCY / 2;
		}
	}


	float Time = fTime * 0.001f ;
	
	m_vDir.Normalize();
	m_tInfo.vPos += m_vDir * ( m_fSpeed * Time) ;

}

bool Object::CollisionCheck(float x, float y, int size , float damage)
{
	RECT	rcMyRect;
	RECT	rcYouRect;
	rcMyRect.left = (long)(m_tInfo.vPos.x - m_tInfo.size / 2);
	rcMyRect.top = (long)(m_tInfo.vPos.y - m_tInfo.size / 2);
	rcMyRect.right = (long)(m_tInfo.vPos.x + m_tInfo.size / 2);
	rcMyRect.bottom = (long)(m_tInfo.vPos.y + m_tInfo.size / 2);


	rcYouRect.left = (long)(x - size / 2);
	rcYouRect.top = (long)(y - size / 2);
	rcYouRect.right = (long)(x + size / 2);
	rcYouRect.bottom = (long)(y + size / 2);

	
	RECT rc;
	if (IntersectRect(&rc, &rcMyRect, &rcYouRect))
	{	
		m_fLife -= damage;
		m_IsCollision = true;
		return true;
	}

	return false;
}