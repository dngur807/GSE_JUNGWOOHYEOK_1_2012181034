<<<<<<< HEAD
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

=======
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

>>>>>>> 1dbb55a808a385c2583014e7f4f3da3bd3ece7b8
