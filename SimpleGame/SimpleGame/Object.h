#pragma once
#include "Struct.h"

class Object
{
public:
	Object();
	Object(int iType);
	~Object();

public:
	int Update(float fTime);
	void SetInfo(OBJ_INFO& info)
	{
		m_tInfo = info; 
	}

	const OBJ_INFO& GetInfo() { return m_tInfo; }

	bool CollisionCheck(float x, float y, int size);
	void Move(float fTime);
	void SetIsColl(bool iscoll) { m_IsCollision = iscoll; }

	bool GetIsDestory() { return m_IsDestory; }

	int	 GetType() { return m_iType; }
	void Initialize();
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
	bool		m_IsDestory;
	float		m_fLife;


	float		m_CurR;
	float		m_CurG;
	float		m_CurB;
	float		m_fLifeTime;
	float		m_fTime;
	int		m_iType;
};

