#include "stdafx.h"
#include "Object.h"


Object::Object()
{
	m_vDir.x = 1.0f;
	m_fSpeed = 0.1f;
	m_fTarget = 250.0f;
	m_fDegree = 0;
	m_IsCollision = false;
}


Object::~Object()
{
}

void Object::Update()
{
	Move();
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
void Object::Move()
{
	m_vDir.Normalize();
	if (m_tInfo.vPos.x <= m_fTarget)
	{
		m_vDir.x = 1.0f;
		if (m_fTarget - m_tInfo.vPos.x <= 20)
			m_fTarget = -250;
	}
	else if (m_tInfo.vPos.x >= m_fTarget)
	{
		m_vDir.x = -1.0f;
		if (m_tInfo.vPos.x - m_fTarget <= 20)
			m_fTarget = 250;
	}

	m_tInfo.vPos += m_vDir * m_fSpeed;
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
		m_IsCollision = true;
		return true;
	}
	
	return false;
}