#include "stdafx.h"
#include "Object.h"


Object::Object()
{
	m_vDir.x = 1.0f;
	m_fSpeed = 0.1f;
	m_fTarget = 250.0f;
	m_fDegree = 0;


}


Object::~Object()
{
}

void Object::Update()
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

	/*m_fDegree += 1.0f;

	m_tInfo.vPos.x += cosf(m_fDegree * 3.14 / 180.0f);
	m_tInfo.vPos.y += sinf(m_fDegree * 3.14 / 180.0f);*/
}
