//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
#include "CommonClass.h"
#include "LessonX.h"
#include "../VCProject2015/VCProject2015/AdventureMode.h"
#include "../VCProject2015/VCProject2015/MenuMode.h"
#include "../VCProject2015/VCProject2015/BowlingMode.h"
#include <iostream>
#include <algorithm>
#include <thread>
#include <chrono>

#undef min
#undef max

long double 	fTimeDelta;
FILE* stream;
void init();
int PASCAL WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine,
	int       nCmdShow)
{
	init();
	if (!CSystem::InitGameEngine(hInstance, lpCmdLine)) {
		return 0;
	}
	CSystem::SetWindowTitle("PvZ");
	while (CSystem::EngineMainLoop()) {
		g_GameMain.GameMainLoop(fTimeDelta);
	};

	CSystem::ShutdownGameEngine();
	return 0;
}


/*------------------�¼��ַ�-------------------*/

// ���沶׽����ƶ���Ϣ�󣬽����õ�������
void CSystem::OnMouseMove(const float fMouseX, const float fMouseY)
{
	switch (g_GameMain.map_id)
	{
	case CGameMain::MapType::WelcomeType:
		break;
	case CGameMain::MapType::MenuType:
		Menu::OnMouseMove(fMouseX, fMouseY);
		break;
	case CGameMain::MapType::AdventureType:
		Adventure::OnMouseMove(fMouseX, fMouseY);
	case CGameMain::MapType::BowlingType:
		Bowling::OnMouseMove(fMouseX, fMouseY);
		break;
	default:
		break;
	}
}

// ���沶׽�������Ϣ�󣬽����õ�������
void CSystem::OnMouseClick(const int iMouseType, const float fMouseX, const float fMouseY)
{
	static CStaticSprite load_bar("LoadBar");
	switch (g_GameMain.map_id)
	{
	case CGameMain::MapType::WelcomeType:
		if (load_bar.IsPointInSprite(fMouseX, fMouseY)) {
			CSystem::LoadMap("menu.t2d");
			g_GameMain.map_id = CGameMain::MapType::MenuType;
		}
		break;
	case CGameMain::MapType::MenuType:
		Menu::OnMouseClick(iMouseType, fMouseX, fMouseY);
		break;
	case CGameMain::MapType::AdventureType:
		Adventure::OnMouseClick(iMouseType, fMouseX, fMouseY);
		break;
	case CGameMain::MapType::BowlingType:
		Bowling::OnMouseClick(iMouseType, fMouseX, fMouseY);
		break;
	default:
		break;
	}
}

// ���沶׽��굯����Ϣ�󣬽����õ�������
void CSystem::OnMouseUp(const int iMouseType, const float fMouseX, const float fMouseY)
{
	switch (g_GameMain.map_id)
	{
	case CGameMain::MapType::WelcomeType:
		break;
	case CGameMain::MapType::MenuType:
		Menu::OnMouseUp(iMouseType, fMouseX, fMouseY);
		break;
	case CGameMain::MapType::AdventureType:
		Adventure::OnMouseUp(iMouseType, fMouseX, fMouseY);
	case CGameMain::MapType::BowlingType:
		Bowling::OnMouseUp(iMouseType, fMouseX, fMouseY);
		break;
	default:
		break;
	}
}

// ���沶׽���̰�����Ϣ�󣬽����õ�������
void CSystem::OnKeyDown(const int iKey, const bool bAltPress, const bool bShiftPress, const bool bCtrlPress)
{
	switch (g_GameMain.map_id)
	{
	case CGameMain::MapType::WelcomeType:
		break;
	case CGameMain::MapType::MenuType:
		Menu::OnKeyDown(iKey, bAltPress, bShiftPress, bCtrlPress);
		break;
	case CGameMain::MapType::AdventureType:
		Adventure::OnKeyDown(iKey, bAltPress, bShiftPress, bCtrlPress);
	default:
		break;
	}
}

// ���沶׽���̵�����Ϣ�󣬽����õ�������
void CSystem::OnKeyUp(const int iKey)
{
	switch (g_GameMain.map_id)
	{
	case CGameMain::MapType::WelcomeType:
		break;
	case CGameMain::MapType::MenuType:
		Menu::OnKeyUp(iKey);
		break;
	case CGameMain::MapType::AdventureType:
		Adventure::OnKeyUp(iKey);
	default:
		break;
	}
}

// ���沶׽�������뾫����ײ֮�󣬵��ô˺���
void CSystem::OnSpriteColSprite(const char* szSrcName, const char* szTarName)
{
	switch (g_GameMain.map_id)
	{
	case CGameMain::MapType::WelcomeType:
		break;
	case CGameMain::MapType::MenuType:
		Menu::OnSpriteColSprite(szSrcName, szTarName);
		break;
	case CGameMain::MapType::AdventureType:
		Adventure::OnSpriteColSprite(szSrcName, szTarName);
		break;
	case CGameMain::MapType::BowlingType:
		Bowling::OnSpriteColSprite(szSrcName, szTarName);
		break;
	default:
		break;
	}
}

// ���沶׽������������߽���ײ֮�󣬵��ô˺��� iColSide : 0 ��ߣ�1 �ұߣ�2 �ϱߣ�3 �±�
void CSystem::OnSpriteColWorldLimit(const char* szName, const int iColSide)
{
	switch (g_GameMain.map_id)
	{
	case CGameMain::MapType::WelcomeType:
		break;
	case CGameMain::MapType::MenuType:
		Menu::OnSpriteColWorldLimit(szName, iColSide);
		break;
	case CGameMain::MapType::AdventureType:
		Adventure::OnSpriteColWorldLimit(szName, iColSide);
	case CGameMain::MapType::BowlingType:
		Bowling::OnSpriteColWorldLimit(szName, iColSide);
		break;
	default:
		break;
	}
}

void init() {
	//��������̨�����������Ϣ���
	AllocConsole();
	freopen_s(&stream, "CONOUT$", "a+", stdout);

	std::thread timer([&]() {
		while (true) {
			fTimeDelta += CSystem::GetTimeDelta();
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}
	});
	timer.detach();
}