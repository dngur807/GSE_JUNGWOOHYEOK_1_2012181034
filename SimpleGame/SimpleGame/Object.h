#pragma once
#include "Struct.h"

class Object
{
public:
	Object();
	~Object();

public:
	void Update();
	void SetInfo(OBJ_INFO& info)
	{
		m_tInfo = info; 
	}

	const OBJ_INFO& GetInfo() { return m_tInfo; }

	bool CollisionCheck(float x, float y, int size);
	void Move();
	void SetIsColl(bool iscoll) { m_IsCollision = iscoll; }
private:
	OBJ_INFO	m_tInfo;
	float		m_fSpeed;

	float		m_fTarget;
	float		m_fTargetY;
	MYVECTOR	m_vPos;
	MYVECTOR	m_vDir;
	MYVECTOR	m_vPrevDir;
	float		m_fDegree;
	bool		m_IsCollision;
};

