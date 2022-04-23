#include "stdafx.h"
#include "Ending.h"
#include "AbstractFactory.h"
#include "ObjMgr.h"
#include "EndingPage.h"
#include "SoundMgr.h"

CEnding::CEnding()
{
}


CEnding::~CEnding()
{
}

void CEnding::Initialize(void)
{
	//CSoundMgr::Get_Instance()->PlaySoundW(L"../Sound/²É.wav", SOUND_BGM, 1);
	CObjMgr::Get_Instance()->AddObject(OBJ_EFFECT, CAbstractFactory<CEndingPage>::Create(0.f, 0.f));

}

void CEnding::Update(void)
{
	CSoundMgr::Get_Instance()->PlaySound(L"¿£µù.wav", SOUND_BGM, 1);
	CObjMgr::Get_Instance()->Update();
}

void CEnding::Late_Update(void)
{
	CObjMgr::Get_Instance()->Late_Update();
}

void CEnding::Render(HDC hDC)
{
	CObjMgr::Get_Instance()->Render(hDC);
}

void CEnding::Release(void)
{

	CObjMgr::Get_Instance()->Delete_ID(OBJ_EFFECT);
}
