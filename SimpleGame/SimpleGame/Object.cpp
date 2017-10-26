#include "stdafx.h"
#include "Object.h"


Object::Object()
{
	m_vPrevDir.x = (rand() % 10 + 1) * 0.1f;
	m_vPrevDir.y = (rand() % 10 + 1) * 0.1f;
	m_vDir.x = (rand() % 10 + 1) * 0.1f;
	m_vDir.y = (rand() % 10 + 1) * 0.1f;
	m_fSpeed = 100;
	m_fTarget = 250.0f;
	m_fTargetY = 250.0f;
	m_fDegree = 0;

	m_fLifeTime = 10000.0f;
	m_fLife = 100.0f;
	m_IsCollision = false;
	m_IsDestory = false;

}


Object::~Object()
{
}

void Object::Update(float fTime)
{

	if (m_fLife <= 0 || m_fLifeTime <= 0)
		m_IsDestory = true;
	if (m_IsDestory == true)
		return;

	m_fLifeTime -= 0.01f;


	Move(fTime);
	if (m_IsCollision)
	{
		//»¡°£»ö
		m_tInfo.r = 1.0f;
		m_tInfo.g = 0.0f;
		m_tInfo.b = 0.0f;
		m_tInfo.a = 1.0f;
	}
	else
	{
		m_tInfo.r = 1.0f;
		m_tInfo.g = 1.0f;
		m_tInfo.b = 1.0f;
		m_tInfo.a = 1.0f;
	}
}
void Object::Move(float fTime)
{
	m_vDir.Normalize();
	if (m_tInfo.vPos.x <= m_fTarget)
	{
		m_vDir.x = m_vPrevDir.x;
		if (m_fTarget - m_tInfo.vPos.x <= 20)
		{
		//	m_vPrevDir.x = (rand() % 10 + 1) * 0.1f;
		//	m_vPrevDir.y = (rand() % 10 + 1) * 0.1f;
			m_fTarget = -250;
		}
	}
	else if (m_tInfo.vPos.x >= m_fTarget)
	{
		m_vDir.x = -m_vPrevDir.x;
		if (m_tInfo.vPos.x - m_fTargetY <= 20)
		{
			m_vPrevDir.x = (rand() % 10 + 1) * 0.1f;
			m_vPrevDir.y = (rand() % 10 + 1) * 0.1f;
			m_fTarget = 250;
		}
	}

	if (m_tInfo.vPos.y <= m_fTargetY)
	{
		m_vDir.y = m_vPrevDir.y;
		if (m_fTarget - m_tInfo.vPos.y <= 20)
		{
			m_fTargetY = -250;
			m_vPrevDir.x = (rand() % 10 + 1) * 0.1f;
			m_vPrevDir.y = (rand() % 10 + 1) * 0.1f;
		}
	}
	else if (m_tInfo.vPos.y >= m_fTargetY)
	{
		m_vDir.y = -m_vPrevDir.y;
		if (m_tInfo.vPos.y - m_fTargetY <= 20)
		{
			m_vPrevDir.x = (rand() % 10 + 1) * 0.1f;
			m_vPrevDir.y = (rand() % 10 + 1) * 0.1f;
			m_fTargetY = 250;
		}
	}

	float Time = fTime * 0.001f ;

//	cout << fTime << endl;
	
	m_tInfo.vPos += m_vDir * ( m_fSpeed * Time) ;

	//cout << m_tInfo.vPos.x << "\t" << m_tInfo.vPos .y<< endl;
}
bool Object::CollisionCheck(float x, float y, int size)
{
	RECT	rcMyRect;
	RECT	rcYouRect;
	rcMyRect.left = m_tInfo.vPos.x - m_tInfo.size / 2;
	rcMyRect.top = m_tInfo.vPos.y - m_tInfo.size / 2;
	rcMyRect.right = m_tInfo.vPos.x + m_tInfo.size / 2;
	rcMyRect.bottom = m_tInfo.vPos.y + m_tInfo.size / 2;


	rcYouRect.left = x - size / 2;
	rcYouRect.top = y - size / 2;
	rcYouRect.right = x + size / 2;
	rcYouRect.bottom = y + size / 2;

	RECT rc;
	if (IntersectRect(&rc, &rcMyRect, &rcYouRect))
	{
		m_fLife -= 0.01f;
		m_IsCollision = true;
		return true;
	}

	return false;
}