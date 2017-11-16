#pragma once
#include "Struct.h"

class Object
{
public:
	Object();
	Object(int iType , int iTeam);
	~Object();

public:
	int Update(float fTime);
	void SetInfo(OBJ_INFO& info)
	{
		m_tInfo = info; 
	}

	const OBJ_INFO& GetInfo() { return m_tInfo; }

	bool CollisionCheck(float x, float y, int size, float damage);
	void Move(float fTime);
	void SetIsColl(bool iscoll) { m_IsCollision = iscoll; }
	void SetVisible(bool Isvisible) { m_IsVisible = Isvisible; }
	bool GetIsVisible() { return m_IsVisible; }
	bool GetIsDestory() { return m_IsDestory; }
	float GetDamege() { return m_fDamage; }
	int	 GetType() { return m_iType; }
	void Initialize();


	bool GetPrevColl() { return m_PrevColl; }
	float GetLife() { return m_fLife; }
	Object* GetMe() { return m_pME; }
	void SetMe(Object* pme) { m_pME = pme; }
	GLuint GetTexture() { return m_texCharacter; }
	void SetTexture(GLuint texture) {m_texCharacter = texture;}

	int GetTeam() { return m_iTeam; }
private:
	OBJ_INFO	m_tInfo;
	float		m_fSpeed;

	float		m_fTarget;
	float		m_fTargetY;

	MYVECTOR	m_vPos;
	MYVECTOR	m_vDir;
	MYVECTOR	m_vPrevDir;
	bool		m_IsCollision;
	bool		m_IsDestory;
	float		m_fLife;


	float		m_CurR;
	float		m_CurG;
	float		m_CurB;
	float		m_fLifeTime;
	float		m_fTime;

	float		m_fDamage;
	int			m_iType;

	bool		m_PrevColl;
	float		m_fCollTime;
private:
	bool		m_IsVisible;
	Object*		m_pME;
	GLuint		m_texCharacter;

private://11��16�� �߰�
	int			m_iTeam;
};

