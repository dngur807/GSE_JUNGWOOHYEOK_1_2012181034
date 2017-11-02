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
	m_fTime = 0.0f;
	m_fLifeTime = 10000.0f;
	m_fLife = 100.0f;
	m_IsCollision = false;
	m_IsDestory = false;

	Initialize();

}
Object::Object(int type)
{
	m_fTime = 0.0f;
	m_vPrevDir.x = (rand() % 10 + 1) * 0.1f;
	m_vPrevDir.y = (rand() % 10 + 1) * 0.1f;
	m_vDir.x = (rand() % 10 + 1) * 0.1f;
	m_vDir.y = (rand() % 10 + 1) * 0.1f;

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

	m_fSpeed = 100;
	m_fTarget = 250.0f;
	m_fTargetY = 250.0f;
	m_fDegree = 0;

	m_fLifeTime = 10000.0f;
	m_fLife = 100.0f;
	m_IsCollision = false;
	m_IsDestory = false;

	m_iType = type;
	Initialize();
}

Object::~Object()
{
}

int Object::Update(float fTime)
{

	if (m_fLife <= 0 || m_fLifeTime <= 0)
		m_IsDestory = true;
	if (m_IsDestory == true)
		return 1 ;

	int CreateBullet = 0;//2이면 생성

	if (m_iType == OBJECT_BUILDING)
	{
		m_fTime += fTime * 0.001f;
		if (m_fTime > 0.5f)
		{
			m_fTime = 0;
			CreateBullet = 2;
		}
		//총알 0.5초마다 생성
	}
	//m_fLifeTime -= 0.01f;


	if (m_iType != OBJECT_BULLET)
		Move(fTime);
	else
	{
		float Time = fTime * 0.001f;
		m_vDir.Normalize();
		m_tInfo.vPos += m_vDir * (m_fSpeed * Time);


		if (m_tInfo.vPos.x >= 250
			|| m_tInfo.vPos.x < -250
			|| m_tInfo.vPos.y >= 250
			|| m_tInfo.vPos.y < -250
			)
		{
			m_IsDestory = true;
			return 1;
		}
	}
	if (m_IsCollision)
	{
		//빨간색
		m_tInfo.r = 1.0f;
		m_tInfo.g = 0.0f;
		m_tInfo.b = 1.0f;
		m_tInfo.a = 1.0f;
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
			//m_vPrevDir.x = (rand() % 10 + 1) * 0.1f  * -1.0f;
			//m_vPrevDir.y = (rand() % 10 + 1) * 0.1f * -1.0f;
			m_fTarget = -250;
		}
	}
	else if (m_tInfo.vPos.x >= m_fTarget)
	{
		m_vDir.x = m_vPrevDir.x;
		if (m_tInfo.vPos.x - m_fTarget <= 20)
		{
			m_vPrevDir.x = 1.0f;
			//m_vPrevDir.x = (rand() % 10 + 1) * 0.1f;
			//m_vPrevDir.y = (rand() % 10 + 1) * 0.1f;
			m_fTarget = 250;
		}
	}

	if (m_tInfo.vPos.y <= m_fTargetY)
	{
		m_vDir.y = m_vPrevDir.y;
		if (m_fTargetY - m_tInfo.vPos.y <= 20)
		{
			m_fTargetY = -250;
			m_vPrevDir.y = -1.0f;
			//m_vPrevDir.x = (rand() % 10 + 1) * 0.1f ;
			//m_vPrevDir.y = (rand() % 10 + 1) * 0.1f ;
		}
	}
	else if (m_tInfo.vPos.y >= m_fTargetY)
	{
		m_vDir.y = m_vPrevDir.y;
		if (m_tInfo.vPos.y - m_fTargetY <= 20)
		{
			m_vPrevDir.y = 1.0f;
		//	m_vPrevDir.x = (rand() % 10 + 1) * 0.1f ;
		//	m_vPrevDir.y = (rand() % 10 + 1) * 0.1f ;
			m_fTargetY = 250;
		}
	}




	

	float Time = fTime * 0.001f ;

//	cout << fTime << endl;
	
	m_vDir.Normalize();
	m_tInfo.vPos += m_vDir * ( m_fSpeed * Time) ;

	//cout << m_tInfo.vPos.x << "\t" << m_tInfo.vPos .y<< endl;
}
void Object::Initialize()
{
//#define OBJECT_BUILDING		0
//#define OBJECT_CHARACTER		1
//#define OBJECT_BULLET		2
//#define OBJECT_ARROW		3
	switch (m_iType)
	{
	case OBJECT_BUILDING:
		m_fLife = 500;
		m_fSpeed = 0;
		m_tInfo.size = 50;
		m_CurR = 1.0f;
		m_CurG = 1.0f;
		m_CurB = 0.0f;
		m_tInfo.a = 1.0f;
		break;
	case OBJECT_CHARACTER:
		m_fLife = 10;
		m_fSpeed = 300;
		m_tInfo.size = 10;
		m_tInfo.r = m_CurR = 1.0f;
		m_tInfo.g = m_CurG = 1.0f;
		m_tInfo.b = m_CurB = 1.0f;
		m_tInfo.a = 1.0f;
		break;
	case OBJECT_BULLET:
		m_fLife = 20;
		m_fSpeed = 600;
		m_tInfo.size = 4;
		m_tInfo.r = m_CurR = 1.0f;
		m_tInfo.g = m_CurG = 0.0f;
		m_tInfo.b = m_CurB = 0.0f;
		m_tInfo.a = 1.0f;
		break;
	}
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
		m_fLife -= 0.1f;
		m_IsCollision = true;
		return true;
	}

	return false;
}