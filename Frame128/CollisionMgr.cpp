#include "stdafx.h"
#include "CollisionMgr.h"
#include "ScrollMgr.h"
#include "Potato.h"
#include "Bullet.h"
#include "SPlayer.h"
#include "Onion.h"
#include "CarrotBullet.h"
#include "Carrot.h"
#include "Dice.h"
#include "Flower.h"
#include "Venes.h"

int CCollisionMgr::Stage01Hit = 0;

int CCollisionMgr::Stage02Hit = 0;

int CCollisionMgr::Stage03Hit = 0;


CCollisionMgr::CCollisionMgr()
{
}


CCollisionMgr::~CCollisionMgr()
{
}

void CCollisionMgr::Collision_RectEx(list<CObj*> Dest, list<CObj*> Sour)
{
	RECT	rc{};

	for (auto& DestIter : Dest)
	{
		for (auto& SourIter : Sour)
		{
			float	fX = 0.f, fY = 0.f;

			if (Check_Rect(DestIter, SourIter, &fX, &fY))
			{
				// 가로 > 세로
				// 상하 충돌
				if (fX > fY)
				{
					// 상 충돌
						// 충돌 대상						플레이어
					if (DestIter->Get_Info().fY > SourIter->Get_Info().fY)
					{
						SourIter->Set_Y(-fY);
						
					}
						

					// 하 충돌
					else
					{
						SourIter->Set_Y(fY);
						
					}
						
				}

				// 좌우 충돌
				else
				{
					// 좌 충돌
					if (DestIter->Get_Info().fX > SourIter->Get_Info().fX)
					{
						SourIter->Set_X(-fX);
						
					}
						
					// 우 충돌
					else
					{
						SourIter->Set_X(fX);
						
					}
						
				}
			}
		}
	}
}

void CCollisionMgr::Collision_Rect_Potato(list<CObj*> Dest, list<CObj*> Sour)
{
	RECT	rc{};

	for (auto& DestIter : Dest)
	{
		for (auto& SourIter : Sour)
		{
			if (IntersectRect(&rc, &(DestIter->Get_ImageRect()), &(SourIter->Get_Rect())))
			{
				//dead상태가 아닐때만 충돌하게만듬.
				if (!dynamic_cast<CPotato*>(DestIter)->Get_Death())
				{
					
					dynamic_cast<CBullet*>(SourIter)->Set_Death();
					DestIter->Set_Hp(SourIter->Get_iAttck());
					
				}

				if (0 >= (DestIter)->Get_Hp())
				{
					dynamic_cast<CPotato*>(DestIter)->Set_State(dynamic_cast<CPotato*>(DestIter)->Get_State());
					dynamic_cast<CPotato*>(DestIter)->Set_Death();

				}
				++Stage01Hit;
			}
		}
	}
}

void CCollisionMgr::Collision_Rect_Carrot(list<CObj*> Dest, list<CObj*> Sour)
{
	RECT	rc{};

	for (auto& DestIter : Dest)
	{
		for (auto& SourIter : Sour)
		{
			if (IntersectRect(&rc, &(DestIter->Get_Rect()), &(SourIter->Get_Rect())))
			{
				//dead상태가 아닐때만 충돌하게만듬.
				if (!dynamic_cast<CCarrot*>(DestIter)->Get_Death())
				{
					dynamic_cast<CBullet*>(SourIter)->Set_Death();
					DestIter->Set_Hp(SourIter->Get_iAttck());
					
				}

				if (0 >= (DestIter)->Get_Hp())
				{
					//dynamic_cast<CCarrot*>(DestIter)->Set_State(dynamic_cast<CCarrot*>(DestIter)->Get_State());
					dynamic_cast<CCarrot*>(DestIter)->Set_Death();

				}
				++Stage01Hit;
			}
		}
	}
}

void CCollisionMgr::Collision_Rect_Onion(list<CObj*> Dest, list<CObj*> Sour)
{
	RECT	rc{};

	for (auto& DestIter : Dest)
	{
		for (auto& SourIter : Sour)
		{
			if (IntersectRect(&rc, &(DestIter->Get_ImageRect()), &(SourIter->Get_Rect())))
			{
				if (!dynamic_cast<COnion*>(DestIter)->Get_Death())
				{
					dynamic_cast<CBullet*>(SourIter)->Set_Death();
					DestIter->Set_Hp(SourIter->Get_iAttck());
					
				}

				if (0 >= (DestIter)->Get_Hp())
				{
					//dynamic_cast<COnion*>(DestIter)->Set_State(dynamic_cast<COnion*>(DestIter)->Get_State());
					dynamic_cast<COnion*>(DestIter)->Set_Death();

				}
				++Stage01Hit;
			}
		}
	}
}

void CCollisionMgr::Collision_Rect_Ball(list<CObj*> Dest, list<CObj*> Sour)
{
}

void CCollisionMgr::Collision_Rect_Dice(list<CObj*> Dest, list<CObj*> Sour)
{
	RECT	rc{};

	for (auto& DestIter : Dest)
	{
		for (auto& SourIter : Sour)
		{
			if (IntersectRect(&rc, &(DestIter->Get_Rect()), &(SourIter->Get_Rect())))
			{
				if (!dynamic_cast<CDice*>(DestIter)->Get_Death())
				{
					dynamic_cast<CBullet*>(SourIter)->Set_Death();
					DestIter->Set_Hp(SourIter->Get_iAttck());
					
				}

				if (0 >= (DestIter)->Get_Hp())
				{
					dynamic_cast<CDice*>(DestIter)->Set_State(dynamic_cast<CDice*>(DestIter)->Get_State());
					dynamic_cast<CDice*>(DestIter)->Set_Death();

				}
				++Stage02Hit;
			}
		}
	}
}

void CCollisionMgr::Collision_Rect_PBullet(list<CObj*> Dest, list<CObj*> Sour)
{
	RECT	rc{};

	for (auto& DestIter : Dest)
	{
		for (auto& SourIter : Sour)
		{
			if (IntersectRect(&rc, &(DestIter->Get_Rect()), &(SourIter->Get_ImageRect())))
			{
				DestIter->Set_Hp(SourIter->Get_iAttck());
				dynamic_cast<CSPlayer*>(DestIter)->Set_Hit();

				if (0 >= DestIter->Get_Hp())
				{


				}
			}
		}
	}
}

void CCollisionMgr::Collision_Rect_Card(list<CObj*> Dest, list<CObj*> Sour)
{
	RECT	rc{};

	for (auto& DestIter : Dest)
	{
		for (auto& SourIter : Sour)
		{
			if (IntersectRect(&rc, &(DestIter->Get_Rect()), &(SourIter->Get_Rect())))
			{
				dynamic_cast<CBullet*>(DestIter)->Set_Death();
				SourIter->Set_Dead();
				++Stage02Hit;

			}
		}
	}
}

void CCollisionMgr::Collision_Rect_CardHit(list<CObj*> Dest, list<CObj*> Sour)
{
	RECT	rc{};

	for (auto& DestIter : Dest)
	{
		for (auto& SourIter : Sour)
		{
			if (IntersectRect(&rc, &(DestIter->Get_Rect()), &(SourIter->Get_Rect())))
			{
				//DestIter->Set_Hp(SourIter->Get_iAttck());
				dynamic_cast<CSPlayer*>(DestIter)->Set_Hit();

				if (0 >= DestIter->Get_Hp())
				{


				}
			}
		}
	}
}

void CCollisionMgr::Collision_Rect_Flower(list<CObj*> Dest, list<CObj*> Sour)
{
	RECT	rc{};

	for (auto& DestIter : Dest)
	{
		for (auto& SourIter : Sour)
		{
			//bullet , flower 
			if (IntersectRect(&rc, &(DestIter->Get_Rect()), &(SourIter->Get_ImageRect())))
			{
				
					dynamic_cast<CBullet*>(DestIter)->Set_Death();
					SourIter->Set_Hp(DestIter->Get_iAttck());
					

				if (0 >= (SourIter)->Get_Hp())
				{
					/*dynamic_cast<CFlower*>(DestIter)->Set_State(dynamic_cast<CFlower*>(DestIter)->Get_State());
					dynamic_cast<CFlower*>(DestIter)->Set_Death();*/

				}
				++Stage03Hit;
			}
		}
	}
}

void CCollisionMgr::Collision_Rect_Face(list<CObj*> Dest, list<CObj*> Sour)
{
	RECT	rc{};

	for (auto& DestIter : Dest)
	{
		for (auto& SourIter : Sour)
		{
			if (IntersectRect(&rc, &(DestIter->Get_Rect()), &(SourIter->Get_Rect())))
			{
				//DestIter->Set_Hp(SourIter->Get_iAttck());
				dynamic_cast<CSPlayer*>(DestIter)->Set_Hit();

			}
		}
	}
}

void CCollisionMgr::Collision_Rect_SeedHit(list<CObj*> Dest, list<CObj*> Sour)
{
	RECT	rc{};

	for (auto& DestIter : Dest)
	{
		for (auto& SourIter : Sour)
		{
			if (IntersectRect(&rc, &(DestIter->Get_Rect()), &(SourIter->Get_ImageRect())))
			{
				//DestIter->Set_Hp(SourIter->Get_iAttck());
				dynamic_cast<CSPlayer*>(DestIter)->Set_Hit();
				//++Stage03Hit;
			}
		}
	}
}

void CCollisionMgr::Collision_Rect_Venes(list<CObj*> Dest, list<CObj*> Sour)
{
	RECT	rc{};

	for (auto& DestIter : Dest)
	{
		for (auto& SourIter : Sour)
		{
			if (IntersectRect(&rc, &(DestIter->Get_Rect()), &(SourIter->Get_Rect())))
			{
				dynamic_cast<CBullet*>(DestIter)->Set_Death();
				dynamic_cast<CVenes*>(SourIter)->Set_Death();
				//++Stage03Hit;
			}
		}
	}

}

void CCollisionMgr::Collision_Rect_BBullet(list<CObj*> Dest, list<CObj*> Sour)
{
	RECT	rc{};

	for (auto& DestIter : Dest)
	{
		for (auto& SourIter : Sour)
		{
			if (IntersectRect(&rc, &(DestIter->Get_Rect()), &(SourIter->Get_ImageRect())))
			{
				//DestIter->Set_Hp(SourIter->Get_iAttck());
				dynamic_cast<CSPlayer*>(DestIter)->Set_Hit();

			}
		}
	}
}

void CCollisionMgr::Collision_Rect_Onion_EX(list<CObj*> Dest, list<CObj*> Sour)
{
	RECT	rc{};

	for (auto& DestIter : Dest)
	{
		for (auto& SourIter : Sour)
		{
			float	fX = 0.f, fY = 0.f;

			if (Check_Rect(DestIter, SourIter, &fX, &fY))
			{
				// 가로 > 세로
				// 상하 충돌
				if (fX > fY)
				{
					// 상 충돌
					// 충돌 대상						플레이어
					if (DestIter->Get_Info().fY > SourIter->Get_Info().fY)
					{
						SourIter->Set_Y(-fY);

					}


				}

				// 좌우 충돌
				else
				{
					// 좌 충돌
					if (DestIter->Get_Info().fX > SourIter->Get_Info().fX)
					{
						SourIter->Set_X(-fX);

					}

					// 우 충돌
					else
					{
						SourIter->Set_X(fX);

					}

				}
			}
		}
	}
}

void CCollisionMgr::Collsion_Rect_CarrotBeam(list<CObj*> Dest, list<CObj*> Sour)
{
	RECT	rc{};

	for (auto& DestIter : Dest)
	{
		for (auto& SourIter : Sour)
		{
			if (IntersectRect(&rc, &(DestIter->Get_Rect()), &(SourIter->Get_Rect())))
			{
				DestIter->Set_Hp(SourIter->Get_iAttck());
				dynamic_cast<CSPlayer*>(DestIter)->Set_Hit();

				if (0 >= DestIter->Get_Hp())
				{


				}
			}
		}
	}

}

void CCollisionMgr::Collision_Rect_Coin(list<CObj*> Dest, list<CObj*> Sour)
{
	RECT	rc{};

	for (auto& DestIter : Dest)
	{
		for (auto& SourIter : Sour)
		{
			if (IntersectRect(&rc, &(DestIter->Get_Rect()), &(SourIter->Get_ImageRect())))
			{

				SourIter->Set_Dead();


			}
		}
	}
}

// void CCollisionMgr::Collision_Rect_Coin(list<CObj*> Dest, list<CObj*> Sour,list<CObj*>)
//{
//	RECT	rc{};
//
//	for (auto& DestIter : Dest)
//	{
//		for (auto& SourIter : Sour)
//		{
//			if (IntersectRect(&rc, &(DestIter->Get_Rect()), &(SourIter->Get_ImageRect())))
//			{
//				
//				SourIter->Set_Dead();
//
//
//			}
//		}
//	}
//}




void CCollisionMgr::Collision_Rect(list<CObj*> Dest, list<CObj*> Sour)
{
	RECT	rc{};

		for (auto& DestIter : Dest)
		{
			for (auto& SourIter : Sour)
			{
				if (IntersectRect(&rc, &(DestIter->Get_Rect()), &(SourIter->Get_ImageRect())))
				{
					DestIter->Set_Hp(SourIter->Get_iAttck());
					dynamic_cast<CSPlayer*>(DestIter)->Set_Hit();

					if (0 >= DestIter->Get_Hp())
					{
					
						
					}
				}
			}
		}

}

void CCollisionMgr::Collision_Rect_Hit(list<CObj*> Dest, list<CObj*> Sour)
{
	RECT	rc{};

	for (auto& DestIter : Dest)
	{
		for (auto& SourIter : Sour)
		{
			if (IntersectRect(&rc, &(DestIter->Get_Rect()), &(SourIter->Get_Rect())))
			{
				dynamic_cast<CBullet*>(DestIter)->Set_Death();
				dynamic_cast<CCarrotBullet*>(SourIter)->Set_Death();

			}
		}
	}
}
	
	


void CCollisionMgr::Collision_Sphere(list<CObj*> Dest, list<CObj*> Sour)
{
	for (auto& DestIter : Dest)
	{
		for (auto& SourIter : Sour)
		{
			if (Check_Sphere(DestIter, SourIter))
			{
				DestIter->Set_Dead();
				SourIter->Set_Dead();
			}
		}
	}
}

bool CCollisionMgr::Check_Sphere(CObj * pDest, CObj * pSour)
{
	float	fWidth  = fabs(pDest->Get_Info().fX - pSour->Get_Info().fX);
	float	fHeight = fabs(pDest->Get_Info().fY - pSour->Get_Info().fY);

	float	fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);

	float	fRadius = (pDest->Get_Info().fCX + pSour->Get_Info().fCX) * 0.5f;
	
	return fRadius > fDiagonal;
}

bool CCollisionMgr::Check_Rect(CObj * pDest, CObj * pSour, float* _pX, float* _pY)
{
	float	fWidth = fabs(pDest->Get_Info().fX - pSour->Get_Info().fX);
	float	fHeight = fabs(pDest->Get_Info().fY - pSour->Get_Info().fY);

	float	fWRadius = (pDest->Get_Info().fCX + pSour->Get_Info().fCX) * 0.5f;
	float	fHRadius = (pDest->Get_Info().fCY + pSour->Get_Info().fCY) * 0.5f;

	if (fWRadius > fWidth &&
		fHRadius > fHeight)
	{
		*_pX = fWRadius - fWidth;
		*_pY = fHRadius - fHeight;

		return true;
	}


	return false;
}
