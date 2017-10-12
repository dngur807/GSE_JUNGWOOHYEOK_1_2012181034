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
private:
	OBJ_INFO	m_tInfo;
	float		m_fSpeed;

	float		m_fTarget;
	MYVECTOR	m_vPos;
	MYVECTOR	m_vDir;

	float		m_fDegree;
};

