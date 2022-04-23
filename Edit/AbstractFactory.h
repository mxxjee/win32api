#pragma once

#include "Obj.h"

template<typename T>
class CAbstractFactory
{
public:
	static CObj*		Create(void)
	{
		CObj*		pObj = new T;
		pObj->Initialize();

		return pObj;
	}

	static CObj*		Create(float _fX, float _fY, DIRECTION eDir = END)
	{
		CObj*		pObj = new T;
		pObj->Initialize();
		pObj->Set_Pos(_fX, _fY);

		if(END != eDir)
			pObj->Set_Dir(eDir);

		return pObj;
	}

	static CObj*		Create(float _fX, float _fY, float _fAngle)
	{
		CObj*		pObj = new T;
		pObj->Initialize();
		pObj->Set_Pos(_fX, _fY);
		pObj->Set_Angle(_fAngle);

		return pObj;
	}

	static CObj* Create(INFO&	m_tInfo)
	{
		CObj*	temp = new T;

		temp->Set_Pos(m_tInfo.fX, m_tInfo.fY);
		temp->Set_Size(m_tInfo.fCX, m_tInfo.fCY);
		temp->Initialize();


		return temp;
	}
public:
	CAbstractFactory()	{	}
	~CAbstractFactory() {	}
};

// �߻� ���丮 ���� : ���� ������ �� ������� �ν��Ͻ��� ����� ������ �߻�ȭ�ϴ� ����
// ��, ��ü ���� �� ���ݵǴ� �������� �۾��� �߻�ȭ ��Ų ���̴�.

// ���ͷ����� ����(�ݺ��� ����) : ���� ǥ�� ����� �������� �ʰ� �������� ���� ����� �����ϴ� ����
// ������ : ����Ǵ� �θ� ���� ������Ʈ���� �ϳ��� �����̳ʷ� ����->��Ӱ� ������ ������ ������ ���̸�, ��ü ������ ���� ������ ���Ͽ� ���Ѵ�.

